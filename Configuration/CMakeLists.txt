cmake_minimum_required(VERSION 3.15)
project(C__)

set(CMAKE_CXX_STANDARD 20)

add_executable(C__
        solution.cpp)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

target_compile_definitions(C__ PRIVATE "LOCAL_ALIKHAN")
target_compile_options(C__ PRIVATE "-g")
target_compile_options(C__ PRIVATE "-Wall")
target_compile_options(C__ PRIVATE "-Werror")
target_compile_options(C__ PRIVATE "-Wextra")
target_compile_options(C__ PRIVATE "-Wconversion")
target_compile_options(C__ PRIVATE "-static")
target_compile_options(C__ PRIVATE "-Wl,--stack=268435456")
target_compile_options(C__ PRIVATE "-O2")
