cmake_minimum_required(VERSION 3.10)
project(MyReleaseApp)

set(CMAKE_CXX_STANDARD 17)

add_executable(xmas xmas.cpp)

if(MSVC)
    set_property(TARGET xmas PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
elseif(UNIX AND NOT APPLE)
    target_link_options(xmas PRIVATE -static-libstdc++ -static-libgcc)
endif()