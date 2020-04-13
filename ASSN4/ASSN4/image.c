#include"image.h"

void copy_for_remove(int num_cubic, int select_image, CUBIC*** put) // 인덱스를 한칸씩 당겨주는 역할을 한다
{
	int i;

	for (i = select_image; i < num_cubic - 1; i++)
	{
		(*put)[i] = (*put)[i + 1];
	}
}

void realloc_func(int num_cubic, CUBIC*** put) // 메인함수에서 num_cubic을 전달받아서, realloc 을 진행해준다.
{
	*put = realloc(*put, num_cubic * sizeof(CUBIC*));
}

CUBIC *image_load(FILE* input, char* name_put)
{
	char trash2;
	int channel, width, height, trash1;
	float read_num;

	CUBIC* image = (CUBIC*)malloc(sizeof(CUBIC)); // CUBIC 동적할당

	strcpy(image->name, name_put); // 이전에 .ppm 을 빼고 저장했던 문자열을 통해 image->name 을 저장해준다.

	fscanf(input, "%c%d%d%d%d", &trash2, &channel, &width, &height, &trash1); // 이미지의 C, W, H 를 입력받는다.

	image->C = channel; image->W = width; image->H = height; image->is_normalized = 0; // CUBIC에 저장한다

	image->data = (float***)malloc(channel * sizeof(float**)); // data 동적할당을 진행한다.

	for (int k = 0; k < channel; k++)
	{
		image->data[k] = (float**)malloc(height * sizeof(float*));

		for (int j = 0; j < height; j++)
		{
			image->data[k][j] = (float*)malloc(width * sizeof(float));

		}
	}

	// data 값을 채워준다

	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
			for (int k = 0; k < channel; k++)
			{
				fscanf(input, "%f", &read_num);
				image->data[k][j][i] = read_num;
			}

	return image;
}

void image_save(CUBIC* selected_image, char* name)
{
	FILE* output;
	output = fopen(name, "w");

	fprintf(output, "%c%d %d %d %d\n", 'P', selected_image->C, selected_image->W, selected_image->H, 255);
	for (int k = 0; k < selected_image->H; k++)
		for (int j = 0; j < selected_image->W; j++)
			for (int i = 0; i < selected_image->C; i++) // 0 ~ 255 이외의 값은 0 또는 255로 저장해준다.
			{
				if (selected_image->data[i][k][j] < 0) selected_image->data[i][k][j] = 0;
				if (selected_image->data[i][k][j] > 255) selected_image->data[i][k][j] = 255;
				fprintf(output, "%d ", (int)selected_image->data[i][k][j]);
			}
	fclose(output);
}

CUBIC* filter_load(FILE* input, char* name_put)
{
	char trash2;
	int channel, width, height, trash1;
	float read_num;

	CUBIC* filter = (CUBIC*)malloc(sizeof(CUBIC));


	strcpy(filter->name, name_put); // 이전에 .ppm을 빼고 저장했던 문자열을 통해 filter->name 을 저장해준다.

	fscanf(input, "%c%d%d%d%d", &trash2, &channel, &width, &height, &trash1); // 필터의 C W H 값을 입력받는다.

	filter->C = channel;  filter->W = width; filter->H = height; filter->is_normalized = 0;

	// k -> j -> i 순

	filter->data = (float***)malloc(channel * sizeof(float**)); // data 동적할당을 시행한다.

	for (int k = 0; k < channel; k++)
	{
		filter->data[k] = (float**)malloc(height * sizeof(float*));

		for (int j = 0; j < height; j++)
		{
			filter->data[k][j] = (float*)malloc(width * sizeof(float));

		}
	}

	//filter 의 data 값을 채워준다.
	for (int j = 0; j < height; j++)
		for (int i = 0; i < width; i++)
			for (int k = 0; k < channel; k++)
			{
				fscanf(input, "%f", &read_num);
				filter->data[k][j][i] = read_num;
			}

	return filter;

}

void print_cubic(int num_cubic, CUBIC** put)
{
	int i;
	char nor[10] = "normalize";

	for (i = 0; i < num_cubic; i++)
	{
		printf("%d. %s [H: %d, W: %d, C: %d] ", i, (put[i])->name, (put[i])->H, (put[i])->W, (put[i])->C);

		if (put[i]->is_normalized == 1) printf(" - normalize\n"); // 정규화된 CUBIC인 경우 출력한다.
		else printf("\n");
	}
	// is_noramlized 보충하기
}

void normalize(CUBIC* image)
{
	int i, j, k;

	for (i = 0; i < image->H; i++)
		for (j = 0; j < image->W; j++)
			for (k = 0; k < image->C; k++)
				image->data[k][i][j] = (image->data[k][i][j] / (float)128) - 1;

	image->is_normalized = 1;

}

void denormalize(CUBIC* image)
{
	int i, j, k;

	for (i = 0; i < image->H; i++)
		for (j = 0; j < image->W; j++)
			for (k = 0; k < image->C; k++)
				image->data[k][i][j] = (image->data[k][i][j] + 1) * (float)128;

	image->is_normalized = 0;
}

CUBIC* image_convolution(CUBIC* selected_image, CUBIC* selected_filter)
{
	int i, j, k, jj, kk;
	int f_w = 0; int f_h = 0;
	int C_C, C_W, C_H; // image_convolutioned 의 c, w, h 값
	float sum = 0;

	C_C = 3;
	C_W = (selected_image->W) - (selected_filter->W) + 1;
	C_H = (selected_image->H) - (selected_filter->H) + 1;

	// 컨볼루션된 CUBIC의 경우, 기존보다 W, H가 작아지게 된다.

	CUBIC* image_convolutioned = (CUBIC*)malloc(sizeof(CUBIC)); // 컨볼루션된 자료를 저장할 구조체 동적할당

	image_convolutioned->is_normalized = selected_image->is_normalized; // 컨볼루션된 CUBIC의 is_normalized 값에 selected_image의 isnormalized 값을 복사해주어야 한다.

	image_convolutioned->data = (float***)malloc(C_C * sizeof(float**)); // data 동적할당

	for (k = 0; k < 3; k++)
	{
		image_convolutioned->data[k] = (float**)malloc(C_H * sizeof(float*));

		for (j = 0; j < C_H; j++)
		{
			image_convolutioned->data[k][j] = (float*)malloc(C_W * sizeof(float));

		}
	}

	image_convolutioned->C = C_C; image_convolutioned->W = C_W; image_convolutioned->H = C_H;

	// 컨볼루션 진행, 컨볼루션 된 CUBIC의 크기만큼 for문을 돌린다
	for (i = 0; i < C_C; i++)
		for (j = 0; j < C_H; j++)
			for (k = 0; k < C_W; k++)
			{
				for (jj = 0; jj < selected_filter->H; jj++) // 컨볼루션 !! 컨볼루션 1칸을 할 때, 필터의 크기만큼 컨볼루션 연산을 해준다.
					for (kk = 0; kk < selected_filter->W; kk++) // 컨볼루션 !!
					{

						sum += ((selected_image->data[i][j + jj][k + kk]) * (selected_filter->data[0][jj][kk]));
					}

				image_convolutioned->data[i][j][k] = sum;
				sum = 0;
			}

	return image_convolutioned;
}

void free_data(CUBIC* selected)
{
	int i, j;

	for (i = 0; i < selected->C; i++)
	{
		for (j = 0; j < selected->H; j++)
		{
			free(selected->data[i][j]);

		}

		free(selected->data[i]);

	}

	free(selected->data);

}