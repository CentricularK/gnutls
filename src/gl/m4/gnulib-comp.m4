# DO NOT EDIT! GENERATED AUTOMATICALLY!
# Copyright (C) 2002-2014 Free Software Foundation, Inc.
#
# This file is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This file is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this file.  If not, see <http://www.gnu.org/licenses/>.
#
# As a special exception to the GNU General Public License,
# this file may be distributed as part of a program that
# contains a configuration script generated by Autoconf, under
# the same distribution terms as the rest of that program.
#
# Generated by gnulib-tool.
#
# This file represents the compiled summary of the specification in
# gnulib-cache.m4. It lists the computed macro invocations that need
# to be invoked from configure.ac.
# In projects that use version control, this file can be treated like
# other built files.


# This macro should be invoked from ./configure.ac, in the section
# "Checks for programs", right after AC_PROG_CC, and certainly before
# any checks for libraries, header files, types and library functions.
AC_DEFUN([ggl_EARLY],
[
  m4_pattern_forbid([^gl_[A-Z]])dnl the gnulib macro namespace
  m4_pattern_allow([^gl_ES$])dnl a valid locale name
  m4_pattern_allow([^gl_LIBOBJS$])dnl a variable
  m4_pattern_allow([^gl_LTLIBOBJS$])dnl a variable
  AC_REQUIRE([gl_PROG_AR_RANLIB])
  # Code from module absolute-header:
  # Code from module alloca-opt:
  # Code from module c-ctype:
  # Code from module clock-time:
  # Code from module environ:
  # Code from module errno:
  # Code from module error:
  # Code from module exitfail:
  # Code from module extensions:
  AC_REQUIRE([gl_USE_SYSTEM_EXTENSIONS])
  # Code from module extern-inline:
  # Code from module gettext-h:
  # Code from module gettime:
  # Code from module gettimeofday:
  # Code from module include_next:
  # Code from module intprops:
  # Code from module malloca:
  # Code from module mktime:
  # Code from module msvc-inval:
  # Code from module msvc-nothrow:
  # Code from module multiarch:
  # Code from module parse-datetime:
  # Code from module progname:
  # Code from module setenv:
  # Code from module snippet/_Noreturn:
  # Code from module snippet/arg-nonnull:
  # Code from module snippet/c++defs:
  # Code from module snippet/warn-on-use:
  # Code from module ssize_t:
  # Code from module stdbool:
  # Code from module stddef:
  # Code from module stdint:
  # Code from module stdio:
  # Code from module stdlib:
  # Code from module strerror:
  # Code from module strerror-override:
  # Code from module string:
  # Code from module sys_time:
  # Code from module sys_types:
  # Code from module time:
  # Code from module time_r:
  # Code from module timespec:
  # Code from module unistd:
  # Code from module unsetenv:
  # Code from module verify:
  # Code from module xalloc:
  # Code from module xalloc-die:
  # Code from module xalloc-oversized:
])

# This macro should be invoked from ./configure.ac, in the section
# "Check for header files, types and library functions".
AC_DEFUN([ggl_INIT],
[
  AM_CONDITIONAL([GL_COND_LIBTOOL], [true])
  gl_cond_libtool=true
  gl_m4_base='src/gl/m4'
  m4_pushdef([AC_LIBOBJ], m4_defn([ggl_LIBOBJ]))
  m4_pushdef([AC_REPLACE_FUNCS], m4_defn([ggl_REPLACE_FUNCS]))
  m4_pushdef([AC_LIBSOURCES], m4_defn([ggl_LIBSOURCES]))
  m4_pushdef([ggl_LIBSOURCES_LIST], [])
  m4_pushdef([ggl_LIBSOURCES_DIR], [])
  gl_COMMON
  gl_source_base='src/gl'
  gl_FUNC_ALLOCA
  gl_CLOCK_TIME
  gl_ENVIRON
  gl_UNISTD_MODULE_INDICATOR([environ])
  gl_HEADER_ERRNO_H
  gl_ERROR
  if test $ac_cv_lib_error_at_line = no; then
    AC_LIBOBJ([error])
    gl_PREREQ_ERROR
  fi
  m4_ifdef([AM_XGETTEXT_OPTION],
    [AM_][XGETTEXT_OPTION([--flag=error:3:c-format])
     AM_][XGETTEXT_OPTION([--flag=error_at_line:5:c-format])])
  AC_REQUIRE([gl_EXTERN_INLINE])
  AC_SUBST([LIBINTL])
  AC_SUBST([LTLIBINTL])
  gl_GETTIME
  gl_FUNC_GETTIMEOFDAY
  if test $HAVE_GETTIMEOFDAY = 0 || test $REPLACE_GETTIMEOFDAY = 1; then
    AC_LIBOBJ([gettimeofday])
    gl_PREREQ_GETTIMEOFDAY
  fi
  gl_SYS_TIME_MODULE_INDICATOR([gettimeofday])
  gl_MALLOCA
  gl_FUNC_MKTIME
  if test $REPLACE_MKTIME = 1; then
    AC_LIBOBJ([mktime])
    gl_PREREQ_MKTIME
  fi
  gl_TIME_MODULE_INDICATOR([mktime])
  gl_MSVC_INVAL
  if test $HAVE_MSVC_INVALID_PARAMETER_HANDLER = 1; then
    AC_LIBOBJ([msvc-inval])
  fi
  gl_MSVC_NOTHROW
  if test $HAVE_MSVC_INVALID_PARAMETER_HANDLER = 1; then
    AC_LIBOBJ([msvc-nothrow])
  fi
  gl_MULTIARCH
  gl_PARSE_DATETIME
  AC_CHECK_DECLS([program_invocation_name], [], [], [#include <errno.h>])
  AC_CHECK_DECLS([program_invocation_short_name], [], [], [#include <errno.h>])
  gl_FUNC_SETENV
  if test $HAVE_SETENV = 0 || test $REPLACE_SETENV = 1; then
    AC_LIBOBJ([setenv])
  fi
  gl_STDLIB_MODULE_INDICATOR([setenv])
  gt_TYPE_SSIZE_T
  AM_STDBOOL_H
  gl_STDDEF_H
  gl_STDINT_H
  gl_STDIO_H
  gl_STDLIB_H
  gl_FUNC_STRERROR
  if test $REPLACE_STRERROR = 1; then
    AC_LIBOBJ([strerror])
  fi
  gl_MODULE_INDICATOR([strerror])
  gl_STRING_MODULE_INDICATOR([strerror])
  AC_REQUIRE([gl_HEADER_ERRNO_H])
  AC_REQUIRE([gl_FUNC_STRERROR_0])
  if test -n "$ERRNO_H" || test $REPLACE_STRERROR_0 = 1; then
    AC_LIBOBJ([strerror-override])
    gl_PREREQ_SYS_H_WINSOCK2
  fi
  gl_HEADER_STRING_H
  gl_HEADER_SYS_TIME_H
  AC_PROG_MKDIR_P
  gl_SYS_TYPES_H
  AC_PROG_MKDIR_P
  gl_HEADER_TIME_H
  gl_TIME_R
  if test $HAVE_LOCALTIME_R = 0 || test $REPLACE_LOCALTIME_R = 1; then
    AC_LIBOBJ([time_r])
    gl_PREREQ_TIME_R
  fi
  gl_TIME_MODULE_INDICATOR([time_r])
  gl_TIMESPEC
  gl_UNISTD_H
  gl_FUNC_UNSETENV
  if test $HAVE_UNSETENV = 0 || test $REPLACE_UNSETENV = 1; then
    AC_LIBOBJ([unsetenv])
    gl_PREREQ_UNSETENV
  fi
  gl_STDLIB_MODULE_INDICATOR([unsetenv])
  gl_XALLOC
  # End of code from modules
  m4_ifval(ggl_LIBSOURCES_LIST, [
    m4_syscmd([test ! -d ]m4_defn([ggl_LIBSOURCES_DIR])[ ||
      for gl_file in ]ggl_LIBSOURCES_LIST[ ; do
        if test ! -r ]m4_defn([ggl_LIBSOURCES_DIR])[/$gl_file ; then
          echo "missing file ]m4_defn([ggl_LIBSOURCES_DIR])[/$gl_file" >&2
          exit 1
        fi
      done])dnl
      m4_if(m4_sysval, [0], [],
        [AC_FATAL([expected source file, required through AC_LIBSOURCES, not found])])
  ])
  m4_popdef([ggl_LIBSOURCES_DIR])
  m4_popdef([ggl_LIBSOURCES_LIST])
  m4_popdef([AC_LIBSOURCES])
  m4_popdef([AC_REPLACE_FUNCS])
  m4_popdef([AC_LIBOBJ])
  AC_CONFIG_COMMANDS_PRE([
    ggl_libobjs=
    ggl_ltlibobjs=
    if test -n "$ggl_LIBOBJS"; then
      # Remove the extension.
      sed_drop_objext='s/\.o$//;s/\.obj$//'
      for i in `for i in $ggl_LIBOBJS; do echo "$i"; done | sed -e "$sed_drop_objext" | sort | uniq`; do
        ggl_libobjs="$ggl_libobjs $i.$ac_objext"
        ggl_ltlibobjs="$ggl_ltlibobjs $i.lo"
      done
    fi
    AC_SUBST([ggl_LIBOBJS], [$ggl_libobjs])
    AC_SUBST([ggl_LTLIBOBJS], [$ggl_ltlibobjs])
  ])
  gltests_libdeps=
  gltests_ltlibdeps=
  m4_pushdef([AC_LIBOBJ], m4_defn([ggltests_LIBOBJ]))
  m4_pushdef([AC_REPLACE_FUNCS], m4_defn([ggltests_REPLACE_FUNCS]))
  m4_pushdef([AC_LIBSOURCES], m4_defn([ggltests_LIBSOURCES]))
  m4_pushdef([ggltests_LIBSOURCES_LIST], [])
  m4_pushdef([ggltests_LIBSOURCES_DIR], [])
  gl_COMMON
  gl_source_base='tests'
changequote(,)dnl
  ggltests_WITNESS=IN_`echo "${PACKAGE-$PACKAGE_TARNAME}" | LC_ALL=C tr abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ | LC_ALL=C sed -e 's/[^A-Z0-9_]/_/g'`_GNULIB_TESTS
changequote([, ])dnl
  AC_SUBST([ggltests_WITNESS])
  gl_module_indicator_condition=$ggltests_WITNESS
  m4_pushdef([gl_MODULE_INDICATOR_CONDITION], [$gl_module_indicator_condition])
  m4_popdef([gl_MODULE_INDICATOR_CONDITION])
  m4_ifval(ggltests_LIBSOURCES_LIST, [
    m4_syscmd([test ! -d ]m4_defn([ggltests_LIBSOURCES_DIR])[ ||
      for gl_file in ]ggltests_LIBSOURCES_LIST[ ; do
        if test ! -r ]m4_defn([ggltests_LIBSOURCES_DIR])[/$gl_file ; then
          echo "missing file ]m4_defn([ggltests_LIBSOURCES_DIR])[/$gl_file" >&2
          exit 1
        fi
      done])dnl
      m4_if(m4_sysval, [0], [],
        [AC_FATAL([expected source file, required through AC_LIBSOURCES, not found])])
  ])
  m4_popdef([ggltests_LIBSOURCES_DIR])
  m4_popdef([ggltests_LIBSOURCES_LIST])
  m4_popdef([AC_LIBSOURCES])
  m4_popdef([AC_REPLACE_FUNCS])
  m4_popdef([AC_LIBOBJ])
  AC_CONFIG_COMMANDS_PRE([
    ggltests_libobjs=
    ggltests_ltlibobjs=
    if test -n "$ggltests_LIBOBJS"; then
      # Remove the extension.
      sed_drop_objext='s/\.o$//;s/\.obj$//'
      for i in `for i in $ggltests_LIBOBJS; do echo "$i"; done | sed -e "$sed_drop_objext" | sort | uniq`; do
        ggltests_libobjs="$ggltests_libobjs $i.$ac_objext"
        ggltests_ltlibobjs="$ggltests_ltlibobjs $i.lo"
      done
    fi
    AC_SUBST([ggltests_LIBOBJS], [$ggltests_libobjs])
    AC_SUBST([ggltests_LTLIBOBJS], [$ggltests_ltlibobjs])
  ])
])

# Like AC_LIBOBJ, except that the module name goes
# into ggl_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([ggl_LIBOBJ], [
  AS_LITERAL_IF([$1], [ggl_LIBSOURCES([$1.c])])dnl
  ggl_LIBOBJS="$ggl_LIBOBJS $1.$ac_objext"
])

# Like AC_REPLACE_FUNCS, except that the module name goes
# into ggl_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([ggl_REPLACE_FUNCS], [
  m4_foreach_w([gl_NAME], [$1], [AC_LIBSOURCES(gl_NAME[.c])])dnl
  AC_CHECK_FUNCS([$1], , [ggl_LIBOBJ($ac_func)])
])

# Like AC_LIBSOURCES, except the directory where the source file is
# expected is derived from the gnulib-tool parameterization,
# and alloca is special cased (for the alloca-opt module).
# We could also entirely rely on EXTRA_lib..._SOURCES.
AC_DEFUN([ggl_LIBSOURCES], [
  m4_foreach([_gl_NAME], [$1], [
    m4_if(_gl_NAME, [alloca.c], [], [
      m4_define([ggl_LIBSOURCES_DIR], [src/gl])
      m4_append([ggl_LIBSOURCES_LIST], _gl_NAME, [ ])
    ])
  ])
])

# Like AC_LIBOBJ, except that the module name goes
# into ggltests_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([ggltests_LIBOBJ], [
  AS_LITERAL_IF([$1], [ggltests_LIBSOURCES([$1.c])])dnl
  ggltests_LIBOBJS="$ggltests_LIBOBJS $1.$ac_objext"
])

# Like AC_REPLACE_FUNCS, except that the module name goes
# into ggltests_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([ggltests_REPLACE_FUNCS], [
  m4_foreach_w([gl_NAME], [$1], [AC_LIBSOURCES(gl_NAME[.c])])dnl
  AC_CHECK_FUNCS([$1], , [ggltests_LIBOBJ($ac_func)])
])

# Like AC_LIBSOURCES, except the directory where the source file is
# expected is derived from the gnulib-tool parameterization,
# and alloca is special cased (for the alloca-opt module).
# We could also entirely rely on EXTRA_lib..._SOURCES.
AC_DEFUN([ggltests_LIBSOURCES], [
  m4_foreach([_gl_NAME], [$1], [
    m4_if(_gl_NAME, [alloca.c], [], [
      m4_define([ggltests_LIBSOURCES_DIR], [tests])
      m4_append([ggltests_LIBSOURCES_LIST], _gl_NAME, [ ])
    ])
  ])
])

# This macro records the list of files which have been installed by
# gnulib-tool and may be removed by future gnulib-tool invocations.
AC_DEFUN([ggl_FILE_LIST], [
  build-aux/snippet/_Noreturn.h
  build-aux/snippet/arg-nonnull.h
  build-aux/snippet/c++defs.h
  build-aux/snippet/warn-on-use.h
  doc/parse-datetime.texi
  lib/alloca.in.h
  lib/c-ctype.c
  lib/c-ctype.h
  lib/errno.in.h
  lib/error.c
  lib/error.h
  lib/exitfail.c
  lib/exitfail.h
  lib/gettext.h
  lib/gettime.c
  lib/gettimeofday.c
  lib/intprops.h
  lib/malloca.c
  lib/malloca.h
  lib/malloca.valgrind
  lib/mktime-internal.h
  lib/mktime.c
  lib/msvc-inval.c
  lib/msvc-inval.h
  lib/msvc-nothrow.c
  lib/msvc-nothrow.h
  lib/parse-datetime.h
  lib/parse-datetime.y
  lib/progname.c
  lib/progname.h
  lib/setenv.c
  lib/stdbool.in.h
  lib/stddef.in.h
  lib/stdint.in.h
  lib/stdio.in.h
  lib/stdlib.in.h
  lib/strerror-override.c
  lib/strerror-override.h
  lib/strerror.c
  lib/string.in.h
  lib/sys_time.in.h
  lib/sys_types.in.h
  lib/time.in.h
  lib/time_r.c
  lib/timespec.c
  lib/timespec.h
  lib/unistd.c
  lib/unistd.in.h
  lib/unsetenv.c
  lib/verify.h
  lib/xalloc-die.c
  lib/xalloc-oversized.h
  lib/xalloc.h
  lib/xmalloc.c
  m4/00gnulib.m4
  m4/absolute-header.m4
  m4/alloca.m4
  m4/bison.m4
  m4/clock_time.m4
  m4/eealloc.m4
  m4/environ.m4
  m4/errno_h.m4
  m4/error.m4
  m4/extensions.m4
  m4/extern-inline.m4
  m4/gettime.m4
  m4/gettimeofday.m4
  m4/gnulib-common.m4
  m4/include_next.m4
  m4/longlong.m4
  m4/malloca.m4
  m4/mktime.m4
  m4/msvc-inval.m4
  m4/msvc-nothrow.m4
  m4/multiarch.m4
  m4/off_t.m4
  m4/parse-datetime.m4
  m4/setenv.m4
  m4/ssize_t.m4
  m4/stdbool.m4
  m4/stddef_h.m4
  m4/stdint.m4
  m4/stdio_h.m4
  m4/stdlib_h.m4
  m4/strerror.m4
  m4/string_h.m4
  m4/sys_socket_h.m4
  m4/sys_time_h.m4
  m4/sys_types_h.m4
  m4/time_h.m4
  m4/time_r.m4
  m4/timespec.m4
  m4/tm_gmtoff.m4
  m4/unistd_h.m4
  m4/warn-on-use.m4
  m4/wchar_t.m4
  m4/xalloc.m4
])
