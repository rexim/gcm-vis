cmake_minimum_required(VERSION 2.8)
project(gcm-vis)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(${SDL_INCLUDE_DIR})

add_executable(gcm-vis
  main.cpp
  states.cpp
  misc.cpp
)

target_link_libraries(gcm-vis
  ${SDL_LIBRARY}
  ${OPENGL_LIBRARY}
)
