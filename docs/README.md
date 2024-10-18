# Encryption utility
## Description
The program implements a simple utility for encrypting and decrypting files using the AES algorithm.
## Installation
### Requirements
- CMake (2.8)
- OpenSSL
- C compiler (GCC)
### Building the project
1. Clone the repository:
git clone <URL>
2. Build (UNIX)

cd encryption

mkdir build

cd build

cmake ..

make

## Usage
### Syntax
encryption -e/d -f <filename> -p <password>
### File encryption
./encryption -e -f <input file> -p <password>
- -e: encryption option.
- -f <input_file>: file name to encrypt or decrypt
- -p <password>: password for key generation.

Example:

./encryption -e -f file  -p password

### Decrypting a file
./encryption -d -f <input file> -p <password>
- -d: decryption option.
- -f <input_file>: file name to decrypt (must have .enc extension)
- -p <password>: password for key generation.

Example:

./encryption -d -f file.enc  -p password
