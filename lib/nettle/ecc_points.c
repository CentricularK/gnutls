/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@gmail.com, http://libtom.org
 */

/* Implements ECC over Z/pZ for curve y^2 = x^3 + ax + b
 *
 * All curves taken from NIST recommendation paper of July 1999
 * Available at http://csrc.nist.gov/cryptval/dss.htm
 */
#include "ecc.h"

/**
  @file ecc_points.c
  ECC Crypto, Tom St Denis
*/

/**
   Allocate a new ECC point
   @return A newly allocated point or NULL on error 
*/
ecc_point *
ecc_new_point (void)
{
  ecc_point *p;
  p = calloc (1, sizeof (*p));
  if (p == NULL)
    {
      return NULL;
    }
  if (mp_init_multi (&p->x, &p->y, &p->z, NULL) != 0)
    {
      free (p);
      return NULL;
    }
  return p;
}

/** Free an ECC point from memory
  @param p   The point to free
*/
void
ecc_del_point (ecc_point * p)
{
  /* prevents free'ing null arguments */
  if (p != NULL)
    {
      mp_clear_multi (&p->x, &p->y, &p->z, NULL);       /* note: p->z may be NULL but that's ok with this function anyways */
      free (p);
    }
}

/* $Source: /cvs/libtom/libtomcrypt/src/pk/ecc/ecc_points.c,v $ */
/* $Revision: 1.7 $ */
/* $Date: 2007/05/12 14:32:35 $ */
