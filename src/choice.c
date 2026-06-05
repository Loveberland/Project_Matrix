#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
	#include <conio.h>
	#include <windows.h>
#else
	#include <unistd.h>
	#include <termios.h>

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
#endif

#ifdef _WIN32
	static void enable_ansi_mode() {
		HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD dw_mode = 0;
		GetConsoleMode(h_out, &dw_mode);
		SetConsoleMode(h_out, dw_mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	}
#endif

int calculate_choice() {
	#ifdef _WIN32
		enable_ansi_mode();
	#else
		enable_raw_mode();
	#endif

	int choice = 0;
	const char *options[] = {"add", "sub", "mul"};

	while (1) {
		fputs("\033[H\033[J", stdout);
		for (int i = 0; i < 3; i++) {
			if (i == choice)
				fprintf(stdout, "-> \033[1;32m%s\033[0m \n", options[i]);
			else
				fprintf(stdout, "    %s \n", options[i]);
		}
		fflush(stdout);

		#ifdef _WIN32
			int c = _getch();
			if (c == 0 || c == 224) {
				int arrow = _getch();
				if (arrow == 72) {	// up arrow
					if (choice > 0)
						choice--;
				} else if (arrow == 80) {	// down arrow
					if (choice < 2)
						choice++;
				}
			} else if (c == '\r' || c == '\n')
				break;
		#else
			char c;
			read(STDIN_FILENO, &c, 1);
			if (c == '\033') {
				char seq[3];
				if (read(STDIN_FILENO, &seq[0], 1) == 0)
					continue;
				if (read(STDIN_FILENO, &seq[1], 1) == 0)
					continue;

				if (seq[0] == '[') {
					if (seq[1] == 'A') {	// up arrow
						if (choice > 0)
							choice--;
					} else if (seq[1] == 'B') {	// down arrow
						if (choice < 2)
							choice++;
					}
				}
			} else if (c == '\n')
				break;
		#endif
	}

	fputs("\033[H\033[J", stdout);
	fflush(stdout);
	#ifndef _WIN32
		disable_raw_mode();
	#endif

	return choice;
}
