cmake_minimum_required(VERSION 3.8)

project(py-vm)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEAE "-O3 -Wall")

add_executable(${PROJECT_NAME}
    main.cpp
    object/hiString.cpp
    object/hiInteger.cpp
    object/hiObject.cpp
    code/binaryFileParser.cpp
    code/bytecode.cpp
    runtime/interpreter.cpp
    runtime/universe.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    .
    object
    code
    util
)
