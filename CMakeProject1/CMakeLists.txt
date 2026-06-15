cmake_minimum_required(VERSION 3.14)
project(SnakeGame)

# Подключаем Raylib через FetchContent
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)

# Находим все .cpp файлы в папке
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# Создаём исполняемый файл
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Линкуем Raylib
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE winmm)
endif()