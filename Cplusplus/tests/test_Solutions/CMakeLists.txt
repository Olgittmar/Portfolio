message(STATUS "Generating tests for Solutions library...")

add_executable(testPointInPolygonExe test_PointInPolygon.cpp)
add_test(NAME test_point_in_polygon COMMAND testPointInPolygonExe)
target_link_libraries(testPointInPolygonExe
  PUBLIC
    Qt6::Test
  PRIVATE
    CPlusPlus::Solutions
)

message(STATUS "Finished generating tests for Solutions lib.")