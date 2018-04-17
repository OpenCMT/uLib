
include $(top_srcdir)/Common.am
include ../Vtk.am

#AM_DEFAULT_SOURCE_EXT = .cpp

# if HAVE_CHECK
TESTS = \
        vtkViewerTest \
        vtkContainerBoxTest \
        vtkMuonScatter \
        vtkStructuredGridTest \
        vtkVoxRaytracerTest \
        vtkVoxImageTest
#	vtkTriangleMeshTest

all: $(TESTS)

LDADD = $(top_srcdir)/libmutom-${PACKAGE_VERSION}.la $(AM_LIBS_ALL)
check_PROGRAMS = $(TESTS)

