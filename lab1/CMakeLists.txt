cmake_minimum_required(VERSION 3.7)
project(Unitsv1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(SOURCE_FILES main.cpp header.h make_grid.cpp local_matrix.cpp global_matrix.cpp lu_decomp.cpp matrix_operations.cpp hermit_base_functions.cpp b_vector_ops.cpp)
add_executable(Unitsv1 ${SOURCE_FILES})
