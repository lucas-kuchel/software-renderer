cmake_minimum_required(VERSION 3.21)

project(software-renderer LANGUAGES CXX)

file(GLOB_RECURSE SOURCES "source/*.cpp")

add_executable(software-renderer ${SOURCES})

target_include_directories(software-renderer PRIVATE
    "source/include"
)
