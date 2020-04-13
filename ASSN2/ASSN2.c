#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>

#define FLUSH while(getchar()!= '\n'); // ���۸� ����� ����

void print_tutorial(void);
int show_menu(void);
void game_start(int gamenum, int comscore, int userscore);
int get_user_card(int gamenum, int comscore, int userscore, int draw, int a);
void show_table(int draw, int a);
int get_computer_card(int a);
int compare_card(int a, int usercard1, int comcard);
int calc_score(int a, int next);

int main(void)
{
	int aa;
	while (1)
	{
		int gamenum = 0;
		int comscore = 0;
		int userscore = 0; 
		//���� �޴��� ���ƿԴٴ� ����, ����Ƚ��, ��ǻ�� ����, ���� ������ ��� �ʱ�ȭ �Ǿ����� �ǹ�.
		aa = show_menu(); 

			if (aa == 1)
			{
				system("cls");
				print_tutorial();
			}
			else if (aa == 2)
			{
				system("cls");
				game_start(gamenum, comscore, userscore);
			}
			else
			{
				printf("���α׷��� �����մϴ�...");
				return 0;
			}
	}
}

int show_menu(void) // 1,2,3 �� �Է¹޾� ��ȯ�Ѵ�.
{
	int startnumber;
	while (1)
	{
		printf("\n************ E - Card ************\n\n");
		printf("           1. ���� ����\n\n");
		printf("           2. ���� ����\n\n");
		printf("           3. ���� ����\n\n");
		printf("**********************************\n\n");
		printf("�Է�: ");
		scanf("%d", &startnumber);

		switch (startnumber)
		{
		case 1:
			return 1;
		case 2:
			return 2;
		case 3:
			return 3;
		default:
			{
				printf("�ùٸ� �޴��� �����ϼ���...\n");
				Sleep(1000);
				system("cls");
			}
		}
	}
}

void print_tutorial(void)
{
	char cc;
	while(1)
	{
		printf("************* E - Card ���� ���� *******************************************\n\n");
		printf(" �� ������ ���ڹ��÷� ī������ E-Card ������ ������� �Ѵ�.\n\n");
		printf(" 1. �� �÷��̾�� Ȳ���п� �뿹�� �� �ϳ��� �и� ���� �����Ѵ�.\n");
		printf("    Ȳ���� = Ȳ�� ī�� 1�� + �ù� ī�� 4��\n");
		printf("    �뿹�� = �뿹 ī�� 1�� + �ù� ī�� 4��\n");
		printf("2. �� ����ڴ� �� �ϸ��� �� ���� ī�带 �Ⱥ��̰� ���а�, �Բ� �����´�.\n\n");
		printf("3. �Ʒ��� ī�� �� �� ���迡 ���� ���и� �����Ѵ�.\n");
		printf("��, �� �÷��̾ �ù� ī�带 �´ٸ�, ���ºη� ó���Ѵ�.\n\n");
		printf("4. ���о��� ī��� �Ҹ�ǰ� ���а� ������ ������ 2�� ���ư� �ݺ��Ѵ�.\n\n");
		printf(" �󼺰��� : Ȳ�� > �ù� > �뿹 > Ȳ��\n\n");
		printf("****************************************************************************\n");
		printf("�޴��� ���ư����� EnterŰ�� �Է��ϼ���...");
		FLUSH;
		scanf("%c", &cc); // ���� �̿��� ���� �Է��ϸ� �ȵ�
		
		if (cc == 10)
		{
			system("cls");
			break;
		}
		else
		{
			system("cls");
			continue;
		}
	}
}

void game_start(int gamenum, int comscore, int userscore)
{
	while (1)
	{
		int a = 0; // a�� �÷��̾ 0(Ȳ����), 1(�뿹��) �� ������ �޾Ҵ����� ����
		int draw = 0; // game_start�� �Դٴ� ��, ���а� ���� draw�� 0���� �ʱ�ȭ �Ǿ��ٴ� ��
		gamenum += 1; // ���а� ���� ���⿡ �Դٴ� ��, ����Ƚ���� �߰��� ��
		int for_user = 0; // �� �ǿ��� ������ �޾Ҵ� ������ �ٽ� �ʱ�ȭ
		int wannagame = 0; // wannagame = 0 �̸� while �� ���, =1 �̸� ���� ����
		char nNyY, bb, bbb; // ��Ÿ ���͸� ���� �� ����� ����
		int next = 0; // �÷��̾ �� �ǿ��� �̰����(1) ������(2)�� �Է¹޴� ����
		int usercard1 = 0; // ó�� �÷��̾��� ī�带 �Է� �ޱ� ���� �ʱ�ȭ
		int comcard = 0; // ó�� ��ǻ���� ī�带 �Է� �ޱ� ���� �ʱ�ȭ
		

		while (1)
		{
			printf("\n[����Ƚ��: %d, ��ǻ��: %d��, ��: %d��]\n\n", gamenum, comscore, userscore);
			printf("\n[ī�� �� ����]\n");
			printf("**********************************\n\n");
			printf(" 0. Ȳ���� (Ȳ�� 1��, �ù� 4��)\n\n");
			printf(" 1. �뿹�� (�뿹 1��, �ù� 4��)\n\n");
			printf("**********************************\n");
			printf("�Է�: ");
			FLUSH;
			scanf_s("%d", &a);
		
			if (a == 0 || a == 1) break;
			else
			{
				printf("�ùٸ� �޴��� �����ϼ���...\n");
				Sleep(1000);
				system("cls");
			}
		}
		
		while (1) // ���ºΰ� ���� ��, draw += 1; �ϰ� �ݺ��ؼ� ������ �ٽ� �����ؾ� �Ѵ�.
		{
			system("cls");
			usercard1 = get_user_card(gamenum, comscore, userscore, draw, a);
			comcard = get_computer_card(a); // a�� ���� ������ Ȳ����, �뿹�� �� �� ������� ��
			next = compare_card(a, usercard1, comcard);
			
			printf("\n\n[���� ���]\n");
			printf("******************\n\n");
			if (a == 0)
			{
				if (usercard1==0) printf(" * ���� ī��     : Ȳ��\n\n");
				else printf(" * ���� ī��     : �ù�\n\n");

				if (comcard==2) printf(" * ��ǻ���� ī�� : �뿹\n\n");
				else printf(" * ��ǻ���� ī�� : �ù�\n\n");
			}
			else
			{
				if (usercard1==0) printf(" * ���� ī��     : �뿹\n\n");
				else printf(" * ���� ī��     : �ù�\n\n");

				if (comcard==2) printf(" * ��ǻ���� ī�� : Ȳ��\n\n");
				else printf(" * ��ǻ���� ī�� : �ù�\n\n");
			}

			if (next == 1) printf(" * ���: �¸�\n\n");
			else if (next == 2) printf(" * ���: �й�\n\n");
			else printf(" * ���: ���º�\n\n");
			printf("******************\n\n");

			if (next == 1 || next == 2) break;
			else
			{
				draw += 1; // ���º��� ��� next = 0 �̹Ƿ�, �ٽ� while �� ����
				printf("���� �� (EnterŰ�� �Է��ϼ���...)");
				FLUSH;
				scanf_s("%c", &bb);
				continue;
			}
		}

		for_user = calc_score(a, next);

		switch (for_user)
		{
		case 200:
		{
			comscore += -300;
			userscore += 200;
			break;
		}
		case -500:
		{
			comscore += 700;
			userscore += -500;
			break;
		}
		case 700:
		{
			comscore += -500;
			userscore += 700;
			break;
		}
		default: // case -300
		{
			comscore += 200;
			userscore += -300;
			break;
		}
		}

		printf("[���� ����]\n");
		printf("******************\n\n");
		printf(" * ���� ����    : %d\n\n", userscore);
		printf(" * ��ǻ���� ����: %d\n\n", comscore);
		printf("******************\n\n");

		if (comscore >= 2000)
		{
			printf("[���� ���]\n");
			printf("*****************\n\n");
			printf(" * ����� �й� !\n\n");
			printf("*****************\n\n");
			printf("EnterŰ�� �Է��ϼ���...");
			FLUSH;
			scanf_s("%c", &bbb);
			wannagame = 1;
		}
	
		else if (userscore >= 2000)
		{
			printf("[���� ���]\n");
			printf("*****************\n\n");
			printf(" * ����� �¸� !\n\n");
			printf("*****************\n\n");
			printf("EnterŰ�� �Է��ϼ���...");
			scanf_s("%c", &bbb);
			FLUSH;
			wannagame = 1;
		}

		else
		{
			printf("������ ����ϰڽ��ϱ�? (y/n): ");
			FLUSH;
			scanf_s("%c", &nNyY);

			if (nNyY == 'y'|| nNyY == 'Y')
			{
				wannagame = 0;
			}
			else wannagame = 1; // n,N,y,Y �̿��� �Է��� ������� �����Ƿ�
		}

		if (wannagame == 0)
		{
			system("cls");
		}

		else // wannagame = 1;
		{
			system("cls");
			break;
		}
	}
}

int get_user_card(int gamenum, int comscore, int userscore, int draw, int a)
{
	int usercard2;
	while (1)
	{
		printf("\n[����Ƚ��: %d, ��ǻ��: %d��, ��: %d��]\n\n", gamenum, comscore, userscore);
		show_table(draw, a); // a�� ���� Ȳ����, �뿹�� �����ؼ� �� ���, draw�� ���� ī�� ���� ��� (�ù� ī���� ���� = 4 - draw ��ŭ �ִ�.)

		printf("[ī�� ����]\n");
		printf("*****************\n\n");
		if (a == 0) printf(" 0. Ȳ�� (1��)\n\n");
		else printf(" 0. �뿹 (1��)\n\n");
		printf(" 1. �ù� (%d��)\n\n", 4 - draw);
		printf("*****************\n");
		printf("�Է�: ");
		scanf_s("%d", &usercard2);


		if (usercard2 == 0 || usercard2 == 1)
		{
			return usercard2;
		}

		else
		{
			printf("�ùٸ� �޴��� �����ϼ���...\n");
			Sleep(1000);
			system("cls");
		}
	}
}

void show_table(int draw, int a) // a�� i�� ���� S, E, C ���ڸ� ��� ����� �� �ִ� content �ۼ�
{
	int i = 1;
	char content, special;

	if (a == 0) special = 'E';
	else special = 'S';
		
	for (i = 1; i <= 5 - draw; i++) printf("*******");
	printf("\n");
	for (i = 1; i <= 5 - draw; i++) printf(" ����������");
	printf("\n");
	for (i = 1; i <= 5 - draw; i++) printf(" �� ? ��");
	printf("\n");
	for (i = 1; i <= 5 - draw; i++) printf(" ����������");
	printf("\n\n");
	for (i = 1; i <= 5 - draw; i++) printf(" ����������");
	printf("\n");
	for (i = 1; i <= 5 - draw; i++)
	{
		if (i == 1) content = special;
		else content = 'C';
		printf(" �� %c ��", content);
	}
	printf("\n");
	for (i = 1; i <= 5 - draw; i++) printf(" ����������");
	printf("\n\n");
	for (i = 1; i <= 5 - draw; i++) printf("*******");
	printf("\n\n");
}

int get_computer_card(int a) // ��ǻ�Ͱ� �� �� ��ȯ
{
	int range = 2;
	return rand() % range + 2; // ��� ���ϰ� �Ϸ��� ��ǻ�ʹ� 2 (�뿹 orȲ��) �Ǵ� 3 ��ȯ
}

int compare_card(int a, int usercard1, int comcard)
{
	if (a == 0)
	{
		if (usercard1 == 0) // ������ Ȳ��ī�� ����
		{
			if (comcard == 2) return 2;
			else return 1;
		}
		else // ������ �ù�ī�� ����
		{
			if (comcard == 2) return 1;
			else return 0;
		}
	}

	else // a = 1 �� ���
	{
		if (usercard1 == 0) // ������ �뿹ī�� ����
		{
			if (comcard == 2) return 1;
			else return 2;
		}
		else // ������ �ù�ī�� ����
		{
			if (comcard == 2) return 2;
			else return 0;
		}
	}
}

int calc_score(int a, int next)
{
	if (a == 0) // ������ Ȳ���и� ��� ����� �� ���
	{
		if (next == 1) return 200; // �̱� ���
		else return -500;
	}
	else // ������ �뿹�и� ��� ����� �� ���
	{
		if (next == 1) return 700;
		else return -300;
	}
}