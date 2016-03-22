find_package(Boost REQUIRED)
find_package(CryptoPP REQUIRED)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/CopyHeaders.cmake)

add_definitions(-DBOOST_PP_VARIADICS)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${CRYPTOPP_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "-fPIC")
endif()

file(GLOB_RECURSE LIBRARY_SOURCES "src/*.cpp")


add_library(abi STATIC ${LIBRARY_SOURCES})

CopyHeaders()

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/include/abi DESTINATION include)
install (TARGETS abi ARCHIVE DESTINATION lib LIBRARY DESTINATION lib RUNTIME DESTINATION bin)
