target_sources(Utils
    PRIVATE
        Point.cpp
        Line.cpp
        Polygon.cpp
    PUBLIC
        Point.h
        Line.h
        Polygon.h
)

target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_LIST_DIR})