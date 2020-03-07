cmake_minimum_required(VERSION 3.12.4)
project(cpp_project)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Set standard library to libc++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")

# cpprestsdk
if(EXISTS "external/cpprestsdk")
    add_subdirectory("external/cpprestsdk")
endif()

# Header files list
set(HEADER "")

# Source files list
set(SOURCE "src/main.cc")

# Libraries
set(LIBS "cpprest")

add_executable(${CMAKE_PROJECT_NAME} ${HEADER} ${SOURCE})

target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})