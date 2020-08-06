#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX_SIZE 255

/*
Written by Eddie Atkinson, far from my best work, but working(-ish)
*/

const char* ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char* encrypt();
char* decrypt(char* input, int shift);
void crack(void);
int main(int argc, char* argv[]) {
    crack();
    return 0;
}

char* encrypt() {
    char* input = malloc(sizeof(char) * MAX_SIZE);
    char* encrypted = malloc(sizeof(char) * MAX_SIZE);
    int shift;
    char* enc_ptr = encrypted;
    printf("Enter string to be encrypted: ");
    scanf("%s", input);
    printf("Enter the shift: ");
    scanf("%d", &shift);
    printf("Original string was: %s\n", input);  
    while((*input) != '\0') {
        (*enc_ptr) = (*input) + shift;
        ++enc_ptr;
        ++input; 
    }
    
    return(encrypted);
}

char* decrypt(char* input, int shift) {
    int chars = 0;
    char* decrypted = malloc(sizeof(char) * MAX_SIZE);
    char* temp_ptr = decrypted;
    char *ptr = input;
    while( (*ptr) != '\0' ) {
        char current = (*ptr);
        if(isalpha(current)) {
            (*temp_ptr) = ALPHABET[(current + (26 - shift)) % 26];
        } else {
            (*temp_ptr) = current;
        } 
        ++chars;
        ++ptr;
        ++temp_ptr;
    }
    return decrypted;
}

void crack() {
    char *input = malloc(sizeof(char) * MAX_SIZE);
    printf("Enter the string to crack: ");
    fgets(input, MAX_SIZE,  stdin);
    char* attempt;
    for(int i = 1; i < 26; ++i) {
        attempt = decrypt(input, i);
        printf("%d          %s\n", i, attempt);
        printf("\n");    
        free(attempt);
    }
}
