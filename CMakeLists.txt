cmake_minimum_required(VERSION 3.17)
project(templateArray)

set(CMAKE_CXX_STANDARD 20)

add_library(templateArray templateArray.h)
set_target_properties(templateArray PROPERTIES LINKER_LANGUAGE CXX)