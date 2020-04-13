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


void copy_for_remove(int num_cubic, int select_image, CUBIC*** put); // 바뀌기 전 int num_cubic을 받는다.
	// 임의의 CUBIC[4]를 지우면 [5] [6] [7]... 을 앞으로 땡겨준다.

void realloc_func(int num_cubic, CUBIC*** put); // main 에서 num_cubic ++ 혹은 -- 이후 호출
	// 전달받은 int num_cubic을 인식해서 Realloc을 진행한다.

CUBIC* image_load(FILE* input, char* name_put); // 메인에서 realloc_func 이후 호출
	// FILE* input 으로 파일을 읽고, CUBIC의 멤버를 채워서 CUBIC*을 반환한다.

void image_save(CUBIC* selsected_image, char* name_put); // main 에서 scnaf(&select), scanf(&name) 받는다.
	// FILE* output으로 CUBIC* image[select] 내용을 "name" 이라는 파일명으로 저장한다.

CUBIC* filter_load(FILE* input, char* name_put); // realloc_func 이후 메인에서 호출한다.
	// 위의 image_load와 동일하다.

void print_cubic(int num_cubic, CUBIC** put); // CUBIC의 목록을 출력한다.
	// 인자로 주어지는 CUBIC** put 에 따라서 image 출력과 filter의 출력을 모두 할 수 있다

void normalize(CUBIC* image); // main 함수에서 print_func 진행하고 normalize 할 인수를 scanf(&select) 한다.
	// CUBIC[select] -> data 를 normalize 한다.

void denormalize(CUBIC* image); // normalize 함수와 동일하다.
	// CUBIC[select] -> data 를 denormalize 한다.

CUBIC* image_convolution(CUBIC* selected_image, CUBIC* selected_filter);
// 메인함수에서 scanf(&select1), scanf(&select2) 하고, realloc_func 이후 호출
// 선택된 두 CUBIC[select]->data 를 통해 convolution을 진행하고 CUBIC* 반환

void free_data(CUBIC* selected); // CUBIC* 내부의 data 및 CUBIC* 동적할당 해제