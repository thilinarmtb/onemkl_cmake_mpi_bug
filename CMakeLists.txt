cmake_minimum_required(VERSION 3.13)

project(oneMKL_Example LANGUAGES CXX)

find_package(MKL CONFIG REQUIRED PATHS $ENV{MKLROOT})

add_executable(myapp gpu_file.cpp)
target_link_libraries(myapp PUBLIC MKL::MKL_SYCL)
