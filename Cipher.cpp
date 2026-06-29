#include "Cipher.h"
#include <cctype>

CaesarCipher::CaesarCipher(int key) : key_(key) {}

std::string CaesarCipher::encrypt(const std::string &text) {
    std::string result = text;
    int shift = (key_ % 26 + 26) % 26;

    for (int i = 0; i < result.length(); i++) {
        char r = result[i];

        if (std::isupper(r)) {
            result[i] = (r - 'A' + shift) % 26 + 'A';
        } else if (std::islower(r)) {
            result[i] = (r - 'a' + shift) % 26 + 'a';
        }
    }

    return result;
}

std::string CaesarCipher::decrypt(const std::string &text) {
    return CaesarCipher(-key_).encrypt(text);
}

VigenereCipher::VigenereCipher(const std::string &key) : key_(key) {}

std::string VigenereCipher::encrypt(const std::string &text) {
    std::string result = text;
    int key_length = key_.length();
    int key_index = 0;

    if (key_length == 0) return result;

    for (int i = 0; i < result.length(); i++) {
        char r = result[i];
        int shift = std::tolower(key_[key_index % key_length]) - 'a';

        if (std::isupper(r)) {
            result[i] = (r - 'A' + shift) % 26 + 'A';
            key_index++;
        } else if (std::islower(r)) {
            result[i] = (r - 'a' + shift) % 26 + 'a';
            key_index++;
        }
    }

    return result;
}

std::string VigenereCipher::decrypt(const std::string &text) {
    std::string result = text;
    int key_length = key_.length();
    int key_index = 0;

    for (int i = 0; i < result.length(); i++) {
        char r = result[i];
        int shift = std::tolower(key_[key_index % key_length]) - 'a';

        if (std::isupper(r)) {
            result[i] = (r - 'A' - shift + 26) % 26 + 'A';
            key_index++;
        } else if (std::islower(r)) {
            result[i] = (r - 'a' - shift + 26) % 26 + 'a';
            key_index++;
        }
    }
    return result;
}
