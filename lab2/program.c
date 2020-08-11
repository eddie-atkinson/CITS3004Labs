//You can modify the below code to get started, or you are welcome to write from scratch

#include <openssl/evp.h>

#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <stdbool.h>

#define ENCRYP_LEN 32

char wordx[17];
char filex[17];
FILE * fp;

char engword[17];
unsigned char encryp[ENCRYP_LEN] = {
0x8d,
0x20,
0xe5,
0x05,
0x6a,
0x8d,
0x24,
0xd0,
0x46,
0x2c,
0xe7,
0x4e,
0x49,
0x04,
0xc1,
0xb5,
0x13,
0xe1,
0x0d,
0x1d,
0xf4,
0xa2,
0xef,
0x2a,
0xd4,
0x54,
0x0f,
0xae,
0x1c,
0xa0,
0xaa,
0xf9
};

void KeyGen(char * in , char * out) {
    int i = 0;
    char * temp = malloc(17);

    memcpy(temp, in , strlen( in ));
    i = strlen( in );
    while (i < 16) {
        temp[i] = 0x20;
        i++;
    }

    memcpy(out, temp, 17);

}

int do_crypt(char * outfile, unsigned char * key) {
    unsigned char outbuf[1024];
    int outlen, tmplen;
    /* Bogus key and IV: we'd normally set these from
     * another source.
     */
    //unsigned char key[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    unsigned char iv[16] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    };
    char intext[] = "This is a top secret.";
    EVP_CIPHER_CTX * ctx;
    FILE * out;

    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv);

    if (!EVP_EncryptUpdate(ctx, outbuf, & outlen, intext, strlen(intext))) {
        /* Error */
        return 0;
    }
    /* Buffer passed to EVP_EncryptFinal() must be after data just
     * encrypted to avoid overwriting it.
     */
    if (!EVP_EncryptFinal_ex(ctx, outbuf + outlen, & tmplen)) {
        /* Error */
        return 0;
    }
    outlen += tmplen;
    EVP_CIPHER_CTX_cleanup(ctx);
    /* Need binary mode for fopen because encrypted data is
     * binary data. Also cannot use strlen() on it because
     * it wont be null terminated and may contain embedded
     * nulls.
     */
    out = fopen(outfile, "wb");
    fwrite(outbuf, 1, outlen, out);
    fclose(out);
    return 1;
}

bool checkCipher(char* cipherFile) {
    bool keyFound = true;
    FILE* fstream = fopen(cipherFile, "rb");
    if(fstream == NULL ) {
        fprintf(stderr, "\n");
        exit(EXIT_FAILURE);
    }
    unsigned char cipher[ENCRYP_LEN];
    size_t read = fread(cipher, sizeof(unsigned char), ENCRYP_LEN, fstream);
    if(read < ENCRYP_LEN) {
        printf("Cipher file read error, only read %ld\n", read);
        exit(EXIT_FAILURE); 
    }
    for(int i = 0; i < ENCRYP_LEN; ++i) {
        if(memcmp(&encryp[i], &cipher[i], sizeof(encryp[i])) != 0) {
            keyFound = false;
            break;
        }
    }
    fclose(fstream);
    return keyFound;
}

int main() {
    //create the main function
    //create a char length 17 (our limit)
    //open a file containing the list of words
    //for each word, use it as a key to see if the ciphertext matches
    //once you found a word that matches the ciphertext, print
    char word[64];
    FILE * word_file = fopen("words.txt", "r");
    size_t len;
    while (fgets(word, 64, word_file) != NULL) {
        len = strlen(word);
        if (len > 17) {
            continue;
        }
        // Strip the newline character from the word if it's present
        if (word[len - 1] == '\n') {
            word[len - 1] = '\0';
        }
        --len;
        KeyGen(word, word);
        do_crypt("ciphertext.bin", word);
        if(checkCipher("ciphertext.bin") == true) {
            printf("Correct key is %s\n", word);
            break;
        }
    }
    return 0;
}