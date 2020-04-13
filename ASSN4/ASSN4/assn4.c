#include "image.h"

int main(void)
{
	CUBIC** images = NULL;
	CUBIC** filters = NULL;
	int select_menu, select_image, select_filter; // 무엇인가 처리를 실행할 image와 filter를 고르는 변수도 만들었다.
	int num_image = 0;  int num_filter = 0; // print_cubic을 할 때 현재 보유하고 있는 cubic의 개수를 알고 있어야 한다.
	int i = 0; int j = 0; // 단순히 for 문 돌릴 때 사용할 변수
	char name_put[100] = { 0. }; // girl.ppm 에서 girl 만 저장할 변수
	char temp[100] = { 0, }; // girl.ppm 을 입력받을 변수

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

				if (!(input = fopen(temp, "r"))) // 파일이 존재하는지 체크
				{
					printf("파일이 존재하지 않습니다.\n");
					continue;
				}
			
				num_image++; // 파일이 존재해서 load할 것임으로, num_image ++을 해준다.
				realloc_func(num_image, &images); // num_image ++ 된 것을 가지고 realloc 을 해준다.
			
				i = 0;

				while (!(temp[i] == '.')) // 입력받은 girl.ppm 중에서 girl 만 떼어낸다.
					{
						name_put[i] = temp[i];
						i++;
					}

				name_put[i] = NULL;

				images[num_image - 1] = image_load(input, name_put); // images[num_image-1] 에 load된 CUBIC의 주소를 넣는다.
				
				fclose(input); // load FILE이 끝났으므로, input을 닫아준다.
				continue;
			}

			case 2:
			{
				print_cubic(num_image, images); // CUBIC 목록 출력
				printf("Enter the number of image to save: ");
				scanf("%d", &select_image);

				if (num_image < select_image || select_image < 0) // 인덱스를 잘못 입력했을 때 에러 출력
				{
					printf("올바른 인덱스를 입력하세요.\n");
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
				printf("삭제할 이미지 인덱스를 입력하세요: ");
				scanf("%d", &select_image);
				
				if (select_image < 0 || select_image > num_image) // 이미지 인덱스 잘못 입력했을 때
				{
					printf("올바른 이미지 인덱스를 입력하세요.\n");
					continue;
				}

				free_data(images[select_image]); // CUBIC 내부의 data 동적할당을 풀어준다
				free(images[select_image]); // CUBIC의 동적할당을 풀어준다

				copy_for_remove(num_image, select_image, &images); // select_image이후 인덱스를 한칸씩 땡겨준다.

				num_image--;
				realloc_func(num_image, &images); // num_image-- 되었으니, realloc 해주기

				continue;
			}

			case 4:
			{
				FILE* input;

				printf("Enter filter filename: ");
				scanf("%s", &temp);

				if (!(input = fopen(temp, "r"))) // 파일이 존재하는지 체크한다.
				{
					printf("파일이 존재하지 않습니다.\n");
					continue;
				}

				num_filter++;
				realloc_func(num_filter, &filters); // realloc

				i = 0;

				while (!(temp[i] == '.')) // filter.ppm 에서 filter만 저장한다.
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
				printf("삭제할 필터 인덱스를 입력하세요: ");
				scanf("%d", &select_filter);

				if (num_filter < select_filter || select_filter < 0) // 잘못된 인덱스 입력했을 경우
				{
					printf("올바른 인덱스를 입력하세요.\n");
					continue;
				}

				free_data(filters[select_filter]); // CUBIC 구조체 내의 data 동적할당을 풀어준다.
				free(filters[select_filter]); // CUBIC 구조체의 동적할당을 풀어준다.
	

				copy_for_remove(num_filter, select_filter, &filters); // select_filter 이후 CUBIC들을 한 칸씩 당겨준다.


				num_filter--;
				realloc_func(num_filter, &filters); // CUBIC 개수가 변화되었으므로, realloc 해준다.

				continue;
			}

			case 6:
			{
				printf("======== IMAGE LIST ========\n");
				if(num_image > 0) print_cubic(num_image, images); // 이미지 목록 출력
				printf("======== FILTER LIST ========\n");
				if(num_filter > 0)print_cubic(num_filter, filters); // 필터 목록 출력
				continue;
			}

			case 7:
			{
				printf("======== IMAGE LIST ========\n");
				if (num_image > 0) print_cubic(num_image, images);
				printf("정규화 할 이미지 인덱스를 입력하세요:");
				scanf("%d", &select_image);

				if (num_image < select_image || select_image < 0) // 잘못된 목록을 입력했을 때
				{
					printf("올바른 인덱스를 입력하세요.\n");
					continue;
				}

				if (images[select_image]->is_normalized == 1) // 이미 정규화된 인덱스라면, 에러메세지 출력
				{
					printf("이미 정규화된 인덱스입니다.\n");
					continue;
				}

				normalize(images[select_image]); // 정규화 시킨다
				
				continue;

			}

			case 8:
			{
				printf("======== IMAGE LIST ========\n");
				if (num_image > 0) print_cubic(num_image, images);
				printf("역정규화 할 이미지 인덱스를 입력하세요:");
				scanf("%d", &select_image);

				if (num_image < select_image || select_image < 0) // 잘못된 인덱스를 입력했을 때
				{
					printf("올바른 인덱스를 입력하세요.\n");
					continue;
				}

				if (images[select_image]->is_normalized == 0) // 이미 역정규화 된 인덱스라면 에러메세지 출력
				{
					printf("이미 역정규화된 인덱스입니다.\n");
					continue;
				}

				denormalize(images[select_image]); // 역정규화 해준다

				continue;
			}
			case 9:
			{
				if (num_image < 1 || num_filter < 1) continue; // 컨볼루션 하려면 각 1개 이상 필요

				printf("======== IMAGE LIST ========\n");
				print_cubic(num_image, images);
				printf("이미지 인덱스를 입력하세요: "); // image_filter 를 입력받는다
				scanf("%d", &select_image);
				if (num_image < select_image || select_image < 0) // 인덱스 에러메세지 출력
				{
					printf("올바른 인덱스를 입력하세요.\n");
					continue;
				}
				printf("======== FILTER LIST ========\n");
				print_cubic(num_filter, filters);
				printf("필터 인덱스를 입력하세요: "); // select_filter 를 입력받는다
				scanf("%d", &select_filter);
				if (num_filter < select_filter || select_filter < 0) // 인덱스 에러메세지 출력
				{
					printf("올바른 인덱스를 입력하세요.\n");
					continue;
				}
				num_image++;
				realloc_func(num_image, &images); // 컨볼루션하면, 이미지 인덱스 하나가 추가되므로 realloc

				images[num_image - 1] = image_convolution(images[select_image], filters[select_filter]); // 컨볼루션 결과를 반환받는다

				if (images[num_image - 1]->is_normalized == 0) // is_normalized = 0 인 이미지를 컨볼루션하면 _blur
				{
					strcpy(images[num_image - 1]->name, images[select_image]->name);
					strcat(images[num_image - 1]->name, "_blur");
				}
				else // is_normalized = 1 인 이미지를 컨볼루션하고 -> denormalized 하면 _edge 가 되니까 그냥 이름을 _edge라 미리 지었다.
				{
					strcpy(images[num_image - 1]->name, images[select_image]->name);
					strcat(images[num_image - 1]->name, "_edge");
				}
				continue;
			}

			case 10:
			{
				// images 에 대한 free
				for (i = 0; i < num_image ; i++)
				{
				
					free_data(images[i]);
					free(images[i]);

				
				}
				if (num_image > 0)
				{
					free(images);

				}

				// filters 에 대한 free
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

			default: // 목록 1~10 이외의 숫자를 입력했을 경우
			{
				printf("올바른 값을 입력해주세요");
				continue;
			}
		}
	}

}