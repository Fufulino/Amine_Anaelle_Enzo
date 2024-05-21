
#ifndef BTS_H
#define BTS_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

int better_scan_int(WINDOW *win, int y, int x, char *message);
float better_scan_float(WINDOW *win, int y, int x, char *message);
void better_scan_str(WINDOW *win, int y, int x, char *message, char *tableau, int taille);
int better_scan_compare(WINDOW *win, int y, int x, int min_1, int max_1, char *message);

#endif
