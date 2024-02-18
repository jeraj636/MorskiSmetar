cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
project(MorskiSmetar)

add_subdirectory(lib/HenigmaEngine)

add_executable(${PROJECT_NAME}
src/main.cpp
src/zacetna.cpp
src/level.cpp
src/vegovec.cpp
src/tocke.cpp
src/crnc.cpp
src/smece.cpp
src/greta.cpp
src/jasek.cpp
src/jud.cpp
src/cekin.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
lib/HenigmaEngine/include
lib/CelicniAvtomat
lib/asio/include
)

target_link_libraries(${PROJECT_NAME}
HenigmaEngine
)