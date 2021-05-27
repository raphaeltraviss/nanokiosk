cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(NanoKiosk)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets Network Qml Quick QuickWidgets Bluetooth SerialPort)

qt5_add_resources(QML_qrc src/qml.qrc)
qt5_add_resources(QML_qrc src/asset.qrc)

add_executable(nanokiosk
  src/main.cpp
  src/MainWindow.cpp
  src/BluetoothServer.cpp
  src/SocketServer.cpp
  src/ConsoleListener.cpp
  ${QML_qrc}
)

# Windows: copy relavent Qt6 DLL libraries beside the executable.
add_custom_command(
    TARGET nanokiosk POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Widgets>
        $<TARGET_FILE:Qt5::Core>
        $<TARGET_FILE:Qt5::Gui>
        $<TARGET_FILE:Qt5::Network>
        $<TARGET_FILE:Qt5::Qml>
        $<TARGET_FILE:Qt5::Quick>
        $<TARGET_FILE:Qt5::Bluetooth>
        $<TARGET_FILE:Qt5::SerialPort>
        $<TARGET_FILE:Qt5::QuickWidgets>
        $<TARGET_FILE_DIR:nanokiosk>
)

target_link_libraries(nanokiosk Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Network Qt5::Quick Qt5::Qml Qt5::QuickWidgets Qt5::Bluetooth Qt5::SerialPort)
