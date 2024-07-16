cmake_minimum_required(VERSION 3.10)
project(OSINTSystem)

set(CMAKE_CXX_STANDARD 11)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

find_package(SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})

find_package(jsoncpp REQUIRED)
include_directories(${jsoncpp_INCLUDE_DIRS})

add_executable(OSINTSystem main.cpp src/alert_system.cpp src/osint_system.cpp)

target_link_libraries(OSINTSystem ${CURL_LIBRARIES} ${SQLite3_LIBRARIES} jsoncpp)

