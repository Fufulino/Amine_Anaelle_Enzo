#include "temps.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define MAX 50
#define TEST 1

// Ajouter comparaison heure avec heure du concert


void ajouter_heure(int *heure, int *minute,WINDOW *win) {
  int ajout_minute, ajout_heure;
  ajout_heure = better_scan_compare(win, 20, 5, 0, 23, "Saisissez le nombre d'heures que vous voulez ajouter\n");
  *heure += ajout_heure;
  while (*heure > 23) {
    *heure -= 24;
  }
  ajout_minute = better_scan_compare(win, 20, 5, 0, 59, "Choisissez le nombre de minutes à ajouter\n");
  *minute += ajout_minute;
  while (*minute > 59) {
    *minute -= 60;
    *heure += 1;
  }

  mvwprintw(win,"Vous avez ajouté : %d heure(s) et %d minute(s)\n", ajout_heure,ajout_minute);
}

void afficher_heure(int heure, int minute,WINDOW *win) {
  if (heure > 1) {
    if (minute > 1) {
      mvwprintw(win, 20, 5, "Il est %d heures et %d minutes\n", heure, minute);
    } else {
      mvwprintw(win, 20, 5, "Il est %d heures et %d minute\n", heure, minute);
    }
  } else {
    mvwprintw(win, 20, 5, "Il est %d heure et %d minute\n", heure, minute);
  }
}
