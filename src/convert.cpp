/* convert a binary/octal/hexadecimal string to unsigned long long number(128 bit).
The number should fit in 128 bits, bit/digit should be valid
0B0100 - binary, 032 - Octal, 0x34F - hesadecimal number. conversion
should be done by shifting 
Author: Ananya Jana*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static unsigned long long convert(char*, char*);	// function to convert

int main()
{
	char ptr[130];
	printf("Enter a binary/octal/hexadecimal string:\n" );
	scanf("%s", ptr);
	printf("The string is: %s\n", ptr);
	convert(ptr, NULL);
}

static unsigned long long convert(char* ptr, char* endptr)
{
	char c;
	int base = 0;
	const char *s;
	unsigned int num;
	

	//skip the spaces
	s = ptr;
	do{
		c = *s++;
	}while(isspace((unsigned char)c));
	
	if (c == '-') {
		printf("Negative number is not allowed.\n");
		exit(1);
	}
	else {
		if (c == '+')
			c = *s++;	
	}
	
	//determing the base of the number which has been passed
	if('0' == c){
		if(('b' == *s) || ('B' == *s)){
			base = 2;
		}
		else if(('x' == *s)|| ('X' == *s)){
			base = 16;
		}	
		else if(('0' == *s)|| ('0' == *s)){
			base = 8;
		}
		else{
			printf("Error!");
			exit(1);
		}
		c = s[1];
		s += 2;
	}
	else if(isdigit(c)){
		base = 10;
		s += 1;
	}
	
	// if base is 2, then convert directly by shifting
	if(base == 2){
		num = 0;
		for(; c != '\0'; c = *s++){
			num = num << 1;
			if(c == '1')
				num = num | 0x01;
			else if(c == '0')
				num = num | 0x00;
			else{
				printf("Error! only valid binary digits are 0 and 1.\n");
				exit(1);
			}	
		}
		printf("The number is: %u", num);
	}
	
	// for all other bases convert by the usual method: refer strtoull
}
