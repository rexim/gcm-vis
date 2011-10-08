cmake_minimum_required(VERSION 2.8)
project(gcm)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(gcm
  main.cpp
  states.cpp
  misc.cpp
)

target_link_libraries(gcm
  ${SDL_LIBRARY}
  ${OPENGL_LIBRARY}
)