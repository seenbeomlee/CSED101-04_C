#include"player.h"

int getstu(FILE* input, char name[], char* gender, char dept[], int* stuid, int* jo)
{
	int ioResult;
	char name1[20];
	char name2[20];

	ioResult = fscanf(input, "%s %s\t%c\t%s\t%d\t%d", name1, name2, gender, dept, stuid, jo);

	if (ioResult != EOF)
	{
		strcat(name1, " ");
		strcat(name1, name2);

		strcpy(name, name1);
	}

	return (ioResult + 1); // EOF == -1 �̴ϱ�, ���� EOF �� ���, EOF + 1 = 0 ���� while(0)�� �� ���̴�.
}

STUDENT putstu(char name[], char gender, char dept[], int stuid, int jo)
{
	STUDENT stu;

	strcpy(stu.name, name);
	strcpy(stu.dept, dept);
	stu.gender = gender;
	stu.stuid = stuid;
	stu.jo = jo;

	return stu;
}