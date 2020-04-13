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
	int mynum; // �ش� ������ head = 1��, �� ���ķκ��� 2��, 3��, ... //
	struct node* next;
}NODE;

typedef struct
{
	int count;
	NODE* head;
}TEAM;

// players.txt ���� �̸�, ����, �а�, �й�, ���� �ݹ��� ��巹���� �о���� �Լ� //
int getstu(FILE* input, char name[], char* gender, char dept[], int* stuid, int* jo);

// �о�� STUDENT �Ż����� ä�� STUDENT�� ��ȯ�ϴ� �Լ� //
STUDENT putstu(char name[], char gender, char dept[], int stuid, int jo);
