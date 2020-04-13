#include<stdio.h>

int main(void)

{
	char a; /* 문자와 대응되는 아스키코드 값을 이용하여 프로그램을 완성한다 */
	int b;

	printf("Enter an uppercase character: ");
	scanf_s("%c", &a);

	b = a + 32; /* 알파벳 소문자의 아스키코드 넘버 = 알파벳 대문자의 아스키코드 넘버 + 32 */

	printf("Lowercase of Entered character is %c\n", b); 
	printf("Position of '%c' in English Alphabets is %d", b, a -= 64); /* A의 아스키코드가 65이고, A는 알파벳 충 1번째 이므로, a -= 64를 해준다. */

	return 0;
}