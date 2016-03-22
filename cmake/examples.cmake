find_package(CryptoPP REQUIRED)
find_package(Boost REQUIRED)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
find_package(Threads REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/examples)

file(GLOB EXAMPLES 
    "examples/*.cpp"
)

include_directories(${Boost_INCLUDE_DIRS} ${CRYPTOPP_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/include)

foreach(EXAMPLE ${EXAMPLES})
    get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)
    add_executable(${EXAMPLE_NAME} ${EXAMPLE})
    target_link_libraries(${EXAMPLE_NAME} 
        abi
        ${CRYPTOPP_LIBRARY}
        ${CMAKE_THREAD_LIBS_INIT}
    )
    add_dependencies(${EXAMPLE_NAME} abi)
endforeach(EXAMPLE)
