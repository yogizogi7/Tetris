#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define LEFT 75    
#define RIGHT 77 
#define SPACE 32 
#define DOWN 80
clock_t dropStart, dropEnd, GroundStart;
int x = 8, y = 0;
int blockForm;
int blockRotation = 0;
int key;
int record = 0;
int block[7][4][4][4] = {//7종류
	{ // T모양 
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{0,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{    // 번개 
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{   // 번개 블럭
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		}
	},
	{   // 1자형
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		}
	},
	{   // L자형
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{1,0,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,0,0,0}
		}
	},
	{   // L자형 블럭
		{
			{0,0,0,0},
			{0,0,1,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{1,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{1,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		}
	},
	{   // 네모 블럭
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		}
	}
};
int space[16][12] = { {1,0,0,0,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},{1,1,1,1,1,1,1,1,1,1,1,1} };
void InvisibleCursor() {//커서제거
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	srand(time(NULL));
}
void Position(int x, int y) {//지정한 위치에 마우스 커서 위동
	COORD position = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
void BlockShape() {//블럭의 종류 랜덤으로 지정
	blockForm = rand() % 7;

}
int CollisionCheck(int x, int y) {//충돌 감지(겹치면 true , 안겹치면 false)
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j] == 1) {
				int check = space[i + y][j + x / 2];
				if (check == 1 || check == 2) {
					return 1;
				}
			}
		}
	}
	return 0;
}
void BlockDown() {//블럭 밑으로 내려가게하기
	dropEnd = clock();
	if ((double)(dropEnd - dropStart) > 1000) {
		if (CollisionCheck(x, y + 1) == 1) {
			return;
		}
		dropStart = clock();
		GroundStart = clock();
		system("cls");
		y++;
	}
}
void BlockToGround() {//블럭이 일정 시간이상 땅 or 블럭에 닿여일을 때 땅으로 변하게하고 랜덤한 블럭을 만들어 위로 올림
	if (CollisionCheck(x, y + 1) == 1) {
		if ((double)(dropEnd - GroundStart) > 1000) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (block[blockForm][blockRotation][i][j] == 1) {
						space[i + y][j + x / 2] = 2;
					}
				}
			}
			BlockShape();
			x = 8;
			y = 0;
			
		}
	}

}
void DestroyBlock(){	//한 줄이 모두 꽉차있으면 블럭 제거(천장일 때도 생각)

	for (int i = 15; i >= 0; i--) { 
		int sum = 0;
		for (int j = 1; j < 11; j++) { // 
			if (space[i][j] == 2) {
				sum++;
			}
		}
		if (sum >= 10) { 
			for (int j = 0; i - j >= 0; j++) {
				for (int x = 1; x < 11; x++) {
					if (i - j - 1 >= 0) {
						space[i - j][x] = space[i - j - 1][x];
					}
					else {
						space[i - j][x] = 0;
					}
				}
			}
			record+=100;
		}
	}
}
void DrawMap() {//맵 그리기

	Position(0, 0);
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 12; j++) {
			if (space[i][j] == 1) {
				Position(j * 2, i);
				printf("□");
			}
			else if (space[i][j] == 2) {
				Position(j * 2, i);
				printf("■");
			}
		}
	}
}
void DrawBlock() {//블록 그리기
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j]==1) {
				Position(x + j * 2, y + i);
				printf("■");
			}
		}
	}

}
void DrawRecord() {
	Position(70,1);
	printf("점수 : %d",record);
}
void InputKey(){//키 입력받기
	if (_kbhit()) {
		key = _getch();
		switch (key) {
		case LEFT: 
			if (CollisionCheck(x - 2, y) == 0) {
				x -= 2;
				GroundStart = clock();
			}
			break;
		case RIGHT:
			if (CollisionCheck(x + 2, y) == 0) {
				x += 2;
				GroundStart = clock();
			}
			break;
		case 32: 
			blockRotation++;
			if (blockRotation >= 4) {
				blockRotation = 0;
			}
			GroundStart = clock();
			break;
		case DOWN :
			if (CollisionCheck(x, y + 1) == 0) {
				y++;
				break;
			}
		}
		system("cls");
	}
}
void PlayBgm() {
	PlaySound(TEXT("BGM.wav"), NULL, SND_ASYNC | SND_FILENAME);

}
int main()
{
	PlayBgm();
	InvisibleCursor();
	dropStart = clock();
	BlockShape();
	while(1){
		DrawRecord();
		DrawMap();
		DrawBlock();
		BlockDown();
		BlockToGround();
		DestroyBlock();
		InputKey();
	}
	
	return 0;
}