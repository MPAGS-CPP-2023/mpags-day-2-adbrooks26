#ifndef MPAGSCIPHER_RUNCAESARCIPHER_HPP
#define MPAGSCIPHER_RUNCAESARCIPHER_HPP

#include <string>

std::string runCaesarCipher(const std::string& inputText, const std::size_t key, const bool encrypt, const bool decrypt);

#endif //MPAGSCIPHER_RUNCAESARCIPHER_HPP