#ifndef TOTP_AES_UTILS_H
#define TOTP_AES_UTILS_H

#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <ctime>
#include <vector>
#include <string>
#include <iostream>

const std::string SHARED_SECRET = "CLAVE_SECRETA_COMPARTIDA";
const unsigned char AES_IV[16]  = {
    '0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5'
}; // IV fijo para pruebas

void handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
}

std::vector<unsigned char> derive_aes_key() {
    time_t now = std::time(nullptr);
    uint64_t timestep = now / 30; // cada 30 segundos cambia la clave

    std::cout << "[TOTP] Tiempo actual (epoch): " << now << std::endl;
    std::cout << "[TOTP] Timestep (epoch/30s): " << timestep << std::endl;

    unsigned int len = 0;
    unsigned char* key = HMAC(
        EVP_sha256(),
        SHARED_SECRET.c_str(), SHARED_SECRET.length(),
        reinterpret_cast<const unsigned char*>(&timestep), sizeof(timestep),
        nullptr, &len
    );

    std::cout << "[TOTP] Clave AES derivada (hex): ";
    for (unsigned int i = 0; i < len; i++) {
        printf("%02x", key[i]);
    }
    std::cout << std::endl;

    return std::vector<unsigned char>(key, key + 32); // 256-bit key
}

std::vector<unsigned char> aes_encrypt(const std::string& plaintext) {
    std::vector<unsigned char> key = derive_aes_key();

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    std::vector<unsigned char> ciphertext(plaintext.size() + EVP_MAX_BLOCK_LENGTH);
    int len, ciphertext_len;

    std::cout << "[AES] Texto plano: " << plaintext << std::endl;

    if (!EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key.data(), AES_IV))
        handleErrors();

    if (!EVP_EncryptUpdate(ctx, ciphertext.data(), &len, reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size()))
        handleErrors();
    ciphertext_len = len;

    if (!EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len))
        handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    ciphertext.resize(ciphertext_len);

    std::cout << "[AES] Texto cifrado (hex): ";
    for (auto c : ciphertext) {
        printf("%02x", c);
    }
    std::cout << std::endl;

    return ciphertext;
}

std::string aes_decrypt(const std::vector<unsigned char>& ciphertext) {
    std::vector<unsigned char> key = derive_aes_key();

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    std::vector<unsigned char> plaintext(ciphertext.size());
    int len, plaintext_len;

    std::cout << "[AES] Texto cifrado recibido (hex): ";
    for (auto c : ciphertext) {
        printf("%02x", c);
    }
    std::cout << std::endl;

    if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key.data(), AES_IV))
        handleErrors();

    if (!EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size()))
        handleErrors();
    plaintext_len = len;

    if (!EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len))
        handleErrors();
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    plaintext.resize(plaintext_len);

    std::string decrypted(plaintext.begin(), plaintext.end());
    std::cout << "[AES] Texto plano descifrado: " << decrypted << std::endl;

    return decrypted;
}

#endif
