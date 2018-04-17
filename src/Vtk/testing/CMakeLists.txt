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

include(${VTK_USE_FILE})
uLib_add_tests(${uLib-module})
