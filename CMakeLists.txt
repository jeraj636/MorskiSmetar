cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

project(MorskiSmetar)

add_subdirectory(lib/HenigmaEngine)

add_executable(${PROJECT_NAME}
src/main.cpp
src/zacetna.cpp
src/level.cpp
src/vegovec.cpp
src/ladja.cpp
src/tocke.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
lib/HenigmaEngine/include
lib/CelicniAvtomat
)

target_link_libraries(${PROJECT_NAME}
HenigmaEngine
)