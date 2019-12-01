cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(Playground CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Bullet REQUIRED)
find_package(Irrlicht REQUIRED)

file(GLOB PLAYGROUND_SRC src/*.cpp)

add_executable(Playground "")
target_sources(Playground PRIVATE ${PLAYGROUND_SRC})
target_link_libraries(Playground PRIVATE
  ${BULLET_LIBRARIES}
  ${IRRLICHT_LIBRARY})
target_include_directories(Playground PRIVATE
  include/
  ${BULLET_INCLUDE_DIRS}
  ${IRRLICHT_INCLUDE_DIR})
