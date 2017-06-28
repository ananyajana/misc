/* convert a binary/octal/hexadecimal string to unsigned long long number(128 bit).
The number should fit in 128 bits, bit/digit should be valid
0B0100 - binary, 032 - Octal, 0x34F - hesadecimal number. conversion
should be done by shifting 
Author: Ananya Jana*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long convert(char*);	// function to convert
static unsigned long long convert2(char*, char*, base);

int main()
{
	char ptr[130];
	printf("Enter a binary/octal/hexadecimal string:\n" );
	scanf("%s", ptr);
	printf("The string is: %s\n", ptr);
	convert(ptr);
}

static unsigned long long convert2(char* ptr, char* endptr)
{
	int base = 0;
	
	//skip the spaces and sign
	
	//determing the base of the number which has been passed
	if('0' == ptr[0]){
		if(('b' == ptr[1]) || ('B' == ptr[1])){
			base = 2;
		}
		else if(('x' == ptr[1])|| ('X' == ptr[1])){
			base = 16;	
		}	
		else if(('0' == ptr[1])|| ('0' == ptr[1])){
			base = 8;
		}
		else{
			printf("Error!");
			exit(1);
		}
	}
	else if(isdigit(ptr[0]))
		base = 10;
		
	// if base is 2, then convert directly by shifting
	
	// for all other bases convert by the usual method: refer strtoull
}

unsigned long convert(char* ptr)
{
	int len = strlen(ptr), i = 2;
	unsigned int num;
	
	if('0' == ptr[0]){
		printf("Can be a valid number!");
		if(('b' == ptr[1]) || ('B' == ptr[1])){
			printf("A  binary number\n");
			if(len > 130){		// actual binary number's length can be maximum 128 characters + 0b/0B  = 130 
				printf("Number exceeds  128 bit limit.\n");
				exit(1);	
			}
			num = 0;
			for(;i < len && ptr[i]; ++i){
				num = num << 1;
				if(ptr[i] == '1')
					num = num | 0x01;
				else if(ptr[i] == '0')
					num = num | 0x00;
				else{
					printf("Error! only valid binary digits are 0 and 1.\n");
					exit(1);
				}	
				printf("%d th iteration.\n", i);
			}
			printf("The number is: %u", num);
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
