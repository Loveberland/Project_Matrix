#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "input_handler.h"

static void out(const char *s, size_t len) {
	write(STDOUT_FILENO, s, len);
}

#define OUTS(lit) out((lit), sizeof(lit) - 1)

static size_t parse_uint(const char *s, size_t len) {
	size_t n = 0;
	for (size_t i = 0; i < len; i++) {
		n = n * 10 + (size_t) (s[i] - '0');
	}
	return n;
}

static double parse_double(const char *s, size_t len) {
	double n = 0.0;
	double frac = 0.1;
	int in_frac = 0;
	for (size_t i = 0; i < len; i++) {
		if (s[i] == ','){
			in_frac	 = 1;
			continue;
		}
		int d = s[i] - '0';
		if (in_frac) {
			n += d * frac;
			frac *= 0.1;
		} else {
			n = n * 10.0 + d;
		}
	}
	return n;
}

static int valid_uint(const char *s, size_t len) {
	if (len == 0)
		return 0;
	for (size_t i = 0; i < len; i++)
		if (s[i] < '0' || s[i] > '9')
			return 0;
	return 1;
}

static int valid_double(const char *s, size_t len) {
	if (len == 0)
		return 0;
	int dot_seen = 0;
	for (size_t i = 0; i < len; i++) {
		if (s[i] == '.' && !dot_seen) {
			dot_seen = 1;
			continue;
		}
		if (s[i] < '0' || s[i] > '9')
			return 0;
	}
	return 1;
}

#define BUF_SIZ 32
static char buf[BUF_SIZ];

static size_t read_line(const char *prompt, size_t prompt_len) {
	out(prompt, prompt_len);
	ssize_t n = read(STDIN_FILENO, buf, BUF_SIZ - 1);
	if (n <= 0)
		return 0;
	if (buf[n - 1] == '\n')
		n--;
	buf[n] = '\0';
	return (size_t) n;
}

static size_t get_number(const char *prompt, size_t prompt_len) {
	while (1) {
		size_t len = read_line(prompt, prompt_len);
		if (valid_uint(buf, len))
			return parse_uint(buf, len);
		OUTS("only number\n");
	}
}

static double get_number_double(const char *prompt, size_t prompt_len) {
	while (1) {
		size_t len = read_line(prompt, prompt_len);
		if (valid_double(buf, len))
			return parse_double(buf, len);
		OUTS("only number\n");	
	}
}

size_t get_mat_cnt() {
#define P1 "how many count of matrix: "
	return get_number(P1, sizeof(P1) - 1);
}

size_t get_rows() {
#define P2 "enter rows of matrix: "
	return get_number(P2, sizeof(P2) - 1);
}

size_t get_cols() {
#define P3 "enter columns of matrix: "
	return get_number(P3, sizeof(P3) - 1);
}

Matrix *get_mat(int cnt) {
	char hdr[BUF_SIZ];
	int hlen = 0;
	hdr[hlen++] = '\n';
	memcpy(hdr + hlen, "Matrix ", 7); hlen += 7;
	char tmp[16]; int tlen = 0;
	int v = cnt;
	if (v == 0)
		tmp[tlen++] = '0';
	else {
		while (v) {
			tmp[tlen++] = '0' + v % 10;
			v /= 10;
		}
	}
	for (int i = tlen - 1; i >= 0; i--)
		hdr[hlen++] = tmp[i];
	hdr[hlen++] = ':'; hdr[hlen++] = '\n';
	out(hdr, (size_t) hlen);

	size_t rows = get_rows();
	size_t cols = get_cols();
	Matrix *mat = malloc(sizeof(Matrix));
	mat->rows = rows;
	mat->cols = cols;
	mat->data = malloc(rows * cols * sizeof(double));

	char prompt[BUF_SIZ];
	for (size_t i = 0; i < rows * cols; i++) {
		int plen = 0;
		prompt[plen++] = '[';
		tlen = 0;
		size_t vi = i;
		if (vi == 0)
			tmp[tlen++] = '0';
		else {
			while (vi) {
				tmp[tlen++] = '0' + vi % 10;
				vi /= 10;
			}
		}
		for (int j = tlen - 1; j >= 0; j--)
			prompt[plen++] = tmp[j];
		prompt[plen++] = ']'; prompt[plen++] = ':'; prompt[plen++] = ' ';
		mat->data[i] = get_number_double(prompt, (size_t) plen);
	}
	return mat;
}
