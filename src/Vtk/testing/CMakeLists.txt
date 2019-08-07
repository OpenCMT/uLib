# TESTS
set( TESTS
        vtkViewerTest
        vtkContainerBoxTest
        vtkMuonScatter
        vtkStructuredGridTest
        vtkVoxRaytracerTest
        vtkVoxImageTest
#	vtkTriangleMeshTest
)

set(LIBRARIES
       ${PACKAGE_LIBPREFIX}Core
       ${PACKAGE_LIBPREFIX}Vtk
)

include(${VTK_USE_FILE})
uLib_add_tests(${uLib-module})
