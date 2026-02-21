#ifndef TOKEN_PROVIDER_H
#define TOKEN_PROVIDER_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "../../interface/type_token.h"

class TokenProvider {
    private:
        std::unordered_map<std::string, TokenType> tokenMap;
    public:
        TokenProvider();

        static std::string toString(TokenType type);
        static TokenType toTypeToken(const std::string& str);
        bool loadConfig(std::ifstream& file_config);
        TokenType getToken(const std::string& key) const;

        bool isToken(const std::string &key) const;

        bool hasToken(const std::string& key) const;
    };

inline TokenProvider::TokenProvider() = default;

/**
 * @brief Convierte un enumerador TypeToken a su representación en cadena de texto.
 * * @param type El tipo de token de enumeración (TypeToken).
 * @return std::string El nombre del tipo en mayúsculas (ej: "IDENTIFIER") o "UNKNOWN" si no coincide.
 */
inline std::string TokenProvider::toString(const TokenType type) {
    switch (type) {
        case TokenType::IDENTIFIER: return "IDENTIFIER";
        case TokenType::VALUE:      return "VALUE";
        case TokenType::OPERATOR:   return "OPERATOR";
        case TokenType::ASSIGNMENT: return "ASSIGNMENT";
        case TokenType::KEYWORD:    return "KEYWORD";
        case TokenType::OPEN_DELIMITER:  return "OPEN-DELIMITER";
        case TokenType::CLOSE_DELIMITER: return "CLOSE-DELIMITER";
        case TokenType::DELIMITER:  return "DELIMITER";
        case TokenType::TEXT_DELIMITER: return "TEXT-DELIMITER";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Convierte una cadena de texto a su correspondiente enumerador TypeToken.
 * * @param str Cadena de texto que representa el tipo (ej: "KEYWORD").
 * @return TypeToken El valor de la enumeración correspondiente o TypeToken::UNKNOWN si no hay coincidencia.
 */
inline TokenType TokenProvider::toTypeToken(const std::string& str) {
    if (str == "KEYWORD")           return TokenType::KEYWORD;
    if (str == "OPERATOR")          return TokenType::OPERATOR;
    if (str == "ASSIGNMENT")        return TokenType::ASSIGNMENT;
    if (str == "OPEN-DELIMITER")    return TokenType::OPEN_DELIMITER;
    if (str == "CLOSE-DELIMITER")   return TokenType::CLOSE_DELIMITER;
    if (str == "DELIMITER")         return TokenType::DELIMITER;
    if (str == "TEXT-DELIMITER")    return TokenType::TEXT_DELIMITER;
    if (str == "VALUE")             return TokenType::VALUE;
    if (str == "IDENTIFIER")        return TokenType::IDENTIFIER;
    return TokenType::UNKNOWN;
}

/**
 * @brief Carga la tabla de tokens desde un archivo CSV.
 * * Lee el archivo línea por línea esperando el formato: `TIPO;VALOR`.
 * Realiza una limpieza de espacios en blanco y saltos de línea tanto en la clave como en el valor.
 * * @note Ejemplo de formato de archivo: `KEYWORD;while`
 * * @param file_config @param filename Ruta relativa o absoluta del archivo de configuración.
 * @return true Si el archivo se cargó y procesó correctamente.
 * @return false Si hubo un error al intentar abrir el archivo.
 */
inline bool TokenProvider::loadConfig(std::ifstream& file_config) {
    if (!file_config.is_open()) return false;

    std::string line;
    while (std::getline(file_config, line)) {
        line.erase(line.find_last_not_of("\r\n\t ") + 1);
        if (line.empty()) continue;

        std::istringstream ss(line);
        std::string typeStr;

        if (std::getline(ss, typeStr, ';')) {
            std::string tokenValue;
            if (std::getline(ss, tokenValue)) {

                tokenValue.erase(0, tokenValue.find_first_not_of(' '));
                tokenValue.erase(tokenValue.find_last_not_of(' ') + 1);

                typeStr.erase(0, typeStr.find_first_not_of(' '));
                typeStr.erase(typeStr.find_last_not_of(' ') + 1);

                this->tokenMap[tokenValue] = TokenProvider::toTypeToken(typeStr);
            }
        }
    }
    file_config.close();
    return true;
}

/**
 * @brief Obtiene la categoría (TypeToken) de un lexema específico.
 * * Busca en el mapa interno si el lexema (key) existe y devuelve su clasificación.
 * * @param key El lexema a buscar (ej: "if", "+", "==").
 * @return TypeToken La categoría del token o TypeToken::UNKNOWN si no está registrado.
 */
inline TokenType TokenProvider::getToken(const std::string &key) const {
    if (this->tokenMap.count(key)) return this->tokenMap.at(key);
    return TokenType::UNKNOWN;
}

/**
 * @brief Verifica si un lexema está registrado en la configuración cargada.
 * * @param key El lexema a verificar.
 * @return true Si el token existe en el mapa.
 * @return false Si el token no está registrado.
 */
inline bool TokenProvider::isToken(const std::string &key) const {
    return tokenMap.count(key) > 0;
}
#endif