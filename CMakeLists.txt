project(ali)
cmake_minimum_required (VERSION 3.5)
add_definitions(-std=c++11)

find_package( Eigen3 REQUIRED )
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

include_directories(include
                    include/QuadTree)

set(sources src/main.cpp
            src/Map.cpp
            src/WayPoint.cpp
        src/QuadTree/Quadtree.cpp)

add_executable(ali ${sources})
target_link_libraries(ali)
