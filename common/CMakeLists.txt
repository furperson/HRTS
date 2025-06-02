cmake_minimum_required(VERSION 3.10) 
project(CommonLibraries CXX)

set(CMAKE_CXX_STANDARD 23)

file(GLOB TASK_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/tasks/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tasks/*.hpp"
)
add_library(common_tasks STATIC ${TASK_SOURCES}) 


target_include_directories(common_tasks
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/tasks" 
)

target_link_libraries(common_tasks
    PUBLIC
        nlohmann_json::nlohmann_json 
)

file(GLOB MYLIBS_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/mylibs/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mylibs/*.hpp"
)
add_library(common_mylibs STATIC ${MYLIBS_SOURCES})

target_include_directories(common_mylibs
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/mylibs" 
)

target_link_libraries(common_mylibs
    PUBLIC
        nlohmann_json::nlohmann_json 
)