#include "lexical_analyzer.h"

/**
 * @brief Constructor de LexicalAnalyzer.
 * * Inicializa el analizador y carga automáticamente la configuración de tokens
 * desde el archivo predeterminado.
 */
LexicalAnalyzer::LexicalAnalyzer() {
    LexicalAnalyzer::loadConfigTokens();
};

/**
 * @brief Carga la configuración de tokens desde un archivo CSV.
 * * @return true si la carga fue exitosa, false en caso contrario.
 * @note Busca el archivo en la ruta relativa "../config/lexical_config.csv".
 */
bool LexicalAnalyzer::loadConfigTokens() {
    return this->tokenProvider.loadConfig("../config/lexical_config.csv");
};

/**
 * @brief Divide el archivo de entrada en líneas y las almacena en memoria.
 * * @param code Referencia al flujo del archivo de código fuente (ifstream).
 * Si el archivo no puede abrirse, imprime un mensaje de error en la consola.
 */
void LexicalAnalyzer::splitLine(std::ifstream &code) {
    if (code.is_open()) {
        std::string line;
        while (std::getline(code, line)) {
            this->arrayLines.addLast(line);
        }
        code.close();
    } else std::cout << "Unable to open file" << std::endl;
}

/**
 * @brief Analiza una palabra (buffer) para determinar su tipo de token.
 * * Sigue el orden de prioridad:
 * 1. ¿Está en el diccionario de palabras reservadas (Keywords/Operators)?
 * 2. ¿Comienza con un dígito? (Clasificado como VALUE).
 * 3. ¿Comienza con letra o guion bajo? (Clasificado como IDENTIFIER).
 * * @param word La cadena de texto a analizar.
 * @return TypeToken El tipo identificado o UNKNOWN.
 */
TypeToken LexicalAnalyzer::wordAnalizer(const std::string& word) {
    // 1. PRIORIDAD: Buscar en el diccionario (Keywords)
    if (this->tokenProvider.isToken(word)) {
        return this->tokenProvider.getToken(word);
    }
    
    // 2. ¿Es un número?
    if (!word.empty() && isdigit(word[0])) {
        return TypeToken::VALUE;
    }
    
    // 3. Si no fue keyword y empieza por letra, es identificador
    if (!word.empty() && (isalpha(word[0]) || word[0] == '_')) {
        return TypeToken::IDENTIFIER;
    }

    return TypeToken::UNKNOWN;
}

/**
 * @brief Analiza un carácter o cadena corta para identificar símbolos simples.
 * * @param letter El símbolo a analizar.
 * @return TypeToken El tipo de token según el proveedor de configuración.
 */
TypeToken LexicalAnalyzer::letterAnalizer(const std::string& letter) {
    if (this->tokenProvider.isToken(letter)) {
        return this->tokenProvider.getToken(letter);
    }
    return TypeToken::UNKNOWN;
}

/**
 * @brief Determina si un carácter es un operador o un delimitador.
 * * @param character El carácter a evaluar.
 * @return true si es un símbolo especial (no alfanumérico y no espacio).
 * @return false si es un espacio o un carácter alfanumérico.
 */
bool LexicalAnalyzer::isOperator(const char character) {
    if (isspace(character)) return false;
    std::string s(1, character);
    if (this->tokenProvider.isToken(s)) return true;
    return !isalnum(character); 
}

/**
 * @brief Crea un nuevo nodo de token y lo añade al diccionario de resultados.
 * * @param value Valor textual del token.
 * @param type Categoría del token.
 * @param line Número de línea donde se encontró.
 * @param word Índice de la palabra en la línea.
 */
void LexicalAnalyzer::addToken(const std::string& value, TypeToken type, int line, int word) {
    NodeStruct node;
    node.type = type;
    node.value = value;
    node.line = line;
    node.word = word;
    this->dictionary.addLast(node);
}

/**
 * @brief Proceso principal de tokenización del código fuente.
 * * Itera sobre cada línea y cada carácter para segmentar el texto. 
 * Maneja espacios en blanco como separadores y tiene lógica para identificar 
 * operadores compuestos (de dos caracteres, ej: `==`, `!=`).
 * * @param code Stream del archivo de entrada.
 * @return ArrayList<NodeStruct> Lista enlazada de todos los tokens encontrados.
 */
ArrayList<NodeStruct> LexicalAnalyzer::tokenize(std::ifstream &code) {
    this->splitLine(code);
    int numLines = 0;
    int numWords = 0;

    do {
        std::string buffer;
        std::string line = this->arrayLines.get()->getData();
        numLines++;
        
        for (size_t i = 0; i < line.length(); i++){
            char c = line[i];

            // CASO 1 - ESPACIO EN BLANCO: Finaliza el token actual si el buffer no está vacío.
            if(isspace(c)){
                if(!buffer.empty()){
                    this->addToken(buffer, this->wordAnalizer(buffer), numLines, numWords++);
                    buffer.clear();
                }
                continue;
            }

            // CASO 2 - OPERADOR O DELIMITADOR
            if (isOperator(c)) {
                // 1. Guardamos lo que había acumulado en el buffer antes del operador
                if(!buffer.empty()){
                    this->addToken(buffer, this->wordAnalizer(buffer), numLines, numWords++);
                    buffer.clear();
                }

                // 2. Lógica para operadores dobles (Lookahead)
                std::string op(1, c);
                if (i + 1 < line.length() && isOperator(line[i+1])){
                    std::string double_op = op + line[i+1];
                    if (this->tokenProvider.isToken(double_op)) {
                        op = double_op;
                        i++; // Saltar el siguiente carácter ya que se consumió en el operador doble
                    }
                }

                // 3. Registrar el operador encontrado
                this->addToken(op, this->letterAnalizer(op), numLines, numWords++);
            } 
            // CASO 3 - ALFANUMÉRICO: Se acumula en el buffer.
            else {
                buffer += c;
            }
        }

        // Limpieza final: procesar remanentes en el buffer al terminar la línea
        if (!buffer.empty()) {
            this->addToken(buffer, this->wordAnalizer(buffer), numLines, numWords++);
            buffer.clear();
        }

    } while (this->arrayLines.currentNext());

    return this->dictionary;
}