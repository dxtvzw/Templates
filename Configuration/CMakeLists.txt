cmake_minimum_required(VERSION 3.15)
project(CPlusPlus)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPlusPlus solution.cpp)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")

target_compile_definitions(CPlusPlus PRIVATE "LOCAL")
target_compile_options(CPlusPlus PRIVATE "-g")
# target_compile_options(CPlusPlus PRIVATE "-Wall")
# target_compile_options(CPlusPlus PRIVATE "-Werror")
# target_compile_options(CPlusPlus PRIVATE "-Wextra")
# target_compile_options(CPlusPlus PRIVATE "-Wconversion")

# target_compile_options(CPlusPlus PRIVATE "-static")
# target_compile_options(CPlusPlus PRIVATE "-Wl,--stack=268435456")
target_link_options(CPlusPlus PRIVATE "-Wl,--stack,268435456")

target_compile_options(CPlusPlus PRIVATE "-O2")
