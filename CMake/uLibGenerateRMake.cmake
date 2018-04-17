

include(uLibMacros)
include(uLibDebugMacro)

## MAKE REMOTE -------------------------------------------------------------- ##

#set(BUILD_REMOTE_MACHINES "10.62.19.4" CACHE STRING "remote build in cloud machine")
#set(BUILD_REMOTE_USER "rigoni" CACHE STRING "remote build user")
#set(BUILD_REMOTE_CMD "${SSH_COMMAND} ${BUILD_REMOTE_USER}@${BUILD_REMOTE_MACHINES} \"make -C \"")
#add_custom_target(cloud COMMAND ${SSH_COMMAND})



set(REMOTE_BUILD_USER "$ENV{USER}" CACHE STRING "ssh remote build user name")

execute_process(COMMAND hostname -I OUTPUT_VARIABLE HOSTNAME_IP)
set(REMOTE_BUILD_MACHINES ${HOSTNAME_IP} CACHE STRING "ssh remote build machines")

find_file(SSH_EXECUTABLE ssh PATHS /bin/local/bin /usr/bin /bin)
set(REMOTE_BUILD_SSHBIN ${SSH_EXECUTABLE} CACHE FILEPATH "ssh remote build command path")
set(REMOTE_BUILD_SSHPORT 22 CACHE STRING "ssh remote build port")

find_file(MAKE_EXECUTABLE make PATHS /usr/local/bin /usr/bin /bin)
set(REMOTE_BUILD_MAKEBIN ${MAKE_EXECUTABLE} CACHE FILEPATH "ssh remote build make path")
set(REMOTE_BUILD_BULIDIR ${PROJECT_BINARY_DIR} CACHE PATH "ssh remote build build path")
set(REMOTE_BUILD_SRCDIR ${PROJECT_SOURCE_DIR} CACHE PATH "ssh remote build source path")

message("remote build ----------------------------------------------------------")
debug(REMOTE_BUILD_USER)
debug(REMOTE_BUILD_MACHINES)
debug(REMOTE_BUILD_SSHBIN)
debug(REMOTE_BUILD_SSHPORT)
debug(REMOTE_BUILD_MAKEBIN)
message("-----------------------------------------------------------------------")


find_file(RMAKE_IN_FILE rmake.in PATHS ${CMAKE_MODULE_PATH})
configure_file(
  "${RMAKE_IN_FILE}"
  "${PROJECT_BINARY_DIR}/CMake/rmake" @ONLY
)

file(COPY "${PROJECT_BINARY_DIR}/CMake/rmake"
  DESTINATION "${PROJECT_BINARY_DIR}"
  FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ
  GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
