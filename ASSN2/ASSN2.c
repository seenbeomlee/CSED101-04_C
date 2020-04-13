#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>

#define FLUSH while(getchar()!= '\n'); // 버퍼를 지우기 위함

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
		//메인 메뉴로 돌아왔다는 것은, 게임횟수, 컴퓨터 점수, 나의 점수가 모두 초기화 되었음을 의미.
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
				printf("프로그램을 종료합니다...");
				return 0;
			}
	}
}

int show_menu(void) // 1,2,3 을 입력받아 반환한다.
{
	int startnumber;
	while (1)
	{
		printf("\n************ E - Card ************\n\n");
		printf("           1. 게임 설명\n\n");
		printf("           2. 게임 시작\n\n");
		printf("           3. 게임 종료\n\n");
		printf("**********************************\n\n");
		printf("입력: ");
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
				printf("올바른 메뉴를 선택하세요...\n");
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
		printf("************* E - Card 게임 설명 *******************************************\n\n");
		printf(" 본 게임은 도박묵시록 카이지의 E-Card 게임을 기반으로 한다.\n\n");
		printf(" 1. 두 플레이어는 황제패와 노예패 중 하나의 패를 각각 선택한다.\n");
		printf("    황제패 = 황제 카드 1장 + 시민 카드 4장\n");
		printf("    노예패 = 노예 카드 1장 + 시민 카드 4장\n");
		printf("2. 두 사용자는 매 턴마다 한 장의 카드를 안보이게 내밀고, 함께 뒤집는다.\n\n");
		printf("3. 아래의 카드 간 상성 관계에 따라 승패를 결정한다.\n");
		printf("단, 두 플레이어가 시민 카드를 냈다면, 무승부로 처리한다.\n\n");
		printf("4. 내밀었던 카드는 소모되고 승패가 결정될 떄까지 2로 돌아가 반복한다.\n\n");
		printf(" 상성관계 : 황제 > 시민 > 노예 > 황제\n\n");
		printf("****************************************************************************\n");
		printf("메뉴로 돌아가려면 Enter키를 입력하세요...");
		FLUSH;
		scanf("%c", &cc); // 엔터 이외의 값을 입력하면 안됨
		
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
		int a = 0; // a는 플레이어가 0(황제패), 1(노예패) 중 무엇을 받았는지의 변수
		int draw = 0; // game_start에 왔다는 건, 승패가 나서 draw가 0으로 초기화 되었다는 것
		gamenum += 1; // 승패가 나서 여기에 왔다는 건, 게임횟수가 추가된 것
		int for_user = 0; // 그 판에서 유저가 받았던 점수도 다시 초기화
		int wannagame = 0; // wannagame = 0 이면 while 문 계속, =1 이면 게임 종료
		char nNyY, bb, bbb; // 기타 엔터를 받을 때 사용할 변수
		int next = 0; // 플레이어가 전 판에서 이겼는지(1) 졌는지(2)를 입력받는 변수
		int usercard1 = 0; // 처음 플레이어의 카드를 입력 받기 위해 초기화
		int comcard = 0; // 처음 컴퓨터의 카드를 입력 받기 위해 초기화
		

		while (1)
		{
			printf("\n[게임횟수: %d, 컴퓨터: %d점, 나: %d점]\n\n", gamenum, comscore, userscore);
			printf("\n[카드 패 선택]\n");
			printf("**********************************\n\n");
			printf(" 0. 황제패 (황제 1장, 시민 4장)\n\n");
			printf(" 1. 노예패 (노예 1장, 시민 4장)\n\n");
			printf("**********************************\n");
			printf("입력: ");
			FLUSH;
			scanf_s("%d", &a);
		
			if (a == 0 || a == 1) break;
			else
			{
				printf("올바른 메뉴를 선택하세요...\n");
				Sleep(1000);
				system("cls");
			}
		}
		
		while (1) // 무승부가 났을 때, draw += 1; 하고 반복해서 게임을 다시 진행해야 한다.
		{
			system("cls");
			usercard1 = get_user_card(gamenum, comscore, userscore, draw, a);
			comcard = get_computer_card(a); // a를 통해 유저가 황제패, 노예패 중 뭘 골랐는지 앎
			next = compare_card(a, usercard1, comcard);
			
			printf("\n\n[선택 결과]\n");
			printf("******************\n\n");
			if (a == 0)
			{
				if (usercard1==0) printf(" * 나의 카드     : 황제\n\n");
				else printf(" * 나의 카드     : 시민\n\n");

				if (comcard==2) printf(" * 컴퓨터의 카드 : 노예\n\n");
				else printf(" * 컴퓨터의 카드 : 시민\n\n");
			}
			else
			{
				if (usercard1==0) printf(" * 나의 카드     : 노예\n\n");
				else printf(" * 나의 카드     : 시민\n\n");

				if (comcard==2) printf(" * 컴퓨터의 카드 : 황제\n\n");
				else printf(" * 컴퓨터의 카드 : 시민\n\n");
			}

			if (next == 1) printf(" * 결과: 승리\n\n");
			else if (next == 2) printf(" * 결과: 패배\n\n");
			else printf(" * 결과: 무승부\n\n");
			printf("******************\n\n");

			if (next == 1 || next == 2) break;
			else
			{
				draw += 1; // 무승부의 경우 next = 0 이므로, 다시 while 문 수행
				printf("다음 턴 (Enter키를 입력하세요...)");
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

		printf("[현재 점수]\n");
		printf("******************\n\n");
		printf(" * 나의 점수    : %d\n\n", userscore);
		printf(" * 컴퓨터의 점수: %d\n\n", comscore);
		printf("******************\n\n");

		if (comscore >= 2000)
		{
			printf("[최종 결과]\n");
			printf("*****************\n\n");
			printf(" * 당신의 패배 !\n\n");
			printf("*****************\n\n");
			printf("Enter키를 입력하세요...");
			FLUSH;
			scanf_s("%c", &bbb);
			wannagame = 1;
		}
	
		else if (userscore >= 2000)
		{
			printf("[최종 결과]\n");
			printf("*****************\n\n");
			printf(" * 당신의 승리 !\n\n");
			printf("*****************\n\n");
			printf("Enter키를 입력하세요...");
			scanf_s("%c", &bbb);
			FLUSH;
			wannagame = 1;
		}

		else
		{
			printf("게임을 계속하겠습니까? (y/n): ");
			FLUSH;
			scanf_s("%c", &nNyY);

			if (nNyY == 'y'|| nNyY == 'Y')
			{
				wannagame = 0;
			}
			else wannagame = 1; // n,N,y,Y 이외의 입력은 고려하지 않으므로
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
		printf("\n[게임횟수: %d, 컴퓨터: %d점, 나: %d점]\n\n", gamenum, comscore, userscore);
		show_table(draw, a); // a를 통해 황제패, 노예패 구분해서 패 출력, draw를 통해 카드 개수 출력 (시민 카드의 개수 = 4 - draw 만큼 있다.)

		printf("[카드 선택]\n");
		printf("*****************\n\n");
		if (a == 0) printf(" 0. 황제 (1장)\n\n");
		else printf(" 0. 노예 (1장)\n\n");
		printf(" 1. 시민 (%d장)\n\n", 4 - draw);
		printf("*****************\n");
		printf("입력: ");
		scanf_s("%d", &usercard2);


		if (usercard2 == 0 || usercard2 == 1)
		{
			return usercard2;
		}

		else
		{
			printf("올바른 메뉴를 선택하세요...\n");
			Sleep(1000);
			system("cls");
		}
	}
}

void show_table(int draw, int a) // a와 i를 통해 S, E, C 문자를 모두 출력할 수 있는 content 작성
{
	int i = 1;
	char content, special;

	if (a == 0) special = 'E';
	else special = 'S';
		
	for (i = 1; i <= 5 - draw; i++) printf("*******");
	printf("\n");
	for (i = 1; i <= 5 - draw; i++) printf(" ┌───┐");
	printf("\n");
	for (i = 1; i <= 5 - draw; i++) printf(" │ ? │");
	printf("\n");
	for (i = 1; i <= 5 - draw; i++) printf(" └───┘");
	printf("\n\n");
	for (i = 1; i <= 5 - draw; i++) printf(" ┌───┐");
	printf("\n");
	for (i = 1; i <= 5 - draw; i++)
	{
		if (i == 1) content = special;
		else content = 'C';
		printf(" │ %c │", content);
	}
	printf("\n");
	for (i = 1; i <= 5 - draw; i++) printf(" └───┘");
	printf("\n\n");
	for (i = 1; i <= 5 - draw; i++) printf("*******");
	printf("\n\n");
}

int get_computer_card(int a) // 컴퓨터가 고른 패 반환
{
	int range = 2;
	return rand() % range + 2; // 계산 편하게 하려고 컴퓨터는 2 (노예 or황졔) 또는 3 반환
}

int compare_card(int a, int usercard1, int comcard)
{
	if (a == 0)
	{
		if (usercard1 == 0) // 유저가 황제카드 뽑음
		{
			if (comcard == 2) return 2;
			else return 1;
		}
		else // 유저가 시민카드 뽑음
		{
			if (comcard == 2) return 1;
			else return 0;
		}
	}

	else // a = 1 인 경우
	{
		if (usercard1 == 0) // 유저가 노예카드 뽑음
		{
			if (comcard == 2) return 1;
			else return 2;
		}
		else // 유저가 시민카드 뽑음
		{
			if (comcard == 2) return 2;
			else return 0;
		}
	}
}

int calc_score(int a, int next)
{
	if (a == 0) // 유저가 황제패를 골라서 결과가 난 경우
	{
		if (next == 1) return 200; // 이긴 경우
		else return -500;
	}
	else // 유저가 노예패를 골라서 결과가 난 경우
	{
		if (next == 1) return 700;
		else return -300;
	}
}