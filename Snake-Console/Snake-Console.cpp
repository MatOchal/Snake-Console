// Snake-Console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <string>
#include "windows.h"
using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

bool gameOver;

const int width = 50;
const int height = 25;
const int tail_max = 100;

int grid[width][height];
int tail_x[tail_max];
int tail_y[tail_max];

int x, y, length, fruit_x, fruit_y;

enum eDirection { STOP=0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	length = 0;
	fruit_x = rand() % width;
	fruit_y = rand() % height;
}

void input() {
	if (_kbhit()) {
		switch (_getch()) {
		case KEY_UP:
			if (dir != DOWN)
				dir = UP;
			break;
		case KEY_DOWN:
			if (dir != UP)
				dir = DOWN;
			break;
		case KEY_LEFT:
			if (dir != RIGHT)
				dir = LEFT;
			break;
		case KEY_RIGHT:
			if (dir != LEFT)
				dir = RIGHT;
			break;
		default: {		}
		}
	}
}

void draw() {
	system("cls");
	char c = ' ';
	std::string s = "";

	for (int i = 0; i < width+2; i++)
		s = s + "#";
	
	s = s + "\n";

	for (int j = 0; j < height; j++) {
		s = s + "#";
		for (int i = 0; i < width; i++) {

			if (i == x && j == y)
				c = gameOver? 'X' : 'O';

			else if (i == fruit_x && j == fruit_y)
				c = 'F';

			else {
				for (int z = 0; z < length; z++) {
					if (i == tail_x[z] && j == tail_y[z]) {
						c = 'o';
					}
				}
			}

			s = s + c;
			c = ' ';
		}
		s = s + "#\n";
	}
	for (int i = 0; i < width+2; i++)
		s = s + "#";

	cout << s;
}

void logic() {

	int prev_x = x;
	int prev_y = y;

	int x1 = 0;
	int y1 = 0;
	
	switch (dir) {
		case UP: {
			y--;
			y = (y < 0) ? height : y;
			break;
		}
		case DOWN: {
			y++;
			y = y % height;
			break;
		}
		case LEFT: {
			x--;
			x = (x < 0) ? width : x;
			break;
		}
		case RIGHT: {
			x++;
			x = x % width;
			break;
		}
	}

	if (x == fruit_x && y == fruit_y) {
		fruit_x = rand() % width;
		fruit_y = rand() % height;
		if (length < tail_max)
			length++;
	}

	for (int z = 0; z < length; z++) {
		x1 = tail_x[z];
		y1 = tail_y[z];
		tail_x[z] = prev_x;
		tail_y[z] = prev_y;
		prev_x = x1;
		prev_y = y1;

		if (x == tail_x[z] && y == tail_y[z]) {
			gameOver = true;
		}
	}
}

int main()
{
	int i = 0;
	setup();
	while (!gameOver) {
		input();
		if (i % 400 == 0)
			logic();
		draw();
		Sleep(1);
	}
	cout << "\n GAMEOVER!!! \n";
	cout << "Your tail was "<< length <<" sections long";
	_getch();
    return 0;
}

