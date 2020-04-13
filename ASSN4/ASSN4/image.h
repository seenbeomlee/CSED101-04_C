#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
	char name[100]; // File name
	float*** data; // Pixel for CUBIC data
	int C, H, W; // C: channel, H: height, W: width
	int is_normalized; // Whether image is normalized or not

} CUBIC;


void copy_for_remove(int num_cubic, int select_image, CUBIC*** put); // �ٲ�� �� int num_cubic�� �޴´�.
	// ������ CUBIC[4]�� ����� [5] [6] [7]... �� ������ �����ش�.

void realloc_func(int num_cubic, CUBIC*** put); // main ���� num_cubic ++ Ȥ�� -- ���� ȣ��
	// ���޹��� int num_cubic�� �ν��ؼ� Realloc�� �����Ѵ�.

CUBIC* image_load(FILE* input, char* name_put); // ���ο��� realloc_func ���� ȣ��
	// FILE* input ���� ������ �а�, CUBIC�� ����� ä���� CUBIC*�� ��ȯ�Ѵ�.

void image_save(CUBIC* selsected_image, char* name_put); // main ���� scnaf(&select), scanf(&name) �޴´�.
	// FILE* output���� CUBIC* image[select] ������ "name" �̶�� ���ϸ����� �����Ѵ�.

CUBIC* filter_load(FILE* input, char* name_put); // realloc_func ���� ���ο��� ȣ���Ѵ�.
	// ���� image_load�� �����ϴ�.

void print_cubic(int num_cubic, CUBIC** put); // CUBIC�� ����� ����Ѵ�.
	// ���ڷ� �־����� CUBIC** put �� ���� image ��°� filter�� ����� ��� �� �� �ִ�

void normalize(CUBIC* image); // main �Լ����� print_func �����ϰ� normalize �� �μ��� scanf(&select) �Ѵ�.
	// CUBIC[select] -> data �� normalize �Ѵ�.

void denormalize(CUBIC* image); // normalize �Լ��� �����ϴ�.
	// CUBIC[select] -> data �� denormalize �Ѵ�.

CUBIC* image_convolution(CUBIC* selected_image, CUBIC* selected_filter);
// �����Լ����� scanf(&select1), scanf(&select2) �ϰ�, realloc_func ���� ȣ��
// ���õ� �� CUBIC[select]->data �� ���� convolution�� �����ϰ� CUBIC* ��ȯ

void free_data(CUBIC* selected); // CUBIC* ������ data �� CUBIC* �����Ҵ� ����