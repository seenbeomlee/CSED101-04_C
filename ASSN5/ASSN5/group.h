#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"player.h"

// ����ü TEAM �� �ʱ�ȭ�ϴ� �Լ� //
void putjo(TEAM* select);

/* �Է¹��� jo�� STUDENT�� ���� NODE (linked list)�� �����ϴ� �Լ�
	Enqueue�� ������ �� ����, TEAM�� count ++���ְ�, NODE -> mynum == count ���ش�. */
void linkjo(TEAM* select, STUDENT data);

/* �������� NODE�� ���� NODE�� �Է� �޾� ����� ���� NODE�� �����ϴ� �Լ��̴�*/
void removenode(TEAM* select, NODE* pPre);