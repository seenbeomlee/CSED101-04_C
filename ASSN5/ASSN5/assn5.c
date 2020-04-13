#include"group.h"

// 입력받은 조의 player 목록을 출력하는 함수 //
void printjo(TEAM* select, int jo); // for 문을 count 번 돌리면 해당 조의 모든 플레이어를 출력할 수 있다. //

/* 해당 학번에 해당하는 학생을 찾기 위해 linked list를 탐색하는 함수이다 
	해당 학번에 해당하는 전 node를 반환해야 단반향 연결리스트에서 의미가 있다.
		주솟값 > 0 이므로, 있으면 true, 없으면 false의 역할을 할 수 있다. */
NODE* findnode(TEAM** tlist, int stuid);

// 명령어 PLAY를 구현하는 함수 안에서 FILE* input2 로 game.txt를 읽는다. //
void Fplay(TEAM** tlist);

// 게임 결과를 result_game.txt에 저장하는 함수, 1조~5조 오름차순으로 차례대로 저장한다. //
void savegame(TEAM** tlist);

int main(int argc, char* argv[])
{
	FILE* input;

	char name[20];
	char gender;
	char dept[20];
	int stuid;
	int jo;
	int i, j, q;
	int check;
	char cmd[10];
	STUDENT tempdata;
	int str_len;
	NODE* temp1;
	NODE* temp2;
	TEAM** tlist;
	tlist = (TEAM**)malloc(5 * sizeof(TEAM*));
	for (i = 0; i < 5; i++)
	{
		tlist[i] = (TEAM*)malloc(sizeof(TEAM));
	}

	for (i = 0; i < 5; i++)
	{
		putjo(tlist[i]);
	}

	if (argc == 1)
	{
		if (!(input = fopen("players.txt", "r")))
		{
			printf("Cannot open file!\n");
			return 0;
		}
	}
	
	else
	{
		if (!(input = fopen(argv[1], "r")))
		{
			printf("Cannot open file!\n");
			return 0;
		}
	}

	while (getstu(input, name, &gender, dept, &stuid, &jo))
	{
		tempdata = putstu(name, gender, dept, stuid, jo);

		linkjo(tlist[(tempdata.jo) - 1], tempdata);
	}
	fclose(input);
	for (i = 0; i < 5; i++)
	{
		printjo(tlist[i], i+1);
	}

	//

	while (1)
	{
		printf("\n>>");
		scanf("%s", &cmd);

		str_len = strlen(cmd);
		for (q = 0; q < str_len; q++)
		{
			cmd[q] = tolower(cmd[q]);
		}
		if (strcmp(cmd, "show") == 0)
		{
			printf("Which group? (0: all) ");
			scanf("%d", &jo);

			if (jo == 0)
				for (i = 0; i < 5; i++)
					printjo(tlist[i], i+1);

				else
					printjo(tlist[jo - 1], jo);
	
			continue;
		}

		else if (strcmp(cmd, "add") == 0)
		{
			printf("StudentID: ");
			scanf("%d", &stuid);
			
			char name1[20];
			char name2[20];

			temp1 = findnode(tlist, stuid);

			if (temp1 == NULL)
			{
				printf("Name: ");
				scanf("%s %s", name1, name2);
				getchar();
				printf("Gender: ");
				scanf("%c", &gender);
				getchar();
				printf("Dept: ");
				scanf("%s", dept);
				getchar();
				printf("Group: ");
				scanf("%d", &jo);

				strcat(name1, " ");
				strcat(name1, name2);
				strcpy(name, name1);

				tempdata = putstu(name, gender, dept, stuid, jo);
				linkjo(tlist[jo - 1], tempdata);
				printf("Player successfully added to group %d.\n", tempdata.jo);
			}

			else
			{
				printf("Player already exists!\n");
				printf("Name	Gender	Dept	StudentID	Group\n");
				printf("%s	%c	%s	%d	%d\n", temp1->next->data.name, temp1->next->data.gender, temp1->next->data.dept, temp1->next->data.stuid, temp1->next->data.jo);
			}


				continue;
		}

		else if (strcmp(cmd, "remove") == 0)
		{
			printf("StudentID: ");
			scanf("%d", &stuid);

			if (!(temp1 = findnode(tlist, stuid)))
				printf("Player does not exist!\n");

			else
			{
				removenode(tlist[temp1->data.jo - 1], temp1);
			}

			continue;
		}

		else if (strcmp(cmd, "play") == 0)
		{
			Fplay(tlist);
			continue;
		}

		else if (strcmp(cmd, "quit") == 0)
		{
			savegame(tlist);

			for (i = 0; i < 5; i++)
			{
				for (j = 0; j < tlist[i]->count; j++)
				{
					removenode(tlist[i], tlist[i]->head);
				}
			}

			free(tlist);

			printf("File saved. Bye!\n");

			return 0;
		}

		else continue;
	}

}

void printjo(TEAM* select, int jo)
{
	NODE* temp;
	temp = select->head;
	printf("Name	Gender	Dept	StudentID\n");
	printf("============= GROUP %d =============\n", jo);
	
	for (int i = 0; i < select->count; i++)
	{
		printf("%s	%c	%s	%d\n", temp->data.name, temp->data.gender, temp->data.dept, temp->data.stuid);
		temp = temp->next;
	}
}

NODE* findnode(TEAM** tlist, int stuid)
{
	NODE* temp;

	for (int i = 0; i < 5; i++)
	{
		temp = tlist[i]->head;

		for (int j = 0; j < tlist[i]->count; j++)
		{
			if (temp->next->data.stuid == stuid)
			{
				return temp;
			}

			else temp = temp->next;
		}
	}

	return NULL;
}

void Fplay(TEAM** tlist)
{
	FILE* input2;
	int numjo; int nummynum; int ioResult = 1;
	int i = 0;
	int aa = 0;
	char cc[20];
	int c;
	int m;

	gets(cc);

	c = strlen(cc);

	for (m = 0; m < c; m++)
	{
		cc[m] = cc[m + 1];
	}

	cc[m] = '\0';

	if (c < 3)
	{
		input2 = fopen("game.txt", "r");
	}

	else
	{
		input2 = fopen(cc, "r");
	}

	NODE* pPre;
	NODE* temp1; NODE* temp2;

	while (tlist[i]->count == 0) // (1~k)조가 비어있을 경우 k+1조의 조장이 술래다.
	{
		i++;
	}
	temp1 = tlist[i]->head;
	pPre = tlist[i]->head;

	for (int j = 1; j < tlist[i]->count; j++)
	{
		pPre = pPre->next;
	}

	pPre->next = tlist[i]->head->next;
	tlist[i]->head = pPre->next;

	printf("From					To\n");

	while (fscanf(input2, "%d %d", &numjo, &nummynum)!= EOF)
	{

		if (tlist[numjo - 1] != 0) // numjo에 해당하는 조가 비지 않은 조일 경우
		{

			while (nummynum > tlist[numjo - 1]->count)
			{
				nummynum = nummynum - tlist[numjo - 1]->count;
			}

			printf("%s (Group %d)	->	", temp1->data.name, temp1->data.jo);

			//바꾸려는 애가 head 인 경우
			if (nummynum == 1)
			{
				temp2 = tlist[numjo - 1]->head;
				pPre = tlist[numjo - 1]->head;
				for (int j = 1; j < tlist[numjo]->count; j++)
				{
					pPre = pPre->next;
				}
				temp1->next = temp2->next;
				pPre->next = temp1;
				tlist[numjo - 1]->head = temp1;
			}

			//바꾸려는 애가 head 가 아닌 경우
			else
			{
				temp2 = tlist[numjo - 1]->head;
				pPre = tlist[numjo - 1]->head;

				for (int j = 1; j < nummynum; j++)
				{
					temp2 = temp2->next;
				}

				for (int k = 1; k < (nummynum - 1); k++)
				{
					pPre = pPre->next;
				}

				temp1->next = temp2->next;
				pPre->next = temp1;
			}

			printf("%s (Group %d)\n", temp2->data.name, temp2->data.jo);
			// temp1이 술래이므로, temp1 에 temp2를 다시 넣어준다.
			temp1 = temp2;
			aa++;
		}
	}

	if (aa > 0)
	{
		printf("Game over!\n");
		printf("%s (Group %d) is out.\n", temp1->data.name, temp1->data.jo);

		removenode(tlist[(temp1->data.jo) - 1], pPre);
	}
	
	else
	{
		printf("Game over!\n");
		printf("%s (Group %d) is out.\n", temp1->data.name, temp1->data.jo);

		pPre = tlist[(temp1->data.jo) - 1]->head;
		for (int j = 1; j < tlist[(temp1->data.jo) - 1]->count; j++)
		{
			pPre = pPre->next;
		}

		removenode(tlist[(temp1->data.jo) - 1], pPre);
	}

	fclose(input2);
}

void savegame(TEAM** tlist)
{
	FILE* output;
	NODE* temp;
	output = fopen("result.txt", "w");

	for (int i = 0; i < 5; i++)
	{
		temp = tlist[i]->head;

		for (int j = 0; j < tlist[i]->count; j++)
		{
			fprintf(output, "%s	%c	%s	%d	%d\n", temp->data.name, temp->data.gender, temp->data.dept, temp->data.stuid, temp->data.jo);
			temp = temp->next;
		}
	}

	fclose(output);
}