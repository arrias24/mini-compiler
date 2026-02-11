#ifndef TOKEN_PROVIDER_H
#define TOKEN_PROVIDER_H

#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include "../../interface/type_token.h"

class TokenProvider {
    private:
        std::unordered_map<std::string, TypeToken> tokenMap;
    public:
        TokenProvider();
        std::string toString(TypeToken type);
        TypeToken toTypeToken(const std::string& str);
        bool loadConfig(const std::string& filename);
        TypeToken getToken(const std::string& key);
        bool isToken(const std::string& key) const;
    };

#endif