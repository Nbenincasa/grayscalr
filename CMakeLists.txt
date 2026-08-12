cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 23)

project(grayscalr LANGUAGES CXX)

add_subdirectory(bmp)

set(PROJECT_SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC bmp_24_lib)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX) # Strict warnings for Windows
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror) # Strict warnings for GCC/Clang
endif()