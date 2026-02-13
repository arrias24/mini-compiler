cmake_minimum_required(VERSION 3.20) # Versión estándar para CLion actual
project(proyectos)

set(CMAKE_CXX_STANDARD 14)

# Directorios de inclusión
include_directories(include)
include_directories(interface)
include_directories(src)

add_executable(proyectos
        # --- FUENTES (Archivos con lógica real .cpp) ---
        src/main.cpp

        # --- HEADERS (Para que CLion los indexe y ayude con el autocompletado) ---
        include/lexical_analyzer/lexical_analyzer.h
        include/token_provider/token_provider.h
        include/array_list/array_list.h
        include/node/node.h
        include/stack/stack.h
        interface/type_token.h
        interface/node_struct.h
)