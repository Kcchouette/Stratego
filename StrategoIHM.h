/**
 * @file StrategoIHM.h
 * Projet de CDP ~ Stratego
 * @author Jérémy CANAT, Warren DARD, Benjamin DAUPHIN et Anthony SOBREIRA
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
