#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cryptopp/rijndael.h"
#include "../cryptopp/modes.h"

int main() {
    using namespace CryptoPP;

    // 定义密钥和明文
    byte key[16] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef, 0xfe, 0xdc, 0xba, 0x98, 0x76, 0x54, 0x32, 0x10};
    byte iv[16] = {0};
    byte plaintext[] = "Hello World!";

    // 定义加密器和加密模式（CBC）
    ECB_Mode<Rijndael>::Encryption encryptor;
    encryptor.SetKeyWithIV(key, sizeof(key), iv);

    // 加密数据
    size_t ciphertextSize = sizeof(plaintext) + Rijndael::BLOCKSIZE;
    byte *ciphertext = (byte *) malloc(ciphertextSize);
    memset(ciphertext, 0, ciphertextSize);

    encryptor.ProcessData(ciphertext, plaintext, sizeof(plaintext));

    // 打印加密结果
    printf("Plaintext:  %s\n", plaintext);
    printf("Ciphertext: ");
    for (size_t i = 0; i < ciphertextSize; ++i) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    free(ciphertext);

    return 0;
}
