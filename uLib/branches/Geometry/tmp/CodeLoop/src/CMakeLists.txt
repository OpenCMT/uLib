
set( Kit_SRCS
ManageFilename.cpp
Test.cpp
)


add_library(ManageFilename SHARED ${Kit_SRCS})

install(TARGETS ManageFilename
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static)

