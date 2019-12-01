cmake_minimum_required(VERSION 3.13.0)
project(rpi-mic)

find_package(ALSA REQUIRED)

add_executable(rpi-mic src/rpi-mic.cpp)
target_compile_features(rpi-mic PUBLIC cxx_std_14)
target_link_libraries(rpi-mic PUBLIC ALSA::ALSA)
