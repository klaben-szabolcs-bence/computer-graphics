cmake_minimum_required(VERSION 3.17)
project(tiger C)

set(CMAKE_C_STANDARD 11)

add_executable(tiger tiger.c model.c draw.c)
target_link_libraries(tiger -lSOIL -lGL -lGLU -lglut -lm)
file(COPY tiger.obj tiger.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})