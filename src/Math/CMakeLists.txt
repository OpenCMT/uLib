
# HEADERS
set(HEADERS
                                ContainerBox.h
                                Dense.h
                                Geometry.h
                                Transform.h
                                StructuredData.h
                                StructuredGrid.h
                                VoxImage.h
                                VoxRaytracer.h
                                Utils.h
                                VoxImageFilter.h
                                VoxImageFilter.hpp
                                VoxImageFilterLinear.hpp
                                VoxImageFilterMedian.hpp
                                VoxImageFilterABTrim.hpp
                                VoxImageFilterBilateral.hpp
                                VoxImageFilterThreshold.hpp
                                VoxImageFilter2ndStat.hpp
                                VoxImageFilterCustom.hpp
                                Accumulator.h
                                TriangleMesh.h
                                BitCode.h
                                Structured2DGrid.h
                                Structured4DGrid.h
)


# SOURCES
set(SOURCES
                VoxRaytracer.cpp
                StructuredData.cpp
                StructuredGrid.cpp
                VoxImage.cpp
                TriangleMesh.cpp
                Dense.cpp
                Structured2DGrid.h
                Structured4DGrid.h
)

set(LIBRARIES
       ${Boost_SERIALIZATION_LIBRARY}
       ${Boost_SIGNALS_LIBRARY}
       ${Boost_PROGRAM_OPTIONS_LIBRARY}
       ${Eigen_LIBRARY}
       ${ROOT_LIBRARIES}
       ${PACKAGE_LIBPREFIX}Core
)


uLib_add_shared_library(${uLib-module})
add_subdirectory(testing)
