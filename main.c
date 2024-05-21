#include "manager.h"
#include "temps.h"
#include "better_scan.h"

#define MAX 50
#define SIZE 3
#define TEST 1



void mode_manager(WINDOW *win, Salle tableau[], int nb_salles){

  for(int i = 0; i < nb_salles; i++){

    tableau[i] = constructeur_salle(win);
    constructeur_concert(&tableau[i], win);
            
    affichage_tribune(win, &tableau[i]);

    wgetch(win);
    werase(win);

    affichage_donnees_manager(win, tableau[i].concert);

    wgetch(win);
    werase(win);
    }
}


void mode_festivalier(WINDOW *win){
  mvwprintw(win, 1, 0, "Voici le mode festivalier");
  wgetch(win);
}


void afficheMenu(WINDOW *win, char menu[SIZE][50], int curseur){
	int i=0,y=5,x=5;
	for(i=0;i<SIZE;i++){
		if(i!=curseur){
			mvwprintw(win,y+i,x,"%s",menu[i]);

		}
		else{
			mvwprintw(win,y+i,x,"> %s <",menu[i]);
		}
	}
}


char mouvementMenu(WINDOW *win, int *curseur){
	char car=wgetch(win);
	switch(car){
		case 'z' :
			if(*curseur>0){
				(*curseur)--;
			}
		break;
		case 's' :
			if(*curseur<SIZE-1){
				(*curseur)++;
			}
	}
	return car;
}


int optionsMenu(WINDOW *win){
	char menu[SIZE][50]={"Manageur","Client","Exit"};
	int k=0;
	werase(win);
	afficheMenu(win,menu,k);
	while(mouvementMenu(win,&k)!='\n'){
		werase(win);
		afficheMenu(win,menu,k);
	}
	return k;
}



int main(){

  /*
  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(1);
}
*/

  initscr(); // Initialiser l'écran ncurses
  cbreak();  // Désactiver la mise en mémoire tampon de ligne
  noecho();  // Désactiver l'affichage des caractères saisis

  int x,y;
  getmaxyx(stdscr, y, x);

  start_color();
  init_pair(TEST, COLOR_YELLOW, COLOR_GREEN);

  WINDOW *win = newwin(300, 300, 0, 0); // hauteur, largeur, début_y, début_x Créer une nouvelle fenêtre
  char texte[MAX];
  int nb_salles;

  while(1){
    int options = optionsMenu(win);
    werase(win);

    if(options == 0){

      char mdp[MAX] = "test";
      char mdp_trouve[MAX]; 
      int r;
      int a;
      do{
        werase(win);
        better_scan_str(win, 1, 0, "Entrer le mot de passe (mdp = test) : ", mdp_trouve, MAX);
        a = strlen(mdp_trouve);
        r = 1;
        for(int i = 0; i<a; i++){
          if(mdp[i] != mdp_trouve[i]){
            r = 0;
          }
        }
      } while (r == 0);

      werase(win);
      
      int nb_salles = better_scan_int(win, 1, 0, "Entrez le nombre de salles que vous voulez créer : ");
      werase(win);
      Salle *tableau = malloc(nb_salles*(sizeof(Salle)));
      
      mode_manager(win,tableau,nb_salles);

      free(tableau);
      werase(win);
    }

    else if(options == 1){
      mode_festivalier(win);
      werase(win);
    }

    else{
      break;
    }
  }

  // ne pas oublier malloc et free
  // https://pubs.opengroup.org/onlinepubs/7908799/xcurses/curses.h.html

  endwin();
  return 0;

}
