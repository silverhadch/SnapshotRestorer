cmake_minimum_required(VERSION 3.5)
project(SnapshotRestorer)

set(CMAKE_CXX_STANDARD 14)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_executable(SnapshotRestorer main.cpp)
target_link_libraries(SnapshotRestorer Qt5::Widgets)

