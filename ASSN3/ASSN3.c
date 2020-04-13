#include<stdio.h>
#include<stdlib.h>

#define MaxArr 10

#define GRAY "\x1b[90m"
#define ORANGE "\x1b[91m"
#define GREEN "\x1b[92m"
#define YELLOW "\x1b[93m"
#define BLUE "\x1b[94m"
#define PURPLE "\x1b[95m"
#define SKY "\x1b[96m"
#define WHITE "\x1b[97m"
#define RESET "\x1b[0m"

int ReadBoard(int board[MaxArr][MaxArr], int* row, int* col);
void PrintBoard(int board[MaxArr][MaxArr], int row, int col);
int RemoveChunk(int board[MaxArr][MaxArr], int row, int col);
void UpdateBoard(int board[MaxArr][MaxArr], int row, int col);

int main(void)
{
	FILE* output;
	int row = 0; int col = 0; int read_board_return, removechunk_return;
	int board[MaxArr][MaxArr] = { 0 };
	char enter1, enter2;
	int ii = 0;
	int jj = 0;
	read_board_return = ReadBoard(board, &row, &col);

	if (read_board_return == 0) return 0; // ������ �߰ߵ� ���
	if (read_board_return == 1) // ������ �߰ߵ��� �ʾ� ��� ������ �����ϴ� ���
	{
		while (1)
		{
			PrintBoard(board, row, col);
			scanf("%c", &enter1);
			system("clear");
			removechunk_return = RemoveChunk(board, row, col);

			PrintBoard(board, row, col);
			scanf("%c", &enter2);
			system("clear");

			if (removechunk_return == 0) break; // removechunk���� ���� ���̰� ���̻� ���� ���
			if (removechunk_return == 1) UpdateBoard(board, row, col); // ���� ���̰� �� �ִ� ���
		}
	}

	output = fopen("result.txt", "w");
	for (ii = 0; ii < row; ii++)
	{
		for (jj = 0; jj < col; jj++)
			fprintf(output, "%d ", board[ii][jj]);

		fprintf(output, "\n");
	}
	fclose(output);
	return 0;
}

int ReadBoard(int board[MaxArr][MaxArr], int* row, int* col)
{
	FILE* input;
	int ioResult;
	int check;
	int i, j;

	if (!(input = fopen("board.txt", "r"))) // board.txt ������ �߰����� ������ ��
	{
		printf("board.txt ������ �����ϴ�.");
		return 0;
	}

	fscanf(input, "%d%d", &*row, &*col);

	for (i = 0; i < *row; i++)
	{
		for (j = 0; j < *col; j++)
		{
			ioResult = fscanf(input, "%d", &board[i][j]);

			if (board[i][j] < 1 || board[i][j] > 7) // 1���� 7 �̿��� ���� ���̿� ���� ��
			{
				printf("1���� 7�̿��� ���̰� �ֽ��ϴ�.");
				fclose(input);
				return 0;
			}

			if (ioResult == EOF) // �迭�� ���� �� ���� ���ߴµ�, ������ ���������� ��
			{
				printf("�������� ���� ������ �ٸ��ϴ�.");
				fclose(input);
				return 0;
			}
		}
	}

	ioResult = fscanf(input, "%d", &check);

	if (ioResult != EOF) // �迭�� ���� �� �־��µ�, ������ ���� ������ ���� ���
	{
		printf("�������� ���� ������ �ٸ��ϴ�.");
		fclose(input);
		return 0;
	}
	fclose(input);
	return 1; // ������ ���� �ٸ��� board.txt�� ���� ���
}

void PrintBoard(int board[MaxArr][MaxArr], int row, int col)
{
	int iii, jjj;

	for (iii = 0; iii < row; iii++)
	{
		for (jjj = 0; jjj < col; jjj++)
		{
			if (board[iii][jjj] == 0) printf(GRAY " %d" RESET, board[iii][jjj]);
			if (board[iii][jjj] == 1) printf(ORANGE " %d" RESET, board[iii][jjj]);
			if (board[iii][jjj] == 2) printf(GREEN " %d" RESET, board[iii][jjj]);
			if (board[iii][jjj] == 3) printf(YELLOW " %d" RESET, board[iii][jjj]);
			if (board[iii][jjj] == 4) printf(BLUE " %d" RESET, board[iii][jjj]);
			if (board[iii][jjj] == 5) printf(PURPLE " %d" RESET, board[iii][jjj]);
			if (board[iii][jjj] == 6) printf(SKY " %d" RESET, board[iii][jjj]);
			if (board[iii][jjj] == 7) printf(WHITE " %d" RESET, board[iii][jjj]);
		}
		printf("\n");
	}
}

int RemoveChunk(int board[MaxArr][MaxArr], int row, int col)
{
	int temp_board[MaxArr][MaxArr] = { 0 };
	int se = 0;
	int re = 0;
	int p, q, pp, qq, n, m, nn, mm, t, tt;

	for (p = 0; p < row; p++)
		for (q = 0; q < col; q++)
			temp_board[p][q] = board[p][q];

	for (n = 0; n < row; n++)
		for (m = 0; m < col; m++)
		{
			if ((board[n][m] != 0) && (board[n][m] == board[n][m + 1])) se += 1;
			else
			{
				if (se >= 2)
					for (t = m; t >= m - se; t--)
					{
						temp_board[n][t] = 0;
						re = 1;
					}
				se = 0;
			}
		}

	for (mm = 0; mm < col; mm++)
		for (nn = 0; nn < row; nn++)
		{
			if ((board[nn][mm] != 0) && (board[nn][mm] == board[nn + 1][mm])) se += 1;
			else
			{
				if (se >= 2)
					for (tt = nn; tt >= nn - se; tt--)
					{
						temp_board[tt][mm] = 0;
						re = 1;
					}
				se = 0;
			}
		}

	for (pp = 0; pp < row; pp++)
		for (qq = 0; qq < col; qq++)
			board[pp][qq] = temp_board[pp][qq];

	return re;
}

void UpdateBoard(int board[MaxArr][MaxArr], int row, int col)
{
	int i, j, k;

	for (j = 0; j < col; j++)
		for (i = row - 1; i > 0; i--)
		{
			if (board[i][j] == 0)
			{
				for (k = i - 1; k >= 0; k--)
				{
					if (board[k][j] != 0)
					{
						board[i][j] = board[k][j];
						board[k][j] = 0;
						break;
					}
				}
			}
		}
}
