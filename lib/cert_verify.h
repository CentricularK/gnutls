int gnutls_verify_certificate(gnutls_cert * certificate_list,
    int clist_size, gnutls_cert * trusted_cas, int tcas_size, void *CRLs,
			      int crls_size, char* cn);
time_t _gnutls_utcTime2gtime(char *ttime);
time_t _gnutls_generalTime2gtime(char *ttime);
