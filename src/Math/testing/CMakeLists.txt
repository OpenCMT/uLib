
set(TESTS
        MathVectorTest
        GeometryTest
        ContainerBoxTest
        ImageDataTest
        VoxImageTest
        VoxRaytracerTest
        StructuredDataTest
        StructuredGridTest
        VoxImageFilterTest
        PolicyTest
        AccumulatorTest
        VoxImageCopyTest
        TriangleMeshTest
        BitCodeTest
)


uLib_add_tests(${uLib-module})
