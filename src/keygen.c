/**
@file keygen.c
*/

#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string.h>
#include "keygen.h"

/**
@brief The function is responsible for generating a cryptographic key from a given password using the PBKDF2 (Password-Based Key Derivation Function 2) algorithm.
@param passwd The password string to derive the key from
@param key The pointer to an unsigned char array where the generated key will be stored
*/


void generate(const char* passwd, unsigned char* key)
{
    const unsigned char salt[] = "some_salt";
    int iter = 10000;
    if ( !PKCS5_PBKDF2_HMAC(passwd, strlen(passwd), salt, sizeof(salt), iter, EVP_sha256(), 32, key))
    {
        perror("Can`t generate key");
    }
}
