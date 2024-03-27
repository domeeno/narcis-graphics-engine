cmake_minimum_required(VERSION 3.0)

project(WallachiaStore)

set(SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/src")
set(SOURCES 
  "${SRC_DIR}/main.cpp" 
  "${SRC_DIR}/Store.cpp" 
  "${SRC_DIR}/glad.c"
  "${SRC_DIR}/shaders.cpp"
  "${SRC_DIR}/cglfw.cpp"
  "${SRC_DIR}/game.cpp"
  )

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include")

target_link_libraries(${PROJECT_NAME}
  glfw 
  GL 
  Xrandr 
  X11 
  rt 
  dl
)

set_target_properties(${PROJECT_NAME} PROPERTIES 
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)
