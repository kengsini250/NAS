cmake_minimum_required(VERSION 3.14)

project(NAS_Client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network REQUIRED)

add_executable(NAS_Server
    pic.qrc
    main.cpp
    mainwindow.h mainwindow.cpp
    mainwindow.ui
    client.h client.cpp
    downloadwidget.h downloadwidget.cpp
    FileFormat.h FileFormat.cpp
    listwidgetui.h listwidgetui.cpp
    presenter.h presenter.cpp

    setting/setting.h setting/setting.cpp
    setting/setting.ui

    newuser/newuser.h newuser/newuser.cpp
    newuser/newuser.ui

    http/downloadqueue.h http/downloadqueue.cpp
    http/downloadqueue.ui
    http/http.cpp http/HTTP.h
    http/httpdownload.h http/httpdownload.cpp
    )
target_link_libraries(NAS_Server Qt${QT_VERSION_MAJOR}::Core  Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)
