dnl config.m4 for extension jieba

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use 'with':

dnl PHP_ARG_WITH([jieba],
dnl   [for jieba support],
dnl   [AS_HELP_STRING([--with-jieba],
dnl     [Include jieba support])])

dnl Otherwise use 'enable':

PHP_ARG_ENABLE([jieba],
  [whether to enable jieba support],
  [AS_HELP_STRING([--enable-jieba],
    [Enable jieba support])],
  [no])

PHP_ADD_INCLUDE(include)
PHP_ADD_INCLUDE(lib)
PHP_ADD_LIBRARY_WITH_PATH(jieba, ./, JIEBA_SHARED_LIBADD)
PHP_SUBST(JIEBA_SHARED_LIBADD)
PHP_EVAL_LIBLINE($LIBFOO_LIBS, JIEBA_SHARED_LIBADD)

if test "$PHP_JIEBA" != "no"; then
  dnl Write more examples of tests here...

  dnl Remove this code block if the library does not support pkg-config.
  dnl PKG_CHECK_MODULES([LIBFOO], [foo])
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBS, JIEBA_SHARED_LIBADD)

  dnl If you need to check for a particular library version using PKG_CHECK_MODULES,
  dnl you can use comparison operators. For example:
  dnl PKG_CHECK_MODULES([LIBFOO], [foo >= 1.2.3])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo < 3.4])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo = 1.2.3])

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-jieba -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/jieba.h"  # you most likely want to change this
  dnl if test -r $PHP_JIEBA/$SEARCH_FOR; then # path given as parameter
  dnl   JIEBA_DIR=$PHP_JIEBA
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for jieba files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       JIEBA_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$JIEBA_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the jieba distribution])
  dnl fi

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-jieba -> add include path
  dnl PHP_ADD_INCLUDE($JIEBA_DIR/include)

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-jieba -> check for lib and symbol presence
  dnl LIBNAME=JIEBA # you may want to change this
  dnl LIBSYMBOL=JIEBA # you most likely want to change this

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   AC_DEFINE(HAVE_JIEBA_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your jieba library.])
  dnl ], [
  dnl   $LIBFOO_LIBS
  dnl ])

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are not using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $JIEBA_DIR/$PHP_LIBDIR, JIEBA_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_JIEBA_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your jieba library.])
  dnl ],[
  dnl   -L$JIEBA_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(JIEBA_SHARED_LIBADD)

  dnl In case of no dependencies
  AC_DEFINE(HAVE_JIEBA, 1, [ Have jieba support ])

  PHP_NEW_EXTENSION(jieba, jieba.c, $ext_shared)
fi
