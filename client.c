#include "client.h"
#include "better_scan.h"
#include "manager.h"

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define TEST 1


void affichage_artiste(WINDOW *win, Salle tableau[], int nb_salles) {
  
  werase(win), mvwprintw(win, 1, 0, "Liste des artistes : \n");
  
  for (int i = 0; i < nb_salles; i++) {
    mvwprintw(win, i + 1, 0, "%s ", tableau[i].concert.artiste);
  }
}


int vertification_dispo(Salle *salle, int nb_reservation, int i, int j) {
  
  for (int a = 0; a < nb_reservation; a++) {
    if (salle->concert.categorieA.cat_rangees != 0) {
      return 1;
    }
  }
  return 0;
}


void reservation_simple(WINDOW *win, Salle *salle) {
  
  int i, j;
  int somme = 0;
  int etudiant = 2;
  char texte_choix[MAX] = {0};
  char choix_categorie = 'R';
  
  while (choix_categorie != 'A' && choix_categorie != 'B' && choix_categorie != 'C') {
    werase(win);
    better_scan_str(win, 1, 0, "Entrez la catégorie que vous souhaitez réserver : ", texte_choix, MAX);
    choix_categorie = texte_choix[0];
    werase(win);
  }
  while (etudiant != 1 && etudiant != 0) {
    werase(win);
    etudiant = better_scan_int(win, 1, 0, "Êtes-vous un étudiant ? (1 pour oui, 0 pour non) : ");
  }
  werase(win);
  if (choix_categorie == 'A') {
    if (salle->concert.categorieA.cat_rangees == 0) {
      mvwprintw(win, 1, 0, "La catégorie A n'esxiste pas, vous ne pouvez pas réserver de siège ! ");
    } else {
      werase(win);
      i = better_scan_compare(win, 1, 0, 0, salle->concert.categorieA.cat_rangees, "Saisissez la rangée que vous voulez réserver : ") - 1;
      werase(win);
      j = better_scan_compare(win, 1, 0, 0, salle->nb_sieges, "Saisissez la colonne que vous voulez réserver : ") -
          1;
      werase(win);
      while (salle->concert.categorieA.tableau[i][j] != 0) {
        i = better_scan_compare(win, 1, 0, 0, salle->concert.categorieA.cat_rangees, "Saisissez la rangée que vous voulez réserver : ") - 1;
        werase(win);
        j = better_scan_compare(win, 1, 0, 0, salle->nb_sieges, "Saisissez la colonne que vous voulez réserver : ") - 1;
        werase(win);
      }
      salle->concert.categorieA.tableau[i][j] = 1;
      if(etudiant){
        somme += 0.8*salle->concert.categorieA.prix;
      }else{
        somme += salle->concert.categorieA.prix;
      }
    }

  } else if (choix_categorie == 'B') {
    if (salle->concert.categorieB.cat_rangees == 0) {
      mvwprintw(win, 1, 0, "La catégorie B n'existe pas, vous ne pouvez pas réserver de siège ! ");
      werase(win);
    } else {
      i = better_scan_compare(win, 1, 0, salle->concert.categorieA.cat_rangees + 1, 
      salle->concert.categorieA.cat_rangees + salle->concert.categorieB.cat_rangees, "Saisissez la rangée que vous voulez réserver : ") - 1;
      werase(win);
      j = better_scan_compare(win, 1, 0, 0, salle->nb_sieges, "Saisissez la colonne que vous voulez réserver : ") - 1;
      werase(win);

      while (salle->concert.categorieB.tableau[i][j] != 0) {
        i = better_scan_compare(win, 1, 0, salle->concert.categorieA.cat_rangees + 1,
        salle->concert.categorieA.cat_rangees + salle->concert.categorieB.cat_rangees, "Saisissez la rangée que vous voulez réserver : ") - 1;
        werase(win);
        j = better_scan_compare(win, 1, 0, 0, salle->nb_sieges, "Saisissez la colonne que vous voulez réserver : ") -
            1;
        werase(win);
      }
      salle->concert.categorieB.tableau[i][j] = 1;
      if(etudiant){
        somme += 0.8*salle->concert.categorieB.prix;
      }else{
        somme += salle->concert.categorieB.prix;
      }
    }
  } else if (choix_categorie == 'C') { // marche pas
    if (salle->concert.categorieC.cat_rangees == 0) {
      mvwprintw(win, 1, 0, "La catégorie C n'esxiste pas, vous ne pouvez pas réserver de siège ! ");
      werase(win);
    } else {
      i = better_scan_compare(win, 1, 0,salle->concert.categorieA.cat_rangees + salle->concert.categorieB.cat_rangees + 1,
      salle->concert.categorieA.cat_rangees + salle->concert.categorieB.cat_rangees + salle->concert.categorieC.cat_rangees,
      "Saisissez la rangée que vous voulez réserver : ") - 1;
      werase(win);
      j = better_scan_compare(win, 1, 0, 0, salle->nb_sieges, "Saisissez la colonne que vous voulez réserver\n") - 1;
      werase(win);
      while (salle->concert.categorieC.tableau[i][j] != 0) {
        i = better_scan_compare(win, 1, 0, salle->concert.categorieA.cat_rangees + salle->concert.categorieB.cat_rangees + 1,
        salle->concert.categorieA.cat_rangees + salle->concert.categorieB.cat_rangees + salle->concert.categorieC.cat_rangees,
        "Saisissez la rangée que vous voulez réserver : ") - 1;
        werase(win);
        j = better_scan_compare(win, 1, 0, 0, salle->nb_sieges, "Saisissez la colonne que vous voulez réserver : ") - 1;
        werase(win);
      }
      salle->concert.categorieC.tableau[i][j] = 1;
      if(etudiant){
        somme += 0.8*salle->concert.categorieC.prix;
      }else{
        somme+= salle->concert.categorieC.prix;
      }
    }
  }
  mvwprintw(win, 1, 0,"La valeur totale de votre réservation est de %d!", somme);
  wgetch(win);
  werase(win);
}

void reservation(WINDOW *win, Salle tableau[], int nb_salles) {
  int nb_tableau = better_scan_int(win, 1, 0, "Pour quel concert voulez-vous réserver ? ") - 1;
  werase(win);
  while (nb_tableau < 0 || nb_tableau > nb_salles) {
    werase(win);
    nb_tableau = better_scan_int(win, 1, 0, "Valeur incorrecte, Pour quel concert voulez-vous réserver ? ");
  }
  int nb_reservation = better_scan_int(win, 1, 0, "Entrez le nombre de siège que vous voulez réserver : ");
  werase(win);
  while (nb_reservation <= 0) {
    werase(win);
    nb_reservation = better_scan_int(
        win, 1, 0, "Entrez le nombre de siège que vous voulez réserver : ");
  }

  for (int i = 0; i < nb_reservation; i++) {
    reservation_simple(win, &tableau[nb_tableau]);
  }
}

