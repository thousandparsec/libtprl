AC_INIT([libtprl],[0.0.1],[lee@thousandparsec.net])
AC_CONFIG_SRCDIR(tprl/rlcommand.cpp)

AC_CANONICAL_TARGET([])

AM_INIT_AUTOMAKE(libtprl, 0.0.1)
AM_CONFIG_HEADER(config.h)

AM_MAINTAINER_MODE

CXXFLAGS="-g -Wall"


AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

AC_LANG_CPLUSPLUS
AC_REQUIRE_CPP

AC_HEADER_STDC



#AC_CHECK_LIB(pthread, pthread_create,,AC_MSG_ERROR(libtprl requires pthread library))
#check headers, functions, etc


#checking for readline
READLINE_LIBS=

AC_CHECK_LIB(termcap,tgetent,
    [READLINE_LIBS="$READLINE_LIBS -ltermcap"],
    AC_CHECK_LIB(ncurses, tgetent,
        [READLINE_LIBS="$READLINE_LIBS -lncurses"],
        AC_MSG_ERROR([Cannot find tgetent in termcap or ncurses libraries!])
    )
)

AC_CHECK_HEADERS(termios.h unistd.h signal.h)
AC_CHECK_LIB(readline,readline,
    [
        AC_DEFINE(HAVE_LIBREADLINE, 1, true if we have libreadline)
        READLINE_LIBS="$READLINE_LIBS -lreadline"
    ],
    [
        AC_MSG_ERROR([Cannot find readline!])
    ],[ $READLINE_LIBS ]
)


AC_CONFIG_FILES([
libtprl.pc
Makefile
tprl/Makefile
]) 

AC_OUTPUT
