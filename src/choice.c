#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

struct termios orig_termios;

void disable_raw_mode() {
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void enable_raw_mode() {
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disable_raw_mode);

	struct termios raw = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

int calculate_choice() {
	enable_raw_mode();

	int choice = 0;
	const char *options[] = {"add", "sub", "mul"};
	char c;

	while (1) {
		fputs("\033[H\033[J", stdout);
		for (int i = 0; i < 3; i++) {
			if (i == choice)
				fprintf(stdout, "-> \033[1;32m%s\033[0m \n", options[i]);
			else
				fprintf(stdout, "    %s \n", options[i]);
		}

		read(STDIN_FILENO, &c, 1);
		if (c == '\033') {
			char seq[3];
			if (read(STDIN_FILENO, &seq[0], 1) == 0)
				continue;
			if (read(STDIN_FILENO, &seq[1], 1) == 0)
				continue;

			if (seq[0] == '[') {
				if (seq[1] == 'A') {
					if (choice > 0)
						choice--;
				} else if (seq[1] == 'B') {
					if (choice < 2)
						choice++;
				}
			}
		} else if (c == '\n')
			break;
	}

	fputs("\033[H\033[J", stdout);
	disable_raw_mode();

	return choice;
}
