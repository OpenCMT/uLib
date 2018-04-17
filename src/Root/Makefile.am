SUBDIRS = .

ROOTCINT = `which rootcint`

include $(top_srcdir)/Common.am

library_includedir = $(includedir)/libmutom-${PACKAGE_VERSION}/Root

library_include_HEADERS = TestTObject.h


_CORE_SOURCES = TestTObject.cpp


MutomDict.cxx: $(library_include_HEADERS) Linkdef.h
	$(ROOTCINT) -f $@ -c $(AM_CXXFLAGS) -p $^


noinst_LTLIBRARIES = libmutomroot.la
libmutomroot_la_SOURCES = MutomDict.cxx ${_CORE_SOURCES}
