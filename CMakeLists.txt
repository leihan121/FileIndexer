cmake_minimum_required(VERSION 3.16)

project(FileIndexer LANGUAGES CXX)

add_executable(file_indexer
    src/main.cpp
)

target_compile_features(file_indexer
    PRIVATE cxx_std_17
)

target_compile_options(file_indexer
    PRIVATE -Wall -Wextra
)