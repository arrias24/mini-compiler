#ifndef TOKEN_PROVIDER_H
#define TOKEN_PROVIDER_H

#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

class TokenProvider {
    private:
        std::unordered_map<std::string, std::string> tokenMap;
        TokenProvider();

    public:
        TokenProvider(const TokenProvider&) = delete;
        void operator=(const TokenProvider&) = delete;
        static TokenProvider& getInstance();

        bool loadConfig(const std::string& filename);
        std::string getToken(const std::string& key);
        bool isToken(const std::string& key) const;
    };

#endif