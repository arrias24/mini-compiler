#ifndef NODE_STRUCT_H
#define NODE_STRUCT_H
#include <string>

#include "../interface/type_token.h"

struct NodeStruct {
    std::string name;
    TokenType type;
    std::string value;
    int line;
    int word;
};

#endif