cmake_minimum_required(VERSION 3.10)
project(CppFeaturesLearning)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main main.cpp)

# Enable threading if needed
find_package(Threads REQUIRED)
target_link_libraries(main PRIVATE Threads::Threads)