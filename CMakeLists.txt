cmake_minimum_required(VERSION 3.10)
project(OSINTSystem)

set(CMAKE_CXX_STANDARD 11)

# Find CURL
find_package(CURL REQUIRED)
if(CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    message(STATUS "Found CURL: ${CURL_LIBRARIES}")
else()
    message(FATAL_ERROR "Could NOT find CURL")
endif()

# Find SQLite3
find_package(SQLite3 REQUIRED)
include_directories(${SQLite3_INCLUDE_DIRS})

# Find jsoncpp
find_package(jsoncpp REQUIRED)
include_directories(${jsoncpp_INCLUDE_DIRS})

# Add path to jsoncpp headers
include_directories(/usr/include/jsoncpp)

# Add path to inih headers
include_directories(${CMAKE_SOURCE_DIR}/external/inih/cpp)

# Add path to your project's include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the inih directory as a subdirectory
add_subdirectory(external/inih)

# Create a single target
add_executable(OSINTAlertSystem main.cpp src/alert_system.cpp 
src/osint_system.cpp src/utils.cpp src/config.cpp
src/alert_api.cpp src/notification.cpp)

# Link libraries
target_link_libraries(OSINTAlertSystem ${CURL_LIBRARIES} ${SQLite3_LIBRARIES} jsoncpp inih)
