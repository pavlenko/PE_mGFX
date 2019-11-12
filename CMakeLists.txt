cmake_minimum_required(VERSION 3.13)
project(PE_mGFX)
set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES "src/*.c" #[["src/*.cpp"]])

add_library(PE_mGFX ${SOURCES})