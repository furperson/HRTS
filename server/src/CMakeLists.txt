file(GLOB_RECURSE APP_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"

)

add_executable(HRTS_Server ${APP_SOURCES})

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPQXX REQUIRED libpqxx)

target_include_directories(HRTS_Server PRIVATE ${LIBPQXX_INCLUDE_DIRS})

# 2. Указать линкеру, с какими библиотеками связываться.
target_link_libraries(HRTS_Server PRIVATE ${LIBPQXX_LIBRARIES})

target_include_directories(HRTS_Server PRIVATE
    ${CMAKE_SOURCE_DIR}/server/src/software/InnerFunction
)


target_include_directories(HRTS_Server
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "${CMAKE_CURRENT_SOURCE_DIR}/software"
        "${CMAKE_CURRENT_SOURCE_DIR}/hardware"
)

target_link_libraries(HRTS_Server
    PRIVATE
        common_tasks   # Из ../common
        common_mylibs    # Из ../common
        nlohmann_json::nlohmann_json
        sodium

        
)

add_custom_target(
        clangformat
        COMMAND clang-format
        -style=file:${CMAKE_CURRENT_SOURCE_DIR}/../.clang-format
        -i
        ${APP_SOURCES}
)