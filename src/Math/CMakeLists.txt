
set(HEADERS ContainerBox.h
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
            Structured4DGrid.h)

set(SOURCES VoxRaytracer.cpp
            StructuredData.cpp
            StructuredGrid.cpp
            VoxImage.cpp
            TriangleMesh.cpp
            Dense.cpp
            Structured2DGrid.cpp
            Structured4DGrid.cpp)

set(LIBRARIES ${Eigen_LIBRARY}
              ${ROOT_LIBRARIES}
              ${VTK_LIBRARIES})

set(libname ${PACKAGE_LIBPREFIX}Math)
set(ULIB_SHARED_LIBRARIES ${ULIB_SHARED_LIBRARIES} ${libname} PARENT_SCOPE)
set(ULIB_SELECTED_MODULES ${ULIB_SELECTED_MODULES} Math PARENT_SCOPE)

add_library(${libname} SHARED ${SOURCES})
set_target_properties(${libname} PROPERTIES
                      VERSION ${PROJECT_VERSION}
                      SOVERSION ${PROJECT_SOVERSION})
target_link_libraries(${libname} ${LIBRARIES})


install(TARGETS ${libname}
        EXPORT "${PROJECT_NAME}Targets"
        RUNTIME DESTINATION ${PACKAGE_INSTALL_BIN_DIR} COMPONENT bin
        LIBRARY DESTINATION ${PACKAGE_INSTALL_LIB_DIR} COMPONENT lib)

install(FILES ${HEADERS} DESTINATION ${PACKAGE_INSTALL_INC_DIR}/Math)

# TESTING
# include(uLibTargetMacros)
# add_subdirectory(testing)

