#include <stdio.h>
#include <conio.h>

#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define ENTER 13

int select_mode(int *time_increase, int *score_increase, int *score_decrease)
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
	case UP : 
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

	return 0;
}




int timer(int *passed_time, int *rest_time)
{
	*rest_time -= *passed_time;

	return 0;

}

int display_card(char* card_shape[][])
{
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			printf("%d", *card_shape[i][j]);
		}
		printf("\n");
	}
	

	return 0;
}

int main()
{
	int time_increase = 0;
	int score_increase = 0;
	int score_decrease = 0;
	int rest_time = 60;
	int passed_time = 0;
	

	// 모드를 선택하는 함수
	select_mode(&time_increase, &score_increase, &score_decrease);

	// 게임시작
	while (1)
	{
		
		



		sleep(1000);
		
		passed_time++

	}





	return 0;
}