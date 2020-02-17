cmake_minimum_required(VERSION 3.15)
project(ringbuf C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
add_link_options(-fprofile-instr-generate -fcoverage-mapping)

add_executable(ringbuf test.c ringbuf.c)