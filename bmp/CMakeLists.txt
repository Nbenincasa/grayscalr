add_library(bmp_v1_lib STATIC
            src/bmp_v1.cpp
)

target_include_directories(bmp_v1_lib INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)