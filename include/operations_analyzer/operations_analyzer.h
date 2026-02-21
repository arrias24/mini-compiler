#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H

#pragma once
#include <stdexcept>
#include "../include/lexical_analyzer/lexical_analyzer.h"
#include "../stack/stack.h"

class OperationsAnalyzer {

    private:
        ArrayList<NodeStruct> inputTokens;

        static bool isOperator(TokenType type);
        static bool isDelimiter(TokenType type);
        static int getPrecedence(const NodeStruct &token);
        ArrayList<NodeStruct> toPostfix();
        static double evaluatePostfix(ArrayList<NodeStruct>& postfixTokens);

    public:
        explicit OperationsAnalyzer(const ArrayList<NodeStruct> &tokens);
        void resolve();
    };

inline OperationsAnalyzer::OperationsAnalyzer(const ArrayList<NodeStruct> &tokens) {
    inputTokens = tokens;
}

inline bool OperationsAnalyzer::isOperator(const TokenType type) {
    return type == TokenType::OPERATOR;
}

inline bool OperationsAnalyzer::isDelimiter(const TokenType type) {
    return type == TokenType::OPEN_DELIMITER || type == TokenType::CLOSE_DELIMITER;
}

inline int OperationsAnalyzer::getPrecedence(const NodeStruct &token) {
    if (isOperator(token.type)) {
        if (token.name == "+" || token.name == "-") return 2;
        if (token.name == "*" || token.name == "/") return 3;
    } else if (isDelimiter(token.type)) return 1;
    return 0;
}

inline ArrayList<NodeStruct> OperationsAnalyzer::toPostfix() {
    Stack<NodeStruct> stack;
    ArrayList<NodeStruct> postfix;

    if (inputTokens.isEmpty()) return postfix;

    inputTokens.currentReset();
    do {
        NodeStruct token = inputTokens.get()->getData();

        if (token.type == TokenType::VALUE) {
            postfix.addLast(token);
            continue;
        }

        if (token.type == TokenType::OPEN_DELIMITER) {
            stack.push(token);
            continue;
        }

        if (token.type == TokenType::CLOSE_DELIMITER) {
            while (!stack.isEmpty() && stack.top().type != TokenType::OPEN_DELIMITER) {
                postfix.addLast(stack.pop());
            }
            if (!stack.isEmpty()) {
                stack.pop();
            }
            continue;
        }

        if (token.type == TokenType::OPERATOR) {
            const int value = getPrecedence(token);
            while (!stack.isEmpty() && stack.top().type == TokenType::OPERATOR &&
                   value <= getPrecedence(stack.top())) {
                postfix.addLast(stack.pop());
            }
            stack.push(token);
        }
    } while (inputTokens.currentNext());

    while (!stack.isEmpty()) {
        if (stack.top().type == TokenType::OPEN_DELIMITER) {
            stack.pop();
            continue;
        }
        postfix.addLast(stack.pop());
    }

    return postfix;
}

inline double OperationsAnalyzer::evaluatePostfix(ArrayList<NodeStruct> &postfixTokens) {
    Stack<double> values;

    if (postfixTokens.isEmpty()) return 0.0;

    postfixTokens.currentReset();
    do {
        NodeStruct token = postfixTokens.get()->getData();

        if (token.type == TokenType::VALUE) {
            values.push(std::stod(token.name));
            continue;
        }

        if (token.type == TokenType::OPERATOR) {
            if (values.getSize() < 2) {
                throw std::out_of_range("Invalid postfix expression");
            }
            const double x = values.pop();
            const double y = values.pop();
            double result;

            if (token.name == "+") result = y + x;
            else if (token.name == "-") result = y - x;
            else if (token.name == "*") result = y * x;
            else if (token.name == "/") result = y / x;
            else continue;

            values.push(result);
        }
    } while (postfixTokens.currentNext());

    if (values.getSize() != 1) {
        throw std::out_of_range("Invalid postfix expression");
    }

    return values.pop();
}

inline void OperationsAnalyzer::resolve() {
    try {
        ArrayList<NodeStruct> postfix = toPostfix();
        std::cout << "Postfix Tokens: ";
        if (!postfix.isEmpty()) {
            postfix.currentReset();
            do {
                std::cout << " " << postfix.get()->getData().name << " ";
            } while (postfix.currentNext());
        }
        std::cout << std::endl;

        const double result = evaluatePostfix(postfix);
        std::cout << std::endl;
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error evaluating expression: " << e.what() << std::endl;
    }
}
#endif