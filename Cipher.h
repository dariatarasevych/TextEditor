#ifndef ASSIGNMENT_4_CIPHER_H
#define ASSIGNMENT_4_CIPHER_H

#include <string>

class Cipher {
private:
    int type;
    int caesar_key;
    std::string vigenere_key;
    std::string lib_path;

    typedef void* cipher_t;

    typedef cipher_t* (*CreateCaesarFunc)(int);
    typedef cipher_t* (*CreateVigenereFunc)(const char*);
    typedef char* (*EncryptFunc)(cipher_t*, const char*);
    typedef char* (*DecryptFunc)(cipher_t*, const char*);
    typedef void (*DestroyFunc)(cipher_t*);
    typedef void (*FreeStrFunc)(char*);
public:
    Cipher(int t, int c_key, const std::string& v_key, const std::string& path = "./libcipher.dylib") : type(t), caesar_key(c_key), vigenere_key(v_key), lib_path(path) {}

    std::string encrypt(const std::string& text);
    std::string decrypt(const std::string& text);
};
#endif //ASSIGNMENT_4_CIPHER_H
