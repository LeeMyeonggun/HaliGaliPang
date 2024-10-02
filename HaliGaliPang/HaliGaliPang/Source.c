#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>


#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define CARDHEIGHT 3
#define CARDWIDTH 3



// 각각의 요소들을 typedef로 특성을 정의

// 타임 바의 경우 타이머의 위치, 시간
typedef struct
{
	const int x;
	const int y;
	int time;
	int count;

} Timebar;

// 타이머의 경우 위치, 시간
typedef struct
{
	const int x;
	const int y;
	int time;


} Timer;


typedef struct
{
	const int x;
	const int y;
	int score;

} ScoreBoard;

typedef struct
{
	const int x;
	const int y;

} Bell;

// 포지션을 잡아주는 함수
void Position(int x, int y)
{

	COORD position = { x, y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);

}



int main()
{
	// 난이도에 따라 결정되는 맞았을 경우 : 시간 증가량, 스코어 증가량 틀렸을 경우 스코어 감소량
	int time_increase = 0;
	int score_increase = 0;
	int score_decrease = 0;
	int passed_time = 0;
	int hit = 0;
	int num_card = 0;
	int sum[] = { 0, 0, 0, 0 };
	int score = 0;
	int card_set[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56 };
	int random_number1 = 0;
	int random_number2 = 0;
	int temporary = 0;
	int ind = 0;
	int cnt = 0;
	int multiple = 0;

	for (int i = 0; i < 1000; i++)
	{
		random_number1 = rand() % 55;
		random_number2 = rand() % 55;

		temporary = card_set[random_number1];
		card_set[random_number1] = card_set[random_number2];
		card_set[random_number2] = temporary;

	}


	Timebar timebar = { 0, 0, 60 - passed_time, 0 };
	Timer timer = { 122, 0, 60 - passed_time };
	ScoreBoard scoreboard = { 122, 2, score };
	Bell bell = { 60, 10 };


	srand(time(NULL));

	// 모드를 선택하는 함수


	int key = 0;

	Position(45, 3);
	printf("Select Mode");
	Position(45, 5);
	printf("← : Hard");
	Position(45, 6);
	printf("↓ : Normal");
	Position(45, 7);
	printf("→ : Easy");

	


	key = _getch();

	if (key == 224)
	{
		key = _getch();
	}

	switch (key)
	{
		// 위쪽 방향키 Extreme 난이도
	case LEFT:

		score_increase = 500;
		score_decrease = 200;
		multiple = 1;

		break;

		// 왼쪽 방향키 Hard 난이도

	case DOWN:
		score_increase = 200;
		score_decrease = 50;
		multiple = 2;

		break;
		// 오른쪽 방향키 Normal 난이도
	case RIGHT:
		score_increase = 50;
		score_decrease = 0;
		multiple = 3;

		break;
		// 아래쪽 방향키 Easy 난이도
	case UP:
		score_increase = 50;
		score_decrease = 0;

		break;
	}

	system("cls");


	// 난이도 선택 디버깅용 출력
	// printf("%d", score_increase);
	// printf("%d", score_decrease);

	Sleep(1000);
	
	// 3
	Position(43, 4);
	printf("■");
	Position(45, 4);
	printf("■");
	Position(47, 4);
	printf("■");
	Position(49, 4);
	printf("■");
	Position(49, 5);
	printf("■");
	Position(49, 6);
	printf("■");
	Position(49, 7);
	printf("■");
	Position(47, 7);
	printf("■");
	Position(45, 7);
	printf("■");
	Position(49, 8);
	printf("■");
	Position(49, 9);
	printf("■");
	Position(49, 10);
	printf("■");
	Position(49, 11);
	printf("■");
	Position(47, 11);
	printf("■");
	Position(45, 11);
	printf("■");
	Position(43, 11);
	printf("■");
	Position(43, 5);
	printf("■");
	Position(43, 10);
	printf("■");

	Sleep(1000);
	system("cls");


	//2
	Position(43, 5);
	printf("■");
	Position(45, 4);
	printf("■");
	Position(47, 4);
	printf("■");
	Position(49, 5);
	printf("■");
	Position(48, 6);
	printf("■");
	Position(47, 7);
	printf("■");
	Position(46, 8);
	printf("■");
	Position(45, 9);
	printf("■");
	Position(44, 10);
	printf("■");
	Position(43, 11);
	printf("■");
	Position(45, 11);
	printf("■");
	Position(47, 11);
	printf("■");
	Position(49, 11);
	printf("■");

	Sleep(1000);
	system("cls");

	//1
	Position(46, 4);
	printf("■");
	Position(46, 5);
	printf("■");
	Position(46, 6);
	printf("■");
	Position(46, 7);
	printf("■");
	Position(46, 8);
	printf("■");
	Position(46, 9);
	printf("■");
	Position(46, 10);
	printf("■");
	Position(46, 11);
	printf("■");
	Position(44, 5);
	printf("■");
	Position(42, 6);
	printf("■");
	Position(44, 11);
	printf("■");
	Position(42, 11);
	printf("■");
	Position(48, 11);
	printf("■");
	Position(50, 11);
	printf("■");


	Sleep(1000);
	system("cls");




	// 게임시작
	while (1)
	{

		// 타임바, 타이머, 스코어, 종 디스플레이
		// Display_Timebar();


		for (int i = 0; i < 30 - passed_time; i++)
		{
			timebar.count = i;
			Position(timebar.x + timebar.count*2, timebar.y);
			printf("■");

		}


		// Display_Timer();
		Position(timer.x, timer.y);
		timer.time = 30 - passed_time;
		printf("%d", timer.time);


		// Display_Score();
		Position(scoreboard.x, scoreboard.y);
		printf("Score : %d", score);

		// Display_Bell();
		Position(44, 10);
		printf("■");
		Position(46, 10);
		printf("■");
		Position(45, 11);
		printf("■");
		Position(44, 12);
		printf("■");
		Position(46, 12);
		printf("■");
		Position(43, 13);
		printf("■");
		Position(45, 13);
		printf("■");
		Position(47, 13);
		printf("■");
		Position(42, 14);
		printf("■");
		Position(44, 14);
		printf("■");
		Position(46, 14);
		printf("■");
		Position(48, 14);
		printf("■");
		Position(41, 15);
		printf("■");
		Position(43, 15);
		printf("■");
		Position(45, 15);
		printf("■");
		Position(47, 15);
		printf("■");
		Position(49, 15);
		printf("■");


		// 랜덤하게 뽑을 카드를 저장할 변수를 while문을 돌면서 초기화
		int card_shape[CARDHEIGHT][CARDWIDTH] = { {0, 0, 0},
												  {0, 0, 0},
												  {0, 0, 0} };
		int card_character[] = { 0 , 0 };


		// 카드를 랜덤하게 뽑아주는 함수
		// 한번 나온 숫자가 다시 안 나오게하는 알고리즘 필요
		// Random_Card();

		for (int i = 0; i < 4; i++)
		{
			sum[i] = 0;
		}



		for (int k = ind; k < passed_time / multiple; k++)
		{




			for (int j = 0; j < 3; j++)
			{

				for (int i = 0; i < 3; i++)
				{
					card_shape[i][j] = 0;
				}

			}

			for (int i = 0; i < 2; i++)
			{
				card_character[i] = 0;
			}




			switch (card_set[k])
			{

			case 1:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 1;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 1;
				card_character[1] = 1;

				break;

			}

			case 2:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 1;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 1;
				card_character[1] = 1;

				break;

			}

			case 3:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 1;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 1;
				card_character[1] = 1;

				break;

			}

			case 4:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 1;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 1;
				card_character[1] = 1;

				break;

			}

			case 5:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 1;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 1;
				card_character[1] = 1;

				break;

			}

			case 6:
			{
				card_shape[0][0] = 1;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 1;
				card_character[0] = 1;
				card_character[1] = 2;

				break;

			}

			case 7:
			{
				card_shape[0][0] = 1;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 1;
				card_character[0] = 1;
				card_character[1] = 2;

				break;

			}

			case 8:
			{
				card_shape[0][0] = 1;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 1;
				card_character[0] = 1;
				card_character[1] = 2;

				break;

			}

			case 9:
			{
				card_shape[0][0] = 1;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 1;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 1;
				card_character[0] = 1;
				card_character[1] = 3;

				break;

			}

			case 10:
			{
				card_shape[0][0] = 1;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 1;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 1;
				card_character[0] = 1;
				card_character[1] = 3;

				break;

			}

			case 11:
			{
				card_shape[0][0] = 1;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 1;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 1;
				card_character[0] = 1;
				card_character[1] = 3;

				break;

			}

			case 12:
			{
				card_shape[0][0] = 1;
				card_shape[0][1] = 0;
				card_shape[0][2] = 1;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 1;
				card_shape[2][1] = 0;
				card_shape[2][2] = 1;
				card_character[0] = 1;
				card_character[1] = 4;

				break;

			}

			case 13:
			{
				card_shape[0][0] = 1;
				card_shape[0][1] = 0;
				card_shape[0][2] = 1;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 1;
				card_shape[2][1] = 0;
				card_shape[2][2] = 1;
				card_character[0] = 1;
				card_character[1] = 4;

				break;

			}

			case 14:
			{
				card_shape[0][0] = 1;
				card_shape[0][1] = 0;
				card_shape[0][2] = 1;
				card_shape[1][0] = 0;
				card_shape[1][1] = 1;
				card_shape[1][2] = 0;
				card_shape[2][0] = 1;
				card_shape[2][1] = 0;
				card_shape[2][2] = 1;
				card_character[0] = 1;
				card_character[1] = 5;

				break;

			}

			case 15:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 2;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 2;
				card_character[1] = 1;

				break;

			}

			case 16:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 2;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 2;
				card_character[1] = 1;

				break;

			}

			case 17:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 2;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 2;
				card_character[1] = 1;

				break;

			}

			case 18:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 2;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 2;
				card_character[1] = 1;

				break;

			}

			case 19:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 2;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 2;
				card_character[1] = 1;

				break;

			}

			case 20:
			{
				card_shape[0][0] = 2;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 2;
				card_character[0] = 2;
				card_character[1] = 2;

				break;

			}

			case 21:
			{
				card_shape[0][0] = 2;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 2;
				card_character[0] = 2;
				card_character[1] = 2;

				break;

			}

			case 22:
			{
				card_shape[0][0] = 2;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 2;
				card_character[0] = 2;
				card_character[1] = 2;

				break;

			}

			case 23:
			{
				card_shape[0][0] = 2;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 2;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 2;
				card_character[0] = 2;
				card_character[1] = 3;

				break;

			}

			case 24:
			{
				card_shape[0][0] = 2;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 2;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 2;
				card_character[0] = 2;
				card_character[1] = 3;

				break;

			}

			case 25:
			{
				card_shape[0][0] = 2;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 2;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 2;
				card_character[0] = 2;
				card_character[1] = 3;

				break;

			}

			case 26:
			{
				card_shape[0][0] = 2;
				card_shape[0][1] = 0;
				card_shape[0][2] = 2;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 2;
				card_shape[2][1] = 0;
				card_shape[2][2] = 2;
				card_character[0] = 2;
				card_character[1] = 4;

				break;

			}

			case 27:
			{
				card_shape[0][0] = 2;
				card_shape[0][1] = 0;
				card_shape[0][2] = 2;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 2;
				card_shape[2][1] = 0;
				card_shape[2][2] = 2;
				card_character[0] = 2;
				card_character[1] = 4;

				break;

			}

			case 28:
			{
				card_shape[0][0] = 2;
				card_shape[0][1] = 0;
				card_shape[0][2] = 2;
				card_shape[1][0] = 0;
				card_shape[1][1] = 2;
				card_shape[1][2] = 0;
				card_shape[2][0] = 2;
				card_shape[2][1] = 0;
				card_shape[2][2] = 2;
				card_character[0] = 2;
				card_character[1] = 5;

				break;

			}

			case 29:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 3;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 3;
				card_character[1] = 1;

				break;

			}

			case 30:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 3;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 3;
				card_character[1] = 1;

				break;

			}

			case 31:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 3;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 3;
				card_character[1] = 1;

				break;

			}

			case 32:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 3;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 3;
				card_character[1] = 1;

				break;

			}

			case 33:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 3;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 3;
				card_character[1] = 1;

				break;

			}

			case 34:
			{
				card_shape[0][0] = 3;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 3;
				card_character[0] = 3;
				card_character[1] = 2;

				break;

			}

			case 35:
			{
				card_shape[0][0] = 3;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 3;
				card_character[0] = 3;
				card_character[1] = 2;

				break;

			}

			case 36:
			{
				card_shape[0][0] = 3;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 3;
				card_character[0] = 3;
				card_character[1] = 2;

				break;

			}

			case 37:
			{
				card_shape[0][0] = 3;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 3;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 3;
				card_character[0] = 3;
				card_character[1] = 3;

				break;

			}

			case 38:
			{
				card_shape[0][0] = 3;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 3;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 3;
				card_character[0] = 3;
				card_character[1] = 3;

				break;

			}

			case 39:
			{
				card_shape[0][0] = 3;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 3;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 3;
				card_character[0] = 3;
				card_character[1] = 3;

				break;

			}

			case 40:
			{
				card_shape[0][0] = 3;
				card_shape[0][1] = 0;
				card_shape[0][2] = 3;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 3;
				card_shape[2][1] = 0;
				card_shape[2][2] = 3;
				card_character[0] = 3;
				card_character[1] = 4;

				break;

			}

			case 41:
			{
				card_shape[0][0] = 3;
				card_shape[0][1] = 0;
				card_shape[0][2] = 3;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 3;
				card_shape[2][1] = 0;
				card_shape[2][2] = 3;
				card_character[0] = 3;
				card_character[1] = 4;

				break;

			}

			case 42:
			{
				card_shape[0][0] = 3;
				card_shape[0][1] = 0;
				card_shape[0][2] = 3;
				card_shape[1][0] = 0;
				card_shape[1][1] = 3;
				card_shape[1][2] = 0;
				card_shape[2][0] = 3;
				card_shape[2][1] = 0;
				card_shape[2][2] = 3;
				card_character[0] = 3;
				card_character[1] = 5;

				break;

			}

			case 43:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 4;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 4;
				card_character[1] = 1;

				break;

			}

			case 44:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 4;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 4;
				card_character[1] = 1;

				break;

			}

			case 45:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 4;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 4;
				card_character[1] = 1;

				break;

			}

			case 46:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 4;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 4;
				card_character[1] = 1;

				break;

			}

			case 47:
			{
				card_shape[0][0] = 0;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 4;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 0;
				card_character[0] = 4;
				card_character[1] = 1;

				break;

			}

			case 48:
			{
				card_shape[0][0] = 4;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 4;
				card_character[0] = 4;
				card_character[1] = 2;

				break;

			}

			case 49:
			{
				card_shape[0][0] = 4;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 4;
				card_character[0] = 4;
				card_character[1] = 2;

				break;

			}

			case 50:
			{
				card_shape[0][0] = 4;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 4;
				card_character[0] = 4;
				card_character[1] = 2;

				break;

			}

			case 51:
			{
				card_shape[0][0] = 4;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 4;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 4;
				card_character[0] = 4;
				card_character[1] = 3;

				break;

			}

			case 52:
			{
				card_shape[0][0] = 4;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 4;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 4;
				card_character[0] = 4;
				card_character[1] = 3;

				break;

			}

			case 53:
			{
				card_shape[0][0] = 4;
				card_shape[0][1] = 0;
				card_shape[0][2] = 0;
				card_shape[1][0] = 0;
				card_shape[1][1] = 4;
				card_shape[1][2] = 0;
				card_shape[2][0] = 0;
				card_shape[2][1] = 0;
				card_shape[2][2] = 4;
				card_character[0] = 4;
				card_character[1] = 3;

				break;

			}

			case 54:
			{
				card_shape[0][0] = 4;
				card_shape[0][1] = 0;
				card_shape[0][2] = 4;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 4;
				card_shape[2][1] = 0;
				card_shape[2][2] = 4;
				card_character[0] = 4;
				card_character[1] = 4;

				break;

			}

			case 55:
			{
				card_shape[0][0] = 4;
				card_shape[0][1] = 0;
				card_shape[0][2] = 4;
				card_shape[1][0] = 0;
				card_shape[1][1] = 0;
				card_shape[1][2] = 0;
				card_shape[2][0] = 4;
				card_shape[2][1] = 0;
				card_shape[2][2] = 4;
				card_character[0] = 4;
				card_character[1] = 4;

				break;

			}

			case 56:
			{
				card_shape[0][0] = 4;
				card_shape[0][1] = 0;
				card_shape[0][2] = 4;
				card_shape[1][0] = 0;
				card_shape[1][1] = 4;
				card_shape[1][2] = 0;
				card_shape[2][0] = 4;
				card_shape[2][1] = 0;
				card_shape[2][2] = 4;
				card_character[0] = 4;
				card_character[1] = 5;

				break;

			}

			}

			// 카드의 위치를 정해주고 디스플레이
			// Set_Postion_Card();

			// Display_Card();
			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < 3; i++)
				{
					switch (card_shape[i][j])
					{
					case 1:
					{
						Position((k - ind) * 9 + i, 3 + j);
						printf("●");
						break;
					}
					case 2:
					{
						Position((k - ind) * 9 + i, 3 + j);
						printf("■");
						break;
					}
					case 3:
					{
						Position((k - ind) * 9 + i, 3 + j);
						printf("▲");
						break;
					}
					case 4:
					{
						Position((k - ind) * 9 + i, 3 + j);
						printf("★");
						break;
					}
					default:
					{
						Position((k - ind) * 9 + i, 3 + j);
						printf("  ");
						break;

					}
					}


				}

			}

			switch (card_character[0])
			{
			case 1: sum[0] += card_character[1];
				break;

			case 2: sum[1] += card_character[1];
				break;

			case 3: sum[2] += card_character[1];
				break;

			case 4: sum[3] += card_character[1];
				break;

			}


			//합 계산 알고리즘 디버깅용 출력
			// for (int i = 0; i < 4; i++)
			// {
			// 	Position(i * 2, 10);
			// 	printf("%d", sum[i]);
			// 
			// }


		}

		
		Sleep(500 * multiple);


		if (GetAsyncKeyState(VK_SPACE) & 0x0001)
		{


			Position(44, 11);
			printf("■");
			Position(46, 11);
			printf("■");
			Position(44, 12);
			printf("■");
			Position(46, 12);
			printf("■");
			Position(43, 13);
			printf("■");
			Position(45, 13);
			printf("■");
			Position(47, 13);
			printf("■");
			Position(42, 14);
			printf("■");
			Position(44, 14);
			printf("■");
			Position(46, 14);
			printf("■");
			Position(48, 14);
			printf("■");
			Position(41, 15);
			printf("■");
			Position(43, 15);
			printf("■");
			Position(45, 15);
			printf("■");
			Position(47, 15);
			printf("■");
			Position(49, 15);
			printf("■");

			if (sum[0] % 5 == 0 && sum[0] != 0)
			{
				score += score_increase;
				ind = passed_time;


			}
			else if (sum[1] % 5 == 0 && sum[1] != 0)
			{
				score += score_increase;
				ind = passed_time;


			}
			else if (sum[2] % 5 == 0 && sum[2] != 0)
			{
				score += score_increase;
				ind = passed_time;
			}
			else if (sum[3] % 5 == 0 && sum[3] != 0)
			{
				score += score_increase;
				ind = passed_time;
			}
			else
			{
				if (score > score_decrease)
				{
					score -= score_decrease;
				}

			}


		}

		Sleep(500 * multiple);
		

		passed_time += multiple;

		if (passed_time == 30)
		{
			system("cls");
			break;
		}


		if (passed_time - ind > 10 * multiple)
		{
			system("cls");
			break;
		}

		system("cls");
	}



	Position(45, 8);
	printf("game over! your score is %d.", score);





	return 0;
}
