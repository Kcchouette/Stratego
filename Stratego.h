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
 * @file Stratego.h
 * Stratego
 */

#ifndef STRATEGO_H
#define STRATEGO_H

#include <string>
//#include <set>

#include "unittest.h"


class Stratego {

public:
	Stratego();
	std::string getEtat() const;

	enum {
		SUD = 0,
		NORD = 1
	};

	enum {
		MINUS = 32
	};

	enum {
		MARECHAL = 'A',
		GENERAL = 'B',
		COLONEL = 'C',
		COMMANDANT = 'D',
		CAPITAINE = 'E',
		LIEUTENANT = 'F',
		SERGENT = 'G',
		DEMINEUR = 'H',
		ECLAIREUR = 'I',
		ESPION = 'J',
		BOMBE = 'O',
		DRAPEAU = 'X',
		VIDE = ' '
	};


	enum {
		COLONNES = 7,
		LIGNES = 8,
		SIZE = COLONNES * LIGNES + COLONNES/2
	};

	enum {
		COLGAUCHE = 'A',
		COLDROITE = COLGAUCHE + COLONNES - 1
	};

	void put(char colonne, int ligne, char piece);
	void setEtat(std::string& etat);
	bool placer(char colonne, int ligne, char piece, int camp);
	char getPiece(char colonne, int ligne) const;
	char getPieceInd(unsigned int indice) const;
	unsigned int getSize() const;
	unsigned int getColonnes() const;
	unsigned int getLignes() const;

	static char piecePour(int camp, char piece);
	static bool estDansCamp(char colonne, int ligne, int camp);
	static bool estPieceDe(char piece, int camp);
	static bool estDansTerrain(char colonne, int ligne);
	static bool estPiece(char piece);
	static std::string getNomDuCamp(int camp);
	static int getNbAPlacer(char piece);
	void getClef(const std::string& clef, std::string& texte);
	bool deplacer(char colonneO, int ligneO, char colonne, int ligne);
	bool limitePiece(char piece);

	bool mouvement(char colonneO, int ligneO, char colonne, int ligne, int camp);
	bool campsOpposes(char piece1, char piece2);
	void combat(char colAtq, int ligAtq, char colAdv, int ligAdv);
	int deplacementPossible(char colonneO, int ligneO,
							char colonne, int ligne) const;
	bool deplacementEclaireur(char colonneO, int ligneO, char direction,
							unsigned int cases);
	bool mouvementEclaireur(char colDep, int ligDep, char colDest, int ligDest);

	static void tester() {
		testerImplementation();
		Stratego s;

		assertFalse(estDansTerrain('A', 0),"('A',0) n'est pas dans le Terrain");
		assertFalse(estDansTerrain('A', 9),"('A',9) n'est pas dans le Terrain");
		assertFalse(estDansTerrain('H', 1),"('H',1) n'est pas dans le Terrain");
		assertFalse(estDansTerrain('C', 9),"('C',9) n'est pas dans le Terrain");
		assertTrue(estDansTerrain('B', 9), "('B',9) est dans le Terrain");
		assertTrue(estDansTerrain('G', 4), "('G',4) est dans le Terrain");
		assertTrue(estDansTerrain('D', 1), "('D',1) est dans le Terrain");

		assertFalse(estDansCamp('A', 4, SUD), "('A',4) n'est pas au Sud");
		assertTrue(estDansCamp('A', 1, SUD), "('A',1) est au Sud");
		assertTrue(estDansCamp('B', 4, SUD), "('B',4) est au Sud");
		assertFalse(estDansCamp('B', 5, SUD), "('B',5) n'est pas au Sud");
		assertTrue(estDansCamp('G', 3, SUD), "('G',3) est au Sud");

		assertTrue(estDansCamp('A', 6, NORD), "('A',6) est au Nord");
		assertFalse(estDansCamp('A', 5, NORD), "('A',5) n'est pas dans Nord");
		assertTrue(estDansCamp('B', 9, NORD), "('B',9) est au Nord");
		assertFalse(estDansCamp('C', 9, NORD), "('C',9) n'est pas dans Nord");
		assertTrue(estDansCamp('G', 6, NORD), "('G',6) est au Nord");

		assertTrue(estPieceDe('X', SUD), "X est une piece de SUD");
		assertFalse(estPieceDe('Z', SUD), "Z n'est pas une piece de SUD");
		assertTrue(estPieceDe('A', SUD), "A est une piece de SUD");
		assertFalse(estPieceDe('a', SUD), "a n'est pas une piece de SUD");
		assertTrue(estPieceDe('J', SUD), "J est une piece de SUD");
		assertTrue(estPieceDe('O', SUD), "O est une piece de SUD");

		assertTrue(estPieceDe('x', NORD), "X est une piece de NORD");
		assertFalse(estPieceDe('z', NORD), "z n'est pas une piece de NORD");
		assertTrue(estPieceDe('a', NORD), "a est une piece de NORD");
		assertFalse(estPieceDe('A', NORD), "A n'est pas une piece de NORD");
		assertTrue(estPieceDe('j', NORD), "j est une piece de NORD");
		assertTrue(estPieceDe('o', NORD), "o est une piece de NORD");

		assertEquals(piecePour(NORD, 'A'),'a', "a pour NORD");
		assertEquals(piecePour(SUD,'D'),'D',"D pour SUD");

		assertTrue(estPiece('A'), "A est une pièce");
		assertTrue(estPiece('B'), "B est une pièce");
		assertFalse(estPiece('Y'), "Y n'est pas une pièce");
		assertFalse(estPiece('Z'), "Z n'est pas une pièce");

		assertEquals(s.getEtat(),std::string("7/7/7/7/7/7/7/7/3"),
					"Etat initial 7/7/7/7/7/7/7/7/3");

		s.placer('D', 1, DRAPEAU, SUD);
		assertEquals(s.getPiece('D',1), 'X', "X en D 1");
		assertEquals(s.getEtat(),std::string("3X3/7/7/7/7/7/7/7/3"),
					"Etat 1 3X3/7/7/7/7/7/7/7/3");

		s.placer('D', 9, DRAPEAU, NORD);
		assertEquals(s.getPiece('D',9), 'x', "x en D 9");
		assertEquals(s.getEtat(),std::string("3X3/7/7/7/7/7/7/7/1x1"),
					"Etat 2 3X3/7/7/7/7/7/7/7/1x1");

		s.placer('E', 1,ESPION, SUD);
		assertEquals(s.getEtat(),std::string("3XJ2/7/7/7/7/7/7/7/1x1"),
					"Etat 3 3XJ2/7/7/7/7/7/7/7/1x1");

		s.placer('D', 1, DRAPEAU, SUD);
		assertEquals(s.getEtat(),std::string("3XJ2/7/7/7/7/7/7/7/1x1"),
					"Etat 4 ~ Pas de changement");

		s.placer('F', 9, BOMBE, NORD);
		assertEquals(s.getEtat(),std::string("3XJ2/7/7/7/7/7/7/7/1xo"),
					"Etat 5 3XJ2/7/7/7/7/7/7/7/1xo");

		s.placer('A', 7, GENERAL, NORD);
		assertEquals(s.getEtat(),std::string("3XJ2/7/7/7/7/7/b6/7/1xo"),
					"Etat 6 3XJ2/7/7/7/7/7/b6/7/1xo");

		assertFalse(s.placer('A', 6, LIEUTENANT, SUD),
					"Pas de placement Nord dans le Sud !");
		assertEquals(s.getEtat(),std::string("3XJ2/7/7/7/7/7/b6/7/1xo"),
					"Etat 6bis - N/S");

		assertTrue(s.deplacer('D',1,'F',1), "Deplacement dans le sud");
		assertFalse(s.deplacer('F',1,'A',8),
					"Pas de Deplacement du sud vers le nord");
		assertTrue(s.deplacer('F',9,'G',7),
					"Deplacement dans le nord de F9 en G7");
		assertFalse(s.deplacer('G',6,'E',2),
					"Pas de Deplacement du nord vers le sud");
		assertFalse(s.deplacer('F',1,'D',5),
					"Pas de Deplacement du sud vers le milieu");
		assertFalse(s.deplacer('G',6,'F',5),
					"Pas de Deplacement du nord vers le milieu");

		assertFalse(s.deplacer('A',3,'C',2), "Piece vide");

		assertEquals(s.getEtat(),std::string("4JX1/7/7/7/7/7/b5o/7/1x1"),
					"Etat 7 4JX1/7/7/7/7/7/b5o/7/1x1");

		assertFalse(s.limitePiece(DRAPEAU), "Pas deux drapeaux dans le sud");
		assertTrue(s.limitePiece(MARECHAL), "Mettre un marechal dans le sud");

		assertFalse(s.placer('B', 7, GENERAL, NORD),
					"Placement impossible deja général dans le Nord");
		assertTrue(s.placer('E', 8, BOMBE, NORD), "Deux bombes dans le nord");


		assertEquals(s.getEtat(),std::string("4JX1/7/7/7/7/7/b5o/4o2/1x1"),
					"Etat 8 4JX1/7/7/7/7/7/b5o/4o2/1x1");

		assertTrue(s.deplacer('A', 7, 'E', 8),
					"Test echange des pieces lors du deplacement");

		assertEquals(s.getEtat(),std::string("4JX1/7/7/7/7/7/o5o/4b2/1x1"),
					"Etat 9  4JX1/7/7/7/7/7/o5o/4b2/1x1");

		assertEquals(getNbAPlacer(MARECHAL), 1, "nb de marechaux");
		assertEquals(getNbAPlacer(BOMBE), 4, "nb de bombes");
		assertEquals(getNbAPlacer(ECLAIREUR), 3, "nb d'eclaireurs");
		assertEquals(getNbAPlacer(COLONEL), 2, "nb de colonels");

		assertEquals(s.getSize(), (unsigned int)SIZE, "SIZE = SIZE");
		assertEquals(s.getColonnes(), (unsigned int)COLONNES,
					"COLONNES = COLONNES");
		assertEquals(s.getLignes(), (unsigned int)LIGNES, "LIGNES = LIGNES");

		assertEquals(s.getNomDuCamp(NORD), std::string("NORD"), "NORD = NORD");
		assertEquals(s.getNomDuCamp(SUD), std::string("SUD"), "SUD = SUD");

		assertTrue(s.deplacementPossible('E', 8, 'E', 7), "Déplacement de E8 vers E7");
		s.placer('D', 4, ECLAIREUR, SUD);
		assertTrue(s.deplacementEclaireur('D', 4, 'x', 1),
					"éclaireur D4 -> D3 possible");
		assertTrue(s.deplacementEclaireur('D', 3, 'e', 3),
					"éclaireur D3 -> G4 possible");
		assertFalse(s.deplacementEclaireur('G', 4, 'c', 1),
					"éclaireur G4 -> H4 impossible");

		assertFalse(s.mouvement('A', 7, 'A', 6, NORD),
					"Une bombe ne se déplace pas");
		assertFalse(s.mouvement('E', 8, 'G', 8, NORD),
					"Pas de déplacement vers case non adjacente");

		s.put('D', 1, MARECHAL+MINUS);
		s.combat('E', 1, 'D', 1);
		assertEquals(s.getEtat(), std::string("3J1X1/7/7/6I/7/7/o5o/4b2/1x1"),
					"Espion > Maréchal");
		s.put('B', 7, DEMINEUR);
		s.combat('B', 7, 'A', 7);
		assertEquals(s.getEtat(), std::string("3J1X1/7/7/6I/7/7/H5o/4b2/1x1"),
					"Démineur > Bombe");
		s.put('E', 1, MARECHAL+MINUS);
		s.combat('E', 1, 'D', 1);
		assertEquals(s.getEtat(), std::string("3a1X1/7/7/6I/7/7/H5o/4b2/1x1"),
					"Maréchal > Espion");
	}

	static void testerImplementation();

private:
	static int cl2i(char colonne, int ligne);
	char terrain[SIZE];
	void encoderLigne (const std::string& clef, std::string& texte);
};

#endif
