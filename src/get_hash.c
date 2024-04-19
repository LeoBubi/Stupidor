#include "includes.h"

char* compute_sha256_hex(const char *input) {
    SHA256_CTX ctx;
    unsigned char hash[SHA256_BLOCK_SIZE];
    char *hex_str = malloc(SHA256_BLOCK_SIZE * 2 + 1);
    if (!hex_str) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    sha256_init(&ctx);
    sha256_update(&ctx, (const BYTE *)input, strlen(input));
    sha256_final(&ctx, hash);

    // Convert hash bytes to a hexadecimal string
    for (size_t i = 0; i < SHA256_BLOCK_SIZE; i++) {
        sprintf(hex_str + (i * 2), "%02x", hash[i]);
    }
    hex_str[SHA256_BLOCK_SIZE * 2] = '\0';

    return hex_str;
}