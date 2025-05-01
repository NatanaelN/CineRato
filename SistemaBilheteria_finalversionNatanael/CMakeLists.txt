cmake_minimum_required(VERSION 3.29.6)
project(SistemaBilheteria C)

set(CMAKE_C_STANDARD 11)


# Fonte: todos os .c em src/ e main.c
file(GLOB_RECURSE SOURCES
        "${CMAKE_SOURCE_DIR}/src/*.c"
        "${CMAKE_SOURCE_DIR}/main.c"
)

# Executável
add_executable(${PROJECT_NAME} ${SOURCES})

# Include root
target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)