#include <stdio.h>
#include <openssl/bn.h>
#define NBITS 256



void printBN(char* msg, BIGNUM *a) {
    char *number_str = BN_bn2hex(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

void euler(BIGNUM *p, BIGNUM *q, BIGNUM *tot, BN_CTX *ctx) {
    
    BIGNUM *one = BN_new();
    BIGNUM *p2 = BN_new();
    BIGNUM *q2 = BN_new();
    BN_hex2bn(&one, "01");
    BN_sub(p2, p, one);
    BN_sub(q2, q, one);
    BN_mul(tot, p2, q2, ctx);    
}

BIGNUM* crack_d(BIGNUM *p, BIGNUM *q, BIGNUM* e, BN_CTX* ctx) {
    BIGNUM *totient = BN_new(); 
    BIGNUM *d = BN_new();
    euler(p, q, totient, ctx);
    BN_mod_inverse(d, e, totient, ctx);
    printBN("Totient is: ", totient);   
    printBN("Private key is: ", d);
    return(d);
}

void q1b1(BN_CTX* ctx) {
    
    BIGNUM *p = BN_new();
    BIGNUM *q = BN_new();
    BIGNUM *e = BN_new();
    BN_hex2bn(&p, "F7E75FDC469067FFDC4E847C51F452DF");	
    BN_hex2bn(&q, "E85CED54AF57E53E092113E62F436F4F");
    BN_hex2bn(&e, "0D88C3");    
    crack_d(p, q, e, ctx);     
}

void q1b2(BN_CTX* ctx) {
        
}

int main(int argc, char** argv) {
    BN_CTX *ctx = BN_CTX_new();
//    q1b1(ctx);
    q1b2(ctx);
    return(0);
}



