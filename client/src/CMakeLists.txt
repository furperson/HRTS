file(GLOB_RECURSE APP_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"

)

# 1. Находим пакет Qt6 и его компонент Widgets (который включает Core и Gui)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# 2. Включаем "магию" Qt для автоматической обработки
set(CMAKE_AUTOMOC ON)   # Для компиляции сигналов и слотов (moc)
set(CMAKE_AUTORCC ON)   # Для файлов ресурсов .qrc (иконки, картинки)
set(CMAKE_AUTOUIC ON)   # Для файлов интерфейса .ui из Qt Designer

# --- Конец секции Qt ---

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

# --- Новая цель: ваше GUI-приложение ---
add_executable(my_gui_app
)

# Линкуем GUI-приложение с библиотеками Qt и вашей логикой
target_link_libraries(my_gui_app PRIVATE
    Qt6::Widgets      # Библиотека Qt
)

add_custom_target(
        clangformat_client
        COMMAND clang-format
        -style=file:${CMAKE_CURRENT_SOURCE_DIR}/../../.clang-format
        -i
        ${APP_SOURCES}
)