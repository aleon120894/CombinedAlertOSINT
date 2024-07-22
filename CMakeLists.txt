cmake_minimum_required(VERSION 3.10)
project(OSINTSystem)

set(CMAKE_CXX_STANDARD 11)

find_package(CURL REQUIRED)

if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    message(STATUS "Found CURL: ${CURL_LIBRARIES}")
else()
    message(FATAL_ERROR "Could NOT find CURL")
endif()

find_package(SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})

find_package(jsoncpp REQUIRED)
include_directories(${jsoncpp_INCLUDE_DIRS})

# Додайте шлях до заголовків jsoncpp
include_directories(/usr/include/jsoncpp)

# Додайте цю лінію, щоб включити директорію src
include_directories(${CMAKE_SOURCE_DIR}/src)

# Створення єдиної цілі
add_executable(OSINTAlertSystem main.cpp src/alert_system.cpp src/osint_system.cpp src/utils.cpp)  # Додайте src/utils.cpp

target_link_libraries(OSINTAlertSystem ${CURL_LIBRARIES} ${SQLite3_LIBRARIES} jsoncpp)
