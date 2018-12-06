#include "DES.h"
#include <iostream>


int main() {
    string plaintext, des_key;
    printf("->Please input the plaintext:");
    cin >> plaintext;
    printf("->Please input the key      :");
    cin >> des_key;

    DES_Algorithm des_cryption;
    string ciphertext = des_cryption.des_encryption_process(plaintext,  des_key);
    string eplaintext = des_cryption.des_decryption_process(ciphertext, des_key);
    printf("->Original plaintext:\t%s\n", plaintext.c_str());
    printf("->The ciphertext:\t%s\n", ciphertext.c_str());
    printf("->Eplaintext:\t\t%s\n", eplaintext.c_str());
    if (plaintext == eplaintext) {
        printf("->This algorithm is right!\n");
    }
    else {
        printf("->This algorithm is wrong!\n");
    }

    return 0;
}