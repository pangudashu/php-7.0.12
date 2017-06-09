dnl $Id$
dnl config.m4 for extension mytest

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(mytest, for mytest support,
dnl  Make sure that the comment is aligned:
dnl[  --with-mytest             Include mytest support])

dnl PHP_ARG_ENABLE(pangu, ddd-configure, [  --disable-pangu          Disable hash support], no)


dnl Otherwise use enable:

PHP_ARG_ENABLE(mytest, whether to enable mytest support,
 Make sure that the comment is aligned:
 [  --enable-mytest           Enable mytest support])


AC_ARG_ENABLE(pangu,help,[enable_pangu="$enableval"],[enable_pangu="no"])

echo "==========================="
echo $enable_pangu

if test "$PHP_MYTEST" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-mytest -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/mytest.h"  # you most likely want to change this
  dnl if test -r $PHP_MYTEST/$SEARCH_FOR; then # path given as parameter
  dnl   MYTEST_DIR=$PHP_MYTEST
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for mytest files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       MYTEST_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$MYTEST_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the mytest distribution])
  dnl fi

  dnl # --with-mytest -> add include path
  PHP_ADD_INCLUDE(/home/qinpeng/php-7.0.12/ext/mytest/user)

  dnl PHP_CHECK_LIBRARY(pthread, pthread_create_333, [], [AC_MSG_ERROR([yyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyyy])])

  dnl PHP_ADD_BUILD_DIR(/home/qinpeng/php-7.0.12/ext/mytest/user)

  dnl # --with-mytest -> check for lib and symbol presence
  dnl LIBNAME=mytest # you may want to change this
  dnl LIBSYMBOL=mytest # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $MYTEST_DIR/$PHP_LIBDIR, MYTEST_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_MYTESTLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong mytest lib version or lib not found])
  dnl ],[
  dnl   -L$MYTEST_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(MYTEST_SHARED_LIBADD)

  PHP_NEW_EXTENSION(mytest, mytest.c user/user.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
