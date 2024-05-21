#ifndef MANAGER_H
#define MANAGER_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 50
#define max_rangees 100
#define TEST 1



typedef struct {
  float prix;
  int nb_place;
  int cat_rangees;
  int tableau[MAX][MAX];   
} Categorie;

typedef struct {
  int jour_debut;
  int heure_debut;
  int minute_debut;
  int jour_fin;
  int heure_fin;
  int minute_fin;
  Categorie categorieA;
  Categorie categorieB;
  Categorie categorieC;
  char artiste[MAX];
} Concert;

typedef struct {
  char nom[MAX];
  int nb_rangees;
  int nb_sieges;
  Concert concert;
} Salle; // On aura un tableau de salle après


Salle constructeur_salle(WINDOW *win);

void constructeur_concert(Salle *salle, WINDOW *win);
void affichage_rangees(WINDOW *win, int y, int x, char *lettre, int nb_places);
void affichage_nb_sieges(WINDOW *win, int y, int x, char *lettre, int nb_sieges);
void affichage_prix(WINDOW *win, int y, int x, char *lettre, float prix);
void affichage_donnees_manager(WINDOW *win, Concert concert);
void affichage_tribune(WINDOW *win, Salle * salle);

#endif