cmake_minimum_required(VERSION 3.10)
project(MyGame)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим или подключаем raylib
set(RAYLIB_VERSION "5.0")

# Опция для поиска raylib на системе или скачивания
option(USE_SYSTEM_RAYLIB "Use system-installed raylib" OFF)

if(USE_SYSTEM_RAYLIB)
    # Пытаемся найти системный raylib
    find_package(raylib REQUIRED)
else()
    # Скачиваем и собираем raylib через FetchContent
    include(FetchContent)
    
    FetchContent_Declare(
        raylib
        URL "https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz"
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    
    # Отключаем предупреждения для raylib
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(raylib)
endif()

# Добавляем исполняемый файл
add_executable(${PROJECT_NAME} 
    src/game.cpp
)

# Подключаем заголовочные файлы
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Линкуем raylib
target_link_libraries(${PROJECT_NAME} raylib)

# Для Windows: отключаем консольное окно
if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()