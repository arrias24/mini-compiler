#include "./token_provider/token_provider.h"

/**
 * @brief Constructor privado.
 * Implementa la restricción del patrón Singleton para evitar instanciaciones externas.
 */
TokenProvider::TokenProvider() {}

/**
 * @brief Acceso al Singleton.
 * @return Referencia a la única instancia de TokenProvider existente en el programa.
 */
TokenProvider& TokenProvider::getInstance() {
    static TokenProvider instance;
    return instance;
}

/**
 * @brief Carga la tabla de tokens desde un archivo CSV.
 * * Lee el archivo línea por línea esperando el formato: KEY;VALUE.
 * Ejemplo: KEYWORD;while
 * * @param filename Ruta del archivo de configuración.
 * @return true si el archivo se cargó correctamente, false si hubo un error de apertura.
 */
bool TokenProvider::loadConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue; // Ignora líneas en blanco

        std::istringstream ss(line);
        std::string key, value;

        // Extrae 'value' (Categoría) hasta el ';' y luego el resto como 'key' (Lexema)
        if (std::getline(ss, value, ';') && std::getline(ss, key)) {
            this->tokenMap[key] = value;
        }
    }
    file.close();
    return true;
}

/**
 * @brief Obtiene la categoría de un key específico.
 * * @param key El key a buscar (ej: "if", "+", "==").
 * @return std::string Nombre de la categoría o un string vacío si no se encuentra.
 */
std::string TokenProvider::getToken(const std::string &key) {
    if (this->tokenMap.count(key)) return this->tokenMap.at(key);
    return "";
}

/**
 * @brief Verifica si un key está registrado en la configuración.
 * * @param key El key a verificar.
 * @return true si existe en el mapa, false de lo contrario.
 */
bool TokenProvider::isToken(const std::string &key) const {
    // Uso de count() para evitar inserciones accidentales en el mapa
    return tokenMap.count(key) > 0;
}