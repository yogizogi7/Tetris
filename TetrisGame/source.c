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
int block[7][4][4][4] = {//7����
	{ // T��� 
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
	{    // ���� 
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
	{   // ���� ��
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
	{   // 1����
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
	{   // L����
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
	{   // L���� ��
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
	{   // �׸� ��
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
void InvisibleCursor() {//Ŀ������
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	srand(time(NULL));
}
void Position(int x, int y) {//������ ��ġ�� ���콺 Ŀ�� ����
	COORD position = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}
void BlockShape() {//���� ���� �������� ����
	blockForm = rand() % 7;

}
int CollisionCheck(int x, int y) {//�浹 ����(��ġ�� true , �Ȱ�ġ�� false)
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
void BlockDown() {//�� ������ ���������ϱ�
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
void BlockToGround() {//���� ���� �ð��̻� �� or ���� �꿩���� �� ������ ���ϰ��ϰ� ������ ���� ����� ���� �ø�
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
void DestroyBlock(){	//�� ���� ��� ���������� �� ����(õ���� ���� ����)

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
void DrawMap() {//�� �׸���

	Position(0, 0);
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 12; j++) {
			if (space[i][j] == 1) {
				Position(j * 2, i);
				printf("��");
			}
			else if (space[i][j] == 2) {
				Position(j * 2, i);
				printf("��");
			}
		}
	}
}
void DrawBlock() {//��� �׸���
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[blockForm][blockRotation][i][j]==1) {
				Position(x + j * 2, y + i);
				printf("��");
			}
		}
	}

}
void DrawRecord() {
	Position(70,1);
	printf("���� : %d",record);
}
void InputKey(){//Ű �Է¹ޱ�
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