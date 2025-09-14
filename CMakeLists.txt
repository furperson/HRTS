# Минимальная требуемая версия CMake
cmake_minimum_required(VERSION 3.14)


project(HRTS CXX) # CXX означает, что проект на C++



set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
    json 
    URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
    URL_HASH MD5=e155202b2a589137f6804724bd182f12
)
FetchContent_MakeAvailable(json)

FetchContent_Declare(
    sodium 
    GIT_REPOSITORY https://github.com/jedisct1/libsodium
)

FetchContent_MakeAvailable(sodium)

FetchContent_MakeAvailable(json)

add_subdirectory(common) 
set(BUILD_SHARED_LIBS OFF)
# Сообщаем CMake, что нужно обработать поддиректории



add_subdirectory(client)
add_subdirectory(server)

