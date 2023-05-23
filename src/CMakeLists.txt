cmake_minimum_required(VERSION 3.16)

project(StandaloneClusterEvent)

set (CMAKE_CXX_STANDARD 17)

add_subdirectory(ThirdParty/sockpp)

add_executable(StandaloneClusterEvent main.cpp)

target_include_directories(StandaloneClusterEvent PUBLIC ThirdParty/sockpp/include)
target_link_libraries(StandaloneClusterEvent sockpp-static)