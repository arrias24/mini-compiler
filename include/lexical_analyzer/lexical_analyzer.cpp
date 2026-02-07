#include "lexical_analyzer.h"

LexicalAnalyzer::LexicalAnalyzer() {}

LexicalAnalyzer & LexicalAnalyzer::getInstance() {
    static LexicalAnalyzer instance;
    return instance;
}

void LexicalAnalyzer::splitLine(std::ifstream &code) {

    if (code.is_open()) {
        std::string line;
        while (std::getline(code, line)) {
            this->arrayLines.addLast(line);
        }
        code.close();
    } else std::cout << "Unable to open file" << std::endl;
}

ArrayList<NodeStruct> LexicalAnalyzer::tokenize(std::ifstream &code) {
    int numLines = 0;
    int numWords = 0;

    this->splitLine(code);

    do {
        std::string word;
        std::string line = this->arrayLines.get()->getData();
        numLines++;
        for (char c : line) {

        }
    }
    while (this->arrayLines.currentNext());
    return this->dictionary;
}
