dnl $Id$
dnl config.m4 for extension qp

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(qp, for qp support,
dnl Make sure that the comment is aligned:
dnl [  --with-qp             Include qp support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(qp, whether to enable qp support,
dnl Make sure that the comment is aligned:
dnl [  --enable-qp           Enable qp support])

if test "$PHP_QP" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-qp -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/qp.h"  # you most likely want to change this
  dnl if test -r $PHP_QP/$SEARCH_FOR; then # path given as parameter
  dnl   QP_DIR=$PHP_QP
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for qp files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       QP_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$QP_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the qp distribution])
  dnl fi

  dnl # --with-qp -> add include path
  dnl PHP_ADD_INCLUDE($QP_DIR/include)

  dnl # --with-qp -> check for lib and symbol presence
  dnl LIBNAME=qp # you may want to change this
  dnl LIBSYMBOL=qp # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $QP_DIR/$PHP_LIBDIR, QP_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_QPLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong qp lib version or lib not found])
  dnl ],[
  dnl   -L$QP_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(QP_SHARED_LIBADD)

  PHP_NEW_EXTENSION(qp, qp.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
