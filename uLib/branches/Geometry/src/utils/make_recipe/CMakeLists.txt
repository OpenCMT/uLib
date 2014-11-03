set(HEADERS
)

SET(SOURCES
)


## Build target tar file ##
set(CMAKE_TAR_FILE "recipe.tar.gz")
add_custom_command(OUTPUT recipe_tar_data.o
    COMMAND tar -zcvf ${CMAKE_TAR_FILE} -C "${CMAKE_CURRENT_SOURCE_DIR}/src" CMakeLists.txt main.cpp -C ${PROJECT_SOURCE_DIR} CMakeConfig.in.h
    ## -C ${PROJECT_SOURCE_DIR} CMake
    COMMAND objcopy --input binary  --output elf64-x86-64 --binary-architecture i386 ${CMAKE_TAR_FILE} ${CMAKE_CURRENT_BINARY_DIR}/recipe_tar_data.o
)

add_library(recipe_tar_data STATIC recipe_tar_data.o)
set_source_files_properties(recipe_tar_data.o PROPERTIES EXTERNAL_OBJECT true GENERATED true)
set_target_properties(recipe_tar_data PROPERTIES LINKER_LANGUAGE C)


set(CMAKE_TAR_FILE "cmake.tar.gz")
add_custom_command(OUTPUT cmake_tar_data.o
    COMMAND tar -zcvf ${CMAKE_TAR_FILE} -C ${PROJECT_SOURCE_DIR} CMake "--exclude=CMake/.svn"
    COMMAND objcopy --input binary  --output elf64-x86-64 --binary-architecture i386 ${CMAKE_TAR_FILE} ${CMAKE_CURRENT_BINARY_DIR}/cmake_tar_data.o
)

add_library(cmake_tar_data STATIC cmake_tar_data.o)
set_source_files_properties(cmake_tar_data.o PROPERTIES EXTERNAL_OBJECT true GENERATED true)
set_target_properties(cmake_tar_data PROPERTIES LINKER_LANGUAGE C)



uLib_add_target(uLib_config main.cpp)
target_link_libraries(uLib_config cmake_tar_data)
target_link_libraries(uLib_config recipe_tar_data)
target_link_libraries(uLib_config ${PACKAGE_LIBPREFIX}Core)

