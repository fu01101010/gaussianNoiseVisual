cmake_minimum_required(VERSION 3.28)
project("gaussianNoiseVisual")

find_package(OpenGL REQUIRED)

include_directories(
  # library headers
  "./include/"
)

set (CMAKE_CXX_STANDARD 11)

set (GLFW_SHARED_LIB
  "${PROJECT_SOURCE_DIR}/libs/glfw/lib-x86_64/libglfw.3.dylib"
)

set (ALL_LIBS 
  ${OpenGL}
  ${GLFW_SHARED_LIB}
  "-ldl"
)

add_executable(gaussN 
  "source/glad.c"
  "source/graphics/shader.cpp"
  "source/graphics/light.cpp"
  "source/graphics/material.cpp"
  "source/graphics/vMesh.cpp"
  "source/graphics/vModel.cpp"
  "source/graphics/models/vCube.hpp"
  "source/graphics/models/vLightSource.hpp"
  "source/io/screen.cpp"
  "source/io/camera.cpp"
  "source/io/keyboard.cpp"
  "source/io/mouse.cpp"
  "source/main.cpp"
)

target_link_libraries(gaussN ${ALL_LIBS})
install(TARGETS gaussN DESTINATION "${PROJECT_SOURCE_DIR}/bin/")