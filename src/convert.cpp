/* convert a binary/octal/hexadecimal string to unsigned long long number(128 bit).
The number should fit in 128 bits, bit/digit should be valid
0B0100 - binary, 0032 - Octal, 0x34F - hesadecimal number. conversion
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
	unsigned char c;
	int base, size, count;
	const char *s;
	unsigned int num;	// the variable to hold the final decimal value
	base = size = count = 0;
	bool converted = true;

	//skip the spaces
	s = ptr;
	do{
		c = *s++;
	}while(isspace((unsigned char)c));
	
	//check for signs, -ve numbers are not allowed, +ve sign can be skipped
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
		if(('b' == *s) || ('B' == *s)){	//if the first two characters are 0b/0B then the base is 2
			base = 2;
		}
		else if(('x' == *s)|| ('X' == *s)){	//if the first two characters are 0x/0X then the base is 16
			base = 16;
		}	
		else if(('0' == *s)|| ('0' == *s)){	//if the first two characters are 00 then the base is 8
			base = 8;
		}
		else{
			printf("Error!");
			exit(1);
		}
		c = s[1];
		s += 2;		// we have deterrmined the base from the first two characters, so move the pointer.
	}
	else if(isdigit(c)){
		base = 10;
		s += 1;
	}
	
	size = sizeof(unsigned long long)*8;
	// if base is 2, then convert directly by shifting
	if(base == 2){
		num = 0;	// the number is initialized to 0
		for(; c != '\0' && count < size; c = *s++){
			++count;
			num = num << 1;	// shift number to the left by 1 bit so that the new bit can be added
			if(c == '1')	
				num = num | 0x01;	// if the current chacter is '1' then perform bitwise OR of the number and 0x01
			else if(c == '0')
				num = num | 0x00;	// if the current chacter is '0' then perform bitwise OR of the number and 0x00
			else{
				printf("Error! only valid binary digits are 0 and 1.\n");
				break;
			}	
		}
		printf("The number is: %u", num);
	}
	else if(base == 16){	// if base is 16, then capture each hexadecimal digit in c. Since each hexadecimal digit is of 4bits, but the unsigned character is of 8 bits, c will look like 0000XXXX where X is a binary number
		num = 0;	// the number is initialized to 0
		for ( ; ; c = *s++) {	// get the character from the input string
			if (c >= '0' && c <= '9')	// convert the character to integer
				c -= '0';
			else if (c >= 'A' && c <= 'F')
				c -= 'A' - 10;
			else if (c >= 'a' && c <= 'f')
				c -= 'a' - 10;
			else
				break;
	
			// since the least significant nibble holds the actual value, we use bitwise OR and bitwise SHIFT operations and the pattern 0x08 to get those 4 bits in num 
			for(int j = 0; j < 4 && count < size; ++j){
				count++;
				num = num << 1;
				if((c & 0x08) == 0x08)
					num = num | 0x01;
				else if((c & 0x08) == 0)
					num = num | 0x00;
				else{
					printf("Error! only valid binary digits are 0 and 1.\n");
					exit(1);
				}
				c = c << 1;
			}
		}
		printf("The number is: %u", num);
	}	
	else if(base == 8){		// if base is 8, then capture each octal digit in c. Since each octal digit is of 3bits, but the unsigned character is of 8 bits, c will look like 00000XXX where X is a binary number
		num = 0;
		for ( ; ; c = *s++) {
			if (c >= '0' && c <= '7')
				c -= '0';
			else
				break;
				
			// since the least 3 bits hold the actual value, we use bitwise OR and bitwise SHIFT operations and the pattern 0x04 to get those 43bits in num
			for(int j = 0; j < 3 && count < size; ++j){
				count++;
				num = num << 1;
				if((c & 0x04) == 0x04)
					num = num | 0x01;
				else if((c & 0x04) == 0)
					num = num | 0x00;
				else{
					printf("Error! only valid binary digits are 0 and 1.\n");
					exit(1);
				}
				c = c << 1;
			}
		}
		printf("The number is: %u", num);
	}
	
	if(count >= size){
		printf("Overflow!!\n");
		converted = false;
	}
	
	if(endptr != NULL)
		endptr = (converted? s - 1:ptr);
}
