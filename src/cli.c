/*
 *      Copyright (C) 2000,2001,2002 Nikos Mavroyanopoulos
 *
 * This file is part of GNUTLS.
 *
 * GNUTLS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * GNUTLS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <gnutls/gnutls.h>
#include <gnutls/extra.h>
#include <sys/time.h>
#include <signal.h>
#include <netdb.h>
#include <common.h>
#include "cli-gaa.h"

#ifndef SHUT_WR
# define SHUT_WR 1
#endif

#ifndef SHUT_RDWR
# define SHUT_RDWR 2
#endif

#define SA struct sockaddr
#define ERR(err,s) if (err==-1) {perror(s);return(1);}
#define MAX_BUF 4096
#define GERR(ret) fprintf(stderr, "* Error: %s\n", gnutls_strerror(ret))

/* global stuff here */
int resume;
char *hostname = NULL;
int port;
int record_max_size;
int fingerprint;
int crlf;
int quiet = 0;

char *srp_passwd;
char *srp_username;
char *pgp_keyfile;
char *pgp_certfile;
char *pgp_keyring;
char *pgp_trustdb;
char *x509_keyfile;
char *x509_certfile;
char *x509_cafile;
char *x509_crlfile = NULL;
static int x509ctype;


int protocol_priority[16] = { GNUTLS_TLS1, GNUTLS_SSL3, 0 };
int kx_priority[16] =
    { GNUTLS_KX_RSA, GNUTLS_KX_DHE_DSS, GNUTLS_KX_DHE_RSA, GNUTLS_KX_SRP,
  /* Do not use anonymous authentication, unless you know what that means */ 
   GNUTLS_KX_ANON_DH, 0
};
int cipher_priority[16] =
    { GNUTLS_CIPHER_ARCFOUR_EXPORT, GNUTLS_CIPHER_RIJNDAEL_128_CBC, GNUTLS_CIPHER_3DES_CBC,
   GNUTLS_CIPHER_ARCFOUR, 0
};
int comp_priority[16] = { GNUTLS_COMP_ZLIB, GNUTLS_COMP_NULL, 0 };
int mac_priority[16] = { GNUTLS_MAC_SHA, GNUTLS_MAC_MD5, 0 };
int cert_type_priority[16] = { GNUTLS_CRT_X509, GNUTLS_CRT_OPENPGP, 0 };

/* end of global stuff */

#define MAX(X,Y) (X >= Y ? X : Y);
#define DEFAULT_X509_CAFILE "x509/ca.pem"
#define DEFAULT_X509_KEYFILE2 "x509/clikey-dsa.pem"
#define DEFAULT_X509_CERTFILE2 "x509/clicert-dsa.pem"

#define DEFAULT_X509_KEYFILE "x509/clikey.pem"
#define DEFAULT_X509_CERTFILE "x509/clicert.pem"

#define DEFAULT_PGP_KEYFILE "openpgp/cli_sec.asc"
#define DEFAULT_PGP_CERTFILE "openpgp/cli_pub.asc"
#define DEFAULT_PGP_KEYRING "openpgp/cli_ring.gpg"

#define DEFAULT_SRP_USERNAME "test"
#define DEFAULT_SRP_PASSWD "test"


static void gaa_parser(int argc, char **argv);

int main(int argc, char **argv)
{
   int err, ret;
   int sd, ii, i;
   struct sockaddr_in sa;
   GNUTLS_STATE state;
   char buffer[MAX_BUF + 1];
   char *session = NULL;
   char *session_id = NULL;
   int session_size, alert;
   int session_id_size;
   char *tmp_session_id;
   int tmp_session_id_size;
   fd_set rset;
   int maxfd;
   struct timeval tv;
   int user_term = 0;
   GNUTLS_SRP_CLIENT_CREDENTIALS cred;
   GNUTLS_ANON_CLIENT_CREDENTIALS anon_cred;
   GNUTLS_CERTIFICATE_CLIENT_CREDENTIALS xcred;
   struct hostent *server_host;

   gaa_parser(argc, argv);

   signal(SIGPIPE, SIG_IGN);

   if (gnutls_global_init() < 0) {
      fprintf(stderr, "global state initialization error\n");
      exit(1);
   }

   if (gnutls_global_init_extra() < 0) {
      fprintf(stderr, "global state (extra) initialization error\n");
      exit(1);
   }

   /* X509 stuff */
   if (gnutls_certificate_allocate_cred(&xcred) < 0) {
      fprintf(stderr, "Certificate allocation memory error\n");
      exit(1);
   }

   if (x509_cafile != NULL) {
      ret =
	  gnutls_certificate_set_x509_trust_file(xcred, x509_cafile,
					 x509ctype);
      if (ret < 0) {
	 fprintf(stderr, "Error setting the x509 trust file\n");
      } else {
      	 printf("Processed %d CA certificate(s).\n", ret);
      }
   }

   if (x509_certfile != NULL) {
      ret =
	  gnutls_certificate_set_x509_key_file(xcred, x509_certfile,
				       x509_keyfile, x509ctype);
      if (ret < 0) {
	 fprintf(stderr, "Error setting the x509 key files ('%s', '%s')\n",
		 x509_certfile, x509_keyfile);
      }
   }

   if (pgp_certfile != NULL) {
      ret =
	  gnutls_certificate_set_openpgp_key_file(xcred, pgp_certfile,
						  pgp_keyfile);
      if (ret < 0) {
	 fprintf(stderr, "Error setting the x509 key files ('%s', '%s')\n",
		 pgp_certfile, pgp_keyfile);
      }
   }

   if (pgp_keyring != NULL) {
      ret =
	  gnutls_certificate_set_openpgp_keyring_file(xcred, pgp_keyring);
      if (ret < 0) {
	 fprintf(stderr, "Error setting the OpenPGP keyring file\n");
      }
   }

   if (pgp_trustdb != NULL) {
      ret = gnutls_certificate_set_openpgp_trustdb(xcred, pgp_trustdb);
      if (ret < 0) {
	 fprintf(stderr, "Error setting the OpenPGP trustdb file\n");
      }
   }
/*	gnutls_certificate_client_callback_func( xcred, cert_callback); */

   /* SRP stuff */
   if (srp_username!=NULL) {
      if (gnutls_srp_allocate_client_cred(&cred) < 0) {
         fprintf(stderr, "SRP authentication error\n");
      }
      gnutls_srp_set_client_cred(cred, srp_username, srp_passwd);
   }
   
   /* ANON stuff */
   if (gnutls_anon_allocate_client_cred(&anon_cred) < 0) {
      fprintf(stderr, "Anonymous authentication error\n");
   }

   printf("Resolving '%s'...\n", hostname);
   /* get server name */
   server_host = gethostbyname(hostname);
   if (server_host == NULL) {
      fprintf(stderr, "Cannot resolve %s\n", hostname);
      exit(1);
   }

   sd = socket(AF_INET, SOCK_STREAM, 0);
   ERR(sd, "socket");

   memset(&sa, '\0', sizeof(sa));
   sa.sin_family = AF_INET;
   sa.sin_port = htons(port);

   sa.sin_addr.s_addr = *((unsigned int *) server_host->h_addr);

   inet_ntop(AF_INET, &sa.sin_addr, buffer, MAX_BUF);
   fprintf(stderr, "Connecting to '%s:%d'...\n", buffer, port);

   err = connect(sd, (SA *) & sa, sizeof(sa));
   ERR(err, "connect");

   for (i = 0; i < 2; i++) {
      gnutls_init(&state, GNUTLS_CLIENT);

      /* allow the use of private ciphersuites.
       */
      gnutls_handshake_set_private_extensions( state, 1);

      if (i == 1) {
	 gnutls_session_set_data(state, session, session_size);
	 free(session);
      }

      gnutls_cipher_set_priority(state, cipher_priority);
      gnutls_compression_set_priority(state, comp_priority);
      gnutls_kx_set_priority(state, kx_priority);
      gnutls_protocol_set_priority(state, protocol_priority);
      gnutls_mac_set_priority(state, mac_priority);
      gnutls_cert_type_set_priority(state, cert_type_priority);

      gnutls_dh_set_prime_bits(state, 1024);

      gnutls_cred_set(state, GNUTLS_CRD_ANON, anon_cred);
      if (srp_username!=NULL)
         gnutls_cred_set(state, GNUTLS_CRD_SRP, cred);
      gnutls_cred_set(state, GNUTLS_CRD_CERTIFICATE, xcred);

      /* send the fingerprint */
      if (fingerprint != 0)
	 gnutls_openpgp_send_key(state, GNUTLS_OPENPGP_KEY_FINGERPRINT);

      /* use the max record size extension */
      if (record_max_size > 0) {
	 if (gnutls_record_set_max_size(state, record_max_size) < 0) {
	    fprintf(stderr, "Cannot set the maximum record size to %d.\n",
		    record_max_size);
	    exit(1);
	 }
      }

/* This TLS extension may break old implementations.
 */
      gnutls_transport_set_ptr(state, sd);
      do {
	 ret = gnutls_handshake(state);
      } while (ret == GNUTLS_E_INTERRUPTED || ret == GNUTLS_E_AGAIN);

      if (ret < 0) {
	 if (ret == GNUTLS_E_WARNING_ALERT_RECEIVED
	     || ret == GNUTLS_E_FATAL_ALERT_RECEIVED) {
	    alert = gnutls_alert_get(state);
	    printf("*** Received alert [%d]: %s\n",
		   alert, gnutls_alert_get_name(alert));
	 }
	 fprintf(stderr, "*** Handshake has failed\n");
	 gnutls_perror(ret);
	 gnutls_deinit(state);
	 return 1;
      } else {
	 printf("- Handshake was completed\n");
	 if (gnutls_session_is_resumed( state)!=0)
	 	printf("*** This is a resumed session\n");
      }

      if (i == 1) {		/* resume */
	 /* check if we actually resumed the previous session */

	 gnutls_session_get_id(state, NULL, &tmp_session_id_size);
	 tmp_session_id = malloc(tmp_session_id_size);
	 gnutls_session_get_id(state, tmp_session_id,
			       &tmp_session_id_size);

	 if (memcmp(tmp_session_id, session_id, session_id_size) == 0) {
	    printf("- Previous session was resumed\n");
	 } else {
	    fprintf(stderr, "*** Previous session was NOT resumed\n");
	 }
	 free(tmp_session_id);
	 free(session_id);
      }



      if (resume != 0 && i == 0) {

	 gnutls_session_get_data(state, NULL, &session_size);
	 session = malloc(session_size);
	 gnutls_session_get_data(state, session, &session_size);

	 gnutls_session_get_id(state, NULL, &session_id_size);
	 session_id = malloc(session_id_size);
	 gnutls_session_get_id(state, session_id, &session_id_size);

	 /* print some information */
	 print_info(state);

	 printf("- Disconnecting\n");
	 do {
	    ret = gnutls_bye(state, GNUTLS_SHUT_RDWR);
	 } while (ret == GNUTLS_E_INTERRUPTED || ret == GNUTLS_E_AGAIN);

	 shutdown(sd, SHUT_WR);
	 close(sd);

	 gnutls_deinit(state);

	 printf
	     ("\n\n- Connecting again- trying to resume previous session\n");
	 sd = socket(AF_INET, SOCK_STREAM, 0);
	 ERR(sd, "socket");

	 err = connect(sd, (SA *) & sa, sizeof(sa));
	 ERR(err, "connect");
      } else {
	 break;
      }

   }

/* print some information */
   print_info(state);

   printf("\n- Simple Client Mode:\n\n");

   FD_ZERO(&rset);
   for (;;) {
      FD_SET(fileno(stdin), &rset);
      FD_SET(sd, &rset);

      maxfd = MAX(fileno(stdin), sd);
      tv.tv_sec = 3;
      tv.tv_usec = 0;
      select(maxfd + 1, &rset, NULL, NULL, &tv);

      if (FD_ISSET(sd, &rset)) {
	 bzero(buffer, MAX_BUF + 1);
	 do {
	    ret = gnutls_record_recv(state, buffer, MAX_BUF);
	 } while (ret == GNUTLS_E_INTERRUPTED || ret == GNUTLS_E_AGAIN);
	 /* remove new line */

	 if (gnutls_error_is_fatal(ret) == 1 || ret == 0) {
	    if (ret == 0) {
	       printf("- Peer has closed the GNUTLS connection\n");
	       break;
	    } else {
	       fprintf(stderr,
		       "*** Received corrupted data(%d) - server has terminated the connection abnormally\n",
		       ret);
	       break;
	    }
	 } else {
	    if (ret == GNUTLS_E_WARNING_ALERT_RECEIVED
		|| ret == GNUTLS_E_FATAL_ALERT_RECEIVED)
	       printf("* Received alert [%d]\n", gnutls_alert_get(state));
	    if (ret == GNUTLS_E_REHANDSHAKE) {
	       /* There is a race condition here. If application
	        * data is sent after the rehandshake request,
	        * the server thinks we ignored his request.
	        * This is a bad design of this client.
	        */
	       printf("* Received rehandshake request\n");
	       /* gnutls_alert_send( state, GNUTLS_AL_WARNING, GNUTLS_A_NO_RENEGOTIATION); */

	       do {
		  ret = gnutls_handshake(state);
	       } while (ret == GNUTLS_E_AGAIN
			|| ret == GNUTLS_E_INTERRUPTED);

	       if (ret == 0) {
		  printf("* Rehandshake was performed\n");
	       } else {
		  printf("* Rehandshake Failed [%d]\n", ret);
	       }
	    }
	    if (ret > 0) {
	       if (quiet!=0) printf("- Received[%d]: ", ret);
	       for (ii = 0; ii < ret; ii++) {
		  fputc(buffer[ii], stdout);
	       }
	       fputs("\n", stdout);
	    }
	 }
	 if (user_term != 0)
	    break;
      }

      if (FD_ISSET(fileno(stdin), &rset)) {
	 if (fgets(buffer, MAX_BUF, stdin) == NULL) {
	    do {
	       ret = gnutls_bye(state, GNUTLS_SHUT_WR);
	    } while (ret == GNUTLS_E_INTERRUPTED || ret == GNUTLS_E_AGAIN);
	    user_term = 1;
	    continue;
	 }
	 do {
	    if ( crlf != 0) {
	        char* b=strchr( buffer, '\n');
	        if (b!=NULL)
		    	strcpy( b, "\r\n");
	    }
	    	
	    ret = gnutls_record_send(state, buffer, strlen(buffer));
	 } while (ret == GNUTLS_E_AGAIN || ret == GNUTLS_E_INTERRUPTED);
	 if (ret > 0) {
	    if (quiet!=0) printf("- Sent: %d bytes\n", ret);
	 } else
	    GERR(ret);

      }
   }
   if (user_term != 0)
      do
	 ret = gnutls_bye(state, GNUTLS_SHUT_RDWR);
      while (ret == GNUTLS_E_INTERRUPTED || ret == GNUTLS_E_AGAIN);

   shutdown(sd, SHUT_RDWR);	/* no more receptions */
   close(sd);

   gnutls_deinit(state);

   if (srp_username!=NULL) 
      gnutls_srp_free_client_cred(cred);
   gnutls_certificate_free_cred(xcred);
   gnutls_anon_free_client_cred(anon_cred);

   gnutls_global_deinit();

   return 0;
}

#undef DEBUG

static gaainfo info;
void gaa_parser(int argc, char **argv)
{
   int i, j;

   if (gaa(argc, argv, &info) != -1) {
      fprintf(stderr,
	      "Error in the arguments. Use the --help or -h parameters to get more information.\n");
      exit(1);
   }

   resume = info.resume;
   port = info.port;
   record_max_size = info.record_size;
   fingerprint = info.fingerprint;

   if (info.fmtder == 0)
      x509ctype = GNUTLS_X509_FMT_PEM;
   else
      x509ctype = GNUTLS_X509_FMT_DER;

#ifdef DEBUG
   if (info.x509_certfile != NULL)
      x509_certfile = info.x509_certfile;
   else
      x509_certfile = DEFAULT_X509_CERTFILE;

   if (info.x509_keyfile != NULL)
      x509_keyfile = info.x509_keyfile;
   else
      x509_keyfile = DEFAULT_X509_KEYFILE;

   if (info.x509_cafile != NULL)
      x509_cafile = info.x509_certfile;
   else
      x509_cafile = DEFAULT_X509_CAFILE;

   if (info.pgp_certfile != NULL)
      pgp_certfile = info.pgp_certfile;
   else
      pgp_certfile = DEFAULT_PGP_CERTFILE;

   if (info.pgp_keyfile != NULL)
      pgp_keyfile = info.pgp_keyfile;
   else
      pgp_keyfile = DEFAULT_PGP_KEYFILE;

   if (info.srp_passwd != NULL)
      srp_passwd = info.srp_passwd;
   else
      srp_passwd = DEFAULT_SRP_PASSWD;

   if (info.srp_username != NULL)
      srp_username = info.srp_username;
   else
      srp_username = DEFAULT_SRP_USERNAME;
#else
      srp_username = info.srp_username;
      srp_passwd = info.srp_passwd;
      x509_cafile = info.x509_cafile;
      x509_keyfile = info.x509_keyfile;
      x509_certfile = info.x509_certfile;
      pgp_keyfile = info.pgp_keyfile;
      pgp_certfile = info.pgp_certfile;

#endif

   pgp_keyring = info.pgp_keyring;
   pgp_trustdb = info.pgp_trustdb;
   
   crlf = info.crlf;

   if (info.nrest_args == 0)
      hostname = "localhost";
   else
      hostname = info.rest_args[0];

   if (info.proto != NULL && info.nproto > 0) {
      for (j = i = 0; i < info.nproto; i++) {
	 if (strncasecmp(info.proto[i], "SSL", 3) == 0)
	    protocol_priority[j++] = GNUTLS_SSL3;
	 if (strncasecmp(info.proto[i], "TLS", 3) == 0)
	    protocol_priority[j++] = GNUTLS_TLS1;
      }
      protocol_priority[j] = 0;
   }

   if (info.ciphers != NULL && info.nciphers > 0) {
      for (j = i = 0; i < info.nciphers; i++) {
	 if (strncasecmp(info.ciphers[i], "RIJ", 3) == 0)
	    cipher_priority[j++] = GNUTLS_CIPHER_RIJNDAEL_128_CBC;
	 if (strncasecmp(info.ciphers[i], "TWO", 3) == 0)
	    cipher_priority[j++] = GNUTLS_CIPHER_TWOFISH_128_CBC;
	 if (strncasecmp(info.ciphers[i], "3DE", 3) == 0)
	    cipher_priority[j++] = GNUTLS_CIPHER_3DES_CBC;
	 if (strcasecmp(info.ciphers[i], "ARCFOUR-EXPORT") == 0)
	    cipher_priority[j++] = GNUTLS_CIPHER_ARCFOUR_EXPORT;
	 if (strcasecmp(info.ciphers[i], "ARCFOUR") == 0)
	    cipher_priority[j++] = GNUTLS_CIPHER_ARCFOUR;
	 if (strncasecmp(info.ciphers[i], "NUL", 3) == 0)
	    cipher_priority[j++] = GNUTLS_CIPHER_NULL;
      }
      cipher_priority[j] = 0;
   }

   if (info.macs != NULL && info.nmacs > 0) {
      for (j = i = 0; i < info.nmacs; i++) {
	 if (strncasecmp(info.macs[i], "MD5", 3) == 0)
	    mac_priority[j++] = GNUTLS_MAC_MD5;
	 if (strncasecmp(info.macs[i], "SHA", 3) == 0)
	    mac_priority[j++] = GNUTLS_MAC_SHA;
      }
      mac_priority[j] = 0;
   }

   if (info.ctype != NULL && info.nctype > 0) {
      for (j = i = 0; i < info.nctype; i++) {
	 if (strncasecmp(info.ctype[i], "OPE", 3) == 0)
	    cert_type_priority[j++] = GNUTLS_CRT_OPENPGP;
	 if (strncasecmp(info.ctype[i], "X", 1) == 0)
	    cert_type_priority[j++] = GNUTLS_CRT_X509;
      }
      cert_type_priority[j] = 0;
   }

   if (info.kx != NULL && info.nkx > 0) {
      for (j = i = 0; i < info.nkx; i++) {
	 if (strncasecmp(info.kx[i], "SRP", 3) == 0)
	    kx_priority[j++] = GNUTLS_KX_SRP;
	 if (strncasecmp(info.kx[i], "RSA", 3) == 0)
	    kx_priority[j++] = GNUTLS_KX_RSA;
	 if (strncasecmp(info.kx[i], "DHE_RSA", 7) == 0)
	    kx_priority[j++] = GNUTLS_KX_DHE_RSA;
	 if (strncasecmp(info.kx[i], "DHE_DSS", 7) == 0)
	    kx_priority[j++] = GNUTLS_KX_DHE_DSS;
	 if (strncasecmp(info.kx[i], "ANON", 4) == 0)
	    kx_priority[j++] = GNUTLS_KX_ANON_DH;
      }
      kx_priority[j] = 0;
   }

   if (info.comp != NULL && info.ncomp > 0) {
      for (j = i = 0; i < info.ncomp; i++) {
	 if (strncasecmp(info.comp[i], "NUL", 3) == 0)
	    comp_priority[j++] = GNUTLS_COMP_NULL;
	 if (strncasecmp(info.comp[i], "ZLI", 1) == 0)
	    comp_priority[j++] = GNUTLS_COMP_ZLIB;
      }
      comp_priority[j] = 0;
   }

}

void cli_version(void) {
	fprintf(stderr, "GNU TLS test client, ");
	fprintf(stderr, "version %s.\n", LIBGNUTLS_VERSION);
}
