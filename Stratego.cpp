/*
Copyright (c) 2013, Kcchouette and b-dauphin on GitHub ; Warren Dard

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

	Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.
	Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
*/
/**
 * @file Stratego.cpp
 * Stratego
 */

#include <cassert>
#include <sstream>

#include "Stratego.h"

void Stratego::testerImplementation() {

	assertFalse(estDansTerrain('A',0), "implem : out('A',0)");
	assertFalse(estDansTerrain('A',9), "implem : out('A',9)");
	assertFalse(estDansTerrain('H',1), "implem : out('H',1)");
	assertFalse(estDansTerrain('C',9), "implem : out('C',9)");
	assertTrue(estDansTerrain('B',9), "implem : in('B',9)");

	assertEquals(cl2i('A',1), 0, "implem : cl2i('A',1)");
	assertEquals(cl2i('G',8), 55, "implem : cl2i('G',8)");
	assertEquals(cl2i('B',9), 56, "implem : cl2i('B',9)");
	assertEquals(cl2i('D',9), 57, "implem : cl2i('B',9)");
	assertEquals(cl2i('F',9), 58, "implem : cl2i('F',9)");
}


/**
 * @brief Initialisation du terrain
 */
Stratego::Stratego() {
	for (unsigned int i =0; i < SIZE ; ++i)
		terrain[i] = VIDE;
}

/**
 * @brief état du tableau
 * @return l'État en type string
 */
std::string Stratego::getEtat() const {
	std::stringstream fluxChaine;
	unsigned int nbEspace = 0;
	for (unsigned int i = 0; i < SIZE ; ++i) {
		if (terrain[i] == VIDE)
			++nbEspace;
		else {
			if (nbEspace != 0)
				fluxChaine << nbEspace;
			fluxChaine << terrain[i];
			nbEspace = 0;
		}
		if ((i+1)%COLONNES == 0 ) {
			if (nbEspace != 0)
				fluxChaine << nbEspace;
			fluxChaine << '/';
			nbEspace = 0;
		}
	}
	if (nbEspace != 0)
		fluxChaine << nbEspace;
	return (fluxChaine.str());
}

/**
 * @brief initialisation du terrain
 * @param[in] colonne la colonne du placement de la pièce
 * @param[in] ligne la ligne du placement de la pièce
 * @param[in] piece la pièce à placer
 * @param[in] camp le camp de la pièce à placer
 * @return un booléen pour savoir si la pièce a bien été placée
 */
bool Stratego::placer(char colonne, int ligne, char piece, int camp) {
	if (!estDansCamp(colonne, ligne, camp) || !estPiece(piece))
		return (false);
	if (limitePiece(piecePour(camp, piece))) {
		put(colonne, ligne, piecePour(camp, piece));
		return (true);
	}
	else
		return (false);
}

/**
 * @brief placer une pièce à une colonne et ligne donnée
 * @param[in] colonne la colonne où placer une pièce
 * @param[in] ligne la ligne où placer la pièce
 * @param[in] piece la pièce à placer
 */
void Stratego::put(char colonne, int ligne, char piece) {
	assert(estDansTerrain(colonne, ligne));
	terrain[cl2i(colonne, ligne)] = piece;
}

/**
 * @brief retourne la pièce
 * @param[in] colonne la colonne où est placé la pièce
 * @param[in] ligne la ligne où est placé la pièce
 * @return la pièce en question
 */
char Stratego::getPiece(char colonne, int ligne) const {
	assert(estDansTerrain(colonne, ligne));
	return (terrain[cl2i(colonne, ligne)]);
}

/**
 * @brief retourne la pièce
 * @param[in] indice L'indice du tableau
 * @return la pièce en question
 */
char Stratego::getPieceInd(unsigned int indice) const {
	assert(indice < SIZE);
	return (terrain[indice]);
}

/**
 * @brief vérifie que la colonne et la ligne sont situées dans un camp donné
 * @param[in] colonne la colonne à vérifier en fonction de la ligne et du camp
 * @param[in] ligne la ligne à vérifier en fonction de la colonne et du camp
 * @param[in] camp le camp permet de vérifier la colonne et la ligne
 * @return un booléen pour savoir si la colonne et la ligne sont bien situées
 */
bool Stratego::estDansCamp(char colonne, int ligne, int camp) {
	if (camp == NORD && estDansTerrain(colonne, ligne) && ligne >=6) {
		if (colonne == COLGAUCHE+1 || colonne == COLGAUCHE+3 ||
			colonne == COLGAUCHE+5)
			return (ligne <= 9);
		else
			return (ligne <= 8);
	}
	if (camp == SUD && estDansTerrain(colonne, ligne) && ligne >= 1) {
		if (colonne == COLGAUCHE+1 || colonne == COLGAUCHE+3 ||
			colonne == COLGAUCHE+5)
				return (ligne <= 4 );
		else
			return (ligne <= 3);
	}
	return (false);
}

/**
 * @brief vérifie que la pièce appartient bien à un camp donné
 * @param[in] piece la piece à vérifier en fonction du camp
 * @param[in] camp le camp qui permet de vérifer la pièce
 * @return un booléen pour savoir si la pièce a bien été placée
 */
bool Stratego::estPieceDe(char piece, int camp) {
	if (camp == SUD && estPiece(piece))
		return (true);
	if (camp == NORD && estPiece(piece-MINUS))
		return (true);
	return (false);
}

/**
 * @brief Indique si la pièce existe
 * @param[in] piece la piece donnée sous forme majuscule
 * @return un boléen si la pièce existe
 */
bool Stratego::estPiece(char piece) {
	return ((piece >= MARECHAL && piece <= ESPION) || piece == BOMBE ||
			 piece == DRAPEAU);
}

/**
 * @brief vérifie si une colonne et une ligne sont bien dans le terrain.
 * @param[in] colonne la colonne à vérifier en fonction des limites du terrain
 * @param[in] ligne la ligne à vérifier en fonction des limites du terrain
 * @return un booléen pour savoir si les coordonné sont bien dans le terrain
 */
bool Stratego::estDansTerrain(char colonne, int ligne) {
	if (colonne < COLGAUCHE || colonne > COLDROITE || ligne <1)
		return (false);
	if ((colonne-COLGAUCHE) % 2 == 1)
		return (ligne <=9);
	else
		return (ligne <=8);
}

/**
 * @brief tranforme les colonnes et les lignes en un indice du terrain
 * @param[in] ligne la ligne qui permet de retrouver l'indice du terrain
 * @param[in] colonne la colonne qui permet de retrouver l'indice du terrain
 * @return l'indice dans le tableau
 */
int Stratego::cl2i(char colonne, int ligne) {
	if (ligne <= LIGNES)
		return ((ligne -1)*COLONNES + colonne -COLGAUCHE);
	else
		return ((ligne -1)*COLONNES + (colonne -COLGAUCHE)/2);
}

/**
 * @brief Déplace une pièce appartenant à colonneO, ligneO sur colonne, ligne
 * @param[in] colonneO la colonne d'origine de la pièce
 * @param[in] ligneO la ligne d'origine de la pièce
 * @param[in] colonne la colonne où la pièce doit se déplacer
 * @param[in] ligne la ligne où la pièce doit se déplacer
 * @return un booléen pour savoir si la pièce a bien été déplacée
 */
bool Stratego::deplacer(char colonneO, int ligneO, char colonne, int ligne) {
	char piece = getPiece(colonneO, ligneO);
	if ((estDansCamp(colonneO, ligneO, NORD) && estDansCamp(colonne, ligne,NORD)
		&& estPieceDe(piece, NORD))
		|| (estDansCamp(colonneO, ligneO, SUD) && estDansCamp(colonne,ligne,SUD)
		&& estPieceDe(piece, SUD) )) {

		char pieceO = getPiece(colonne, ligne);
		put(colonne, ligne, piece);
		put(colonneO, ligneO, pieceO);
		return (true);
	}
	return (false);
}

/**
 * @brief vérifie que le nombre de cette pièce n'est pas dépassé
 * @param[in] la piece à vérifier
 * @return un booléen pour savoir si le nombre de la pièce n'est pas dépassé
 * @see int Stratego::getNbAPlacer(char piece)
 */
bool Stratego::limitePiece(char piece) {
	std::string chaine = getEtat();
	unsigned int taille = chaine.size();
	unsigned int nbMax = getNbAPlacer(piece);
	for (unsigned int i = 0, nbPiece = 0; i < taille; ++i) {
		if (chaine[i] == piece)
			++nbPiece;
		if (nbPiece >= nbMax)
			return (false);
	}
	return (true);
}

/**
 * @brief Le nombre de pièce d'une pièce à placer
 * @param[in] une pièce pour contrôler le nombre de cette pièce à placer
 * @return un entier qui est le nombre de pièce de ce genre à placer
 * @see bool Stratego::limitePiece(char piece)
 */
int Stratego::getNbAPlacer(char piece) {
	unsigned int nbMax;
	switch (piece) {
		case DRAPEAU :
		case MARECHAL :
		case GENERAL :
		case ESPION :
		case DRAPEAU + MINUS :
		case MARECHAL + MINUS :
		case GENERAL + MINUS :
		case ESPION + MINUS :
			nbMax = 1;
			break;
		case COLONEL :
		case COMMANDANT :
		case CAPITAINE :
		case LIEUTENANT :
		case SERGENT :
		case COLONEL + MINUS :
		case COMMANDANT + MINUS :
		case CAPITAINE + MINUS :
		case LIEUTENANT + MINUS :
		case SERGENT + MINUS :
			nbMax = 2;
			break;
		case DEMINEUR :
		case ECLAIREUR :
		case DEMINEUR + MINUS :
		case ECLAIREUR + MINUS :
			nbMax = 3;
			break;
		case BOMBE :
		case BOMBE + MINUS :
			nbMax = 4;
			break;
		default :
			nbMax = 0;
			break;
	}
	return (nbMax);
}

/**
 * @brief Permet de mettre en minuscule une pièce pour le camp nord
 * @param[in] une pièce et son camp de destination
 * @return la pièce transformée
 */
char Stratego::piecePour(int camp, char piece) {
	if (camp == NORD)
		piece += MINUS;
	return (piece);
}

/**
 * @brief Permet de retourner la taille du tableau de la classe privée
 * @return la taille
 */
unsigned int Stratego::getSize() const {
	return (SIZE);
}

/**
 * @brief Permet de retourner le nombre de colonnes du tableau
 * @return le nombre de colonnes
 */
unsigned int Stratego::getColonnes() const {
	return (COLONNES);
}

/**
 * @brief Permet de retourner le nombre de lignes du tableau
 * @return le nombre de ligne
 */
unsigned int Stratego::getLignes() const {
	return (LIGNES);
}

/**
 * @brief Permet de retourner le nom du camp
 * @param[in] le numéro du camp
 * @return le nom du camp
 * @see les énumérations de la classe Stratego
 */
std::string Stratego::getNomDuCamp(int camp) {
	if (camp == NORD)
		return ("NORD");
	else
		return ("SUD");
}

/**
 * @brief Permet de vérifier qu'un déplacement d'une pièce est possible
 * @param[in] colonneO la colonne d'origine de la pièce
 * @param[in] ligneO la ligne d'origine de la pièce
 * @param[in] colonne la colonne où la pièce doit se déplacer
 * @param[in] ligne la ligne où la pièce doit se déplacer
 * @return 0 : non déplaçable, 1 : case libre, 2 : case occupée
 * @see bool Stratego::deplacer(char colonneO,int ligneO,char colonne,int ligne)
 */
int Stratego::deplacementPossible(char colonneO, int ligneO,
								char colonne, int ligne) const {
	if (!estDansTerrain(colonne, ligne))
		return 0;

	char piece = getPiece(colonne, ligne);
	if ((colonneO-COLGAUCHE) % 2 == 0 &&
		( (colonneO == colonne && (ligneO == ligne-1 || ligneO == ligne+1)) ||
		((colonneO == colonne-1 || colonneO == colonne+1) && (ligneO == ligne ||
														ligneO == ligneO-1)) ))
			if (piece == VIDE)
				return 1;
			else
				return 2;
	else if ((colonneO-COLGAUCHE) % 2 == 1 &&
		((colonneO == colonne && (ligneO == ligne-1 || ligneO == ligne+1)) ||
		((colonneO == colonne-1 || colonneO == colonne+1) &&
		(ligneO == ligne+1 || ligneO == ligneO))))
			if (piece == VIDE)
				return 1;
			else
				return 2;
	else
		return 0;
}

/**
 * @brief Permet de savoir si l'on peut déplacer la pièce éclaireur,
 * dont le mouvement est différent des autres pièces
 * @param[in] colonneO la colonne d'origine de la pièce éclaireur
 * @param[in] ligneO la ligne d'origine de la pièce éclaireur
 * @param[in] direction la direction d ans laquelle se dirige l'éclaireur
 * @param[in] cases le nombre de case sur lequel l'éclaireur doit se déplacer
 * @return un booléen pour savoir si le déplacement de l'éclaireur est possible
 */
bool Stratego::deplacementEclaireur(char colonneO, int ligneO, char direction,
									unsigned int cases) {
	int lig = ligneO;
	for(unsigned int i = 0; i < cases ; ++i) {
		switch (direction) { //6 cas, car 6 côtés dans un hexagone
		case 'z' : //Haut
			if(deplacementPossible(colonneO, ligneO+i, colonneO, ligneO+1+i)!=1)
				return mouvementEclaireur(colonneO, ligneO,colonneO,ligneO+1+i);
			break;
		case 'x' : //Bas
			if(deplacementPossible(colonneO, ligneO-i, colonneO, ligneO-1-i)!=1)
				return mouvementEclaireur(colonneO, ligneO,colonneO,ligneO-1-i);
			break;

		case 'a' : //Haut-gauche
			if( ((colonneO-i-COLGAUCHE)%2 == 0) &&
				deplacementPossible(colonneO-i, lig, colonneO-i-1, (++lig))!=1)
					return mouvementEclaireur(colonneO,ligneO,colonneO-i-1,lig);
			if( ((colonneO-i-COLGAUCHE)%2 == 1) &&
				deplacementPossible(colonneO-i, lig, colonneO-i-1, lig) != 1)
					return mouvementEclaireur(colonneO,ligneO,colonneO-i-1,lig);
			break;

		case 'e' : //Haut-droite
			if( ((colonneO-i-COLGAUCHE)%2 == 0) &&
				deplacementPossible(colonneO+i, lig, colonneO+i+1, (++lig))!= 1)
					return mouvementEclaireur(colonneO,ligneO,colonneO+i+1,lig);
			if( ((colonneO-i-COLGAUCHE)%2 == 1) &&
				deplacementPossible(colonneO+i, lig, colonneO+i+1, lig) != 1)
					return mouvementEclaireur(colonneO,ligneO,colonneO+i+1,lig);
			break;

		case 'w' : //Bas-gauche
			if( ((colonneO-i-COLGAUCHE)%2 == 0) &&
				deplacementPossible(colonneO-i, lig, colonneO-i-1, lig) != 1)
					return mouvementEclaireur(colonneO,ligneO,colonneO-i-1,lig);
			if( ((colonneO-i-COLGAUCHE)%2 == 1) &&
				deplacementPossible(colonneO-i, lig, colonneO-i-1, (--lig))!= 1)
					return mouvementEclaireur(colonneO,ligneO,colonneO-i-1,lig);
			break;

		case 'c' : //Bas-droite
			if( ((colonneO-i-COLGAUCHE)%2 == 0) &&
				deplacementPossible(colonneO+i, lig, colonneO+i+1, lig) != 1 )
					return mouvementEclaireur(colonneO,ligneO,colonneO+i+1,lig);
			if( ((colonneO-i-COLGAUCHE)%2 == 1) &&
				deplacementPossible(colonneO+i, lig, colonneO+i+1, (--lig))!= 1)
					return mouvementEclaireur(colonneO,ligneO,colonneO+i+1,lig);
			break;

		default :
			return (false);
		}
	}

	switch (direction) {
	case 'z' : //Haut
		return mouvementEclaireur(colonneO, ligneO, colonneO, ligneO+cases);
	case 'x' : //Bas
		return mouvementEclaireur(colonneO, ligneO, colonneO, ligneO-cases);
	case 'a' :
	case 'w' : //Gauche
		return mouvementEclaireur(colonneO, ligneO, colonneO-cases, lig);
	case 'e' :
	case 'c' : //Droite
		return mouvementEclaireur(colonneO, ligneO, colonneO+cases, lig);
	default :
		return (false);
	}
}

/**
 * @brief Si une case sur le chemin de l'éclaireur est occupée, cette fonction
 * détremine si un combat est nécesssaire ou si le mouvement est impossible
 * param[in] colDep la colonne d'origine de la pièce éclaireur
 * param[in] ligDep la ligne d'origine de la pièce éclaireur
 * param[in] colDest la colonne où la pièce éclaireur doit se déplacer
 * param[in] ligDest la ligne où la pièce éclaireur doit se déplacer
 * @return false : mouvement impossible, true : combat effectué
 */
bool Stratego::mouvementEclaireur(char colDep, int ligDep, char colDest,
								int ligDest) {
	if (!estDansTerrain(colDest, ligDest))
		return (false);

	char pieceDep = getPiece(colDep, ligDep),
		pieceDest = getPiece(colDest, ligDest);

	if (pieceDest == VIDE) {
		put(colDest, ligDest, pieceDep);
		put(colDep, ligDep, VIDE);
		return (true);
	}
	if (!campsOpposes(pieceDep, pieceDest))
		return (false);
	else {
		combat(colDep, ligDep, colDest, ligDest);
		return (true);
	}
}

/**
 * @brief Permet de vérifier si la pièce peut bouger, et se déplace si oui
 * @param[in] colonnneO la colonne d'origine de la pièce
 * @param[in] ligneO la ligne d'origine de la pièce
 * @param[in] colonne la colonne où la pièce doit se déplacer
 * @param[in] ligne la ligne où la pièce doit se déplacer
 * @param[in] camp le camp de la pièce
 * @return un booléen pour savoir si le mouvement est possible
 * et si la pièce a été déplacée
 * @see bool Stratego::deplacementPossible(char colonneO, int ligneO,
 *							char colonne, int ligne) const
 */
bool Stratego::mouvement(char colonneO, int ligneO, char colonne, int ligne, int camp) {
	char piece = getPiece(colonneO, ligneO);

	if (!estPieceDe(piece, camp) || !estDansTerrain(colonne, ligne))
		return (false);

	if (piece == BOMBE || piece == DRAPEAU || piece == BOMBE+MINUS || piece == DRAPEAU+MINUS)
		return (false);

	if (!deplacementPossible(colonneO, ligneO, colonne, ligne))
		return (false);

	char pieceDest = getPiece(colonne, ligne);
	if (pieceDest != VIDE) {
		if(!campsOpposes(piece, pieceDest))
			return (false);
		else {
			combat(colonneO, ligneO, colonne, ligne);
			return (true);
		}
	}
	else { // Case destination vide
		put(colonne, ligne, piece);
		put(colonneO, ligneO, VIDE);
	}
	return (true);
}

/**
 * @brief Vérifie le camp de la pièce sur la case de destination
 * @param[in] piece1 la pièces aux coordonnées d'origine
 * @param[in] piece2 la pièces aux coordonnées de destination
 * @return false si les 2 pièces sont du même camp, true si camps opposés
 */
bool Stratego::campsOpposes(char piece1, char piece2) {
	return ( (estPieceDe(piece1, NORD) && estPieceDe(piece2, SUD)) ||
		(estPieceDe(piece1, SUD) && estPieceDe(piece2, NORD)) );
}

/**
 * @brief Permet un combat
 * @param[in] colAtq la colonne de la pièce attaquante
 * @param[in] ligAtq la ligne de la pièce attaquante
 * @param[in] colAdv la colonne de la pièce adverse
 * @param[in] ligAdv la ligne de la pièce adverse
 * @see bool Stratego::dejaUnePiece(char colDep, int ligDep, char colDest,
 *									int ligDest)
 */
void Stratego::combat(char colAtq, int ligAtq, char colAdv, int ligAdv) {
	char pieceAttaquante = getPiece(colAtq, ligAtq),
		pieceAdverse = getPiece(colAdv, ligAdv),
		// Évite un changement de camp de pieceAttaquante
		pieceAtq = pieceAttaquante;

	if (estPieceDe(pieceAttaquante, NORD))
		pieceAttaquante -= MINUS;
	if (estPieceDe(pieceAdverse, NORD))
		pieceAdverse -= MINUS;

	if ( ((pieceAttaquante < pieceAdverse) && pieceAdverse != BOMBE) ||
		(pieceAttaquante == DEMINEUR && pieceAdverse == BOMBE) ||
		(pieceAttaquante == ESPION && pieceAdverse == MARECHAL) )
			put(colAdv, ligAdv, pieceAtq);
	else if (pieceAttaquante == pieceAdverse) {
		put(colAdv, ligAdv, VIDE);
	}
	put(colAtq, ligAtq, VIDE);
}

/**
 * @brief Permet de l'encodage du getEtat
 * @param[in,out] clef la clé de cryptage ou décryptage
 * @param[in,out] texte le texte à crypter ou décrypter
 * @see std::string Stratego::getEtat() const
 */
void Stratego::encoderLigne(const std::string& clef, std::string& texte) {
	for (unsigned int i = 0; i < texte.size(); ++i) {
		texte[i] ^= clef[i%clef.size()];
	}
}

/**
 * @brief Permet de retourner le getEtat cryptée
 * @param[in,out] clef la clé pour le cryptage ou décryptage
 * @param[in,out] texte le texte à crypter ou à décrypter
 * @see std::string Stratego::encoderLigne (const std::string& clef)
 */
void Stratego::getClef(const std::string& clef, std::string& texte) {
	encoderLigne(clef, texte);
}

/**
 * @brief Rénitialise l'état depuis la sauvegarde
 * @param[in] l'état décrypté
 * @see void StrategoIHM::reprendreUnePartie()
 */
void Stratego::setEtat(std::string& etat) {
	for(unsigned int i = 0, j = 0; i < etat.size(); ++i) {
		switch(etat[i]) { //Fonctionne car il n'y a pas de break;
			case '7' :
				terrain[j++]=VIDE;
			case '6' :
				terrain[j++]=VIDE;
			case '5' :
				terrain[j++]=VIDE;
			case '4' :
				terrain[j++]=VIDE;
			case '3' :
				terrain[j++]=VIDE;
			case '2' :
				terrain[j++]=VIDE;
			case '1' :
				terrain[j++]=VIDE;
				break;
			case '/':
				break;
			default:
				terrain[j++]=etat[i];
		}
	}
}
