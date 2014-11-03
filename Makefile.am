if ENABLE_VTK
VTK_SUBDIR = src/Vtk
VTK_CONLIB = src/Vtk/libconvtk.la
endif

SUBDIRS = src $(VTK_SUBDIR) .

ACLOCAL_AMFLAGS = -I m4

include Common.am

if ENABLE_VTK
include src/Vtk/Vtk.am
endif


_uLib_SOURCES =

library_includedir = $(includedir)/libmutom-${PACKAGE_VERSION}/
library_include_HEADERS = config.h \
                          ulib.h


bin_PROGRAMS = test
test_LDADD = libmutom-${PACKAGE_VERSION}.la $(AM_LIBS_BOOST) $(AM_LIBS_ROOT)

if ENABLE_VTK
bin_PROGRAMS += vtk_test
vtk_test_LDADD = libmutom-${PACKAGE_VERSION}.la $(AM_LIBS_BOOST) $(AM_LIBS_ROOT)
endif


##PACKAGE_MAJOR=@PACKAGE_MAJOR@
##PACKAGE_MINOR=@PACKAGE_MINOR@

LIBRARY_VERSION = 1:0:0

CONLIBS = src/Core/libmutomcore.la \
          src/Root/libmutomroot.la \
          src/Math/libmutommath.la \
          src/Detectors/libmutomdetectors.la


lib_LTLIBRARIES = libmutom-0.2.la
libmutom_0_2_la_SOURCES = ${_uLib_SOURCES}
libmutom_0_2_la_LDFLAGS = -version-info $(LIBRARY_VERSION)
libmutom_0_2_la_LIBADD  = $(AM_LIBS_ALL) ${CONLIBS} ${VTK_CONLIB}
###libmutom_0_2_la_LDFLAGS = -release $(PACKAGE_VERSION) -version-info $(LIBRARY_VERSION)

pkgconfigdir   = $(libdir)/pkgconfig
pkgconfig_DATA = libmutom-${PACKAGE_VERSION}.pc

