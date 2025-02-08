cmake_minimum_required(VERSION 3.16)
project(c-render VERSION 1.0.0)

# find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0
add_subdirectory(dependencies/SDL-release-2.30.10/)
add_subdirectory(dependencies/cglm-0.9.4)
add_subdirectory("./dependencies/libspng-0.7.4/")

set(CMAKE_C_STANDARD 11) # Requires C11 standard
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME}
	src/main.c
	src/c-render/pixels.c
)

target_link_libraries(${PROJECT_NAME} SDL2)
target_link_libraries(${PROJECT_NAME} cglm)
target_link_libraries(${PROJECT_NAME} spng)

# libm (C math library)
target_link_libraries(${PROJECT_NAME} m)
