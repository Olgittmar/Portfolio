# --------------------------------------------------------------------------------------
# This is a project created with the intent to figure out the kinks and particularies of
# CMake, Conan, Ninja, Clang and C++ in general.
# I want to keep the source, build and installation files separate, mostly to make it easier
# for me to keep track of, as such the structure of the project might seem wierd regarding
# best practices when it comes to cmake.
# 
# -project
#   CMakeLists.txt
#   main.cpp
#   -conan
#       just conan-related files
#   -src : The project source code
#       -solutions : This is where specific applications go
#       -other_source_code : Anything that is needed for the solutions, such as Utils, non solutions pecific classes etc.
#   -build : Build folder where the makefiles and such are generated
#       -debug
#       -release
#   -install : Install folder where the executable and required libraries go.
#       -debug
#       -release
#
# You might see comments that starts with "TODO", "!", "?" or similar,
# this is because VScode has a neat way of keeping track of issues and todo-lists through comments.
# --------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.8)
project(CPlusPlus VERSION 0.1.0)
configure_file(CPlusPlusConfig.h.in CPlusPlusConfig.h)

# c++ 11 is equally fine, I just enjoy discovering the QoL improvements
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CONAN_CMAKE_GENERATOR Ninja)
set(CMAKE_DEBUG_POSTFIX d)
# Haven't used a sanitizer before, might be fun to try...
set(SANITIZER ${CONAN_SETTINGS_COMPILER_SANITIZER})

# CMAKE_BUILD_TYPE is apparently compiler dependent, and should never be used in if statements
#TODO Found a more elegant way to structure using generator expressions, but one thing at a time.
include( ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake )

conan_basic_setup()

#TODO Figure out more extensively how sanitizers are used
if(SANITIZER)
    if(SANITIZER MATCHES "(Address)")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    endif()
endif()

add_executable(CPlusPlus
    "main.cpp"
)

add_subdirectory(
    src
)

set_target_properties(CPlusPlus PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
conan_target_link_libraries( CPlusPlus )
target_include_directories(CPlusPlus PUBLIC
    "${PROJECT_BINARY_DIR}"
)

target_link_libraries(CPlusPlus
    Utils
)

#! This is not a very portable way of doing things, need to rework...
install(TARGETS CPlusPlus
    CONFIGURATIONS Debug
    RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/install/debug/bin
    LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/install/debug/lib
)
install(TARGETS CPlusPlus
    CONFIGURATIONS Release
    RUNTIME DESTINATION ${PROJECT_BINARY_DIR}/install/release/bin
    LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/install/release/lib
)

#TODO Add more extensive testing
enable_testing()
add_test(NAME Runs COMMAND CPlusPlus)