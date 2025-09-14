cmake_minimum_required(VERSION 3.14)
project(HRTS_Client LANGUAGES CXX)
include(FetchContent)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

FetchContent_Declare(json 
URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
