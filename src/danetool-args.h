/*   -*- buffer-read-only: t -*- vi: set ro:
 *  
 *  DO NOT EDIT THIS FILE   (danetool-args.h)
 *  
 *  It has been AutoGen-ed  October 28, 2012 at 11:58:30 PM by AutoGen 5.16
 *  From the definitions    danetool-args.def
 *  and the template file   options
 *
 * Generated from AutoOpts 36:4:11 templates.
 *
 *  AutoOpts is a copyrighted work.  This header file is not encumbered
 *  by AutoOpts licensing, but is provided under the licensing terms chosen
 *  by the danetool author or copyright holder.  AutoOpts is
 *  licensed under the terms of the LGPL.  The redistributable library
 *  (``libopts'') is licensed under the terms of either the LGPL or, at the
 *  users discretion, the BSD license.  See the AutoOpts and/or libopts sources
 *  for details.
 *
 * The danetool program is copyrighted and licensed
 * under the following terms:
 *
 *  Copyright (C) 2000-2012 Free Software Foundation, all rights reserved.
 *  This is free software. It is licensed for use, modification and
 *  redistribution under the terms of the
 *  GNU General Public License, version 3 or later
 *      <http://gnu.org/licenses/gpl.html>
 *
 *  danetool is free software: you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  danetool is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *  See the GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License along
 *  with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
 *  This file contains the programmatic interface to the Automated
 *  Options generated for the danetool program.
 *  These macros are documented in the AutoGen info file in the
 *  "AutoOpts" chapter.  Please refer to that doc for usage help.
 */
#ifndef AUTOOPTS_DANETOOL_ARGS_H_GUARD
#define AUTOOPTS_DANETOOL_ARGS_H_GUARD 1
#include "config.h"
#include <autoopts/options.h>

/*
 *  Ensure that the library used for compiling this generated header is at
 *  least as new as the version current when the header template was released
 *  (not counting patch version increments).  Also ensure that the oldest
 *  tolerable version is at least as old as what was current when the header
 *  template was released.
 */
#define AO_TEMPLATE_VERSION 147460
#if (AO_TEMPLATE_VERSION < OPTIONS_MINIMUM_VERSION) \
 || (AO_TEMPLATE_VERSION > OPTIONS_STRUCT_VERSION)
# error option template version mismatches autoopts/options.h header
  Choke Me.
#endif

/*
 *  Enumeration of each option:
 */
typedef enum {
    INDEX_OPT_DEBUG             =  0,
    INDEX_OPT_VERBOSE           =  1,
    INDEX_OPT_INFILE            =  2,
    INDEX_OPT_OUTFILE           =  3,
    INDEX_OPT_LOAD_PUBKEY       =  4,
    INDEX_OPT_LOAD_CERTIFICATE  =  5,
    INDEX_OPT_HASH              =  6,
    INDEX_OPT_INDER             =  7,
    INDEX_OPT_INRAW             =  8,
    INDEX_OPT_TLSA_RR           =  9,
    INDEX_OPT_HOST              = 10,
    INDEX_OPT_PROTO             = 11,
    INDEX_OPT_PORT              = 12,
    INDEX_OPT_CA                = 13,
    INDEX_OPT_X509              = 14,
    INDEX_OPT_LOCAL             = 15,
    INDEX_OPT_VERSION           = 16,
    INDEX_OPT_HELP              = 17,
    INDEX_OPT_MORE_HELP         = 18
} teOptIndex;

#define OPTION_CT    19
#define DANETOOL_VERSION       "@VERSION@"
#define DANETOOL_FULL_VERSION  "danetool @VERSION@"

/*
 *  Interface defines for all options.  Replace "n" with the UPPER_CASED
 *  option name (as in the teOptIndex enumeration above).
 *  e.g. HAVE_OPT(DEBUG)
 */
#define         DESC(n) (danetoolOptions.pOptDesc[INDEX_OPT_## n])
#define     HAVE_OPT(n) (! UNUSED_OPT(& DESC(n)))
#define      OPT_ARG(n) (DESC(n).optArg.argString)
#define    STATE_OPT(n) (DESC(n).fOptState & OPTST_SET_MASK)
#define    COUNT_OPT(n) (DESC(n).optOccCt)
#define    ISSEL_OPT(n) (SELECTED_OPT(&DESC(n)))
#define ISUNUSED_OPT(n) (UNUSED_OPT(& DESC(n)))
#define  ENABLED_OPT(n) (! DISABLED_OPT(& DESC(n)))
#define  STACKCT_OPT(n) (((tArgList*)(DESC(n).optCookie))->useCt)
#define STACKLST_OPT(n) (((tArgList*)(DESC(n).optCookie))->apzArgs)
#define    CLEAR_OPT(n) STMTS( \
                DESC(n).fOptState &= OPTST_PERSISTENT_MASK;   \
                if ((DESC(n).fOptState & OPTST_INITENABLED) == 0) \
                    DESC(n).fOptState |= OPTST_DISABLED; \
                DESC(n).optCookie = NULL )

/* * * * * *
 *
 *  Enumeration of danetool exit codes
 */
typedef enum {
    DANETOOL_EXIT_SUCCESS = 0,
    DANETOOL_EXIT_FAILURE = 1,
    DANETOOL_EXIT_LIBOPTS_FAILURE = 70
} danetool_exit_code_t;
/* * * * * *
 *
 *  Interface defines for specific options.
 */
#define VALUE_OPT_DEBUG          'd'

#define OPT_VALUE_DEBUG          (DESC(DEBUG).optArg.argInt)
#define VALUE_OPT_VERBOSE        'V'
#define VALUE_OPT_INFILE         2
#define VALUE_OPT_OUTFILE        3
#define VALUE_OPT_LOAD_PUBKEY    4
#define VALUE_OPT_LOAD_CERTIFICATE 5
#define VALUE_OPT_HASH           6
#define VALUE_OPT_INDER          7
#define VALUE_OPT_INRAW          8
#define VALUE_OPT_TLSA_RR        9
#define VALUE_OPT_HOST           10
#define VALUE_OPT_PROTO          11
#define VALUE_OPT_PORT           12

#define OPT_VALUE_PORT           (DESC(PORT).optArg.argInt)
#define VALUE_OPT_CA             13
#define VALUE_OPT_X509           14
#define VALUE_OPT_LOCAL          15
#define VALUE_OPT_HELP          'h'
#define VALUE_OPT_MORE_HELP     '!'
#define VALUE_OPT_VERSION       'v'
/*
 *  Interface defines not associated with particular options
 */
#define ERRSKIP_OPTERR  STMTS(danetoolOptions.fOptSet &= ~OPTPROC_ERRSTOP)
#define ERRSTOP_OPTERR  STMTS(danetoolOptions.fOptSet |= OPTPROC_ERRSTOP)
#define RESTART_OPT(n)  STMTS( \
                danetoolOptions.curOptIdx = (n); \
                danetoolOptions.pzCurOpt  = NULL)
#define START_OPT       RESTART_OPT(1)
#define USAGE(c)        (*danetoolOptions.pUsageProc)(&danetoolOptions, c)
/* extracted from opthead.tlib near line 484 */

#ifdef  __cplusplus
extern "C" {
#endif
/*
 *  global exported definitions
 */
#include <gettext.h>


/* * * * * *
 *
 *  Declare the danetool option descriptor.
 */
extern tOptions danetoolOptions;

#if defined(ENABLE_NLS)
# ifndef _
#   include <stdio.h>
static inline char* aoGetsText(char const* pz) {
    if (pz == NULL) return NULL;
    return (char*)gettext(pz);
}
#   define _(s)  aoGetsText(s)
# endif /* _() */

# define OPT_NO_XLAT_CFG_NAMES  STMTS(danetoolOptions.fOptSet |= \
                                    OPTPROC_NXLAT_OPT_CFG;)
# define OPT_NO_XLAT_OPT_NAMES  STMTS(danetoolOptions.fOptSet |= \
                                    OPTPROC_NXLAT_OPT|OPTPROC_NXLAT_OPT_CFG;)

# define OPT_XLAT_CFG_NAMES     STMTS(danetoolOptions.fOptSet &= \
                                  ~(OPTPROC_NXLAT_OPT|OPTPROC_NXLAT_OPT_CFG);)
# define OPT_XLAT_OPT_NAMES     STMTS(danetoolOptions.fOptSet &= \
                                  ~OPTPROC_NXLAT_OPT;)

#else   /* ENABLE_NLS */
# define OPT_NO_XLAT_CFG_NAMES
# define OPT_NO_XLAT_OPT_NAMES

# define OPT_XLAT_CFG_NAMES
# define OPT_XLAT_OPT_NAMES

# ifndef _
#   define _(_s)  _s
# endif
#endif  /* ENABLE_NLS */

#ifdef  __cplusplus
}
#endif
#endif /* AUTOOPTS_DANETOOL_ARGS_H_GUARD */
/* danetool-args.h ends here */
