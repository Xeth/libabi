project(abi)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/modules")

if(ENABLE_DEBUG)
    set(CMAKE_BUILD_TYPE Debug)
else()
    set(CMAKE_BUILD_TYPE Release)
endif()

include(${PROJECT_SOURCE_DIR}/cmake/lib.cmake)

if(ENABLE_EXAMPLES)
    include(${PROJECT_SOURCE_DIR}/cmake/examples.cmake)
endif()
