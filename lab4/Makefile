INC=/usr/local/ssl/include/
LIB=/usr/local/ssl/lib/

all :
	gcc -I$(INC) -L$(LIB) -o owb OneWayBreaker.c -lcrypto -ldl
	gcc -I$(INC) -L$(LIB) -o cfb cfb.c -lcrypto -ldl
