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
 * @file StrategoIHM.h
 * Stratego
 */
#ifndef STRATEGOIHM_H
#define STRATEGOIHM_H

#include <map>
#include <set>

#include "Stratego.h"


class StrategoIHM {
public:
	StrategoIHM();
	void placer(int camp);
	void jouerUnePartie(int camp);
	void aideEclaireur() const;

	bool ilResteDelaPlaceVideDans(int camp) const;
	unsigned int getNombreDePlaceVideSurPlateau(int camp) const ;
	int getNombreDePieceMobileSurPlateau(int camp) const;

	void afficherEtat(int camp) const;
	void aidePlacement(int camp) const;
	void sauvegarder();
	void reprendreUnePartie();
	int finDePartie() const;

	void pieceCombatEclaireur(char& colonneO, int& ligneO,
								char direction, unsigned int cases);

	void setDebug(bool actif);
	bool getDebug() const;

	static void tester() {
		StrategoIHM s;
		assertEquals(s.getNombreDePieceMobileSurPlateau(Stratego::NORD),19,
					"nombre de pieces mobiles au debut pour Nord");
		assertEquals(s.getNombreDePieceMobileSurPlateau(Stratego::SUD),19,
					"nombre de pieces mobiles au debut pour Sud");
	}

private:
	//std::set<char> pieces[2];
	std::map<char,int> aPlacer[2];
	std::map<const char, std::string> nomsDesPieces;
	//int nbPiecesMobilesSurPlateau[2];
	Stratego s;
	bool debug;
};

#endif
