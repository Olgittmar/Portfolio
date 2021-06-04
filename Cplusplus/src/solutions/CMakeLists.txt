message(STATUS "Generating Solutions...")
add_library(Solutions STATIC)
add_dependencies(Solutions Utils)

target_include_directories(Solutions PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_INSTALL_PREFIX}/include
)

target_link_directories(Solutions
    PRIVATE ${CMAKE_INSTALL_PREFIX}/lib
)

target_link_libraries(Solutions
    CPlusPlus::Utils
)


target_sources(Solutions
    PUBLIC
        PointInPolygon.h
    PRIVATE
        PointInPolygon.cpp
)

install(TARGETS Solutions
    EXPORT SolutionsTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)
add_library(CPlusPlus::Solutions ALIAS Solutions)

message(STATUS "Finished generating Solutions!")