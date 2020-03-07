cmake_minimum_required(VERSION 3.12.4)
project(cpp_rest_server)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Set standard library to libc++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# cpprestsdk
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/external/cpprestsdk/CMakeLists.txt)
    add_subdirectory(external/cpprestsdk)
endif ()

# gflags
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/external/gflags/CMakeLists.txt)
    add_subdirectory(external/gflags)
endif ()

# Header files list
set(HEADER "src/common/user_interrupt.h")

# Source files list
set(SOURCE "src/main.cc")

add_executable(${CMAKE_PROJECT_NAME} ${HEADER} ${SOURCE})

target_link_libraries(${CMAKE_PROJECT_NAME} cpprest gflags)