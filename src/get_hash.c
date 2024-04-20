#include "includes.h"

char* compute_sha256_hex(const char *input) 
{
    SHA256_CTX ctx;
    unsigned char hash[SHA256_BLOCK_SIZE];
    char *hex_str = malloc(SHA256_BLOCK_SIZE * 2 + 1);
    if (!hex_str)
        return NULL;

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

/*
The random seed is for creating an hash that
is not reversibile using John The Ripper or 
websites like crackstation.net
*/
char* get_hash(const char *input, long long seed) 
{
    char* hash1 = compute_sha256_hex(input);
    if (!hash1)
        return NULL;
    
    /* append the 10-digit seed to hash1 */
    char* hash2 = malloc(strlen(hash1) + 11);
    if (!hash2) {
        free(hash1);
        return NULL;
    }
    sprintf(hash2, "%s%lld", hash1, seed);
    free(hash1);

    char* hash3 = compute_sha256_hex(hash2);
    free(hash2);

    return hash3;
}