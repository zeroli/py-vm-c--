cmake_minimum_required(VERSION 3.8)

project(py-vm)

add_executable(${PROJECT_NAME}
    main.cpp
    object/hiString.cpp
    code/binaryFileParser.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    .
    object
    code
    util
)
