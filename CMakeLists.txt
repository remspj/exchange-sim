cmake_minimum_required(VERSION 4.5)
project(exchange_sim LANGUAGES CXX)

add_executable(exchange_sim src/main.cpp src/lob_csv_reader.cpp)

target_include_directories(
    exchange_sim
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

set_target_properties(
    exchange_sim
    PROPERTIES CXX_STANDARD 23 CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF
)
