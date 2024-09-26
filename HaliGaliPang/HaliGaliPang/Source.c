#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>


#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ENTER 13
#define CARDHEIGHT 3
#define CARDWIDTH 3



// 각각의 요소들을 typedef로 특성을 정의

// 타임 바의 경우 타이머의 위치, 시간
typedef struct
{
	const int x;
	const int y;
	int time;

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

// 모드를 설정하는 함수
void select_mode(int* time_increase, int* score_increase, int* score_decrease)
{

	// 난이도에 따라 정답에 종을 칠 경우 시간 증가, 점수 증가, 틀릴 때 종을 칠 경우 점수 감소 정의
	int key = 0;


	if (_kbhit)
	{
		key = _getch();
	}

	if (key == -32)
	{
		key = _getch();
	}

	switch (key)
	{
		// 위쪽 방향키 Extreme 난이도
	case UP:
		*time_increase = 1;
		*score_increase = 1000;
		*score_decrease = 500;
		// 왼쪽 방향키 Hard 난이도
	case LEFT:
		*time_increase = 2;
		*score_increase = 500;
		*score_decrease = 200;
		// 오른쪽 방향키 Normal 난이도
	case RIGHT:
		*time_increase = 4;
		*score_increase = 200;
		*score_decrease = 50;
		// 아래쪽 방향키 Easy 난이도
	case DOWN:
		*time_increase = 6;
		*score_increase = 50;
		*score_decrease = 0;
	}

}





int main()
{
	// 난이도에 따라 결정되는 맞았을 경우 : 시간 증가량, 스코어 증가량 틀렸을 경우 스코어 감소량
	int time_increase = 0;
	int score_increase = 0;
	int score_decrease = 0;
	int rest_time = 60;
	int passed_time = 0;
	int hit = 0;
	int is_collect = 0;
	int num_card = 0;
	int sum[] = { 0, 0, 0, 0 };
	int score = 0;
	

	Timebar timebar = { 0, 0, rest_time };
	Timer timer = { 122, 0, rest_time };
	ScoreBoard scoreboard = { 122, 2, score };
	Bell bell = { 60, 10 };


	srand(time(NULL));

	// 모드를 선택하는 함수
	select_mode(&time_increase, &score_increase, &score_decrease);

	

	// 게임시작
	while (1)
	{	
		
		// 타임바, 타이머, 스코어, 종 디스플레이
		// Display_Timebar();
		Position(timebar.x, timebar.y);
		for (int i = 0; i < rest_time; i++)
		{
			
			printf("■");

		}
		

		// Display_Timer();
		Position(timer.x, timer.y);
		printf("%d", rest_time);


		// Display_Score();
		Position(scoreboard.x, scoreboard.y);
		printf("Score : %d", score);

		// Display_Bell();
		Position(bell.x, bell.y);
		

		// 랜덤하게 뽑을 카드를 저장할 변수를 while문을 돌면서 초기화
		int card_shape[CARDHEIGHT][CARDWIDTH] = { {0, 0, 0},
												  {0, 0, 0},
												  {0, 0, 0} };
		int card_character[] = { 0 , 0 };


		// 카드를 랜덤하게 뽑아주는 함수
		// 한번 나온 숫자가 다시 안 나오게하는 알고리즘 필요
		// Random_Card();
		
		num_card = rand() % 56;
		
		switch (num_card)
		{

		case 1:
		{
			card_shape[1][1] =  1;
			card_character[0] = 1;
			card_character[1] = 1;

			break;

		}

		case 2:
		{
			card_shape[1][1] = 1;
			card_character[0] = 1;
			card_character[1] = 1;

			break;

		}

		case 3:
		{
			card_shape[1][1] = 1;
			card_character[0] = 1;
			card_character[1] = 1;

			break;

		}

		case 4:
		{
			card_shape[1][1] = 1;
			card_character[0] = 1;
			card_character[1] = 1;

			break;

		}

		case 5:
		{
			card_shape[1][1] = 1;
			card_character[0] = 1;
			card_character[1] = 1;

			break;

		}

		case 6:
		{
			card_shape[0][0] = 1;
			card_shape[2][2] = 1;
			card_character[0] = 1;
			card_character[1] = 2;

			break;

		}

		case 7:
		{
			card_shape[0][0] = 1;
			card_shape[2][2] = 1;
			card_character[0] = 1;
			card_character[1] = 2;

			break;

		}

		case 8:
		{
			card_shape[0][0] = 1;
			card_shape[2][2] = 1;
			card_character[0] = 1;
			card_character[1] = 2;

			break;

		}

		case 9:
		{
			card_shape[0][0] = 1;
			card_shape[1][1] = 1;
			card_shape[2][2] = 1;
			card_character[0] = 1;
			card_character[1] = 3;

			break;

		}

		case 10:
		{
			card_shape[0][0] = 1;
			card_shape[1][1] = 1;
			card_shape[2][2] = 1;
			card_character[0] = 1;
			card_character[1] = 3;

			break;

		}

		case 11:
		{
			card_shape[0][0] = 1;
			card_shape[1][1] = 1;
			card_shape[2][2] = 1;
			card_character[0] = 1;
			card_character[1] = 3;

			break;

		}

		case 12:
		{
			card_shape[0][0] = 1;
			card_shape[0][2] = 1;
			card_shape[2][0] = 1;
			card_shape[2][2] = 1;
			card_character[0] = 1;
			card_character[1] = 4;

			break;

		}

		case 13:
		{
			card_shape[0][0] = 1;
			card_shape[0][2] = 1;
			card_shape[2][0] = 1;
			card_shape[2][2] = 1;
			card_character[0] = 1;
			card_character[1] = 4;

			break;

		}

		case 14:
		{
			card_shape[0][0] = 1;
			card_shape[0][2] = 1;
			card_shape[1][1] = 1;
			card_shape[2][0] = 1;
			card_shape[2][2] = 1;
			card_character[0] = 1;
			card_character[1] = 5;

			break;

		}

		case 15:
		{
			card_shape[1][1] = 2;
			card_character[0] = 2;
			card_character[1] = 1;

			break;

		}

		case 16:
		{
			card_shape[1][1] = 2;
			card_character[0] = 2;
			card_character[1] = 1;

			break;

		}

		case 17:
		{
			card_shape[1][1] = 2;
			card_character[0] = 2;
			card_character[1] = 1;

			break;

		}

		case 18:
		{
			card_shape[1][1] = 2;
			card_character[0] = 2;
			card_character[1] = 1;

			break;

		}

		case 19:
		{
			card_shape[1][1] = 2;
			card_character[0] = 2;
			card_character[1] = 1;

			break;

		}

		case 20:
		{
			card_shape[0][0] = 2;
			card_shape[2][2] = 2;
			card_character[0] = 2;
			card_character[1] = 2;

			break;

		}

		case 21:
		{
			card_shape[0][0] = 2;
			card_shape[2][2] = 2;
			card_character[0] = 2;
			card_character[1] = 2;

			break;

		}

		case 22:
		{
			card_shape[0][0] = 2;
			card_shape[2][2] = 2;
			card_character[0] = 2;
			card_character[1] = 2;

			break;

		}

		case 23:
		{
			card_shape[0][0] = 2;
			card_shape[1][1] = 2;
			card_shape[2][2] = 2;
			card_character[0] = 2;
			card_character[1] = 3;

			break;

		}

		case 24:
		{
			card_shape[0][0] = 2;
			card_shape[1][1] = 2;
			card_shape[2][2] = 2;
			card_character[0] = 2;
			card_character[1] = 3;

			break;

		}

		case 25:
		{
			card_shape[0][0] = 2;
			card_shape[1][1] = 2;
			card_shape[2][2] = 2;
			card_character[0] = 2;
			card_character[1] = 3;

			break;

		}

		case 26:
		{
			card_shape[0][0] = 2;
			card_shape[0][2] = 2;
			card_shape[2][0] = 2;
			card_shape[2][2] = 2;
			card_character[0] = 2;
			card_character[1] = 4;

			break;

		}

		case 27:
		{
			card_shape[0][0] = 2;
			card_shape[0][2] = 2;
			card_shape[2][0] = 2;
			card_shape[2][2] = 2;
			card_character[0] = 2;
			card_character[1] = 4;

			break;

		}

		case 28:
		{
			card_shape[0][0] = 2;
			card_shape[0][2] = 2;
			card_shape[1][1] = 2;
			card_shape[2][0] = 2;
			card_shape[2][2] = 2;
			card_character[0] = 2;
			card_character[1] = 5;

			break;

		}

		case 29:
		{
			card_shape[1][1] = 3;
			card_character[0] = 3;
			card_character[1] = 1;

			break;

		}

		case 30:
		{
			card_shape[1][1] = 3;
			card_character[0] = 3;
			card_character[1] = 1;

			break;

		}

		case 31:
		{
			card_shape[1][1] = 3;
			card_character[0] = 3;
			card_character[1] = 1;

			break;

		}

		case 32:
		{
			card_shape[1][1] = 3;
			card_character[0] = 3;
			card_character[1] = 1;

			break;

		}

		case 33:
		{
			card_shape[1][1] = 3;
			card_character[0] = 3;
			card_character[1] = 1;

			break;

		}

		case 34:
		{
			card_shape[0][0] = 3;
			card_shape[2][2] = 3;
			card_character[0] = 3;
			card_character[1] = 2;

			break;

		}

		case 35:
		{
			card_shape[0][0] = 3;
			card_shape[2][2] = 3;
			card_character[0] = 2;
			card_character[1] = 2;

			break;

		}

		case 36:
		{
			card_shape[0][0] = 3;
			card_shape[2][2] = 3;
			card_character[0] = 3;
			card_character[1] = 2;

			break;

		}

		case 37:
		{
			card_shape[0][0] = 3;
			card_shape[1][1] = 3;
			card_shape[2][2] = 3;
			card_character[0] = 3;
			card_character[1] = 3;

			break;

		}

		case 38:
		{
			card_shape[0][0] = 3;
			card_shape[1][1] = 3;
			card_shape[2][2] = 3;
			card_character[0] = 3;
			card_character[1] = 3;

			break;

		}

		case 39:
		{
			card_shape[0][0] = 3;
			card_shape[1][1] = 3;
			card_shape[2][2] = 3;
			card_character[0] = 3;
			card_character[1] = 3;

			break;

		}

		case 40:
		{
			card_shape[0][0] = 3;
			card_shape[0][2] = 3;
			card_shape[2][0] = 3;
			card_shape[2][2] = 3;
			card_character[0] = 3;
			card_character[1] = 4;

			break;

		}

		case 41:
		{
			card_shape[0][0] = 3;
			card_shape[0][2] = 3;
			card_shape[2][0] = 3;
			card_shape[2][2] = 3;
			card_character[0] = 3;
			card_character[1] = 4;

			break;

		}

		case 42:
		{
			card_shape[0][0] = 3;
			card_shape[0][2] = 3;
			card_shape[1][1] = 3;
			card_shape[2][0] = 3;
			card_shape[2][2] = 3;
			card_character[0] = 3;
			card_character[1] = 5;

			break;

		}

		case 43:
		{
			card_shape[1][1] = 4;
			card_character[0] = 4;
			card_character[1] = 1;

			break;

		}

		case 44:
		{
			card_shape[1][1] = 4;
			card_character[0] = 4;
			card_character[1] = 1;

			break;

		}

		case 45:
		{
			card_shape[1][1] = 4;
			card_character[0] = 4;
			card_character[1] = 1;

			break;

		}

		case 46:
		{
			card_shape[1][1] = 4;
			card_character[0] = 4;
			card_character[1] = 1;

			break;

		}

		case 47:
		{
			card_shape[1][1] = 4;
			card_character[0] = 4;
			card_character[1] = 1;

			break;

		}

		case 48:
		{
			card_shape[0][0] = 4;
			card_shape[2][2] = 4;
			card_character[0] = 4;
			card_character[1] = 2;

			break;

		}

		case 49:
		{
			card_shape[0][0] = 4;
			card_shape[2][2] = 4;
			card_character[0] = 4;
			card_character[1] = 2;

			break;

		}

		case 50:
		{
			card_shape[0][0] = 4;
			card_shape[2][2] = 4;
			card_character[0] = 4;
			card_character[1] = 2;

			break;

		}

		case 51:
		{
			card_shape[0][0] = 4;
			card_shape[1][1] = 4;
			card_shape[2][2] = 4;
			card_character[0] = 4;
			card_character[1] = 3;

			break;

		}

		case 52:
		{
			card_shape[0][0] = 4;
			card_shape[1][1] = 4;
			card_shape[2][2] = 4;
			card_character[0] = 4;
			card_character[1] = 3;

			break;

		}

		case 53:
		{
			card_shape[0][0] = 4;
			card_shape[1][1] = 4;
			card_shape[2][2] = 4;
			card_character[0] = 4;
			card_character[1] = 3;

			break;

		}

		case 54:
		{
			card_shape[0][0] = 4;
			card_shape[0][2] = 4;
			card_shape[2][0] = 4;
			card_shape[2][2] = 4;
			card_character[0] = 4;
			card_character[1] = 4;

			break;

		}

		case 55:
		{
			card_shape[0][0] = 4;
			card_shape[0][2] = 4;
			card_shape[2][0] = 4;
			card_shape[2][2] = 4;
			card_character[0] = 4;
			card_character[1] = 4;

			break;

		}

		case 56:
		{
			card_shape[0][0] = 4;
			card_shape[0][2] = 4;
			card_shape[1][1] = 4;
			card_shape[2][0] = 4;
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
					Position(passed_time * 9 + i, 3 + j);
					printf("●");
					break;
					}
					case 2:
					{
						Position(passed_time * 9 + i, 3 + j);
						printf("■");
						break;
					}
					case 3:
					{
						Position(passed_time * 9 + i, 3 + j);
						printf("▲");
						break;
					}
					case 4:
					{
						Position(passed_time * 9 + i, 3 + j);
						printf("★");
						break;
					}
					default:
					{
						Position(passed_time * 9 + i, 3 + j);
						printf("  ");
						
					}
				}
				

			}
			
			Position(passed_time, 4 + j);
		}


		 // 현재까지 나온 모든 카드의 문양별 갯수의 합을 저장하는 함수
		 // 종을 눌렀을 때 검사
		 // Calc_Sum();
		 
		 switch (card_character[0])
		 {
		 case 1 : sum[0] += card_character[1];
		 
		 case 2: sum[1] += card_character[1];
		 
		 case 3: sum[2] += card_character[1];
		 
		 case 4: sum[3] += card_character[1];
		 
		 }
		 
		 // 종을 누르는 인풋을 받는 단계
		 if (_kbhit)
		 {
		 	hit = _getch();
		 
		 	if (hit == -32);
		 	{
		 		hit = _getch();
		 	}
		 
		 
		 	// 엔터가 눌러졌을 때 맞는 조건인지 확인하는 부분
		 	switch (hit)
		 	{
		 	case ENTER:
		 		if (sum[0] % 5 == 0 | sum[1] % 5 == 0 | sum[2] % 5 == 0 | sum[3] % 5 == 0)
		 		{
		 			is_collect = 1;
		 		}
		 		else
		 		{
		 			is_collect = 0;
		 		}
		 		
		 		break;
		 
		 	default:
		 		break;
		 	}
		 
		 	
		 
		 
		 }
		 
		 
		 // is_collect에 따라 플레이 시간(수정하면 자동으로 남은 시간 변경) 및 점수 수정하는 함수
		 
		 if (is_collect == 1)
		 {
		 	score += score_increase;
		 	passed_time -= time_increase;
		 
		 }
		 else
		 {
		 	score -= score_decrease;
		 	
		 }



		Sleep(1000);
		
		passed_time++;
		rest_time--;

		system("cls");

	}





	return 0;
}