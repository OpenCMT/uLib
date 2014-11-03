
set(HEADERS
                                Archives.h
                                Array.h
                                Collection.h
                                Debug.h
                                Export.h
                                Function.h
                                Macros.h
                                Mpl.h
                                Object.h
                                ObjectProps.h
                                Options.h
                                Serializable.h
                                Signal.h
                                Singleton.h
                                SmartPointer.h
                                StaticInterface.h
                                StringReader.h
                                Types.h
                                Uuid.h
                                Vector.h
                                CommaInitializer.h
                                ProgrammableAccessor.h
)

SET(SOURCES
                Archives.cpp
                Object.cpp
                Options.cpp
                Serializable.cpp
                Signal.cpp
                Uuid.cpp
)

set(LIBRARIES
       ${Boost_SERIALIZATION_LIBRARY}
       ${Boost_SIGNALS_LIBRARY}
       ${Boost_PROGRAM_OPTIONS_LIBRARY}
       ${ROOT_LIBRARIES}
       ${PACKAGE_LIBPREFIX}Core
       ${PACKAGE_LIBPREFIX}Math
)

uLib_add_shared_library(${uLib-module})
add_subdirectory(testing)
