cmake_minimum_required(VERSION 3.20)

project(MorskiSmetar)

add_subdirectory(src/HenigmaEngine)

add_executable(${PROJECT_NAME}
    ../src/test.cpp 
)

target_link_libraries(${PROJECT_NAME} 
HenigmaEngine
)