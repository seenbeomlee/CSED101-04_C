#include"player.h"

void putjo(TEAM* select)
{
	select->count = 0;
	select->head = NULL;
}

void linkjo(TEAM* select, STUDENT data)
{
	select->count++;

	NODE* stu;
	NODE* temp = (NODE*)malloc(sizeof(NODE));
	temp->data = data;
	temp->mynum = select->count;
	stu = select->head;

	if (select->count == 1)
	{
		select->head = temp;
		temp->next = select->head;
	}


	else if (select->count == 2)
	{
		stu->next = temp;
		temp->next = select->head;
	}

	else
	{
		for (int i = 2; i < select->count; i++)
		{
			stu = stu->next;
		}
		stu->next = temp;
		temp->next = select->head;
	}

}

void removenode(TEAM* select, NODE* pPre)
{
	NODE* temp;

	temp = pPre->next;
	pPre->next = temp->next;

	int cc = temp->mynum;

	if (temp == select->head) // head 를 지울경우 select->head가 가르키는 주솟값도 바꿔주어야 한다.
	{
		select->head = pPre->next;
	}

	free(temp);

	NODE* temp1;

	temp1 = pPre->next;

	for (int i = 0; i < (select->count - cc); i++)
	{
		temp1->mynum--;
		temp1 = temp1->next;
	}

	select->count--;
}