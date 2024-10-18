cmake_minimum_required(VERSION 2.8)
project("Ecryption")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")

include_directories(libs)

set(SOURCES
src/main.c
src/crypt.c
src/keygen.c
)

add_executable(encryption ${SOURCES})

find_package(OpenSSL REQUIRED)
target_link_libraries(encryption OpenSSL::Crypto)
