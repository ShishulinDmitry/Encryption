/**
@file crypt.c
*/

#include <stdio.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include "crypt.h"
#include <unistd.h>

/**
\brief AES-256 encryption in CBC (Cipher Block Chaining) mode

Conceptual Algorithm for `encryption` Function:

1. Setup:
   - Prepare the encryption key (`encryption_key`) using the provided `key`.
   - Create a new filename by appending ".enc" to the original `filename`.
   - Open the input file (`file`) for reading and the output file (`enc_file`) for writing.
   - Generate a random Initialization Vector (IV) to ensure secure encryption.

2. Encryption:
   - Write the IV to the beginning of the output file.
   - Read the input file in blocks of `AES_BLOCK_SIZE`.
   - For each block:
     - Encrypt the block using AES-256 in CBC mode with the `encryption_key` and the IV.
     - Write the encrypted block to the output file.

3. Cleanup:
   - Close both input and output files.
   - Print a success message.

@param filename The name of the file to encrypt.
@param key The encryption key (256 bits).
*/

void encryption(const char* filename, const unsigned char* key)
{

    AES_KEY encryption_key;
    AES_set_encrypt_key(key, 256, &encryption_key);

    char* new_filename = malloc(256);
    strcpy(new_filename, filename);
    char extension[10] = ".enc\0";
    strcat(new_filename, extension);
    char* error_msg = malloc(256);
    strcpy(error_msg, "Can`t open file: ");
    
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
    {
        strcat(error_msg, filename);
        perror(error_msg);
        return;
    }

    FILE* enc_file = fopen(new_filename, "wb");
    if (!enc_file)
    {
        strcat(error_msg, new_filename);
        perror(error_msg);
        fclose(file);
        return;
    }

    unsigned char buf[AES_BLOCK_SIZE];
    unsigned char out_buf[AES_BLOCK_SIZE];

    unsigned char init_vec[AES_BLOCK_SIZE];
    if ( !RAND_bytes(init_vec, sizeof(init_vec)) )
    {
        perror("Can`t generate initializing vector");
        fclose(file);
        fclose(enc_file);
        return;
    }

    fwrite(init_vec, sizeof(init_vec), 1, enc_file);
    int r_bytes;
    while ( (r_bytes = fread(buf, 1, AES_BLOCK_SIZE, file)) > 0)
    {
        AES_cbc_encrypt(buf, out_buf, r_bytes, &encryption_key, init_vec, AES_ENCRYPT);
        fwrite(out_buf, 1, r_bytes, enc_file);
       
    }
     

    fclose(file);
    fclose(enc_file);
    printf("File encrypted successfully to %s\n", new_filename);
}


/**
  @brief AES-256 decryption in CBC (Cipher Block Chaining) mode.
  
  Conceptual Algorithm for `decryption` Function:

1. Setup:
   - Verify that the filename ends with ".enc".
   - Prepare the decryption key (`decryption_key`) using the provided `key`.
   - Create a new filename by replacing the ".enc" extension with ".dec".
   - Open the encrypted file (`file`) for reading and the output file (`dec_file`) for writing.
   - Read the Initialization Vector (IV) from the beginning of the encrypted file. 

2. Decryption:
   - Read the encrypted file in blocks of `AES_BLOCK_SIZE`.
   - For each block:
     - Decrypt the block using AES-256 in CBC mode with the `decryption_key` and the IV.
     - Write the decrypted block to the output file.

3. Cleanup:
   - Close both input and output files.
   - Print a success message.
   
  @param filename The name of the file to decrypt (must end with ".enc").
  @param key The decryption key (256 bits).
*/


void decryption(const char* filename, const unsigned char* key)
{
    AES_KEY decryption_key;
    AES_set_decrypt_key(key, 256, &decryption_key);
    
    if (strlen(filename) < 4 || strcmp(filename + strlen(filename) - 4, ".enc")) {
        printf("Error: File name does not end with '.enc'\n");
        return; // Indicate an error
    }
    
    char* new_filename = malloc(256);
    strcpy(new_filename, filename);
    char *dot = strrchr(new_filename, '.');
    if (dot != NULL) {
        strcpy(dot + 1, "dec"); 
    }
    char* error_msg = malloc(256);
    strcpy(error_msg, "Can`t open file: ");
    
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
    {
        strcat(error_msg, filename);
        perror(error_msg);
        return;
    }

    FILE* dec_file = fopen(new_filename, "wb");
    if (!dec_file)
    {
        strcat(error_msg, new_filename);
        perror(error_msg);
        fclose(file);
        return;
    }

    unsigned char buf[AES_BLOCK_SIZE];
    unsigned char out_buf[AES_BLOCK_SIZE];

    unsigned char init_vec[AES_BLOCK_SIZE];
    if ( fread(init_vec, 1, AES_BLOCK_SIZE, file) != AES_BLOCK_SIZE)
    {
        perror("Can`t read init vector");
        fclose(file);
        fclose(dec_file);
        return;
    }

    int r_bytes;
    while ( (r_bytes = fread(buf, 1, AES_BLOCK_SIZE, file)) > 0)
    {
        AES_cbc_encrypt(buf, out_buf, r_bytes, &decryption_key, init_vec, AES_DECRYPT);
        fwrite(out_buf, 1, r_bytes, dec_file);

    }
    fclose(file);
    fclose(dec_file);
    
    printf("File decrypted successfully to %s\n", new_filename);
}








