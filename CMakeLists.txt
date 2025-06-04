# Минимальная требуемая версия CMake
cmake_minimum_required(VERSION 3.14)


project(HRTS CXX) # CXX означает, что проект на C++


set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Сообщаем CMake, что нужно обработать поддиректории
add_subdirectory(client)
add_subdirectory(server)

