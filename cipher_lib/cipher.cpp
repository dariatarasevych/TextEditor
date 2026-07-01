#include <string>

#include "cipher_private.h"
#include "cipher_api.h"

CaesarCipher::CaesarCipher(int key) : key_(key) {
}

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


VigenereCipher::VigenereCipher(const std::string &key) : key_(key) {
}

std::string VigenereCipher::encrypt(const std::string &text) {
    std::string result = text;
    int key_length = key_.length();
    int key_index = 0;

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


#include <cstring>

#ifdef _WIN32
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __attribute__((visibility("default")))
#endif

//щоб не спотворювалися імена

extern "C" {
EXPORT cipher_t *cipher_create_caesar(int key) {
    void **holder = new void *; //виділити місце-холдер пам'яті в купі де буде зберігатися адреса алгоритму
    *holder = static_cast<void *>(new CaesarCipher(key)); //створити об'єкт класу цезаря і покласти на це місце його адресу
    return reinterpret_cast<cipher_t *>(holder); // повернути адрусу того місця-холдера
}

EXPORT cipher_t *cipher_create_vigenere(const char *key) {
    void **holder = new void *;
    *holder = static_cast<void *>(new VigenereCipher(std::string(key)));
    return reinterpret_cast<cipher_t *>(holder);
}

EXPORT char *cipher_encrypt(cipher_t *cipher, const char *text) {
    void **holder = reinterpret_cast<void **>(cipher); //бере адресу що прийшла від програми
    Cipher *obj = static_cast<Cipher *>(*holder); //відкрити холдер і взяти об'єкт шифру

    std::string res = obj->encrypt(std::string(text)); //запустити енкріпт

    return strdup(res.c_str()); // копі зашифрований текст у хіп через strdup, щоб він не стерся після виходу з методу
}

EXPORT char *cipher_decrypt(cipher_t *cipher, const char *text) {
    void **holder = reinterpret_cast<void **>(cipher);
    Cipher *obj = static_cast<Cipher *>(*holder);

    std::string res = obj->decrypt(std::string(text));
    return strdup(res.c_str());
}

EXPORT void cipher_destroy(cipher_t *cipher) {
    if (cipher) {
        void **holder = reinterpret_cast<void **>(cipher); //розпізнати вхідну адресу
        Cipher *obj = static_cast<Cipher *>(*holder); //дістати об'єкт шифру
        delete obj; //видалити об'єкт з купи
        delete holder;
    }
}

EXPORT void cipher_free(char *str) {
    std::free(str);
}
}

