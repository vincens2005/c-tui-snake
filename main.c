#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

int game[1000][1000];

int snake[1000][3];

int snake_len = 1;

void setup_ncurses() {
	initscr();
	cbreak();
	noecho();
	clear();
	curs_set(FALSE);
	refresh();
}

void draw_frame() {
	for (int i = 0; i < COLS; i++) {
		for (int ii = 0; ii < LINES; ii++) {
			if (game[i][ii] == 1) {
				mvprintw(ii, i, "#");
			}
			if (game[i][ii] == 2) {
				mvprintw(ii, i, "()");
			}
		}
	}
	refresh();
}

void move_snake() {
	int new_snake[1000][3];
	for (int i = 0; i < 1000; i++) {
		new_snake[i + 1][0] = snake[i][0];
		new_snake[i + 1][1] = snake[i][1];
		new_snake[i + 1][2] = snake[i][2];
		if (!snake[i][0]) {
			break;
		}
	}
	int snake = new_snake;
}

int main() {
	setup_ncurses();
	game[50][10] = 1;
	draw_frame();
	sleep(1);
	
	snake[0][0] = 1;
	snake[0][1] = 15;
	snake[0][2] = 3;
	printf("hellow world");
	endwin();
	return 0;
}

