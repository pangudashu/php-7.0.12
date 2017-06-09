dnl $Id$
dnl config.m4 for extension qin

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(qin, for qin support,
dnl Make sure that the comment is aligned:
dnl [  --with-qin             Include qin support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(qin, whether to enable qin support,
dnl Make sure that the comment is aligned:
dnl [  --enable-qin           Enable qin support])

if test "$PHP_QIN" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-qin -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/qin.h"  # you most likely want to change this
  dnl if test -r $PHP_QIN/$SEARCH_FOR; then # path given as parameter
  dnl   QIN_DIR=$PHP_QIN
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for qin files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       QIN_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$QIN_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the qin distribution])
  dnl fi

  dnl # --with-qin -> add include path
  dnl PHP_ADD_INCLUDE($QIN_DIR/include)

  dnl # --with-qin -> check for lib and symbol presence
  dnl LIBNAME=qin # you may want to change this
  dnl LIBSYMBOL=qin # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $QIN_DIR/$PHP_LIBDIR, QIN_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_QINLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong qin lib version or lib not found])
  dnl ],[
  dnl   -L$QIN_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(QIN_SHARED_LIBADD)

  PHP_NEW_EXTENSION(qin, qin.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
