
#ifndef ASSIGNMENT_4_CIPHER_API_H
#define ASSIGNMENT_4_CIPHER_API_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void* cipher_t;

cipher_t* cipher_create_caesar(int key);
cipher_t* cipher_create_vigenere(const char* key);

char* cipher_encrypt(cipher_t* cipher, const char* text);
char* cipher_decrypt(cipher_t* cipher, const char* text);

void cipher_destroy(cipher_t* cipher);
void cipher_free(char* str);

#ifdef __cplusplus
}
#endif

#endif //ASSIGNMENT_4_CIPHER_API_H
