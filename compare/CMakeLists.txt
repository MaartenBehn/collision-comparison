cmake_minimum_required(VERSION 3.0)

project(collision-comparison VERSION 1.0.0)
set_property(GLOBAL PROPERTY CXX_STANDARD 20)

add_executable(compare 
  main.cpp 
  jolt.cpp 
  fcl.cpp 
  bullet.cpp
  utility.cpp collider.h collider.cpp)

include_directories(/usr/include/assimp)

# Json
include_directories(${CMAKE_SOURCE_DIR}/include/json/include)


# Benchmark
include_directories(${CMAKE_SOURCE_DIR}/include/nanobench/src/include)


# Jolt

add_subdirectory(${CMAKE_SOURCE_DIR}/../JoltPhysics/Build ${CMAKE_BINARY_DIR}/Jolt)
include_directories(${CMAKE_SOURCE_DIR}/../JoltPhysics)

add_library(libjolt STATIC IMPORTED)
set_target_properties(libjolt PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/Jolt/libJolt.a)
set_target_properties(libjolt PROPERTIES INTERFACE_INCLUDE_DIRECTORIES /usr/include)
# set_target_properties(libjolt PROPERTIES COMPILE_DEFINITIONS "")

target_link_libraries(compare libjolt)


# FCL
find_package (Eigen3 3.3 REQUIRED NO_MODULE)
target_link_libraries (compare Eigen3::Eigen)

add_subdirectory(${CMAKE_SOURCE_DIR}/../hpp-fcl/ ${CMAKE_BINARY_DIR}/fcl)
include_directories(${CMAKE_SOURCE_DIR}/../hpp-fcl/include)
include_directories(${CMAKE_BINARY_DIR}/fcl/include)

link_directories(${CMAKE_BINARY_DIR}/fcl/)

target_link_libraries(compare ${CMAKE_BINARY_DIR}/fcl/src/libhpp-fcl.so)


# Bullet3
add_subdirectory(${CMAKE_SOURCE_DIR}/../bullet3 ${CMAKE_BINARY_DIR}/bullet)
set_property(DIRECTORY "${CMAKE_SOURCE_DIR}/../bullet3" APPEND
  PROPERTY COMPILE_DEFINITIONS "-DUSE_DOUBLE_PRECISION=ON -DBT_USE_EGL=ON -DCMAKE_BUILD_TYPE=Release")
include_directories(${CMAKE_SOURCE_DIR}/../bullet3/src)

add_library(libbullet3collsion STATIC IMPORTED)
set_target_properties(libbullet3collsion PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/bullet/src/Bullet3Collision/libBullet3Collision.a)
set_target_properties(libbullet3collsion PROPERTIES INTERFACE_INCLUDE_DIRECTORIES /usr/include)
target_link_libraries(compare libbullet3collsion)

add_library(libbulletcollsion STATIC IMPORTED)
set_target_properties(libbulletcollsion PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/bullet/src/BulletCollision/libBulletCollision.a)
set_target_properties(libbulletcollsion PROPERTIES INTERFACE_INCLUDE_DIRECTORIES /usr/include)
target_link_libraries(compare libbulletcollsion)

add_library(libbulletlinearmath STATIC IMPORTED)
set_target_properties(libbulletlinearmath PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/bullet/src/LinearMath/libLinearMath.a)
set_target_properties(libbulletlinearmath PROPERTIES INTERFACE_INCLUDE_DIRECTORIES /usr/include)
target_link_libraries(compare libbulletlinearmath)

install(TARGETS compare DESTINATION bin)

