cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(NanoKiosk)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network Qml Quick QuickWidgets)

qt6_add_resources(QML_qrc src/qml.qrc)
qt6_add_resources(QML_qrc src/asset.qrc)

add_executable(nanokiosk src/main.cpp src/MainWindow.cpp ${QML_qrc})

# Windows: copy relavent Qt6 DLL libraries beside the executable.
add_custom_command(
    TARGET nanokiosk POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt6::Widgets>
        $<TARGET_FILE:Qt6::Core>
        $<TARGET_FILE:Qt6::Gui>
        $<TARGET_FILE:Qt6::Network>
        $<TARGET_FILE:Qt6::Qml>
        $<TARGET_FILE:Qt6::Quick>
        $<TARGET_FILE:Qt6::QuickWidgets>
        $<TARGET_FILE_DIR:nanokiosk>
)

target_link_libraries(nanokiosk Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network Qt6::Quick Qt6::Qml Qt6::QuickWidgets)
