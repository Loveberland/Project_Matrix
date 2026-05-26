#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "input_handler.h"

size_t get_mat_cnt() {
	size_t cnt;
	char s[64];
	while (1) {
		fputs("how many count of matrix: ", stdout);	
		fgets(s, sizeof(s), stdin);
		s[strcspn(s, "\n")] = '\0';	// remove newline
		int check = 0;
		for (char *c = &s[0]; *c != '\0'; c++) {
			if (!isdigit((unsigned char) *c)) {
				fputs("only number\n", stdout);
				check = 1;	
				break;	
			}	
		}
		if (check) 
			continue;
		cnt = atoi(s);
		break;	
	}

	return cnt;
}
