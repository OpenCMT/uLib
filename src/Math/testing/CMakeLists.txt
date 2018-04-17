
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


uLib_add_tests(${uLib-module})
