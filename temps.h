#ifndef TEMPS_H
#define TEMPS_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TEST 1

void ajouter_heure(int *heure, int *minute,WINDOW *win);
void afficher_heure(int heure, int minute,WINDOW *win);

#endif

