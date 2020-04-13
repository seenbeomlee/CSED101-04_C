#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct
{
	char name[20];
	char gender;
	char dept[20];
	int stuid;
	int jo;
}STUDENT;

typedef struct node
{
	STUDENT data;
	int mynum; // 해당 조에서 head = 1번, 그 이후로부터 2번, 3번, ... //
	struct node* next;
}NODE;

typedef struct
{
	int count;
	NODE* head;
}TEAM;

// players.txt 에서 이름, 성별, 학과, 학번, 조를 콜바이 어드레스로 읽어오는 함수 //
int getstu(FILE* input, char name[], char* gender, char dept[], int* stuid, int* jo);

// 읽어온 STUDENT 신상으로 채운 STUDENT를 반환하는 함수 //
STUDENT putstu(char name[], char gender, char dept[], int stuid, int jo);
