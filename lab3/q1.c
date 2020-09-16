#include <stdio.h>
#include <openssl/bn.h>
#include <string.h>
#define NBITS 256

// Includes the answers for 1b, 1c

char* hex_to_string(char* num_str) {
    size_t len = strlen(num_str);
    // make return length one longer if we have an odd number of bytes
    int ret_len = len % 2 == 0 ? len + 1 : len + 2;
    char* ret_str = malloc(ret_len);
    int counter = 0;
    if(ret_str == NULL) {
        printf("Couldn't allocate memory for string, outta here\n");
        exit(EXIT_FAILURE);
    }

    if(len % 2 != 0 || len < 2) {
        printf("String too short to process or has an odd number of bytes\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i < len; i = i + 2) {
        char* temp_str = malloc(3);
        if(temp_str == NULL) {
            printf("Malloc failed\n");
            exit(EXIT_FAILURE);
        }
        temp_str[0] = num_str[i - 1];
        temp_str[1] = num_str[i];
        temp_str[2] = '\0';
        int ret = strtol(temp_str, NULL, 16);
        ret_str[counter] = ret;
        ++counter;
    }
    return ret_str;
}


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

BIGNUM* decrypt(BIGNUM* n, BIGNUM *d, BIGNUM* c, BN_CTX* ctx) { 
    BIGNUM* deciphered = BN_new();
    BN_mod_exp(deciphered, c, d, n, ctx);
    return deciphered;
}

void q1b2(BN_CTX* ctx) {
    char* msg = "4120746f702073656372657421"; 
    BIGNUM* e = BN_new();
    BIGNUM* n = BN_new();
    BIGNUM* d = BN_new();  
    BIGNUM* m = BN_new();
    BIGNUM* c = BN_new();
    BN_hex2bn(&m, msg);
    BN_hex2bn(&e, "010001");
    BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
    BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");    
    BN_mod_exp(c, m, e, n, ctx);
    printBN("Original bytes: ", m);
    m = decrypt(n, d, c, ctx); 
    printf("Ciphered bytes:");
    printBN("", c); 
    printBN("Deciphered bytes: ", m);
}

void q1b3(BN_CTX* ctx) { 
    BIGNUM* e = BN_new();
    BIGNUM* n = BN_new();
    BIGNUM* d = BN_new();  
    BIGNUM* m = BN_new();
    BIGNUM* c = BN_new();
    BN_hex2bn(&e, "010001");
    BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
    BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");    
    BN_hex2bn(&c, "8C0F971DF2F3672B28811407E2DABBE1DA0FEBBBDFC7DCB67396567EA1E2493F");
    //BN_hex2bn(&c, "24C89C26F6DA860963AF6A6CC6335ED8176A71BADF4771C7726D09E66A6BE4AB");
     m = decrypt(n, d, c, ctx);
    printBN("Deciphered message: ", m);
    
    char *number_str = BN_bn2hex(m);
    printf("%s\n", number_str);
    char* ascii_str = hex_to_string(number_str);
    printf("%s\n", ascii_str);
    free(ascii_str);    
    OPENSSL_free(number_str);
}

void q1b4(BN_CTX* ctx) {
    BIGNUM* e = BN_new();
    BIGNUM* n = BN_new();
    BIGNUM* d = BN_new();  
    BIGNUM* m_one = BN_new();
    BIGNUM* c = BN_new();
    BIGNUM *sig_one = BN_new();
    BIGNUM *sig_two = BN_new();
    BIGNUM *deciphered_one = BN_new();    
    BIGNUM *deciphered_two = BN_new();    
    BIGNUM *m_two = BN_new();
    BN_hex2bn(&e, "010001");
    BN_hex2bn(&n, "DCBFFE3E51F62E09CE7032E2677A78946A849DC4CDDE3A4D0CB81629242FB1A5");
    BN_hex2bn(&d, "74D806F9F3A62BAE331FFE3F0A68AFE35B3D2E4794148AACBC26AA381CD7D30D");    
    BN_hex2bn(&c, "8C0F971DF2F3672B28811407E2DABBE1DA0FEBBBDFC7DCB67396567EA1E2493F");
    BN_hex2bn(&m_one, "49206f776520796f75202432303030");
    BN_mod_exp(sig_one, m_one, d, n, ctx);
    BN_mod_exp(deciphered_one, sig_one, e, n, ctx);
    // printBN("original: ", m);
    BN_hex2bn(&m_two, "49206f776520796f75202433303030");
    BN_mod_exp(sig_two, m_two, d, n, ctx);
    BN_mod_exp(deciphered_two, sig_two, e, n, ctx);
    printBN("first original message:\t", m_one);
    printBN("first signature:\t", sig_one);
    printBN("first deciphered signature:\t", deciphered_one);
    printBN("second original message:\t", m_two);
    printBN("second signature:\t", sig_two);
    printBN("two deciphered signature:\t", deciphered_two);
    
}

void q1b5(BN_CTX* ctx) {
    BIGNUM* n = BN_new(); 
    BIGNUM* e = BN_new();
    BIGNUM* m = BN_new();
    BIGNUM* s = BN_new();
    BIGNUM* d_s = BN_new();
    BN_hex2bn(&m, "4c61756e63682061206d6973736c652e");
    BN_hex2bn(&e, "010001");
    BN_hex2bn(&s, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6802F");
//    BN_hex2bn(&s, "643D6F34902D9C7EC90CB0B2BCA36C47FA37165C0005CAB026C0542CBDB6803F");
    BN_hex2bn(&n, "AE1CD4DC432798D933779FBD46C6E1247F0CF1233595113AA51B450F18116115"); 
    BN_mod_exp(d_s, s, e, n, ctx); 
    printBN("Original message ", m);
    printBN("Unsigned signature: ", d_s);
    printf("Equality test: %d\n", BN_cmp(m, d_s));
    
    
}

int main(int argc, char** argv) {
    BN_CTX *ctx = BN_CTX_new();
   //q1b1(ctx);
//      q1b2(ctx);
//    q1b3(ctx);  
    q1b4(ctx);
//   q1b5(ctx);
    return(0);
}



