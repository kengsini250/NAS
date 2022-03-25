cmake_minimum_required(VERSION 3.21)

project(NAS_Server LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "E:\\Qt\\6.3.0\\msvc2019_64\\lib\\cmake")

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Network REQUIRED)

add_executable(NAS_Server
  main.cpp
  server.h server.cpp
  client_thread.h client_thread.cpp
  Status.h
  client.h client.cpp
  dir.h dir.cpp
  user.h user.cpp)
target_link_libraries(NAS_Server 
Qt::Core 
Qt::Network
)
