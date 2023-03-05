cmake_minimum_required(VERSION 3.24)
project(ArcticFox)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/bin/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/lib/${CMAKE_BUILD_TYPE})

include_directories(${CMAKE_INSTALL_PREFIX}/include)

add_subdirectory(ArcticFox)
add_subdirectory(third_part)
add_subdirectory(example)
