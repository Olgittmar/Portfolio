#TODO Not sure which version is required atm...
cmake_minimum_required(VERSION 3.8)
project( CPlusPlus VERSION 0.1.0)
configure_file( CPlusPlusConfig.h.in CPlusPlusConfig.h )

# c++ 11 is equally fine, I just enjoy the QoL improvements
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)
# set(CMAKE_AUTOUIC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CONAN_CMAKE_GENERATOR Ninja)
set(CMAKE_DEBUG_POSTFIX d)

if( EXISTS ${BUILD_DIR}/conanbuildinfo.cmake )
    include(${BUILD_DIR}/conanbuildinfo.cmake )
else()
    include(${BUILD_DIR}/conanbuildinfo.cmake)
endif()



conan_basic_setup()

add_executable( CPlusPlus
"main.cpp"
)

set_target_properties(CPlusPlus PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

conan_target_link_libraries( CPlusPlus )

add_subdirectory(
    "src"
    )
    
#! Not sure...
target_include_directories(CPlusPlus PUBLIC
    "${PROJECT_BINARY_DIR}"
)

if( CMAKE_BUILD_TYPE EQUAL Debug)
    install( TARGETS CPlusPlus
    CONFIGURATIONS
    Debug RUNTIME DESTINATION install/debug/bin
    )
elseif( CMAKE_BUILD_TYPE EQUAL Release)
    install( TARGETS CPlusPlus
        CONFIGURATIONS Release
            RUNTIME DESTINATION install/release/bin
            LIBRARY DESTINATION install/release/lib
    )
else()
    message("Installation folder not found!")
endif()

#TODO Add more extensive testing
enable_testing()
add_test(NAME Runs COMMAND CPlusPlus)