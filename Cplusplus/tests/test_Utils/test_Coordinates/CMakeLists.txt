message(STATUS "Generating tests for Coordinates component...")

add_executable(testPointExe test_Point.cpp)
add_test(NAME test_point COMMAND testPointExe)
target_link_libraries(testPointExe
  PUBLIC
    Qt6::Test
  PRIVATE
    CPlusPlus::Utils
)

add_executable(testLineExe test_Line.cpp)
add_test(NAME test_line COMMAND testLineExe)
target_link_libraries(testLineExe
  PUBLIC
    Qt6::Test
  PRIVATE
    CPlusPlus::Utils
)

add_executable(testPolygonExe test_Polygon.cpp)
add_test(NAME test_polygon COMMAND testPolygonExe)
target_link_libraries(testPolygonExe
  PUBLIC
    Qt6::Test
  PRIVATE
    CPlusPlus::Utils
)

message(STATUS "Finished generating tests for Coordinates.")