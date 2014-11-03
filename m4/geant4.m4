dnl
dnl m4 macros for setting up Geant4
dnl


##
## Geant4 Config
##

AC_DEFUN([GEANT4_PATH],
[
  AC_ARG_WITH(gean4sys,
  [  --with-geant4sys        top of the GEANT4 installation directory],
    user_genat4sys=$withval,
    user_geant4sys="none")
  if test ! x"$user_geant4sys" = xnone; then
    geant4bin="$user_geant4sys/bin"
  elif test ! x"$GEANT4SYS" = x ; then
    geant4bin="$GEANT4SYS/bin"
  else
   geant4bin=$PATH
  fi
  AC_PATH_PROG(GEANT4CONF, geant4-config , no, $geant4bin)

  if test ! x"$GEANT4CONF" = "xno"; then

    # define some variables
    GEANT4CFLAGS=`$GEANT4CONF --cflags`
    GEANT4LIBS=`$GEANT4CONF --libs`
    GEANT4VERSION=`$GEANT4CONF --version`

    if test $1 ; then
     AC_MSG_CHECKING(wether GEANT4 version >= [$1])
      vers=`$GEANT4CONF --version | tr './' ' ' | awk 'BEGIN { FS = " "; } { printf "%d", ($''1 * 1000 + $''2) * 1000 + $''3;}'`
      requ=`echo $1 | tr './' ' ' | awk 'BEGIN { FS = " "; } { printf "%d", ($''1 * 1000 + $''2) * 1000 + $''3;}'`
      if test $vers -lt $requ ; then
        AC_MSG_RESULT(no)
        no_geant4="yes"
      else
        AC_MSG_RESULT(yes)
        no_genat4="no"
      fi
    fi
  else
    # otherwise, we say no_GEANT4
    no_geant4="yes"
  fi

  AC_SUBST(GEANT4CFLAGS)
  AC_SUBST(GEANT4LIBS)
  AC_SUBST(GEANT4VERSION)

  if test "x$no_geant4" = "x" ; then
    ifelse([$2], , :, [$2])
  else
    ifelse([$3], , :, [$3])
  fi
])






