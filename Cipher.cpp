#include "Cipher.h"
#include <cctype>
#include <iostream>
#include <dlfcn.h>

std::string Cipher::encrypt(const std::string &text) {
    void* handle = dlopen(lib_path.c_str(), RTLD_LAZY); //відкрити динамічну бібліотеку, Run-Time Link Editor - LAZY
    if (!handle) {                                                 // завантажує файл у пам'ять, але не розбирає код функцій, поки їх не викликано
        std::cout << "Cannot open library." << std::endl;
        return text;
    }

    //auto — ключове слово C++, компілятор дивиться після = і сам визначає який тип даних має бути у змінної
    //Dynamic Library Symbol (dlsym) - йде всередину бібліотеки і знаходить точну адресу функції
    auto create_caesar = (CreateCaesarFunc)dlsym(handle, "cipher_create_caesar");
    auto create_vigenere = (CreateVigenereFunc)dlsym(handle, "cipher_create_vigenere");
    auto cipher_encrypt = (EncryptFunc)dlsym(handle, "cipher_encrypt");
    auto cipher_destroy = (DestroyFunc)dlsym(handle, "cipher_destroy");
    auto cipher_free = (FreeStrFunc)dlsym(handle, "cipher_free");

    std::string result = text;

    if (create_caesar && create_vigenere && cipher_encrypt && cipher_destroy && cipher_free) {
        cipher_t* raw_cipher = nullptr;

        if (type == 1) {
            raw_cipher = create_caesar(caesar_key); //адреса об'єкту класу Цезаря
        }else if (type == 2) {
            raw_cipher = create_vigenere(vigenere_key.c_str());
        }

        if (raw_cipher) { //якщо маємо адресу
            char* encrypted_c_row = cipher_encrypt(raw_cipher, text.c_str());
            result = std::string(encrypted_c_row);

            cipher_free(encrypted_c_row); //очистити пам'ять
            cipher_destroy(raw_cipher); //видалити об'єкт
        }
    } else {
        std::cout << "Error loading symbols from library!" << std::endl;
    }

    //Dynamic Library Close - бере handle і стирає файл libcipher.dylib з оперативної пам'яті, пам'ять стає чистою
    dlclose(handle);
    return result; //зашифрований С++ рядок
}

std::string Cipher::decrypt(const std::string &text) {
    void* handle = dlopen(lib_path.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cout << "Cannot open library." << std::endl;
        return text;
    }

    auto create_caesar = (CreateCaesarFunc)dlsym(handle, "cipher_create_caesar");
    auto create_vigenere = (CreateVigenereFunc)dlsym(handle, "cipher_create_vigenere");
    auto cipher_decrypt = (DecryptFunc)dlsym(handle, "cipher_decrypt");
    auto cipher_destroy = (DestroyFunc)dlsym(handle, "cipher_destroy");
    auto cipher_free = (FreeStrFunc)dlsym(handle, "cipher_free");

    std::string result = text;

    if (create_caesar && create_vigenere && cipher_decrypt && cipher_destroy && cipher_free) {
        cipher_t* raw_cipher = nullptr;

        if (type == 1) {
            raw_cipher = create_caesar(caesar_key);
        } else if (type == 2) {
            raw_cipher = create_vigenere(vigenere_key.c_str());
        }

        if (raw_cipher) {
            char* decrypted_c_row = cipher_decrypt(raw_cipher, text.c_str());
            result = std::string(decrypted_c_row);

            cipher_free(decrypted_c_row);
            cipher_destroy(raw_cipher);
        }
    } else {
        std::cout << "Error loading symbols from library!" << std::endl;
    }

    dlclose(handle);
    return result;
}
