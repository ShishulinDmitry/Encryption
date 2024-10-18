/**
@file main.c
*/


#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "keygen.h"
#include "crypt.h"


/**
	\brief Help function
*/

void print_help(){
    printf("encryption -e/-d -f <filename> -p <password>\n");
    printf("\t-e\tEncrypt file\n");
    printf("\t-d\tDecrypt file\n");
    printf("\t-f<filename>\t File \n");
    printf("\t-p<password>\t Password \n");
}

/**
	\brief The main function of the utility
	
	@param argc Number of arguments sent by terminal
	@param argv Array of enered arguments
*/


int main(int argc, char* argv[])
{
    int option = 0;
    char* filename = NULL;
    char *password = NULL;

    int opt;
    while( (opt = getopt(argc, argv, "edf:p:")) != -1)
    {
        switch (opt)
        {
            case 'e':
                option = 1;
                break;
            case 'd':
                option = 2;
                break;
            case 'f':
                filename = optarg;
                break;
            case 'p':
                password = optarg;
                break;
            default:
                print_help();
                exit(EXIT_FAILURE);
        }
    }

    if ( filename == NULL || password == NULL )
    {
        print_help();
        exit(EXIT_FAILURE);
    }

    unsigned char key[32];
    generate(password, key);

    if (option == 1)
    {
        encryption(filename, key);
    }
    else if (option == 2)
    {
        decryption(filename, key);
    }
    return 0;
}
