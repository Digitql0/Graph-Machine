cmake_minimum_required(VERSION 3.16)
project(graph_machine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

add_subdirectory(external/MiniGL)

# Collect your own source files
file(GLOB_RECURSE SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

# Now add your executable target
add_executable(graph_machine ${SRC_FILES})
include_directories(${PROJECT_SOURCE_DIR}/include)
target_link_libraries(graph_machine PRIVATE MiniGL)
