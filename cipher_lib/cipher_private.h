
#ifndef ASSIGNMENT_4_CIPHER_PRIVATE_H
#define ASSIGNMENT_4_CIPHER_PRIVATE_H

//файл який бачить бібліотека під час збірки
//оголошення класів c++ та використання поліморфізму через абстрактний базовий клас Cipher

class Cipher {
public:
    virtual std::string encrypt(const std::string& text) = 0;
    virtual std::string decrypt(const std::string& text) = 0;
    virtual ~Cipher() = default;
};


class CaesarCipher : public Cipher {
    int key_;
public:
    CaesarCipher(int key);
    std::string encrypt(const std::string& text) override;
    std::string decrypt(const std::string& text) override;
};


class VigenereCipher : public Cipher {
    std::string key_;
public:
    VigenereCipher(const std::string& key);
    std::string encrypt(const std::string& text) override;
    std::string decrypt(const std::string& text) override;
};

#endif //ASSIGNMENT_4_CIPHER_PRIVATE_H
