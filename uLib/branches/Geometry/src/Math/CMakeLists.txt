
# HEADERS
set(HEADERS
                                ContainerBox.h
                                Dense.h
                                Geometry.h
                                Transform.h
                                StructuredData.h
#                                StructuredGrid.h
                                ImageSpace.h
                                ImageMap.h
                                ImageData.h
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
)


# SOURCES
set(SOURCES
                VoxRaytracer.cpp
                StructuredData.cpp
#                StructuredGrid.cpp
                ImageSpace.cpp
                ImageMap.cpp
                ImageData.cpp
                VoxImage.cpp
                TriangleMesh.cpp
                Dense.cpp
)

set(LIBRARIES
       ${Boost_SERIALIZATION_LIBRARY}
       ${Boost_SIGNALS_LIBRARY}
       ${Boost_PROGRAM_OPTIONS_LIBRARY}
       ${Eigen_LIBRARY}
       ${ROOT_LIBRARIES}
       ${PACKAGE_LIBPREFIX}Core
       ${PACKAGE_LIBPREFIX}Math
)


uLib_add_shared_library(${uLib-module})
add_subdirectory(testing)
