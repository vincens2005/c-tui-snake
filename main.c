#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int game[1000][1000]; // if your terminal is over 1000 characters wide this will not work

int snake[1000][3];

int apple_pos[2];

int snake_len = 1;

int score = 0;

void setup_ncurses() {
	initscr();
	cbreak();
	noecho();
	clear();
	curs_set(FALSE);
	refresh();
}

int rand_range(int min, int max) {
	srandom(time(0));
	return (random() % (max - min + 1)) + min;
}

void draw_frame() {
	clear();
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

void generate_frame() {
	memset(game, 0, sizeof(game[0][0]) * 1000 * 1000); // clear framebuffer
	game[apple_pos[0]][apple_pos[1]] = 2;
	for (int i = 0; i < 1000; i++) {
		if (!snake[i][0]) {
			break;
		}
		game[snake[i][1]][snake[i][2]] = 1;
	}
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
	
	// random apple position
	apple_pos[0] = rand_range(0, COLS - 2);
	apple_pos[1] = rand_range(0, LINES);
	
	generate_frame();
	draw_frame();
	sleep(2);
	endwin();
	printf("hellow world\r\n");
	printf("%d\r\n", rand_range(0, 10));
	return 0;
}
