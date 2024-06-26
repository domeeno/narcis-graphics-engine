cmake_minimum_required(VERSION 3.0)

project(NarcisGE)

find_package(glm CONFIG REQUIRED)

set(SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")

set(SOURCES 
  "${SRC_DIR}/main.cpp" 
  "${SRC_DIR}/external/glad.c"
  "${SRC_DIR}/external/stb_image.cpp"
  "${SRC_DIR}/lib/textures.cpp"
  "${SRC_DIR}/nge/Engine/AppEngine.cpp"
  "${SRC_DIR}/nge/Window/Window.cpp"
  "${SRC_DIR}/nge/Render/Render.cpp"
  "${SRC_DIR}/nge/Render/Shader.cpp"
  "${SRC_DIR}/nge/Models/Point.cpp"
  "${SRC_DIR}/nge/Models/Grid.cpp"
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
