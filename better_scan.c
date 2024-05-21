
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "better_scan.h"

#define MAX 50



/// Better_scan pour demander uniquement des int

int better_scan_int(WINDOW *win, int y, int x, char *message) {
  
  char tableau[MAX] = {0};
  int val = 1;
  int chr;
  int longueur = 0;
  int nx, ny;

  mvwprintw(win, y, x, "%s", message);
  getyx(win, ny, nx);

  while (TRUE) {
    chr = wgetch(win);
    if ((chr == KEY_ENTER || chr == '\n' || chr == '\r') && longueur > 0) {
      break;
    }
    if ((chr == KEY_BACKSPACE || chr == KEY_DC || chr == 127) && longueur > 0 ) {
      tableau[--longueur] = '\0';
      mvwaddstr(win, ny, nx+longueur, " ");
      wmove(win, ny, nx+longueur);
    }
    if (chr >= '0' && chr <= '9'){
      waddch(win, chr);
      tableau[longueur++] = chr;
    }
  }
  return atoi(tableau);
}



/// Better_scan pour demander uniquement des float

float better_scan_float(WINDOW *win, int y, int x, char *message) {
  
  char tableau[MAX] = {0};
  int val = 1;
  int chr;
  int longueur = 0;
  char *fin; 
  float prix;
  int nx,ny;

  mvwprintw(win, y, x, "%s", message);
  getyx(win, ny, nx);
  
  while (TRUE) {
    chr = wgetch(win);
    if ((chr == KEY_ENTER || chr == '\n' || chr == '\r') && longueur > 0) {
      prix = strtof(tableau,&fin);
      if(fin == tableau){
        mvwprintw(win, y, x, "Erreur");
      }
      else{
        return prix;
      }
      break;
    }
    if ((chr == KEY_BACKSPACE || chr == KEY_DC || chr == 127) && longueur > 0 ) {
      tableau[--longueur] = '\0';
      mvwaddstr(win, ny, nx+longueur, " ");
      wmove(win, ny, nx+longueur);
    }
    if (chr >= '0' && chr <= '9' || chr == '.') {
      waddch(win, chr);
      tableau[longueur++] = chr;
    }
  }
  return strtof(tableau,&fin);
}



/// Better_scan pour demander une chaine de caractere (espaces, chiffres, lettres uniquement)

void better_scan_str(WINDOW *win, int y, int x, char *message, char *tableau, int taille) {

  int chr;
  int longueur = 0;
  int nx, ny;

  for (int i = 0; i < taille; i++) {
    tableau[i] = '\0';
  }
  
  mvwprintw(win, y, x, "%s", message);
  getyx(win, ny, nx);

  while (TRUE) {
    chr = wgetch(win);
    if ((chr == KEY_ENTER || chr == '\n' || chr == '\r') && longueur > 0) {
      break;
    }
    if ((chr == KEY_BACKSPACE || chr == KEY_DC || chr == 127) && longueur > 0 ) {
      tableau[--longueur] = '\0';
      mvwaddstr(win, ny, nx+longueur, " ");
      wmove(win, ny, nx+longueur);
    }
    if (((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z') || (chr >= '0' && chr <= '9') || (chr == ' ')) && (longueur < taille - 1)) {
      waddch(win, chr);
      tableau[longueur++] = chr;
    }
  } 
}



/// Better_scan pour demander uniquement des int en comparant entre une valeur (int) minimum et maximum 

int better_scan_compare(WINDOW *win, int y, int x, int min_1, int max_1, char *message) {
  
  char tableau[MAX] = {0};
  int val = 1;
  int chr;
  int longueur = 0;
  int nx, ny;

  mvwprintw(win, y, x, "%s", message);
  getyx(win, ny, nx);

  while (TRUE) {
    chr = wgetch(win);
    if ((chr == KEY_ENTER || chr == '\n' || chr == '\r') && longueur > 0  && (atoi(tableau) >= min_1 && atoi(tableau) <= max_1)) {
      break;
    }
    if ((chr == KEY_BACKSPACE || chr == KEY_DC || chr == 127) && longueur > 0 ) {
      tableau[--longueur] = '\0';
      mvwaddstr(win, ny, nx+longueur, " ");
      wmove(win, ny, nx+longueur);
    }
    if (chr >= '0' && chr <= '9') {
      waddch(win, chr);
      tableau[longueur++] = chr;
    }
  }
  return atoi(tableau);
}

