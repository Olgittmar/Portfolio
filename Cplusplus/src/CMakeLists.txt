add_subdirectory(
    utils
    solutions
)

# Since solutions are not built as libraries we need to add the directory to includes
target_include_directories(Utils PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/solutions"
)