find_package(Boost REQUIRED)
find_package(CryptoPP REQUIRED)

include(${PROJECT_SOURCE_DIR}/cmake/modules/CopyHeaders.cmake)

add_definitions(-DBOOST_PP_VARIADICS)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${CRYPTOPP_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/src
)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "-fPIC")
endif()

file(GLOB_RECURSE LIBRARY_SOURCES "src/*.cpp")


add_library(abi STATIC ${LIBRARY_SOURCES})

CopyHeaders()
