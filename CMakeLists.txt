cmake_minimum_required(VERSION 3.0)

project(NarcisGE)

find_package(glm CONFIG REQUIRED)

set(SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES 
  "${SRC_DIR}/main.cpp" 
  "${SRC_DIR}/gl/glad.c"
  "${SRC_DIR}/gl/shaders.cpp"
  "${SRC_DIR}/lib/cglfw.cpp"
  "${SRC_DIR}/lib/stb_image.cpp"
  "${SRC_DIR}/lib/textures.cpp"
  "${SRC_DIR}/nge/Engine/AppEngine.cpp"
  )

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include")

target_link_libraries(${PROJECT_NAME}
  glfw 
  Xrandr 
  X11 
  rt 
  dl
  glm::glm
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
