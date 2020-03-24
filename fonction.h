/*
 * fonction.h
 *
 *  Created on: 22 janv. 2020
 *      Author: gregbilly
 */

#ifndef FONCTION_H_
#define FONCTION_H_

void fenetre_horizontal(unsigned char character);
void fenetre_vertical(unsigned char character);
void menu_accueil (void);
void lancer_jeu (void);
void regle_jeu(void);
void lancer_jeu2(void);
void interface(void);
void mouvement_vaisseau();
void tir_vaisseau(void);
void Condition_sup_ligne1(int x, int ecart);
void Condition_sup_ligne2(int x, int ecart);
void Condition_sup_ligne3(int x, int ecart);
void sup_ennemi(int x, int y);
void Delai(unsigned long n);
void position_ennemis(unsigned char ennemi_x, unsigned char ennemi_y, unsigned char max_x);
void position_ennemis_2(unsigned char ennemi_x, unsigned char ennemi_y_2, unsigned char max_x);
void position_ennemis_3(void);
void mouvement_vaisseau(void);
void deplacement_ennemis(void);
void deplacement_ennemis_ligne2(void);
void position_protection(void);
void Condition_sup_protection(int x, int ecart);



#endif /* FONCTION_H_ */
