message(STATUS "Generating UserInterface...")
add_library(UserInterface STATIC)

target_include_directories(UserInterface PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_INSTALL_PREFIX}/include
    ${CMAKE_PREFIX_PATH}
)

target_link_directories(UserInterface PUBLIC
    ${CMAKE_PREFIX_PATH}
)

target_link_libraries(UserInterface
    Qt::Core
    Qt::Widgets
)

target_sources(UserInterface
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/MyApp/MyApp.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow/MainWindow.h
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow/MainWindow.ui
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/MyApp/MyApp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow/MainWindow.cpp
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
add_library(CPlusPlus::UserInterface ALIAS UserInterface)

message(STATUS "Finished generating UserInterface!")