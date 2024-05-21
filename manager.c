#include "manager.h"
#include "better_scan.h"
#include "temps.h"

#define MAX 50
#define TEST 1


void affichage_rangees(WINDOW *win, int y, int x, char *lettre, int nb_places) {
  mvwprintw(win, y, x, "Nombre de rangées de la categorie %c = %d", *lettre, nb_places);
}

void affichage_nb_sieges(WINDOW *win, int y, int x, char *lettre, int nb_sieges) {
  mvwprintw(win, y, x, "Nombre de sièges de la categorie %c = %d", *lettre, nb_sieges);
}


void affichage_prix(WINDOW *win, int y, int x, char *lettre, float prix) {
  mvwprintw(win, y, x, "Prix de la categorie %c = %.2f", *lettre, prix);
}


void affichage_donnees_manager(WINDOW *win, Concert concert) {

  mvwprintw(win, 1, 0, "Heure de début du concert : %d h %d", concert.heure_debut,
         concert.minute_debut);
  mvwprintw(win, 2, 0,"Heure de fin du concert : %d h %d", concert.heure_fin,
         concert.minute_fin);

  mvwprintw(win, 3, 0, "Le nom de l'artiste est : %s", concert.artiste);
  mvwprintw(win, 4, 0, "Nombre de rangées : %d", concert.categorieA.cat_rangees +
                                         concert.categorieB.cat_rangees +
                                         concert.categorieC.cat_rangees);
  mvwprintw(win, 5, 0, "Nombre de rangées pour la catégorie A : %d",
         concert.categorieA.cat_rangees);
  mvwprintw(win, 6, 0, "Nombre de rangées pour la catégorie B : %d",
         concert.categorieB.cat_rangees);
  mvwprintw(win, 7, 0, "Nombre de rangées pour la catégorie C : %d",
         concert.categorieC.cat_rangees);
  mvwprintw(win, 8, 0, "Le nombre de sièges par rangée est : %d", 
        (concert.categorieA.nb_place + concert.categorieB.nb_place + concert.categorieC.nb_place)/(concert.categorieA.cat_rangees + concert.categorieB.cat_rangees + concert.categorieC.cat_rangees));

  mvwprintw(win, 9, 0, "Nombre de sièges : %d", concert.categorieA.nb_place +
                                        concert.categorieB.nb_place +
                                        concert.categorieC.nb_place);

  affichage_nb_sieges(win,11,0, "A", concert.categorieA.nb_place);
  affichage_nb_sieges(win,12,0, "B", concert.categorieB.nb_place);
  affichage_nb_sieges(win,13,0, "C", concert.categorieC.nb_place);

  affichage_prix(win,15,0, "A", concert.categorieA.prix);
  affichage_prix(win,16,0, "B", concert.categorieB.prix);
  affichage_prix(win,17,0, "C", concert.categorieC.prix);

  mvwprintw(win, 20, 0, "Chiffre d'affaire potentiel : %2.f",
         concert.categorieA.prix * concert.categorieA.nb_place +
             concert.categorieB.prix * concert.categorieB.nb_place +
             concert.categorieC.prix * concert.categorieC.nb_place);

  // chiffre d'affaire actuel (si tableau == 1 alors ajouter valeure place)
  float somme = 0;
  float compteur = 0;
  for (int i = 0; i < concert.categorieA.cat_rangees; i++) {
    for (int j = 0; j < concert.categorieA.nb_place; j++) {
      if (concert.categorieA.tableau[i][j] == 1) {
        compteur ++;
        somme += concert.categorieA.prix;
      }
    }
  }
  for (int i = 0; i < concert.categorieB.cat_rangees; i++) {
    for (int j = 0; j < concert.categorieB.nb_place; j++) {
      if (concert.categorieB.tableau[i][j] == 1) {
        compteur ++;
        somme += concert.categorieB.prix;
      }
    }
  }
  for (int i = 0; i < concert.categorieC.cat_rangees; i++) {
    for (int j = 0; j < concert.categorieC.nb_place; j++) {
      if (concert.categorieC.tableau[i][j] == 1) {
        compteur ++;
        somme += concert.categorieC.prix;
      }
    }
  }
  mvwprintw(win, 22, 0, "Chiffre d'affaire actuel : %.2f", somme);
  mvwprintw(win, 23, 0, "Ratio des sièges : %.2f", compteur/(concert.categorieA.nb_place + concert.categorieB.nb_place + concert.categorieC.nb_place)); 
}


void affichage_tribune(WINDOW *win, Salle *salle){

  int rang = 1;

  mvwprintw(win, 1, salle->nb_sieges+1, "Salle");

  for(int i=0; i<salle->nb_sieges;i++){
    mvwprintw(win, 2, 3*i, "---");
  }

  for(int i=0; i<salle->nb_sieges;i++){
    mvwprintw(win, 3, 3*i + 3, " C ");
  }

  for(int i=0; i<salle->nb_sieges;i++){
    if(i<9){
      mvwprintw(win, 4, 3*i+3, " 0%d", i+1);
    }
    else{
      mvwprintw(win, 4, 3*i+3, " %d",i+1);
    }
  }

  int y = 5;
  for(int i = 0; i < salle->concert.categorieA.cat_rangees; i++){
    mvwprintw(win, y, 0, "R%d", rang);
    rang++;
    for(int j = 0; j < salle->nb_sieges; j++){
      if(salle->concert.categorieA.tableau[i][j] == 0){
        mvwprintw(win, y, 3*j+3, " 0 ");
      }
      else{
        mvwprintw(win, y, 3*j+3, " X ");
      }
    }
    y++;
  }

  for(int i = 0; i< salle->concert.categorieB.cat_rangees ; i++){
    mvwprintw(win, y, 0, "R%d",rang);
    rang++;
    for(int j = 0; j<salle->nb_sieges; j++){
      if(salle->concert.categorieB.tableau[i][j] == 0){
        mvwprintw(win, y, 3*j+3, " 0 ");
      }
      else{
        mvwprintw(win, y, 3*j+3, " X ");
      }
    }
    y++;
  }
  for(int i = 0; i<salle->concert.categorieC.cat_rangees ; i++){
    mvwprintw(win, y, 0, "R%d", rang);
    rang++;
    for(int j = 0; j<salle->nb_sieges; j++){
      if(salle->concert.categorieC.tableau[i][j] == 0){
        mvwprintw(win, y, 3*j+3, " 0 ");
      }
      else{
        mvwprintw(win, y, 3*j+3, " X ");
      }
    }
    y++;
  }

  // Regler affichage (centré) et decider pour les 6 chiffres apres la virgule
  mvwprintw(win, y, 50, "Légende : ");
  mvwprintw(win, y+1, 50, "0 - Catégorie A (%2.f euros) ",salle->concert.categorieA.prix);
  mvwprintw(win, y+2, 50, "0 - Catégorie B (%2.f euros) ",salle->concert.categorieB.prix);
  mvwprintw(win, y+3, 50, "0 - Catégorie C (%f euros) ",salle->concert.categorieC.prix);
  mvwprintw(win, y+4, 50, "X - Siège réservé ");

}


Salle constructeur_salle(WINDOW *win) {

  Salle salle_concert;
  char texte_nom[MAX];

  better_scan_str(win, 1, 0, "Entrez le nom de la salle : ", texte_nom, MAX); 
  werase(win);  

  salle_concert.nb_rangees = better_scan_int(win, 1, 0, "Entrez le nombre de rangées : ");
  while (salle_concert.nb_rangees <= 0 || salle_concert.nb_rangees > 100) {
    if (salle_concert.nb_rangees > 100) {
      werase(win);
      salle_concert.nb_rangees = better_scan_int(win, 1, 0, "Veuillez entrer un nombre de rangées inférieur ou égal à 100 : ");
    } else {
      werase(win);
      salle_concert.nb_rangees = better_scan_int(win, 1, 0, "Vous ne pouvez pas créer de salle sans rangées. Entrez a nouveau un nombre de rangée : ");
    }
  }
  werase(win);  
  salle_concert.nb_sieges = better_scan_int(win, 1, 0, "Entrez le nombre de sieges par rangées : ");
  while (salle_concert.nb_sieges <= 0 || salle_concert.nb_sieges > 100) {
    if (salle_concert.nb_sieges > 100) {
      werase(win);
      salle_concert.nb_sieges = better_scan_int(win, 1, 0, "Veuillez entrer un nombre de sieges par rangées inférieur ou égal à 100 : ");
    } else {
      werase(win);
      salle_concert.nb_sieges = better_scan_int(win, 1, 0, "Vous ne pouvez pas créer de rangées sans sieges. Entrez a nouveau un nombre de sieges : ");
    }
  }
  werase(win);  
  return salle_concert;
}


void constructeur_concert(Salle * salle, WINDOW *win) {

  //Concert *concert;
  Categorie A, B, C;

  salle->concert.heure_debut = better_scan_compare(win, 1, 0, 0, 23, "Entrez l'heure de début du concert : ");
  werase(win); 
  salle->concert.minute_debut = better_scan_compare(win, 1, 0, 0, 59, "Entrez la minute de début du concert : ");
  werase(win); 
  salle->concert.heure_fin = better_scan_compare(win, 1, 0 ,0, 23, "Entrez l'heure de fin du concert : "); // verifier que heure de fin n'est pas avnt debut attntion debut 23h fin 1h 
  werase(win);                                           
  salle->concert.minute_fin = better_scan_compare(win, 1, 0, 0, 59,  "Entrez la minute de fin du concert : "); // change par Enzo l56-59 dimanche soir
  werase(win);

  better_scan_str(win, 1, 0, "Entrez le nom de l'artiste : ", salle->concert.artiste, MAX); 
  werase(win);  

  int nb_rangees_salle = salle->nb_rangees;
  // définition nombre de rangées

  mvwprintw(win, 1, 0, "Il y a actuellement : %d rangées   ", nb_rangees_salle);
  A.cat_rangees = better_scan_int(win, 2, 0, "Entrez le nombre de rangées que vous souhaitez pour la categorie A : ");
  werase(win);

  while (A.cat_rangees > salle->nb_rangees || A.cat_rangees > 100) {
    if (A.cat_rangees > 100) {
      werase(win);
      mvwprintw(win, 1, 0, "Il y a actuellement : %d rangées   ", nb_rangees_salle);
      A.cat_rangees = better_scan_int(win, 2, 0, "Vous ne pouvez pas créer plus de 100 rangées : ");
    } 
    else{
      werase(win);
      mvwprintw(win, 1, 0, "Il y a actuellement : %d rangées", nb_rangees_salle);
      A.cat_rangees = better_scan_int(win, 2, 0, "Entrez une valeur inferieur ou egal au nombre de rangées disponible : ");
    }
  }

  werase(win); 
  
  nb_rangees_salle -= A.cat_rangees; // permet de ne pas dépasser le nombre de rangées de la salle

  int fosse = -1;
  if(A.cat_rangees != 0){
    while (fosse != 1 && fosse != 0) {
      werase(win);
      fosse = better_scan_int(win, 1, 0, "Souhaitez vous remplacer la categorie A par une fosse ? (Oui = 1 et Non = 0) : ");
    }
    werase(win); 
  }

  werase(win); 

  if (nb_rangees_salle == 0) {
    mvwprintw(win, 1, 0, "Toutes les rangées sont atribuées à la Catégorie A ! ");
    wgetch(win);
    werase(win); 
    B.cat_rangees = 0;
    C.cat_rangees = 0;
  }

  else {
    werase(win);
    mvwprintw(win, 1, 0, "Il reste : %d rangées", nb_rangees_salle);
    B.cat_rangees = better_scan_int(win, 2, 0, "Entrez le nombre de rangées que vous souhaitez pour la categorie B : ");
    while (B.cat_rangees > nb_rangees_salle || B.cat_rangees > 100) {
      if (A.cat_rangees > 100) {
        werase(win);
        mvwprintw(win, 1, 0, "Il reste : %d rangées", nb_rangees_salle);
        A.cat_rangees = better_scan_int(win, 2, 0, "Vous ne pouvez pas créer plus de 100 rangées : ");
      } 
      else{
        werase(win);
        mvwprintw(win, 1, 0, "Il reste : %d rangées", nb_rangees_salle);
        B.cat_rangees = better_scan_int(win, 2, 0, "Entrez une valeur inferieur ou egal au nombre de rangées disponible : ");
      }
    }

    werase(win);

    nb_rangees_salle -= B.cat_rangees; // Permet de ne pas dépasser le nombre de rangées de la salle

    // Défini automatiquement la catégorie C à partir des catégories précédentes et du nombre de rangées restantes
    if (nb_rangees_salle > 100) {
      C.cat_rangees = 100;
    } else {
      C.cat_rangees = nb_rangees_salle;
    }
  } 

  if (fosse == 1) {
    A.nb_place = 2 * A.cat_rangees * salle->nb_sieges; // 2*+ de places pour la fosse
    A.cat_rangees = 2 * A.cat_rangees;
  } else {
    A.nb_place = A.cat_rangees * salle->nb_sieges;
  }

  B.nb_place = B.cat_rangees * salle->nb_sieges;
  C.nb_place = C.cat_rangees * salle->nb_sieges;

  if (A.cat_rangees == 0){
    A.prix = 0.0;
    werase(win);
  }
  else{
    werase(win);
    wrefresh(win);
    A.prix = better_scan_float(win, 1, 0, "Prix de la catégorie A ? ");
    werase(win);
  }
  if (B.cat_rangees == 0) {
    B.prix = 0.0;
    werase(win);
  } 
  else {
    werase(win);
    wrefresh(win);
    B.prix = better_scan_float(win, 1, 0, "Prix de la catégorie B ? ");
    werase(win); 
  }
  werase(win);
  if (C.cat_rangees == 0) {
    C.prix = 0.0;
    werase(win);
  } 
  else {
    werase(win);
    wrefresh(win);
    C.prix = better_scan_float(win, 1, 0, "Prix de la catégorie C ? ");

    werase(win);
  }
  
  werase(win);

  for (int i = 0; i < A.cat_rangees; i++) {
    for (int j = 0; j < salle->nb_sieges; j++) {
      A.tableau[i][j] = 0;
    }
  }
  for (int i = 0; i < B.cat_rangees; i++) {
    for (int j = 0; j < salle->nb_sieges; j++) {
      B.tableau[i][j] = 0;
    }
  }
  for (int i = 0; i < C.cat_rangees; i++) {
    for (int j = 0; j < salle->nb_sieges; j++) {
      C.tableau[i][j] = 0;
    }
  }

  salle->concert.categorieA = A; // affiliation
  salle->concert.categorieB = B;
  salle->concert.categorieC = C;

}