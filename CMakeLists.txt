cmake_minimum_required(VERSION 3.23)
project(SFMLlife)

set(CMAKE_CXX_STANDARD 20)

# path to SFML library
include_directories(C:/Users/tosha/CLionProjects/lib/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/)

# path to SFML cmake dir
set(SFML_DIR C:/Users/tosha/CLionProjects/lib/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib/cmake/SFML)

set(SFML_STATIC_LIBRARIES TRUE)


find_package(SFML 2.5.1 COMPONENTS graphics REQUIRED)

# WIN32 flag to supress console
add_executable(SFMLlife WIN32 main.cpp header.h draw.cpp)

# link SFML library
target_link_libraries(SFMLlife sfml-graphics)