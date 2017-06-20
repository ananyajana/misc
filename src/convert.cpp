/* convert a binary/octal/hexadecimal string to decimal number.
The number should fit in 128 bits, bit/digit should be valid
0B0100 - binary, 032 - Octal, 0x34F - hesadecimal number. conversion
should be done by shifting */

#include <stdio.h>

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
	if('0' == ptr[0]){
		printf("Can be a valid number!");
		if(('b' == ptr[1]) || ('B' == ptr[1]))
			printf("A  binary number\n");
		else if(('x' == ptr[1])|| ('X' == ptr[1]))
			printf("A hexadecimal number\n");
		else
			printf("A octal number\n");
	}
}
