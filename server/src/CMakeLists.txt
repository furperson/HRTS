file(GLOB_RECURSE APP_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"

)

add_executable(HRTS ${APP_SOURCES})


target_include_directories(HRTS
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "${CMAKE_CURRENT_SOURCE_DIR}/software"
        "${CMAKE_CURRENT_SOURCE_DIR}/hardware"
)

target_link_libraries(HRTS
    PRIVATE
        common_tasks   # Из ../common
        common_mylibs    # Из ../common
        nlohmann_json::nlohmann_json
)