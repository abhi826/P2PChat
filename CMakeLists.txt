cmake_minimum_required(VERSION 3.16)
project(PeerToPeerChat VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Network Qml Quick)

add_executable(PeerToPeerChat
    src/main.cpp
    src/chatmodel.h
    src/chatmodel.cpp
    src/chatserver.h
    src/chatserver.cpp
    src/chatclient.h
    src/chatclient.cpp
)

target_link_libraries(PeerToPeerChat PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Network
    Qt6::Qml
    Qt6::Quick
)

# Expose QML files under a QML module
qt_add_qml_module(PeerToPeerChat
    URI PeerApp
    VERSION 1.0
    QML_FILES qml/Main.qml
)

# Automatically embed QML files into the binary via qt_add_qml_module
# No manual copy needed when loading from the QML module resource