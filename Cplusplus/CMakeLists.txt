#TODO Not sure which version is required atm...
cmake_minimum_required(VERSION 3.8)
project( CPlusPlus VERSION 0.1.0)
configure_file( CPlusPlusConfig.h.in CPlusPlusConfig.h )

# c++ 11 is equally fine, I just enjoy the QoL improvements
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# convert relative paths to absolute in target_sources()
cmake_policy(SET CMP0076 NEW)

# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CONAN_CMAKE_GENERATOR Ninja)
set(CMAKE_DEBUG_POSTFIX d)
# Might be fun to try...
set(SANITIZER ${CONAN_SETTINGS_COMPILER_SANITIZER})

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    if( EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake )
        include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake )
    else()
        message(FATAL_ERROR "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake not found.")
    endif()
elseif( CMAKE_BUILD_TYPE STREQUAL "Release" )
    if( EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake )
        include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake )
    else()
    message(FATAL_ERROR "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake not found.")
    endif()
else()
    message("Unknown build type ${CMAKE_BUILD_TYPE}")
endif()

conan_basic_setup()
if(SANITIZER)
    if(SANITIZER MATCHES "(Address)")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    endif()
endif()

add_executable( CPlusPlus
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

install( TARGETS CPlusPlus
    CONFIGURATIONS Debug
    RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/../../install/debug/bin
    LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/../../install/debug/lib
)
install( TARGETS CPlusPlus
    CONFIGURATIONS Release
    RUNTIME DESTINATION ${CMAKE_BINARY_DIR}/../../install/release/bin
    LIBRARY DESTINATION ${CMAKE_BINARY_DIR}/../../install/release/lib
)

#TODO Add more extensive testing
enable_testing()
add_test(NAME Runs COMMAND CPlusPlus)