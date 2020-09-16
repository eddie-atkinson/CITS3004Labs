FLAGS= -Werror -Wall -fno-stack-protector -z execstack

all:	
	gcc $(FLAGS) -o call_shellcode call_shellcode.c
	gcc $(FLAGS) -o test test.c
