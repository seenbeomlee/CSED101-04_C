#include<stdio.h>

int main(void)

{
	char a; /* ���ڿ� �����Ǵ� �ƽ�Ű�ڵ� ���� �̿��Ͽ� ���α׷��� �ϼ��Ѵ� */
	int b;

	printf("Enter an uppercase character: ");
	scanf_s("%c", &a);

	b = a + 32; /* ���ĺ� �ҹ����� �ƽ�Ű�ڵ� �ѹ� = ���ĺ� �빮���� �ƽ�Ű�ڵ� �ѹ� + 32 */

	printf("Lowercase of Entered character is %c\n", b); 
	printf("Position of '%c' in English Alphabets is %d", b, a -= 64); /* A�� �ƽ�Ű�ڵ尡 65�̰�, A�� ���ĺ� �� 1��° �̹Ƿ�, a -= 64�� ���ش�. */

	return 0;
}