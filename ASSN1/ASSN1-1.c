#include<stdio.h>

int main(void)

{
	int a, b, c, q, w, e, r, t; /* 정수형 변수 설정 */

	printf("운반 가능한 물의 양은? : ");
	scanf_s("%d", &a);

	q = a / 29; /* 처음 물의 양 q / 29 = 몫이 나올텐데, 몫이 생수통의 개수*/
	b = a % 29; /* 처음 물의 양 % 29 = 나머지가 나올텐데, 나머지가 이후 약수통, 큰 물통, 작은 물통에 나누어 담을 양*/

	w = b / 11; /* 위의 이유와 같음 */
	c = b % 11;

	e = c / 3;
	r = c % 3;

	t = (q + w + e + r) * 1000; /* t = 가격인데, 가격은 사용된 물통의 개수 x 1000 임을 표시했다. */

	printf("생수통 %d개, 약수통 %d개, 큰 물통 %d개, 작은 물통 %d개로 총 운반 비용은 %d원입니다.", q, w, e, r, t);

	return 0;
}