include $(top_srcdir)/Common.am

#AM_DEFAULT_SOURCE_EXT = .cpp

# if HAVE_CHECK
TESTS = SmartPointerTest \
        SmartVectorTest	\
	VectorTest \
	ObjectFlagsTest \
	ObjectParametersTest \
        ObjectCopyTest \
	StaticInterfaceTest \
	CommaInitTest \
        DebugTTreeDumpTest \
        BoostTest \
	BoostAccumulatorTest \
	PropertiesTest \
        SignalTest \
	SerializeTest \
	SerializeDreadDiamondTest \
	DreadDiamondParameters \
	ObjectPropableTest \
	TypeIntrospectionTraversal \
        OptionsTest

# UuidTest

# else
# TEST =
# endif

LDADD = $(top_srcdir)/libmutom-${PACKAGE_VERSION}.la $(AM_LIBS_BOOST) $(AM_LIBS_ROOT)

check_PROGRAMS = $(TESTS)


all: $(TESTS)

