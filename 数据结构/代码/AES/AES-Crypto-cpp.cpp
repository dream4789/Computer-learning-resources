//
// Created by xulon on 2023/6/25.
//
#include <iostream>
#include <string>
#include "../cryptopp/modes.h"
#include "../cryptopp/aes.h"
#include "../cryptopp/filters.h"

using namespace CryptoPP;

int main() {

    // ���ĺ���Կ
    std::string plaintext = "0123456789abcdef";
    std::string key = "abcdefghijklmnop";

    // ��ʾ���ĺ���Կ
    std::cout << "Plaintext: " << plaintext << std::endl;
    std::cout << "Key: " << key << std::endl;

    // byte iv[AES::DEFAULT_BLOCKSIZE] = {0};
    byte iv[CryptoPP::Rijndael::BLOCKSIZE] = {0};

    try {
        // ���ܹ���
        CBC_Mode<AES>::Encryption encryption((byte *) key.c_str(), key.length(), iv);
        StringSource(plaintext, true,
                     new StreamTransformationFilter(encryption,
                                                    new StringSink(plaintext)
                     )
        );
        std::cout << "Encrypted: " << plaintext << std::endl;

        // ���ܹ���
        CBC_Mode<AES>::Decryption decryption((byte *) key.c_str(), key.length(), iv);
        StringSource(plaintext, true,
                     new StreamTransformationFilter(decryption,
                                                    new StringSink(plaintext)
                     )
        );
        std::cout << "Decrypted: " << plaintext << std::endl;
    }
    catch (const Exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
