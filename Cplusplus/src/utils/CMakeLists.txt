add_library(Utils STATIC
    utils.h
    utils.cpp
)

add_subdirectory(
    StringUtils
    Coordinates
)

# Following along with cmake tutorial here, trying to figure out how things work
# The intent is for solutions to only need something like "#include <Polygon.h>"
target_include_directories(Utils PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:include>"
)

install(TARGETS Utils
    EXPORT UtilsTargets
    CONFIGURATIONS Debug
    LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/install/debug/lib
    ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/install/debug/lib
    RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/install/debug/bin
    INCLUDES DESTINATION ${PROJECT_BINARY_DIR}/install/debug/include
)

install(TARGETS Utils
    EXPORT UtilsTargets
    CONFIGURATIONS Release
    LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/install/release/lib
    ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/install/release/lib
    RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/install/release/bin
    INCLUDES DESTINATION ${PROJECT_BINARY_DIR}/install/release/include
)