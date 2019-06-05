# Target for RPMs creation

set(PKGREL 1 CACHE STRING "Package build number")
set(ITEMS_FOR_SOURCE AUTHORS
                     CMakeConfig.in.h
                     CMakePkgConfig.pc.in
                     test.cpp
                     uLibConfig.cmake.in
                     uLib.creator
                     ulib.h
                     vtk_test.cpp
                     CMake
                     CMakeLists.txt
                     Jenkinsfile
                     src
                     uLib.config
                     uLibConfigVersion.cmake.in
                     uLib.files
                     uLib.includes)

add_custom_target(rpm
                  COMMAND mkdir -p ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/BUILD
                                   ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/RPMS
                                   ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/SOURCES
                                   ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/SPECS
                                   ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/SRPMS
                  COMMAND tar -zcf ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/SOURCES/cmt-ulib-${PACKAGE_VERSION}.tar.gz ${ITEMS_FOR_SOURCE}
                  COMMAND sed -e 's|@PKGVERSION@|${PACKAGE_VERSION}|g'
                              -e 's|@PKGRELEASE@|${PKGREL}|g'
                              CMake/cmt-ulib.spec.in > ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/SPECS/cmt-ulib.spec
                  COMMAND QA_SKIP_BUILD_ROOT=1 rpmbuild -ba --define '_topdir ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild'
                          ${CMAKE_CURRENT_BINARY_DIR}/rpmbuild/SPECS/cmt-ulib.spec
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

