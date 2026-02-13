#ifndef TOKEN_PROVIDER_H
#define TOKEN_PROVIDER_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "../../interface/type_token.h"

class TokenProvider {
    private:
        std::unordered_map<std::string, TypeToken> tokenMap;
    public:
        TokenProvider();

        static std::string toString(TypeToken type);
        static TypeToken toTypeToken(const std::string& str);
        bool loadConfig(std::ifstream& file_config);
        TypeToken getToken(const std::string& key) const;
        bool isToken(const std::string& key) const;
    };

#endif

inline TokenProvider::TokenProvider() = default;

/**
 * @brief Convierte un enumerador TypeToken a su representación en cadena de texto.
 * * @param type El tipo de token de enumeración (TypeToken).
 * @return std::string El nombre del tipo en mayúsculas (ej: "IDENTIFIER") o "UNKNOWN" si no coincide.
 */
inline std::string TokenProvider::toString(const TypeToken type) {
    switch (type) {
        case TypeToken::IDENTIFIER: return "IDENTIFIER";
        case TypeToken::VALUE:      return "VALUE";
        case TypeToken::OPERATOR:   return "OPERATOR";
        case TypeToken::KEYWORD:    return "KEYWORD";
        case TypeToken::DELIMITER:  return "DELIMITER";
        case TypeToken::SPECIAL_DELIMITER: return "SPECIAL_DELIMITER";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Convierte una cadena de texto a su correspondiente enumerador TypeToken.
 * * @param str Cadena de texto que representa el tipo (ej: "KEYWORD").
 * @return TypeToken El valor de la enumeración correspondiente o TypeToken::UNKNOWN si no hay coincidencia.
 */
inline TypeToken TokenProvider::toTypeToken(const std::string& str) {
    if (str == "KEYWORD")           return TypeToken::KEYWORD;
    if (str == "OPERATOR")          return TypeToken::OPERATOR;
    if (str == "DELIMITER")         return TypeToken::DELIMITER;
    if (str == "SPECIAL-DELIMITER") return TypeToken::SPECIAL_DELIMITER;
    if (str == "VALUE")             return TypeToken::VALUE;
    if (str == "IDENTIFIER")        return TypeToken::IDENTIFIER;
    return TypeToken::UNKNOWN;
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
inline TypeToken TokenProvider::getToken(const std::string &key) const {
    if (this->tokenMap.count(key)) return this->tokenMap.at(key);
    return TypeToken::UNKNOWN;
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