#ifndef AES_UTILS_H
#define AES_UTILS_H

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/aes.h>  // <-- para AES_BLOCK_SIZE
#include <string>
#include <vector>

// Inicialización correcta de clave y IV como arrays exactos sin '\0'
const unsigned char MY_AES_KEY[32] = {
  '0','1','2','3','4','5','6','7','8','9',
  '0','1','2','3','4','5','6','7','8','9',
  '0','1','2','3','4','5','6','7','8','9',
  '0','1'
};

const unsigned char MY_AES_IV[16] = {
  '0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5'
};

void handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
}

std::vector<unsigned char> aes_encrypt(const std::string& plaintext) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    std::vector<unsigned char> ciphertext(plaintext.size() + AES_BLOCK_SIZE);
    int len, ciphertext_len;

    if (!EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, MY_AES_KEY, MY_AES_IV))
        handleErrors();

    if (!EVP_EncryptUpdate(ctx, ciphertext.data(), &len, reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size()))
        handleErrors();
    ciphertext_len = len;

    if (!EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len))
        handleErrors();
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    ciphertext.resize(ciphertext_len);
    return ciphertext;
}

std::string aes_decrypt(const std::vector<unsigned char>& ciphertext) {
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    std::vector<unsigned char> plaintext(ciphertext.size());
    int len, plaintext_len;

    if (!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, MY_AES_KEY, MY_AES_IV))
        handleErrors();

    if (!EVP_DecryptUpdate(ctx, plaintext.data(), &len, ciphertext.data(), ciphertext.size()))
        handleErrors();
    plaintext_len = len;

    if (!EVP_DecryptFinal_ex(ctx, plaintext.data() + len, &len))
        handleErrors();
    plaintext_len += len;

    EVP_CIPHER_CTX_free(ctx);
    plaintext.resize(plaintext_len);
    return std::string(plaintext.begin(), plaintext.end());
}

#endif
