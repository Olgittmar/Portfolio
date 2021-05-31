message("In UserInterface...")
add_library(UserInterface STATIC)

target_include_directories(UserInterface PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:include>"
)

target_link_libraries(UserInterface
    Qt5::Widgets
)

target_sources(UserInterface
    PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/MyApp/MyApp.h"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/MainWindow/MainWindow.h"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/MainWindow/MainWindow.ui"
    PRIVATE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/MyApp/MyApp.cpp"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/MainWindow/MainWindow.cpp"
)

target_include_directories(UserInterface
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/MyApp
        ${CMAKE_CURRENT_LIST_DIR}/MainWindow
)

install(TARGETS UserInterface
    EXPORT UserInterfaceTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    INCLUDES DESTINATION ${CMAKE_INSTALL_PREFIX}/include
)

message("Done!")