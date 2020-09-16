#include <stdio.h>
#include <openssl/bn.h>
#include <string.h>
#include <openssl/sha.h>


void printBN(char *msg, BIGNUM * a) {
    char * number_str= BN_bn2hex(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}


char* getString(BIGNUM *a) {
    char* num_str = BN_bn2hex(a);
    return num_str;
}

void q13(BN_CTX* ctx) {
    BIGNUM *g = BN_new();
    BIGNUM *a = BN_new();
    BIGNUM *b = BN_new();
    BIGNUM *n = BN_new();
    BIGNUM *ga = BN_new();
    BIGNUM *gb = BN_new();

    
    BN_hex2bn(&g, "B3F");
    BN_hex2bn(&n, "26C9");
    BN_hex2bn(&a, "9");
    BN_hex2bn(&b, "6");
    
    BN_mod_exp(ga, g, a, n, ctx);
    BN_mod_exp(gb, g, b, n,  ctx);    
    printBN("G^a: ", ga);
    printBN("G^b: ", gb);

    char* ga_str = getString(ga);
    char* gb_str = getString(gb);
    char* a_str = "AE7";
    char final_string[4096];
    
    sprintf(final_string, "%s%s%s", ga_str, gb_str, a_str);
    unsigned char sha[256];
    SHA1((unsigned char* )final_string, strlen(final_string), sha);
    printf("SHA-1 digest: %s\n", sha); 
    for(int i = 0; i < 20; ++i) {
        printf("%x", sha[i]);
    }
    printf("\n");
    OPENSSL_free(ga_str);
    OPENSSL_free(gb_str);
}


int main(int argc, char* argv[]) {
    BN_CTX* ctx = BN_CTX_new();
    q13(ctx);    
}
