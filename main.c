#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

int framerate = 10; 

int game[1000][1000]; // if your terminal is over 1000 characters wide this will not work

int snake[1000][3];

int apple_pos[2];

int snake_len = 8;

int direction = LEFT;

void setup_ncurses() {
	initscr();
	cbreak();
	noecho();
	clear();
	nodelay(stdscr, TRUE);
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

void set_apple_pos() {
	// random apple position
	apple_pos[0] = rand_range(0, COLS - 2);
	apple_pos[1] = rand_range(0, LINES);
}

void move_snake() {
	int new_snake[1000][3];
	
	new_snake[0][0] = 1;
	new_snake[0][1] = snake[0][1];
	new_snake[0][2] = snake[0][2];
	if (direction == RIGHT) {
		new_snake[0][1] += 1;
	}
	else if (direction == LEFT) {
		new_snake[0][1] -= 1;
	}
	else if (direction == DOWN) {
		new_snake[0][2] += 1;
	}
	else if (direction == UP) {
		new_snake[0][2] -= 1;
	}
	
	// wrap snake
	if (new_snake[0][1] < 0) {
		new_snake[0][1] = COLS;
	}
	if (new_snake[0][1] > COLS) {
		new_snake[0][1] = 0;
	}
	if (new_snake[0][2] == LINES) {
		new_snake[0][2] = 0;
	}
	if (new_snake[0][2] < 0) {
		new_snake[0][2] = LINES - 1;
	}
	
	for (int i = 0; i < 999; i++) {
		if (!snake[i][0]) {
			break;
		}
		new_snake[i + 1][0] = snake[i][0];
		new_snake[i + 1][1] = snake[i][1];
		new_snake[i + 1][2] = snake[i][2];
	}
	
	for (int i = 0; i < 1000; i++) {
		// snake[i][0] = new_snake[i][0];
		snake[i][1] = new_snake[i][1];
		snake[i][2] = new_snake[i][2];
	}
}

void build_snake() {
	for (int i = 0; i < snake_len; i++) {
		snake[i][0] = 1;
		snake[i][1] = COLS / 2 + i;
		snake[i][2] = LINES / 2;
	}
}

int main() {
	setup_ncurses();
	build_snake();
	set_apple_pos();
	while (1) {
		move_snake();
		generate_frame();
		draw_frame();
		usleep(100000);
	}
	endwin();
	printf("hellow world\r\n");
	printf("%d\r\n", rand_range(0, 10));
	return 0;
}
