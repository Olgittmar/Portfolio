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
# PROJECT
cmake_minimum_required(VERSION 3.18)
project(CPlusPlus VERSION 0.1.0)
configure_file(CPlusPlusConfig.h.in CPlusPlusConfig.h)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
conan_basic_setup(TARGETS)
# --------------------------------------------------------------------------------------
# SETTINGS
# Need compile_commands for VSCode's intellisense to play nice with Ninja
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Options
option(ENABLE_TESTING "Enable building of test" TRUE )
option(ENABLE_SANITIZER "Use compiler sanitizer" TRUE )
option(ENABLE_CPPCHECK "Enable testing with cppcheck" TRUE )
option(ENABLE_CLANG_TIDY "Enable testing with clang-tidy" TRUE )
option(DETAILED_BUILD "Verbose building" FALSE ) # Not yet implemented

# --------------------------------------------------------------------------------------
# EXTERNAL
find_package(Qt6 COMPONENTS Core Gui Widgets Test REQUIRED CONFIG)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Recount to user what we are doing
message("=========================================")
message("\t\t\tSummary")
message("=========================================")
message("Build type:       \t ${CMAKE_BUILD_TYPE}")
message("Compiler:         \t ${CMAKE_CXX_COMPILER_ID}")
message("Version:          \t ${PROJECT_VERSION}")
message("Install prefix:   \t ${CMAKE_INSTALL_PREFIX}")
message("-----------------------------------------")
message("Sanitizers:       \t ${ENABLE_SANITIZER}")
message("Testing enabled:  \t ${ENABLE_TESTING}")
message("Clang-tidy:       \t ${ENABLE_CLANG_TIDY}")
message("Cppcheck:         \t ${ENABLE_CPPCHECK}")
message("Detailed build:   \t ${DETAILED_BUILD}")
message("-----------------------------------------")

# ---------------------------------------------------------------------------
# BUILD
add_executable(CPlusPlusExe
    main.cpp
    # resources.qrc
)

set_target_properties(CPlusPlusExe
    PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
)

add_subdirectory( src )
# conan_target_link_libraries( CPlusPlusExe )
target_link_libraries(CPlusPlusExe PRIVATE
    Qt6::Core
    Qt6::Widgets
    CPlusPlus::Utils
    CPlusPlus::Solutions
    CPlusPlus::UserInterface
)

if(ENABLE_TESTING)
    enable_testing(TRUE)
    add_subdirectory(tests)
endif()


install(TARGETS CPlusPlusExe
    # EXPORT CPlusPlusTargets
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    INCLUDES DESTINATION include
    RESOURCE DESTINATION rsc
)

# Copy conan imports to installation folder, workaround for testing and installing separately
add_custom_command(TARGET CPlusPlusExe POST_BUILD
    COMMAND conan imports
    ${PROJECT_SOURCE_DIR}/conan/conanfile.py -imf
    ${CMAKE_INSTALL_PREFIX}
)

# The qt.conf file is needed by the qt conan package
add_custom_command(TARGET CPlusPlusExe POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/qt.conf
    ${CMAKE_INSTALL_PREFIX}/bin
)

# -----------------------------------------------------------------------------------------
# My formatter does not play nice with cmake code :/

if(DETAILED_BUILD)
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options("-v")
    endif()
endif()

if(ENABLE_SANITIZER)
    set(SANITIZER ${CONAN_SETTINGS_COMPILER_SANITIZER})
    if(SANITIZER)
        if(SANITIZER MATCHES "(Address)")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
        endif()
    endif()
endif()

if(ENABLE_CPPCHECK)
    find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
    if(CMAKE_CXX_CPPCHECK)
        list(APPEND CMAKE_CXX_CPPCHECK
        --enable=warning
        --library=qt
        --project=compile_commands.json
        )
    else()
        message(SEND_ERROR "cppcheck enabled but program not found")
    endif()
endif()

if(ENABLE_CLANG_TIDY)
    find_program(CLANGTIDY clang-tidy)
    if(CLANGTIDY)
        set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})
    else()
        message(SEND_ERROR "clang-tidy enabled but program not found")
    endif()
endif()