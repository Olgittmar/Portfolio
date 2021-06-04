message(STATUS "Generating Utils lib")
add_library(Utils STATIC)

target_include_directories(Utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_INSTALL_PREFIX}/include
)

target_sources(Utils
    PRIVATE
        utils.cpp
    PUBLIC
        utils.h
)

add_subdirectory(StringUtils)
add_subdirectory(Coordinates)
add_subdirectory(TestingUtils)

install(TARGETS Utils
    EXPORT UtilsTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

add_library(CPlusPlus::Utils ALIAS Utils)

message(STATUS "Finished generating Utils lib")