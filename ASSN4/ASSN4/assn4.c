#include "image.h"

int main(void)
{
	CUBIC** images = NULL;
	CUBIC** filters = NULL;
	int select_menu, select_image, select_filter; // �����ΰ� ó���� ������ image�� filter�� ���� ������ �������.
	int num_image = 0;  int num_filter = 0; // print_cubic�� �� �� ���� �����ϰ� �ִ� cubic�� ������ �˰� �־�� �Ѵ�.
	int i = 0; int j = 0; // �ܼ��� for �� ���� �� ����� ����
	char name_put[100] = { 0. }; // girl.ppm ���� girl �� ������ ����
	char temp[100] = { 0, }; // girl.ppm �� �Է¹��� ����

	while (1)
	{
		printf("\n================================\n");
		printf("I      IMAGE CONVOLUTION       I\n");
		printf("I 1. Image load                I\n");
		printf("I 2. Image save                I\n");
		printf("I 3. Image remove              I\n");
		printf("I 4. Filter load               I\n");
		printf("I 5. Filter remove             I\n");
		printf("I 6. Print                     I\n");
		printf("I 7. Normalize                 I\n");
		printf("I 8. Denormalize               I\n");
		printf("I 9. Image convolution         I\n");
		printf("I 10. Quit                     I\n");
		printf("================================\n");
		printf("Enter number: ");
		scanf("%d", &select_menu);
		
		switch (select_menu)
		{
			case 1: // image load
			{
				FILE* input;

				printf("Enter image filename: ");
				scanf("%s", &temp);

				if (!(input = fopen(temp, "r"))) // ������ �����ϴ��� üũ
				{
					printf("������ �������� �ʽ��ϴ�.\n");
					continue;
				}
			
				num_image++; // ������ �����ؼ� load�� ��������, num_image ++�� ���ش�.
				realloc_func(num_image, &images); // num_image ++ �� ���� ������ realloc �� ���ش�.
			
				i = 0;

				while (!(temp[i] == '.')) // �Է¹��� girl.ppm �߿��� girl �� �����.
					{
						name_put[i] = temp[i];
						i++;
					}

				name_put[i] = NULL;

				images[num_image - 1] = image_load(input, name_put); // images[num_image-1] �� load�� CUBIC�� �ּҸ� �ִ´�.
				
				fclose(input); // load FILE�� �������Ƿ�, input�� �ݾ��ش�.
				continue;
			}

			case 2:
			{
				print_cubic(num_image, images); // CUBIC ��� ���
				printf("Enter the number of image to save: ");
				scanf("%d", &select_image);

				if (num_image < select_image || select_image < 0) // �ε����� �߸� �Է����� �� ���� ���
				{
					printf("�ùٸ� �ε����� �Է��ϼ���.\n");
					continue;
				}
				printf("Enter filename for save image: ");
				scanf("%s", &name_put);
	
				image_save(images[select_image], name_put);
				continue;
			}

			case 3:
			{
				printf("======== IMAGE LIST ========\n");
				if (num_image > 0) print_cubic(num_image, images);
				printf("������ �̹��� �ε����� �Է��ϼ���: ");
				scanf("%d", &select_image);
				
				if (select_image < 0 || select_image > num_image) // �̹��� �ε��� �߸� �Է����� ��
				{
					printf("�ùٸ� �̹��� �ε����� �Է��ϼ���.\n");
					continue;
				}

				free_data(images[select_image]); // CUBIC ������ data �����Ҵ��� Ǯ���ش�
				free(images[select_image]); // CUBIC�� �����Ҵ��� Ǯ���ش�

				copy_for_remove(num_image, select_image, &images); // select_image���� �ε����� ��ĭ�� �����ش�.

				num_image--;
				realloc_func(num_image, &images); // num_image-- �Ǿ�����, realloc ���ֱ�

				continue;
			}

			case 4:
			{
				FILE* input;

				printf("Enter filter filename: ");
				scanf("%s", &temp);

				if (!(input = fopen(temp, "r"))) // ������ �����ϴ��� üũ�Ѵ�.
				{
					printf("������ �������� �ʽ��ϴ�.\n");
					continue;
				}

				num_filter++;
				realloc_func(num_filter, &filters); // realloc

				i = 0;

				while (!(temp[i] == '.')) // filter.ppm ���� filter�� �����Ѵ�.
				{
					name_put[i] = temp[i];
					i++;
				}

				name_put[i] = NULL;

				filters[num_filter - 1] = filter_load(input, name_put);

				fclose(input);
				continue;
			}

			case 5:
			{
				printf("======== FILTER LIST ========\n");
				if (num_filter > 0) print_cubic(num_filter, filters);
				printf("������ ���� �ε����� �Է��ϼ���: ");
				scanf("%d", &select_filter);

				if (num_filter < select_filter || select_filter < 0) // �߸��� �ε��� �Է����� ���
				{
					printf("�ùٸ� �ε����� �Է��ϼ���.\n");
					continue;
				}

				free_data(filters[select_filter]); // CUBIC ����ü ���� data �����Ҵ��� Ǯ���ش�.
				free(filters[select_filter]); // CUBIC ����ü�� �����Ҵ��� Ǯ���ش�.
	

				copy_for_remove(num_filter, select_filter, &filters); // select_filter ���� CUBIC���� �� ĭ�� ����ش�.


				num_filter--;
				realloc_func(num_filter, &filters); // CUBIC ������ ��ȭ�Ǿ����Ƿ�, realloc ���ش�.

				continue;
			}

			case 6:
			{
				printf("======== IMAGE LIST ========\n");
				if(num_image > 0) print_cubic(num_image, images); // �̹��� ��� ���
				printf("======== FILTER LIST ========\n");
				if(num_filter > 0)print_cubic(num_filter, filters); // ���� ��� ���
				continue;
			}

			case 7:
			{
				printf("======== IMAGE LIST ========\n");
				if (num_image > 0) print_cubic(num_image, images);
				printf("����ȭ �� �̹��� �ε����� �Է��ϼ���:");
				scanf("%d", &select_image);

				if (num_image < select_image || select_image < 0) // �߸��� ����� �Է����� ��
				{
					printf("�ùٸ� �ε����� �Է��ϼ���.\n");
					continue;
				}

				if (images[select_image]->is_normalized == 1) // �̹� ����ȭ�� �ε������, �����޼��� ���
				{
					printf("�̹� ����ȭ�� �ε����Դϴ�.\n");
					continue;
				}

				normalize(images[select_image]); // ����ȭ ��Ų��
				
				continue;

			}

			case 8:
			{
				printf("======== IMAGE LIST ========\n");
				if (num_image > 0) print_cubic(num_image, images);
				printf("������ȭ �� �̹��� �ε����� �Է��ϼ���:");
				scanf("%d", &select_image);

				if (num_image < select_image || select_image < 0) // �߸��� �ε����� �Է����� ��
				{
					printf("�ùٸ� �ε����� �Է��ϼ���.\n");
					continue;
				}

				if (images[select_image]->is_normalized == 0) // �̹� ������ȭ �� �ε������ �����޼��� ���
				{
					printf("�̹� ������ȭ�� �ε����Դϴ�.\n");
					continue;
				}

				denormalize(images[select_image]); // ������ȭ ���ش�

				continue;
			}
			case 9:
			{
				if (num_image < 1 || num_filter < 1) continue; // ������� �Ϸ��� �� 1�� �̻� �ʿ�

				printf("======== IMAGE LIST ========\n");
				print_cubic(num_image, images);
				printf("�̹��� �ε����� �Է��ϼ���: "); // image_filter �� �Է¹޴´�
				scanf("%d", &select_image);
				if (num_image < select_image || select_image < 0) // �ε��� �����޼��� ���
				{
					printf("�ùٸ� �ε����� �Է��ϼ���.\n");
					continue;
				}
				printf("======== FILTER LIST ========\n");
				print_cubic(num_filter, filters);
				printf("���� �ε����� �Է��ϼ���: "); // select_filter �� �Է¹޴´�
				scanf("%d", &select_filter);
				if (num_filter < select_filter || select_filter < 0) // �ε��� �����޼��� ���
				{
					printf("�ùٸ� �ε����� �Է��ϼ���.\n");
					continue;
				}
				num_image++;
				realloc_func(num_image, &images); // ��������ϸ�, �̹��� �ε��� �ϳ��� �߰��ǹǷ� realloc

				images[num_image - 1] = image_convolution(images[select_image], filters[select_filter]); // ������� ����� ��ȯ�޴´�

				if (images[num_image - 1]->is_normalized == 0) // is_normalized = 0 �� �̹����� ��������ϸ� _blur
				{
					strcpy(images[num_image - 1]->name, images[select_image]->name);
					strcat(images[num_image - 1]->name, "_blur");
				}
				else // is_normalized = 1 �� �̹����� ��������ϰ� -> denormalized �ϸ� _edge �� �Ǵϱ� �׳� �̸��� _edge�� �̸� ������.
				{
					strcpy(images[num_image - 1]->name, images[select_image]->name);
					strcat(images[num_image - 1]->name, "_edge");
				}
				continue;
			}

			case 10:
			{
				// images �� ���� free
				for (i = 0; i < num_image ; i++)
				{
				
					free_data(images[i]);
					free(images[i]);

				
				}
				if (num_image > 0)
				{
					free(images);

				}

				// filters �� ���� free
				for (j = 0; j < num_filter; j++)
				{
					free_data(filters[j]);
					free(filters[j]);

				}
				if (num_filter > 0)
				{
					free(filters);
	
				}


				return 0;
			}

			default: // ��� 1~10 �̿��� ���ڸ� �Է����� ���
			{
				printf("�ùٸ� ���� �Է����ּ���");
				continue;
			}
		}
	}

}