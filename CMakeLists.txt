cmake_minimum_required(VERSION 3.22.0)

#-----------------------------------------------------
# Edit project-specific information
#-----------------------------------------------------

set(EXECUTABLE prog)

#-----------------------------------------------------
# Usually leave the rest untouched
#-----------------------------------------------------

project(${EXECUTABLE} VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED YES)

# Use stricter compiler warnings
if (MSVC)
    add_compile_options(/W4) 
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_CRT_NONSTDC_NO_DEPRECATE)
endif()

file(GLOB SRCS_LIST "*.c" "*.h")

add_executable(${EXECUTABLE} ${SRCS_LIST})