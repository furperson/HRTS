file(GLOB_RECURSE APP_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"

)

add_executable(HRTS_Client ${APP_SOURCES})


target_include_directories(HRTS_Client
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "${CMAKE_CURRENT_SOURCE_DIR}/software"
)

target_link_libraries(HRTS_Client
    PRIVATE
        common_tasks   # Из ../common
        common_mylibs    # Из ../common
        nlohmann_json::nlohmann_json
)

add_custom_target(
        clangformat_client
        COMMAND clang-format
        -style=file:${CMAKE_CURRENT_SOURCE_DIR}/../.clang-format
        -i
        ${APP_SOURCES}
)