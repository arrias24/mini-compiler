#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <string>
#include <fstream>
#include "../../interface/node_struct.h"
#include "../array_list/array_list.cpp"
#include "../token_provider/token_provider.cpp"

class LexicalAnalyzer {

    private:
        ArrayList<std::string> arrayLines;
        ArrayList<NodeStruct> dictionary;
        TypeToken wordAnalizer(const std::string& word);
        TypeToken letterAnalizer(const std::string& letter);
        void splitLine(std::ifstream &code);
        void addToken(const std::string& value, TypeToken type, int line, int word);
        bool isOperator(const char character);
        bool loadConfigTokens();

    public:
        LexicalAnalyzer();
        TokenProvider tokenProvider;
        ArrayList<NodeStruct> tokenize(std::ifstream &code);
};

#endif
