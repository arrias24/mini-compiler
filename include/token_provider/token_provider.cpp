#include "./token_provider.h"

TokenProvider::TokenProvider() {}

/**
 * @brief Convierte un enumerador TypeToken a su representación en cadena de texto.
 * * @param type El tipo de token de enumeración (TypeToken).
 * @return std::string El nombre del tipo en mayúsculas (ej: "IDENTIFIER") o "UNKNOWN" si no coincide.
 */
std::string TokenProvider::toString(TypeToken type) {
    switch (type) {
        case TypeToken::IDENTIFIER: return "IDENTIFIER";
        case TypeToken::VALUE:      return "VALUE";
        case TypeToken::OPERATOR:   return "OPERATOR";
        case TypeToken::KEYWORD:    return "KEYWORD";
        case TypeToken::DELIMITER:  return "DELIMITER";
        default: return "UNKNOWN";
    }
}

/**
 * @brief Convierte una cadena de texto a su correspondiente enumerador TypeToken.
 * * @param str Cadena de texto que representa el tipo (ej: "KEYWORD").
 * @return TypeToken El valor de la enumeración correspondiente o TypeToken::UNKNOWN si no hay coincidencia.
 */
TypeToken TokenProvider::toTypeToken(const std::string& str) {
    if (str == "KEYWORD")    return TypeToken::KEYWORD;
    if (str == "OPERATOR")   return TypeToken::OPERATOR;
    if (str == "DELIMITER")  return TypeToken::DELIMITER;
    if (str == "VALUE")      return TypeToken::VALUE;
    if (str == "IDENTIFIER") return TypeToken::IDENTIFIER;
    return TypeToken::UNKNOWN;
}

/**
 * @brief Carga la tabla de tokens desde un archivo CSV.
 * * Lee el archivo línea por línea esperando el formato: `TIPO;VALOR`.
 * Realiza una limpieza de espacios en blanco y saltos de línea tanto en la clave como en el valor.
 * * @note Ejemplo de formato de archivo: `KEYWORD;while`
 * * @param filename Ruta relativa o absoluta del archivo de configuración.
 * @return true Si el archivo se cargó y procesó correctamente.
 * @return false Si hubo un error al intentar abrir el archivo.
 */
bool TokenProvider::loadConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        // Eliminar caracteres de control y espacios al final de la línea
        line.erase(line.find_last_not_of("\r\n\t ") + 1);
        if (line.empty()) continue;

        std::istringstream ss(line);
        std::string typeStr, tokenValue;

        if (std::getline(ss, typeStr, ';')) {
            if (std::getline(ss, tokenValue)) {
                
                // Trim de espacios en blanco para el valor del token
                tokenValue.erase(0, tokenValue.find_first_not_of(" "));
                tokenValue.erase(tokenValue.find_last_not_of(" ") + 1);
                
                // Trim de espacios en blanco para el string del tipo
                typeStr.erase(0, typeStr.find_first_not_of(" "));
                typeStr.erase(typeStr.find_last_not_of(" ") + 1);

                // Mapeo del token en la tabla interna
                this->tokenMap[tokenValue] = this->toTypeToken(typeStr);
            }
        }
    }
    file.close();
    return true;
}

/**
 * @brief Obtiene la categoría (TypeToken) de un lexema específico.
 * * Busca en el mapa interno si el lexema (key) existe y devuelve su clasificación.
 * * @param key El lexema a buscar (ej: "if", "+", "==").
 * @return TypeToken La categoría del token o TypeToken::UNKNOWN si no está registrado.
 */
TypeToken TokenProvider::getToken(const std::string &key) {
    if (this->tokenMap.count(key)) return this->tokenMap.at(key);
    return TypeToken::UNKNOWN; 
}

/**
 * @brief Verifica si un lexema está registrado en la configuración cargada.
 * * @param key El lexema a verificar.
 * @return true Si el token existe en el mapa.
 * @return false Si el token no está registrado.
 */
bool TokenProvider::isToken(const std::string &key) const {
    // Uso de count() para evitar inserciones accidentales en el mapa por el operador []
    return tokenMap.count(key) > 0;
}