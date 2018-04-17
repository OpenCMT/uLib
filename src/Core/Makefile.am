SUBDIRS = .

include $(top_srcdir)/Common.am

library_includedir = $(includedir)/libmutom-${PACKAGE_VERSION}/Core

library_include_HEADERS = 	\
                                Archives.h \
                                Array.h \
                                Collection.h \
                                Debug.h \
                                Export.h \
                                Function.h \
                                Macros.h \
                                Mpl.h \
                                Object.h \
                                ObjectProps.h \
                                Options.h \
                                Serializable.h \
                                Signal.h \
                                Singleton.h \
                                SmartPointer.h \
                                StaticInterface.h \
                                StringReader.h \
                                Types.h \
                                Uuid.h \
                                Vector.h


_CORE_SOURCES = \
                Archives.cpp \
                Debug.cpp \
                Object.cpp \
                Options.cpp \
                Serializable.cpp \
                Signal.cpp \
		Uuid.cpp


noinst_LTLIBRARIES = libmutomcore.la
libmutomcore_la_SOURCES = ${_CORE_SOURCES}
