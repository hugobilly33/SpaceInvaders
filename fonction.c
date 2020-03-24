/*
 * fonction.c
 *
 *  Created on: 22 janv. 2020
 *      Author: gregbilly
 */
#include "serial.h"
#include "vt100.h"
#include "fonction.h"
#include <unistd.h>

const int y_ennemis_ligne1 = 3;		//Première ligne d'ennemis (en partant du haut)
const int y_ennemis_ligne2 = 5;		//Deuxième ligne d'ennemis
const int y_ennemis_ligne3 = 12;	//Troisième ligne d'ennemis
const int y_protection = 17;		//Y protection pour mon vaisseau
int x = 3; 							//Départ de mon vaisseau en x
int y_tir = 21;						//Départ de mes tirs en y
int y_tir_ennemis=16;
int tab[8];							//Nombres de vaisseaux sur la première ligne
int tab_2[8];						//Nombres de vaisseaux sur la deuième ligne
int tab_3[8];						//Nombres de vaisseaux sur la troisième ligne
int tab_4[9];
int x_start = 4;					//Depart des vaisseaux ennemis
int x_start_protection = 8;			//Depart en x de ma protection
const int ecart = 10;				//Ecart entre les vaisseaux ennemis


// Pour le déplacement de certains vaisseaux
float ennemi_x = 4;
float max_x = 66;
float ennemi_y = 3;
float ennemi_y_2 = 5;
float sens = 0.1;


// Ligne de caractère permettant de faire mon encadrement (partie horizontal du haut et du bas)
void fenetre_horizontal(unsigned char character) {
	unsigned char i;
	for (i = 1; i < 100; i++) {
		vt100_move(i, 1);
		serial_putchar(character);
		vt100_move(i, 40);
		serial_putchar(character);
	}
}

// Ligne de caractère permettant de faire mon encadrement (partie vertical du haut et du bas)
void fenetre_vertical(unsigned char character) {
	unsigned char i = 1;
	for (i = 1; i < 40; i++) {
		vt100_move(1, i);
		serial_putchar(character);
		vt100_move(100, i);
		serial_putchar(character);
	}
}

// Page d'accueil de mon jeux
void menu_accueil(void) {
	vt100_move(34, 5);
	serial_puts("SPACE INVADERS");
	vt100_move(28, 10);
	serial_puts("JOUER -> Appuyer sur entrer");
	vt100_move(60, 23);
	serial_puts("Hugo BILLY Gregory");
	vt100_move(30, 15);
	serial_puts("Vaisseaux ennemis : ~||~ ");
	vt100_move(30, 18);
	serial_puts("Vôtre vaisseau : [o]");
	vt100_move(33, 6);
	serial_puts("---------------");
	vt100_move(33, 4);
	serial_puts("---------------");
	vt100_move(33, 6);
	serial_puts("|");
	vt100_move(33, 5);
	serial_puts("|");
	vt100_move(33, 4);
	serial_puts("|");
	vt100_move(48, 6);
	serial_puts("|");
	vt100_move(48, 5);
	serial_puts("|");
	vt100_move(48, 4);
	serial_puts("|");
}

// Premier appui qui permet de passer à la seconde page
void lancer_jeu(void) {
	signed char appui = -1;
	while (appui == -1) {
		appui = serial_get_last_char();
	}
}

// Seconde page qui présente les règles du jeux et le fonctionnement
void regle_jeu(void) {
	vt100_clear_screen();
	fenetre_horizontal('-');
	fenetre_vertical('|');
	vt100_move(10, 5);
	serial_puts("Règles du jeu :");
	vt100_move(26, 5);
	serial_puts("-Vous contrôlez un vaisseau pouvant tirer");
	vt100_move(26, 7);
	serial_puts("-Les ennemis descendent dans la zone de jeu");
	vt100_move(26, 9);
	serial_puts("-Ils sont éliminées en 1 coup");
	vt100_move(26, 11);
	serial_puts("-Le jeu est gagné lorsque tout les enemis sont touchés");
	vt100_move(10, 14);
	serial_puts("Fonctionnement :");
	vt100_move(27, 14);
	serial_puts("-Appuyez sur Enter pour démarrer le jeu");
	vt100_move(27, 16);
	serial_puts("-Utilisez q(gauche) et d(droite) pour vous déplacer");
	vt100_move(27, 18);
	serial_puts("-Appuyez sur z pour tirer");
	vt100_move(20, 22);
	serial_puts("Bonne chance dans votre guerre intergalactique !");
}

// Deuxième appui sur une touche pour jouer
void lancer_jeu2(void) {
	signed char appui = -1;
	while (appui == -1) {
		appui = serial_get_last_char();
	}
}

//Création de l'interface de jeux
void interface(void) {
	vt100_clear_screen();
	fenetre_horizontal('-');
	fenetre_vertical('|');
}

//Déplacement en x de mon vaisseau
void mouvement_vaisseau() {

	uint8_t appui = serial_get_last_char();
	vt100_move(x, 22);
	serial_puts("[o]");

	if (x < 77) {
		if (appui == 'd' || appui == 'D') {
			vt100_move(x, 22);
			serial_puts("   ");
			x += 1;
			vt100_move(x, 22);
			serial_puts("[o]");

		}
	}

	if (x > 2) {
		if (appui == 'q' || appui == 'Q') {
			vt100_move(x, 22);
			serial_puts("   ");
			x -= 1;
			vt100_move(x, 22);
			serial_puts("[o]");

		}
	}
	if (appui == 'z' || appui == 'Z') {
		tir_vaisseau();
	}
}

//Tir de suppression de mon vaisseau, qui permet de supprimer les lignes 1, 2 et 3 ennemis
void tir_vaisseau() {
	y_tir = 21;
	for (y_tir = 21; y_tir > 1; y_tir--) {
		vt100_move(x + 1, y_tir);
		serial_puts("°");

		Delai(4);

		if (y_tir == y_ennemis_ligne1) {
			Condition_sup_ligne1(x_start, ecart);
		}
		if (y_tir == y_ennemis_ligne2) {
			Condition_sup_ligne2(x_start, ecart);
		}
		if (y_tir == y_ennemis_ligne3) {
			Condition_sup_ligne3(x_start, ecart);
		}
		if (y_tir == y_protection) {
			Condition_sup_protection(x_start_protection, ecart);
		}

		vt100_move(x + 1, y_tir);
		serial_puts(" ");
	}
}


//Suppression d'un ennemi quand notre missile le touche
void sup_ennemi(int x, int y) {
	vt100_move(x, y);
	serial_puts("     ");
}

void sup_protection(int x, int y) {
	vt100_move(x, y);
	serial_puts(" ");
}

//Delai de tir de notre vaisseau
void Delai(unsigned long n) {
	int i = 0;
	unsigned long int max = n * 50000;
	do {
		i++;
	} while (i <= max);
}

//---------------------------LIGNE VAISSEAUX 1--------------------------------

//Condition de suppression des ennemis de la ligne 1 (celle la plus en haut)avec la hitbox
void Condition_sup_ligne1(int h, int ecart) {
	int a = 0;
	for (h = h; h <= 66; h = h + ecart) {

		if (ennemi_x == h - 1 || ennemi_x == h || ennemi_x == h + 1 || ennemi_x == h + 2) {
			if (tab[a] != 0) {
				sup_ennemi(tab[a], y_ennemis_ligne1);
				tab[a] = 0;
				vt100_move(ennemi_x, y_tir);
				serial_puts(" ");
				y_tir = 2;
			}
		}
		a = a + 1;
	}
}

//Position de la première ligne d'ennemis dans un tableau de 8 ennemis
void position_ennemis(unsigned char ennemi_x, unsigned char ennemi_y, unsigned char max_x) {
	for (int i = ennemi_x; i <= max_x; i = i + ecart) {
		vt100_move(i, ennemi_y);
		serial_puts(" ~||~ ");
		vt100_move(i, ennemi_y-1);
		serial_puts("      ");
	}
	for (int i = 0; i <= sizeof(tab) / sizeof(int) - 1; i++) {
		tab[i] = x_start;
		x_start = x_start + ecart;
	}
	x_start = x_start - (ecart * (sizeof(tab) / sizeof(int)));
}

//Permet de déplacer les ennemis de la ligne 1
void deplacement_ennemis(void) {
	ennemi_x = ennemi_x + sens;
	max_x = max_x + sens ;
	if (ennemi_x > 14) {
		sens = -0.1;
	}
	if (ennemi_x < 4) {
		sens = 0.1;
	}
	if (ennemi_x < 14) {
		ennemi_y = ennemi_y + 0.01;
	}
	position_ennemis(ennemi_x, ennemi_y, max_x) ;
}

//---------------------------LIGNE VAISSEAUX 2--------------------------------

//Condition de suppression des ennemis de la ligne 2 (en partant du haut)avec la hitbox
void Condition_sup_ligne2(int h, int ecart_2) {
	int a = 0;
	for (h = h; h <= 66; h = h + ecart_2) {
		if (x == h - 1 || x == h || x == h + 1 || x == h + 2) {
			if (tab_2[a] != 0) {
				sup_ennemi(tab_2[a], y_ennemis_ligne2);
				tab_2[a] = 0;
				vt100_move(x, y_tir);
				serial_puts(" ");
				y_tir = 2;
			}
		}
		a = a + 1;
	}
}

//Position de la deuxième ligne d'ennemis dans un tableau de 8 ennemis
void position_ennemis_2(unsigned char ennemi_x, unsigned char ennemi_y_2, unsigned char max_x) {
	for (int i = x_start; i <= 66; i = i + ecart) {
		vt100_move(i, y_ennemis_ligne2);
		serial_puts(" ~||~ ");
		vt100_move(i, ennemi_y-1);
		serial_puts("      ");

	}
	for (int i = 0; i <= sizeof(tab_2) / sizeof(int) - 1; i++) {
		tab_2[i] = x_start;
		x_start = x_start + ecart;
	}
	x_start = x_start - (ecart * (sizeof(tab_2) / sizeof(int)));
}

//Permet de déplacer les ennemis de la ligne 1
void deplacement_ennemis_ligne2(void) {
	ennemi_x = ennemi_x + sens;
	max_x = max_x + sens ;
	if (ennemi_x > 14) {
		sens = -0.1;
	}
	if (ennemi_x < 4) {
		sens = 0.1;
	}
	if (ennemi_x < 14) {
		ennemi_y_2 = ennemi_y_2 + 0.01;
	}
	position_ennemis(ennemi_x, ennemi_y_2, max_x) ;
}


//---------------------------LIGNE VAISSEAUX 3--------------------------------

//Condition de suppression des ennemis de la ligne 3 (en partant du haut)avec la hitbox
void Condition_sup_ligne3(int h, int ecart_3) {
	int a = 0;
	for (h = h; h <= 76; h = h + ecart_3) {
		if (x == h - 1 || x == h || x == h + 1 || x == h + 2) {
			if (tab_3[a] != 0) {
				sup_ennemi(tab_3[a], y_ennemis_ligne3);
				tab_3[a] = 0;
				vt100_move(x, y_tir);
				serial_puts(" ");
				y_tir = 2;
			}
		}
		a = a + 1;
	}
}

//Position de la troisème ligne d'ennemis dans un tableau de 8 ennemis
void position_ennemis_3() {
	for (int i = x_start; i <= 66; i = i + ecart) {
		vt100_move(i, y_ennemis_ligne3);
		serial_puts("~||~");
	}
	for (int i = 0; i <= sizeof(tab_3) / sizeof(int) - 1; i++) {
		tab_3[i] = x_start;
		x_start = x_start + ecart;
	}
	x_start = x_start - (ecart * (sizeof(tab_3) / sizeof(int)));
}

//---------------------------LIGNE protection--------------------------------

void Condition_sup_protection(int h, int ecart) {
	int a = 0;
	for (h = h; h <= 76; h = h + ecart) {
		if (x == h - 1 || x == h || x == h + 1 || x == h + 2) {
			if (tab_4[a] != 0) {
				sup_protection(tab_4[a], y_protection);
				tab_4[a] = 0;
				vt100_move(x, y_tir);
				serial_puts(" ");
				y_tir = 2;
			}
		}
		a = a + 1;
	}
}
// Position des protections devant mon vaisseau
void position_protection() {
	for (int i = x_start_protection; i <= 76; i = i + ecart) {
		vt100_move(i, y_protection);
		serial_puts("----");
	}
	for (int i = 0; i <= sizeof(tab_4) / sizeof(int) - 1; i++) {
		tab_4[i] = x_start_protection;
		x_start_protection = x_start_protection + ecart;
	}
	x_start_protection = x_start_protection - (ecart * (sizeof(tab_4) / sizeof(int)));
}
