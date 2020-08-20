#include <stdio.h>
#include <openssl/bn.h>
#include <string.h>



void printBN(char *msg, BIGNUM * a) {
    char * number_str= BN_bn2hex(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}



void q3(BN_CTX* ctx) {
    BIGNUM *n = BN_new();
    BIGNUM *e = BN_new();
    BIGNUM *p = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *c = BN_new();
    BIGNUM *m = BN_new();

    BN_hex2bn(&m, "4d65657420617420313630302e20436f6d6520616c6f6e652e");
    BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");
    BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
    BN_hex2bn(&e, "0D88C3");
    
    BN_mul(n, p, q, ctx);
    BN_mod_exp(c, m, e, n, ctx);
    printBN("ciphered text: ", c);
}


int main(int argc, char* argv[]) {
    BN_CTX* ctx = BN_CTX_new();
    q3(ctx);    
}
