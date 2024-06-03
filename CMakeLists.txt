cmake_minimum_required(VERSION 3.22)

project(sqlite-cpp)

find_package(SQLite3 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${SQLite3_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SQLite3_LIBRARIES})
