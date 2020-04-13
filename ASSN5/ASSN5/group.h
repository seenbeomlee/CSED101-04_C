#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"player.h"

// 구조체 TEAM 을 초기화하는 함수 //
void putjo(TEAM* select);

/* 입력받은 jo와 STUDENT를 통해 NODE (linked list)를 생성하는 함수
	Enqueue를 실행할 때 마다, TEAM의 count ++해주고, NODE -> mynum == count 해준다. */
void linkjo(TEAM* select, STUDENT data);

/* 지우고싶은 NODE의 이전 NODE를 입력 받아 지우고 싶은 NODE를 삭제하는 함수이다*/
void removenode(TEAM* select, NODE* pPre);