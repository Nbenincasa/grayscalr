add_library(bmp_lib STATIC
            src/bmp_24.cpp
)

target_include_directories(bmp_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)