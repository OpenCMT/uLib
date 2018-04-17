SUBDIRS = .

include $(top_srcdir)/Common.am

library_includedir = $(includedir)/libmutom-${PACKAGE_VERSION}/Math
library_include_HEADERS = 	ContainerBox.h	\
				Dense.h 	\
				Geometry.h	\
				Transform.h     \
				StructuredData.h\
				StructuredGrid.h\
				VoxImage.h	\
				VoxRaytracer.h  \
				Utils.h		\
				VoxImageFilter.h\
				VoxImageFilter.hpp \
				VoxImageFilterLinear.hpp \
				VoxImageFilterMedian.hpp \
				VoxImageFilterABTrim.hpp \
				VoxImageFilterBilateral.hpp \
				VoxImageFilterThreshold.hpp \
				VoxImageFilter2ndStat.hpp \
				VoxImageFilterCustom.hpp \
                                Accumulator.h \
				TriangleMesh.h


_MATH_SOURCES = \
                VoxRaytracer.cpp   \
                StructuredData.cpp \
                StructuredGrid.cpp \
                VoxImage.cpp       \
                TriangleMesh.cpp   \
		Dense.cpp




noinst_LTLIBRARIES = libmutommath.la
libmutommath_la_SOURCES = ${_MATH_SOURCES}


