cmake_minimum_required(VERSION 3.13.0)
project(rpi-mic)
add_executable(rpi-mic src/rpi-mic.cpp)
target_compile_features(rpi-mic PUBLIC cxx_std_14)
