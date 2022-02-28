cmake_minimum_required(VERSION 3.16)

project(NAS_Client_qml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Gui Core REQUIRED)

qt_add_executable(appNAS_Client_qml
    main.cpp
    FileFormat.h FileFormat.cpp
    c_newuser.h c_newuser.cpp
    control.h control.cpp
    c_network.h c_network.cpp
    mylistmodel.h mylistmodel.cpp


    resource.qrc
)

qt_add_qml_module(appNAS_Client_qml
    URI NAS_Client_qml
    VERSION 1.0
    QML_FILES
    main.qml
    MyMenuBar.qml MyMenuBarForm.ui.qml
    NewUser.qml NewUserForm.ui.qml
    MyListView.qml	MyListViewForm.ui.qml
)

set_target_properties(appNAS_Client_qml PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(appNAS_Client_qml
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(appNAS_Client_qml
    PRIVATE Qt6::Quick Qt6::Gui Qt6::Core)
