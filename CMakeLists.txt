cmake_minimum_required(VERSION 4.1)
project(proyectos)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/array_list)
include_directories(include/node)
include_directories(include/stack)
include_directories(src)

add_executable(proyectos
        include/array_list/array_list.h
        include/node/node.cpp
        include/node/node.h
        include/stack/stack.h
        src/main.cpp
        include/array_list/array_list.cpp
        include/stack/stack.cpp
        include/lexical_analyzer/lexical_analyzer.h
        interface/type_token.h
        interface/node_struct.h
        include/lexical_analyzer/lexical_analyzer.cpp
        include/token_provider/token_provider.h
        include/token_provider/token_provider.cpp)
