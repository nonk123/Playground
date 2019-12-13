cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

project(Playground CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Bullet REQUIRED)
find_package(Irrlicht REQUIRED)

set(PLAYGROUND_SRC
  src/main.cpp
  src/Program.cpp
  src/EventReceiver.cpp
  src/World.cpp
  src/Entity.cpp
  src/Shapes.cpp)

set(PLAYGROUND_DRIVER "OPENGL" CACHE STRING
  "Irrlicht video driver to use, without the irr::video::EDT_ prefix.")

configure_file(include/config.hpp.in include/config.hpp @ONLY)

add_executable(Playground "")
set_property(TARGET Playground PROPERTY CXX_STANDARD 17)
target_sources(Playground PRIVATE ${PLAYGROUND_SRC})
target_link_libraries(Playground PRIVATE
  ${BULLET_LIBRARIES}
  ${IRRLICHT_LIBRARY})
target_include_directories(Playground PRIVATE
  include/
  ${CMAKE_CURRENT_BINARY_DIR}/include/
  ${BULLET_INCLUDE_DIRS}
  ${IRRLICHT_INCLUDE_DIR})
