message("In Utils...")
add_library(Utils STATIC)

target_include_directories(Utils PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:include>"
)

target_sources(Utils
    PRIVATE
        utils.cpp
    PUBLIC
        utils.h
)

add_subdirectory(StringUtils)
add_subdirectory(Coordinates)

install(TARGETS Utils
    EXPORT UtilsTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

message("Done!")