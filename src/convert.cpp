/* convert a binary/octal/hexadecimal string to decimal number.
The number should fit in 128 bits, bit/digit should be valid
0B0100 - binary, 032 - Octal, 0x34F - hesadecimal number. conversion
should be done by shifting 
Author: Ananya Jana*/

#include <stdio.h>
#include <stdlib.h>

unsigned long convert(char*);	// function to convert

int main()
{
	char ptr[130];
	printf("Enter a binary/octal/hexadecimal string:\n" );
	scanf("%s", ptr);
	printf("The string is: %s\n", ptr);
	convert(ptr);
}

unsigned long convert(char* ptr)
{
	int len = strlen(ptr);
	
	if('0' == ptr[0]){
		printf("Can be a valid number!");
		if(('b' == ptr[1]) || ('B' == ptr[1])){
			printf("A  binary number\n");
			if(len > 130){		// actual binary number's length can be maximum 128 characters + 0b/0B  = 130 
				printf("Number exceeds  128 bit limit.\n");
				exit(1);	
			}
			
		}
		else if(('x' == ptr[1])|| ('X' == ptr[1])){
			printf("A hexadecimal number\n");
			if(len > 34){		// actual hexadecimal number's length can be maximum 32chars + 0b/0B  = 34 
				printf("Number exceeds 128 bit limit.\n");
				exit(1);	
			}
		}	
		else{
			if(len > 45){		// actual octal number's length can be maximum 43 chars + 0b/0B  = 45
				printf("Number exceeds  128 bit limit.\n");
				exit(1);	
			}
			printf("An octal number\n");
		}
	}
}
