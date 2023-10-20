cmake_minimum_required(VERSION 3.17)
project(tiger C)

set(CMAKE_C_STANDARD 11)
set(SOIL_CONFIG_PATH "${CMAKE_INSTALL_LIBDIR}/cmake/soil")

add_executable(tiger tiger.c model.c draw.c)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)


include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(tiger -lSOIL -lm ${OPENGL_LIBRARIES}  ${GLUT_LIBRARIES} )
file(COPY tiger.obj tiger.png DESTINATION ${CMAKE_CURRENT_BINARY_DIR})