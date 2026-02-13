#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "../interface/node_struct.h"
#include "../array_list/array_list.h"
#include "../token_provider/token_provider.h"

class LexicalAnalyzer {

    private:
        ArrayList<std::string> arrayLines;
        ArrayList<NodeStruct> dictionary;
        TypeToken wordAnalyzer(const std::string& word) const;
        TypeToken letterAnalyzer(const std::string& letter) const;
        void splitLine(std::ifstream &code);
        void addToken(const std::string& value, TypeToken type, int line, int word);
        bool isOperator(char character) const;

    public:
        explicit LexicalAnalyzer(std::ifstream &config_file);
        TokenProvider tokenProvider;
        ArrayList<NodeStruct> tokenize(std::ifstream &code);
};

#endif

/**
 * @brief Constructor de la clase LexicalAnalyzer.
 * * Inicializa el analizador léxico y delega la carga de la configuración de tokens
 * al objeto tokenProvider interno utilizando el archivo proporcionado.
 * * @param config_file Referencia al flujo del archivo (.csv/.txt) con la gramática de tokens.
 */
inline LexicalAnalyzer::LexicalAnalyzer(std::ifstream &config_file) {
    LexicalAnalyzer::tokenProvider.loadConfig(config_file);
}

/**
 * @brief Segmenta el archivo de código fuente en líneas individuales.
 * * Lee el archivo de entrada línea por línea y las almacena en la estructura @c arrayLines.
 * Al finalizar la lectura o si ocurre un error, se cierra el flujo del archivo.
 * * @param[in,out] code Referencia al flujo del archivo de código fuente a procesar.
 * @note Si el archivo no es válido o no está abierto, se enviará un error a la salida estándar.
 */
inline void LexicalAnalyzer::splitLine(std::ifstream &code) {
    if (code.is_open()) {
        std::string line;
        while (std::getline(code, line)) {
            this->arrayLines.addLast(line);
        }
        code.close();
    } else std::cout << "Error: Unable to open file" << std::endl;
}

/**
 * @brief Evalúa una cadena de caracteres para clasificarla como un token específico.
 * * La lógica de clasificación sigue esta jerarquía de prioridad:
 * 1. Coincidencia exacta con palabras reservadas, operadores o delimitadores en @c tokenProvider.
 * 2. Valores numéricos (literales de tipo VALUE).
 * 3. Identificadores válidos (comienzan con letra o guion bajo).
 * * @param word Cadena de texto extraída del buffer.
 * @return TypeToken Categoría del token identificada; @c TypeToken::UNKNOWN si no hay coincidencia.
 */
inline TypeToken LexicalAnalyzer::wordAnalyzer(const std::string& word) const {
    if (word.empty()) return TypeToken::UNKNOWN;

    if (this->tokenProvider.isToken(word)) {
        return this->tokenProvider.getToken(word);
    }

    if (isdigit(word[0])) {
        return TypeToken::VALUE;
    }

    if (isalpha(word[0]) || word[0] == '_') {
        return TypeToken::IDENTIFIER;
    }

    return TypeToken::UNKNOWN;
}

/**
 * @brief Identifica el tipo de token para símbolos únicos o caracteres especiales.
 * * Consulta directamente al proveedor de tokens para obtener la clasificación de una cadena corta.
 * * @param letter Cadena que representa el símbolo o carácter a analizar.
 * @return TypeToken Tipo de token correspondiente o @c TypeToken::UNKNOWN.
 */
inline TypeToken LexicalAnalyzer::letterAnalyzer(const std::string& letter) const {
    if (this->tokenProvider.isToken(letter)) {
        return this->tokenProvider.getToken(letter);
    }
    return TypeToken::UNKNOWN;
}

/**
 * @brief Valida si un carácter debe tratarse como un operador o delimitador.
 * * Un carácter se considera operador si no es un espacio en blanco, no es un punto decimal
 * (para soportar números flotantes) y está registrado como token o no es alfanumérico.
 * * @param character Carácter individual extraído de la línea.
 * @return true Si el carácter rompe el buffer actual y debe procesarse como operador/delimitador.
 * @return false Si el carácter es alfanumérico, un espacio o un punto decimal.
 */
inline bool LexicalAnalyzer::isOperator(const char character) const {
    if (isspace(character)) return false;
    if (character == '.') return false;
    std::string s(1, character);
    if (this->tokenProvider.isToken(s)) return true;
    return !isalnum(character);
}

/**
 * @brief Registra un nuevo token en el diccionario de resultados.
 * * Encapsula la información del token en una estructura @c NodeStruct y la añade al final
 * de la lista de tokens identificados.
 * * @param value Valor textual (lexema) del token.
 * @param type Categoría gramatical identificada.
 * @param line Número de línea en el código fuente (basado en 1).
 * @param word Índice secuencial del token dentro de su línea.
 */
inline void LexicalAnalyzer::addToken(const std::string& value, TypeToken type, int line, int word) {
    NodeStruct node;
    node.type = type;
    node.value = value;
    node.line = line;
    node.word = word;
    this->dictionary.addLast(node);
}

/**
 * @brief Ejecuta el análisis léxico completo sobre el código fuente.
 * * Implementa una máquina de estados finitos simple que maneja:
 * - Cadenas literales entre comillas (@c SPECIAL_DELIMITER).
 * - Identificación de números flotantes (preservando el punto).
 * - Operadores compuestos de dos caracteres (ej. `==`, `!=`).
 * - Omisión de espacios en blanco.
 * * @param[in] code Flujo de entrada con el código a tokenizar.
 * @return ArrayList<NodeStruct> Lista enlazada con la secuencia de tokens generada.
 */
inline ArrayList<NodeStruct> LexicalAnalyzer::tokenize(std::ifstream &code) {
    this->splitLine(code);
    int numLines = 0;
    int numWords = 0;

    do {
        std::string buffer;
        std::string line = this->arrayLines.get()->getData();
        numLines++;
        bool inString = false;
        char quoteChar = '\0';

        for (size_t i = 0; i < line.length(); i++) {
            char c = line[i];

            //FLUJO PARA CADENAS DE TEXTO

            if (inString) {
                if (c == quoteChar) {
                    this->addToken(buffer, TypeToken::VALUE, numLines, numWords++);
                    buffer.clear();
                    inString = false;
                } else buffer += c;
                continue;
            }

            std::string singleChar(1, c);
            if (this->tokenProvider.getToken(singleChar) == TypeToken::SPECIAL_DELIMITER) {
                if (!buffer.empty()) {
                    this->addToken(buffer, this->wordAnalyzer(buffer), numLines, numWords++);
                    buffer.clear();
                }
                inString = true;
                quoteChar = c;
                continue;
            }

            //FLUJO PARA OPERADOR INDIVIDUAL Y DOBLE

            if (isspace(c)) {
                if (!buffer.empty()) {
                    this->addToken(buffer, this->wordAnalyzer(buffer), numLines, numWords++);
                    buffer.clear();
                }
                continue;
            }

            if (isOperator(c)) {
                if (!buffer.empty()) {
                    this->addToken(buffer, this->wordAnalyzer(buffer), numLines, numWords++);
                    buffer.clear();
                }

                std::string op(1, c);
                if (i + 1 < line.length() && isOperator(line[i + 1])) {
                    std::string double_op = op + line[i + 1];
                    if (this->tokenProvider.isToken(double_op)) {
                        op = double_op;
                        i++;
                    }
                }
                this->addToken(op, this->letterAnalyzer(op), numLines, numWords++);
            } else {
                buffer += c;
            }
        }

        //LIMPIAR BUFFER

        if (!buffer.empty()) {
            this->addToken(buffer, this->wordAnalyzer(buffer), numLines, numWords++);
            buffer.clear();
        }

    } while (this->arrayLines.currentNext());

    return this->dictionary;
}