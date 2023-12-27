# CMake definitions, compiler flags and useful variables
cmake_minimum_required(VERSION 3.7)
project(TD4 CXX)

add_compile_options(-Wall -Werror)

set(APP_NAME td4app)
set(TD4_LIB_NAME td4Lib)

# Include application build instructions
add_subdirectory(src)

# include tests build instructions
option(UT "Compile the UTs" OFF)
if(UT)
  add_subdirectory(ut)
endif(UT)
