# Минимальная версия CMake
cmake_minimum_required(VERSION 3.14)

# Название проекта
project(The-first-try VERSION 1.0.0 LANGUAGES C CXX)

# --- 1. ПОДКЛЮЧЕНИЕ RAYLIB ---
include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)

FetchContent_MakeAvailable(raylib)

# --- 2. ПОИСК ИСХОДНЫХ ФАЙЛОВ ---
# Путь к папке с CMakeLists.txt
set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# Ищем исходники в разных возможных местах
file(GLOB SRC_FILES 
    ${PROJECT_ROOT}/*.cpp           # Файлы в папке CMakeProject1/
    ${PROJECT_ROOT}/../src/*.cpp    # Файлы в src/ (на уровень выше)
    ${PROJECT_ROOT}/../*.cpp        # Файлы в корне проекта
)

# Выводим список найденных файлов для отладки
message(STATUS "Найдены исходные файлы:")
foreach(file ${SRC_FILES})
    message(STATUS "  - ${file}")
endforeach()

# Проверяем, нашлись ли файлы
if(NOT SRC_FILES)
    message(FATAL_ERROR "Не найдено ни одного .cpp файла! Проверь пути.")
endif()

# --- 3. СОЗДАНИЕ ИСПОЛНЯЕМОГО ФАЙЛА ---
add_executable(${PROJECT_NAME} ${SRC_FILES})

# --- 4. ЛИНКОВКА ---
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm)
endif()

message(STATUS "Проект ${PROJECT_NAME} успешно настроен")