#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <string>
#include <fstream>
#include "../../interface/node_struct.h"
#include "../array_list/array_list.cpp"

class LexicalAnalyzer {

    private:
        ArrayList<std::string> arrayLines;
        ArrayList<NodeStruct> dictionary;

        LexicalAnalyzer();
        void splitLine(std::ifstream &code);

    public:
        LexicalAnalyzer(const LexicalAnalyzer&) = delete;
        void operator=(const LexicalAnalyzer&) = delete;
        static LexicalAnalyzer& getInstance();

        ArrayList<NodeStruct> tokenize(std::ifstream &code);
};

#endif
