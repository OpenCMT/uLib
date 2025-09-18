
set(TESTS
        MathVectorTest
        GeometryTest
        ContainerBoxTest
        VoxImageTest
        VoxRaytracerTest
        StructuredDataTest
        VoxImageFilterTest
        PolicyTest
        AccumulatorTest
        VoxImageCopyTest
        TriangleMeshTest
        BitCodeTest
)

set(LIBRARIES
       ${PACKAGE_LIBPREFIX}Core
       ${PACKAGE_LIBPREFIX}Math
)

uLib_add_tests(Math)
