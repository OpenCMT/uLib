
include $(top_srcdir)/Common.am

#AM_DEFAULT_SOURCE_EXT = .cpp

# if HAVE_CHECK
TESTS = MathVectorTest  	\
	GeometryTest		\
	ContainerBoxTest	\
	VoxImageTest   		\
	VoxRaytracerTest	\
	StructuredDataTest	\
	VoxImageFilterTest	\
	PolicyTest		\
	AccumulatorTest		\
	VoxImageCopyTest	\
	TriangleMeshTest

# else
# TEST =
# endif

LDADD = $(top_srcdir)/libmutom-${PACKAGE_VERSION}.la $(AM_LIBS_ALL)

all: ${TESTS}

check_PROGRAMS = $(TESTS)

