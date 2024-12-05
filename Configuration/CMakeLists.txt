cmake_minimum_required(VERSION 3.20)
project(CPlusPlus)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -std=c++20 -static -DLOCAL -Wl,--stack=268435456")
# -Wl,--stack,268435456
# -Wl,--stack=268435456
# -fsanitize=address -fsanitize=leak -fsanitize=undefined -static-libasan

add_executable(main main.cpp)
