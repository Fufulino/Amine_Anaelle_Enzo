#ifndef CLIENT_H
#define CLIENT_H

#include "manager.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define TEST 1


void affichage_artiste(WINDOW *win, Salle tableau[], int nb_salles);
int vertification_dispo(Salle *salle, int nb_reservation, int i, int j);
void reservation_simple(WINDOW *win, Salle *salle);
void reservation(WINDOW *win, Salle tableau[], int nb_salles);

#endif