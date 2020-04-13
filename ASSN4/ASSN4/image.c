#include"image.h"

void copy_for_remove(int num_cubic, int select_image, CUBIC*** put) // �ε����� ��ĭ�� ����ִ� ������ �Ѵ�
{
	int i;

	for (i = select_image; i < num_cubic - 1; i++)
	{
		(*put)[i] = (*put)[i + 1];
	}
}

void realloc_func(int num_cubic, CUBIC*** put) // �����Լ����� num_cubic�� ���޹޾Ƽ�, realloc �� �������ش�.
{
	*put = realloc(*put, num_cubic * sizeof(CUBIC*));
}

CUBIC *image_load(FILE* input, char* name_put)
{
	char trash2;
	int channel, width, height, trash1;
	float read_num;

	CUBIC* image = (CUBIC*)malloc(sizeof(CUBIC)); // CUBIC �����Ҵ�

	strcpy(image->name, name_put); // ������ .ppm �� ���� �����ߴ� ���ڿ��� ���� image->name �� �������ش�.

	fscanf(input, "%c%d%d%d%d", &trash2, &channel, &width, &height, &trash1); // �̹����� C, W, H �� �Է¹޴´�.

	image->C = channel; image->W = width; image->H = height; image->is_normalized = 0; // CUBIC�� �����Ѵ�

	image->data = (float***)malloc(channel * sizeof(float**)); // data �����Ҵ��� �����Ѵ�.

	for (int k = 0; k < channel; k++)
	{
		image->data[k] = (float**)malloc(height * sizeof(float*));

		for (int j = 0; j < height; j++)
		{
			image->data[k][j] = (float*)malloc(width * sizeof(float));

		}
	}

	// data ���� ä���ش�

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
			for (int i = 0; i < selected_image->C; i++) // 0 ~ 255 �̿��� ���� 0 �Ǵ� 255�� �������ش�.
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


	strcpy(filter->name, name_put); // ������ .ppm�� ���� �����ߴ� ���ڿ��� ���� filter->name �� �������ش�.

	fscanf(input, "%c%d%d%d%d", &trash2, &channel, &width, &height, &trash1); // ������ C W H ���� �Է¹޴´�.

	filter->C = channel;  filter->W = width; filter->H = height; filter->is_normalized = 0;

	// k -> j -> i ��

	filter->data = (float***)malloc(channel * sizeof(float**)); // data �����Ҵ��� �����Ѵ�.

	for (int k = 0; k < channel; k++)
	{
		filter->data[k] = (float**)malloc(height * sizeof(float*));

		for (int j = 0; j < height; j++)
		{
			filter->data[k][j] = (float*)malloc(width * sizeof(float));

		}
	}

	//filter �� data ���� ä���ش�.
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

		if (put[i]->is_normalized == 1) printf(" - normalize\n"); // ����ȭ�� CUBIC�� ��� ����Ѵ�.
		else printf("\n");
	}
	// is_noramlized �����ϱ�
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
	int C_C, C_W, C_H; // image_convolutioned �� c, w, h ��
	float sum = 0;

	C_C = 3;
	C_W = (selected_image->W) - (selected_filter->W) + 1;
	C_H = (selected_image->H) - (selected_filter->H) + 1;

	// ������ǵ� CUBIC�� ���, �������� W, H�� �۾����� �ȴ�.

	CUBIC* image_convolutioned = (CUBIC*)malloc(sizeof(CUBIC)); // ������ǵ� �ڷḦ ������ ����ü �����Ҵ�

	image_convolutioned->is_normalized = selected_image->is_normalized; // ������ǵ� CUBIC�� is_normalized ���� selected_image�� isnormalized ���� �������־�� �Ѵ�.

	image_convolutioned->data = (float***)malloc(C_C * sizeof(float**)); // data �����Ҵ�

	for (k = 0; k < 3; k++)
	{
		image_convolutioned->data[k] = (float**)malloc(C_H * sizeof(float*));

		for (j = 0; j < C_H; j++)
		{
			image_convolutioned->data[k][j] = (float*)malloc(C_W * sizeof(float));

		}
	}

	image_convolutioned->C = C_C; image_convolutioned->W = C_W; image_convolutioned->H = C_H;

	// ������� ����, ������� �� CUBIC�� ũ�⸸ŭ for���� ������
	for (i = 0; i < C_C; i++)
		for (j = 0; j < C_H; j++)
			for (k = 0; k < C_W; k++)
			{
				for (jj = 0; jj < selected_filter->H; jj++) // ������� !! ������� 1ĭ�� �� ��, ������ ũ�⸸ŭ ������� ������ ���ش�.
					for (kk = 0; kk < selected_filter->W; kk++) // ������� !!
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