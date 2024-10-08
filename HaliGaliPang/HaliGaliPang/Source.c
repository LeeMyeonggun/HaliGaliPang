// 헤더 파일을 선언하는 부분
// 출력을 위한 stdio.h
// 콘솔창의 원하는 위치를 지정해주고 비동기 키 입력을 받기 위한 windows.h
// 난이도 설정 시 키 입력을 받기 위한 conio.h
// 랜덤 함수를 사용하기 위한 time.h
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>


// 난이도 선택 시 키 입력에 대한 숫자를 LEFT, RIGHT, DOWN 이라는 이름의 매크로로 매핑하는 부분
// 문양이 들어갈 배열의 높이와 너비를 매크로로 지정
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define CARDHEIGHT 3
#define CARDWIDTH 3
#define SIZE 1000



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

// 스코어 보드의 경우 시작 위치 점수
typedef struct
{
	const int x;
	const int y;
	int score;

} ScoreBoard;

// 벨의 경우 시작 위치
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


// 카드 덱을 섞어주는 함수
void Shuffle(int array[], int size)
{

	int* ptr;
	int temp = 0;
	int ind = 0;

	for (int i = 0; i < size; i++)
	{

		ind = rand() % size;
		ptr = &array[i];

		temp = array[i];

		*ptr = array[ind];

		ptr = &array[ind];

		*ptr = temp;

	}

}


// 텍스트의 색상을 변경해주는 함수
void setColor(int color) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}



int main()
{
	// 난이도에 따라 결정되는 맞았을 경우 스코어 증가량 score_increase,  틀렸을 경우 스코어 감소량 scored_decrease 정의 및 초기화
	int score_increase = 0;
	int score_decrease = 0;

	// 지나간 시간을 체크하는 변수 passed_time 정의 및 초기화
	int passed_time = 0;
	
	// 각 문양 별 합계를 계산하기 위한 sum 배열 정의 및 초기화 
	int sum[] = { 0, 0, 0, 0 };
	
	// 점수를 나타내는 변수 score 정의 및 초기화
	int score = 0;

	// 56장의 카드셋을 담고있는 배열 card_set을 정의하고 1~56의 숫자로 초기화
	int card_set[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56 };

	// 정답을 입력했을 때 카드셋의 인덱스를 저장해 줄 ind 변수 선언 ( 정답을 입력하면 나열된 카드들이 없어지고 다음 카드셋부터 다시 출력되어 나오기 위해서) 및 초기화
	int ind = 0;

	// 난이도에 따라 카드가 나오는 시간 간격을 조정하기 위한 multiple 변수를 선언하고 초기화 
	int multiple = 0;

	// 정답 여부에 따라 효과를 주기 위한 is_collec 변수를 선언하고 초기화
	int is_collect = 0;

	// 총 게임 시간을 나타내는 total_time 변수를 선언하고 초기화
	int	total_time = 0;



	// 랜덤하게 카드셋을 섞어주는 파트
	srand(time(NULL));
	int size = sizeof(card_set) / sizeof(int);
	 
	Shuffle(card_set, size);
	 
	 
	// UI들의 위치를 지정
	Timebar timebar = { 0, 0, total_time - passed_time, 0 };
	Timer timer = { 122, 0, total_time - passed_time };
	ScoreBoard scoreboard = { 122, 2, score };
	Bell bell = { 60, 10 };



	// 모드를 선택하는 부분
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

		score_increase = 400;
		score_decrease = 400;
		multiple = 1;
		total_time = 30;

		break;

		// 왼쪽 방향키 Hard 난이도

	case DOWN:
		score_increase = 200;
		score_decrease = 100;
		multiple = 2;
		total_time = 60;

		break;
		// 오른쪽 방향키 Normal 난이도
	case RIGHT:
		score_increase = 100;
		score_decrease = 0;
		multiple = 3;
		total_time = 90;

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
		
		for (int i = 0; i < total_time - passed_time; i++)
		{
			timebar.count = i;
			Position(timebar.x + timebar.count * 2, timebar.y);
			setColor(7);
			printf("■");

		}
			

		Position(timer.x, timer.y);
		timer.time = total_time - passed_time;
		setColor(7);
		printf("%d", timer.time);

		Position(scoreboard.x, scoreboard.y);
		setColor(7);
		printf("Score : %d", score);

								

		// 랜덤하게 뽑을 카드의 문양을 저장할 행렬 card_shape와 카드의 문양과 숫자에 대한 정보를 저장할 배열card_characte 를 선언 및 초기화
		int card_shape[CARDHEIGHT][CARDWIDTH] = { {0, 0, 0},
												  {0, 0, 0},
												  {0, 0, 0} };
		int card_character[] = { 0 , 0 };


		// 문양 별 합을 계산할 sum도 항상 0으로 초기화해서 이전에 계산한 값들이 영향을 주지 않게 한다.
		for (int i = 0; i < 4; i++)
		{
			sum[i] = 0;
		}

		// 본격적으로 카드셋 배열의 passed_time / multiple 인덱스의 값을 이용해 문양을 출력하기 위한 반복문
		for (int k = ind; k < passed_time / multiple; k++)
		{

			// 카드셋의 문양을 출력하기 위한 card_shape 행렬 초기화
			for (int j = 0; j < 3; j++)
			{

				for (int i = 0; i < 3; i++)
				{
					card_shape[i][j] = 0;
				}

			}


			// 카드셋의 문양과 갯수에 대한 정보를 저장하기 위한 card_character 배열 초기화
			for (int i = 0; i < 2; i++)
			{
				card_character[i] = 0;
			}



			// 카드셋의 값에 따라 card_shape 행렬과 card_character 배열에 값을 할당
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

			// 할당된 card_shape에 따라 문양을 출력
			
			for (int j = 0; j < 3; j++)
			{
				for (int i = 0; i < 3; i++)
				{
					switch (card_shape[i][j])
					{
					case 1:
					{
						setColor(7);
						Position((k - ind) * 9 + i, 3 + j);
						printf("●");
						break;
					}
					case 2:
					{
						setColor(7);
						Position((k - ind) * 9 + i, 3 + j);
						printf("■");
						break;
					}
					case 3:
					{
						setColor(7);
						Position((k - ind) * 9 + i, 3 + j);
						printf("▲");
						break;
					}
					case 4:
					{
						setColor(7);
						Position((k - ind) * 9 + i, 3 + j);
						printf("★");
						break;
					}
					default:
					{
						setColor(7);
						Position((k - ind) * 9 + i, 3 + j);
						printf("  ");
						break;

					}
					}


				}

			}


			// 카드의 문양별 합을 나타내는 sum 배열에 값을 누적
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



		}

		// 스페이스바 입력을 판단할 시간을 주기위해 500ms * multiple 만큼의 시간 대기
		Sleep(500 * multiple);

		// 스페이스바 입력을 받는 경우 
		if (GetAsyncKeyState(VK_SPACE) & 0x0001)
		{


			
			
			// 합 배열의 각 문양 별 모양의 갯수의 합이 5의 배수이면 노란색으로 UI를 바꾸고 점수를 증가
			if (sum[0] % 5 == 0 && sum[0] != 0)
			{
				score += score_increase * sum[0] / 5;
				ind = passed_time / multiple;
				
			

			}
			else if (sum[1] % 5 == 0 && sum[1] != 0)
			{
				score += score_increase * sum[1] / 5;
				ind = passed_time / multiple;
				is_collect = 1;

			}
			else if (sum[2] % 5 == 0 && sum[2] != 0)
			{
				score += score_increase * sum[2] / 5;
				ind = passed_time / multiple;
				is_collect = 1;

			
			}
			else if (sum[3] % 5 == 0 && sum[3] != 0)
			{
				score += score_increase * sum[3] / 5;
				ind = passed_time / multiple;
				is_collect = 1;

					

			}
			else // 5의 배수가 아닐 경우 점수 감소
			{
				if (score > score_decrease)
				{
					score -= score_decrease;
					is_collect = 0;

				}

			}

			// bell.txt를 파일입력 받아 종 모양을 출력
			system("cls");

			FILE* file = fopen("bell.txt", "r");

			char buffer[SIZE] = { 0, };

			fread(buffer, 1, SIZE, file);

			if (is_collect == 1)
			{
				setColor(6);
				printf("%s", buffer);
			}
			else
			{
				setColor(7);
				printf("%s", buffer);
			}

			
			fclose(file);


		}

		// 다음 카드 표시까지 500 * multiple 만큼의 준비 시간
		Sleep(500 * multiple);

		// 지나간 시간을 나타내는 변수 passed_time이 60이 되면 종료
		passed_time += multiple;

		if (passed_time == total_time)
		{
			system("cls");
			break;
		}

		// 화면에 출력된 카드의 숫자가 15 이상이면 종료
		if (passed_time - ind * multiple > 15 * multiple)
		{
			system("cls");
			break;
		}

		// 화면을 초기화하고 다시 게임 시작 준비
		system("cls");



	}


	// 게임이 끝났을 경우 표시되며 획득한 스코어를 화면에 출력
	Position(45, 8);
	setColor(7);
	printf("game over! your score is %d.", score);





	return 0;
}
