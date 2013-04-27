/**
 * @file StrategoIHM.cpp
 * Projet de CDP ~ Stratego
 * @author Jérémy CANAT, Warren DARD, Benjamin DAUPHIN et Anthony SOBREIRA
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "StrategoIHM.h"
#include <cstdio>
using namespace std;

/**
 * @brief Initialiser StrategoIHM
 */
StrategoIHM::StrategoIHM() {
	char touche;
	unsigned int nombreAPlacer;
	cout << "	###############################" << endl;
	cout << "	########### STRATEGO ##########" << endl;
	cout << "	###############################" << endl;
	cout << endl << "Appuyez sur une touche pour commencer à jouer,"
		<<" ou sur 'd' pour activer le mode DEBUG" << endl;
	cin >> touche;
	setDebug (touche == 'd');

	for (char i = s.MARECHAL; i <= s.ESPION; ++i) {
		nombreAPlacer=s.getNbAPlacer(i);
		aPlacer[s.NORD][i]=nombreAPlacer;
		aPlacer[s.SUD][i]=nombreAPlacer;
	}
	nomsDesPieces['A'] = "MARECHAL";
	nomsDesPieces['B'] = "GENERAL";
	nomsDesPieces['C'] = "COLONEL";
	nomsDesPieces['D'] = "COMMANDANT";
	nomsDesPieces['E'] = "CAPITAINE";
	nomsDesPieces['F'] = "LIEUTENANT";
	nomsDesPieces['G'] = "SERGENT";
	nomsDesPieces['H'] = "DEMINEUR";
	nomsDesPieces['I'] = "ECLAIREUR";
	nomsDesPieces['J'] = "ESPION";
	nomsDesPieces['O'] = "BOMBE";
	nomsDesPieces['X'] = "DRAPEAU";
	nombreAPlacer=s.getNbAPlacer(s.DRAPEAU);
	aPlacer[s.NORD][s.DRAPEAU]=nombreAPlacer;
	aPlacer[s.SUD][s.DRAPEAU]=nombreAPlacer;
	nombreAPlacer=s.getNbAPlacer(s.BOMBE);
	aPlacer[s.NORD][s.BOMBE]=nombreAPlacer;
	aPlacer[s.SUD][s.BOMBE]=nombreAPlacer;
	cout << endl;
	system("cls");// Effacement écran

	placer(s.SUD);
	system("cls");
	placer(s.NORD);

	do {
		jouerUnePartie(s.SUD);
		if (finDePartie())
			break;
		jouerUnePartie(s.NORD);
	} while(!finDePartie());

	int codeVictoire=finDePartie();
	switch (codeVictoire) {
	case 1 :
		cout << "Victoire du camp Nord !" << endl;
		break;
	case 2 :
		cout << "Victoire du camp Sud !" << endl;
		break;
	case 3 :
		cout << "Égalité…" << endl;
		break;
	}
}

/**
 * @brief Permet le placement des pièces en début de partie
 * @param[in] camp le camp dans lequel placer les pièces
 */
void StrategoIHM::placer(int camp) {
	system("cls");
	char choix, piece;
	char colonneDepart, colonne;
	int ligneDepart, ligne;
	do {
		cout << endl << endl << endl << "Joueur " << s.getNomDuCamp(camp)
			<< " va placer ses pièces" << endl;

		system("pause");
		system("cls");
		afficherEtat(camp);
		do {
			cout << "Souhaitez-vous " << endl
				<< "\t placer une pièce (p) " << endl
				<< "\t déplacer une pièce (d) " << endl
				<< "\t reprendre votre partie en cours (r) " << endl
				<< "\t quitter (q)" << endl;
			cin >> choix;
		} while (choix != 'p' && choix != 'd' && choix != 'q' && choix != 'r');
		if(choix == 'r') {
			reprendreUnePartie();
		}

		if (choix == 'p') {
			system("cls");
			afficherEtat(camp);
			cout << "merci d'indiquer la colonne puis la ligne" << endl;
			cin >> colonne >> ligne;
			while (!s.estDansCamp(colonne, ligne, camp)) {
				cout << "La case indiquée ne fait pas partie du camp" << endl;
				system("pause");
				system("cls");
				afficherEtat(camp);
				cout << "merci d'indiquer la colonne puis la ligne" << endl;
				cin >> colonne >> ligne;
			}
			do {
				cout << "choisir une pièce à placer en " << colonne << ","
					<< ligne << endl << "\th pour l'aide" << endl;
				cin >> piece;
				if ((s.estPiece(piece) && s.placer(colonne, ligne, piece, camp))
						 || (s.estPiece(piece+s.MINUS) &&
								s.placer(colonne, ligne, piece+s.MINUS, camp))){
					cout << "\tPlacement réussi" << endl;
					aPlacer[camp][piece] -=1;
					break;
				}
				else if (piece == 'h') {
					system("cls");
					aidePlacement(camp);
				}
				else
					cout << "\tPlacement échoué" << endl;
				system("pause");
				system("cls");
				afficherEtat(camp);
			} while (1); //boucle infinie. Devrait s'arrêter grâce au break

		}
		else if (choix == 'd') {
			cout << "merci d'indiquer la colonne et la ligne d'origine" << endl;
			cin >> colonneDepart >> ligneDepart;
			while (!s.estDansCamp(colonneDepart, ligneDepart, camp)) {
				cout << "La case indiquée ne fait pas partie du camp" << endl;
				cout << "merci d'indiquer la colonne et la ligne d'origine"
					<< endl;
				cin >> colonneDepart >> ligneDepart;
			}
			cout << endl << "merci d'indiquer la nouvelle colonne"
				<< " et la nouvelle ligne" << endl;
			cin >> colonne >> ligne;
			while (!s.estDansCamp(colonne, ligne, camp)) {
				cout << "La case indiquée ne fait pas partie du camp" << endl;
				cout << "merci d'indiquer les nouvelles colonne et ligne"
					<< endl;
				cin >> colonne >> ligne;
			}
			piece = s.getPiece(colonneDepart, ligneDepart);
			cout << "Déplacement de la pièce " << piece << " vers " << colonne
				<< "," << ligne << endl;
			if (s.deplacer(colonneDepart, ligneDepart, colonne, ligne)) {
				cout << "\tDéplacement réussi" << endl;
			}
			else
				cout << "\tDéplacement échoué" << endl;
		}
		afficherEtat(camp);
	} while (choix != 'q' || ilResteDelaPlaceVideDans(camp));
}

/**
 * @brief permet de jouer un coup
 * @param[in] camp le camp dans lequel jouer un coup
 */
void StrategoIHM::jouerUnePartie(int camp) {
	afficherEtat(camp);
	char choix;
	char piece;
	char pieceChemin;
	char colonneDepart, colonne;
	int ligneDepart, ligne;
	char direction;
	unsigned int cases;
	bool coupEffectue = false;

	cout << endl << "Joueur " << s.getNomDuCamp(camp)
		<< " va commencer à jouer" << endl;
	do {
		do {
			cout << "Souhaitez-vous " << endl
				<< "\t jouer (j) " << endl
				<< "\t sauvegarder votre jeu (s) " << endl;
			cin >> choix;
		} while (choix != 'j' && choix != 's');
		if (choix == 'j') {
			system("cls");
			cout << "merci d'indiquer la colonne et la ligne d'origine" << endl;
			cin >> colonneDepart >> ligneDepart;
			while (!s.estPieceDe(s.getPiece(colonneDepart, ligneDepart), camp)) {
				cout << "La case indiquée ne contient pas une pièce du camp"
					<< endl;
				cout << "merci d'indiquer la colonne et la ligne d'origine"
					<< endl;
				cin >> colonneDepart >> ligneDepart;
			}
			piece = s.getPiece(colonneDepart, ligneDepart);
			if(piece != s.VIDE) {
				if (piece == s.ECLAIREUR || piece == s.ECLAIREUR + s.MINUS) {
					do {
						cout << "Choisir une direction, h pour l'aide \t";
						cin >> direction;
						if (direction == 'h')
							aideEclaireur();
					} while(direction != 'a' && direction != 'z' &&
								direction != 'e' && direction != 'w' &&
								direction != 'x' && direction != 'c');

					do {
						cout << "Choisir un nombre de case de déplacement : ";
						cin >> cases;
					} while(cases == 0);

					colonne = colonneDepart;
					ligne = ligneDepart;
					pieceCombatEclaireur(colonne, ligne, direction, cases);
					pieceChemin = s.getPiece(colonne, ligne);

					if(s.deplacementEclaireur(colonneDepart, ligneDepart,
												 direction, cases)) {
						if(pieceChemin != s.VIDE &&
								s.campsOpposes(piece, pieceChemin)) {
							cout << "Combat entre votre pièce " << piece
							<< " et la pièce ennemie " << pieceChemin << endl;

							pieceChemin = s.getPiece(colonne, ligne);
							if (pieceChemin != s.VIDE) {
								cout << "La pièce " << pieceChemin
									<< " a gagné le combat" << endl;
							}
							else
								cout << "Égalité" << endl;
						}
						cout << "\t Mouvement réussi" << endl;
						coupEffectue = true;
					}
					else
						cout << "\t Mouvement refusé" << endl;
				}
				else {
					cout << endl << "merci d'indiquer la nouvelle colonne"
						<< " et la nouvelle ligne" << endl;
					cin >> colonne >> ligne;
					while (!s.estDansTerrain(colonne, ligne)) {
						cout << "La case indiquée ne fait pas partie du terrain"
							<< endl;
						cout <<"merci d'indiquer les nouvelles colonne et ligne"
							<< endl;
						cin >> colonne >> ligne;
					}

					cout << "Mouvement de la pièce " << piece << " vers "
					<< colonne << "," << ligne << endl;
					pieceChemin = s.getPiece(colonne,ligne);
					if (s.mouvement(colonneDepart, ligneDepart, colonne, ligne,
											camp)) {
						if(pieceChemin != s.VIDE &&
								s.campsOpposes(piece,pieceChemin)) {
							cout << "Combat entre votre pièce " << piece
							<< " et la pièce ennemie " << pieceChemin << endl;

							pieceChemin = s.getPiece(colonne, ligne);
							if (pieceChemin != s.VIDE) {
								cout << "La pièce " << pieceChemin
									<< " a gagné le combat" << endl;
							}
							else
								cout << "Égalité" << endl;
						}

						cout << "\t Mouvement réussi" << endl;
						coupEffectue = true;
					}
					else
						cout << "\t Mouvement refusé" << endl;
				}
			}
			afficherEtat(camp);
		}
		else {
			cout << "Vous allez sauvegarder la partie en cours" << endl;
			sauvegarder();
			cout << "appuyer sur Q si vous souhaitez quitter le jeu \t";
			cin >> choix;
			if (choix == 'Q')
				exit(0);
		}
	} while (!coupEffectue);
}

/**
 * @brief Sauvegarde une partie en cours
 */
void StrategoIHM::sauvegarder() {
	string mdp;
	string crypte;
	char nomF[25];
	system("cls");

	crypte=s.getEtat();
	if (!debug) {
		cout << "Choississez le mot de passe : \t";
		cin >> mdp;
		s.getClef(mdp, crypte);
	}
	// Ouverture d'un flot en écriture
	ofstream ficE;
	cout << endl << endl << "Saisir le nom du fichier de sauvegarde: \t";
	cin >> nomF;
	ficE.open(nomF, ios::out);
	if (ficE.fail()) {
		cerr << "Impossible d'écrire dans le fichier" << nomF << "." << endl;
		exit(1);
	}
	ficE << crypte; //envoie le flux vers le fichier
	cout << "La sauvegarde du fichier " << nomF << " s'est bien déroulée."
		<< endl;

	// Fermeture du flot
	ficE.close();
}

/**
 * @brief Remet à une partie en cours
 */
void StrategoIHM::reprendreUnePartie() {
	string mdp;
	string crypte;
	ifstream ficL;
	char nomF[25];

	// Ouverture d'un flot en lecture
	cout << "Saisir le nom de la sauvegarde à reprendre :\t";
	cin >> nomF;
	ficL.open(nomF, ios::in);

	if (ficL.fail()) {
		cerr << "Impossible de lire le fichier" << nomF << "." << endl;
		exit(1);
	}

	ficL.seekg(0); //se positionner au début

	//Boucle pour éviter les problèmes de décryptage si espace/tab/fin de ligne
	while (ficL.good()) {
		char c = ficL.get();
		if (ficL.good())
			crypte += c;
	}
	//ficL.get() >> crypte;
	if (!debug) {
		cout << "Entrer votre mot de passe : \t";
		cin >> mdp;
		s.getClef(mdp, crypte);
	}
	// Fermeture du flot
	ficL.close();
	s.setEtat(crypte);
}

/**
 * @brief affiche l'état courant
 * @param[in] camp le camp jouant actuellement
 */
void StrategoIHM::afficherEtat(int camp) const {
	char piece;

	//Haut des hexagones de la ligne du haut
	for (int i = 0; i < s.COLONNES; ++i) {
		if (i % 2 == 0)
			cout << "     ";
		else
			cout << "___";
	}
	cout << endl;

	//Ligne du haut
	cout << " ";
	for (char c = s.COLGAUCHE; c <= s.COLDROITE; ++c) {
		if ((c-s.COLGAUCHE)%2 == 0)
			cout << "___";
		else {
			cout << "/ ";
			piece = s.getPiece(c, s.LIGNES+1);
			if (getDebug() || s.estPieceDe(piece, camp) || piece == s.VIDE)
				cout << piece;
			else
				cout << "?";
			cout<< " \\";
		}
	}
	cout << "  - " << s.LIGNES+1 << endl;

	//Autres lignes
	for (int l = s.LIGNES; l > 0; --l) {
		//Colonnes A, C, E, …
		for (char c = s.COLGAUCHE; c <= s.COLDROITE; ++c) {
			if ((c-s.COLGAUCHE)%2 == 0) {
				piece = s.getPiece(c, l);
				cout << "/ " ;
				if (getDebug() || s.estPieceDe(piece, camp) || piece == s.VIDE)
					cout << piece;
				else
					cout << "?";
				cout << " \\";
			}
			else
				cout << "___";
		}
		cout << endl;
		//Colonnes B, D, …
		for (char c = s.COLGAUCHE; c <= s.COLDROITE; ++c) {
			if ((c-s.COLGAUCHE)%2 == 0)
				cout << "\\___/";
			else {
				piece = s.getPiece(c, l);
				cout << " " ;
				if (getDebug() || s.estPieceDe(piece, camp) || piece == s.VIDE)
					cout << piece;
				else
					cout << "?";
				cout << " ";
			}
		}
		cout << " - " << l << endl;
	}

	//Bas des hexagones de la ligne du bas
	cout << " ";
	for (int i = 0; i < s.COLONNES; ++i) {
		if (i % 2 == 0)
			cout << "   ";
		else
			cout << "\\___/";
	}
	cout << endl;

	//Affichage des colonnes
	for (char colonne = s.COLGAUCHE; colonne <= s.COLDROITE; ++colonne)
		cout << "  " << colonne << " ";
	cout << endl;
}

/**
 * @brief Aide pour le nombre de pièces réstants et le nom des pièces
 * @param[in] camp le camp jouant actuellement
 */
void StrategoIHM::aidePlacement(int camp) const {
	cout << "Aide sur le nom des pièces : " << "rentrer pour" << endl;
	for (std::map<char, int>::const_iterator it = aPlacer[camp].begin();
		it!=aPlacer[camp].end(); ++it) {
		std::cout << "\t\t" << nomsDesPieces.find(it->first)->second
			<< " = '"<< it->first << "',\t\t"<< it->second
			<< " pièces encore à placer" << std::endl;
	}
}

/**
 * @brief Aide pour les déplacements de l'éclaireur
 */
void StrategoIHM::aideEclaireur() const {
	cout << "Pour aller en		HAUT-GAUCHE :	a" << endl;
	cout << "Pour aller en 		HAUT : 		z" << endl;
	cout << "Pour aller en 		HAUT-DROITE :	e" << endl;
	cout << "Pour aller en 		BAS-GAUCHE :	w" << endl;
	cout << "Pour aller en 		BAS : 		x" << endl;
	cout << "Pour aller en 		BAS-DROITE :	c" << endl;
}

/**
 * @brief indique si il reste des emplacements dans le camp donné
 * @param[in] camp le camp jouant actuellement
 * @return un booléen pour savoir si il reste des emplacements
 */
bool StrategoIHM::ilResteDelaPlaceVideDans(int camp) const {
	return (getNombreDePlaceVideSurPlateau(camp) != 0);
}

/**
 * @brief indique le nombre de place vide sur le terrain
 * @param[in] camp le camp jouant actuellement
 * @return le nombre d'emplacement vide
 */
unsigned int StrategoIHM::getNombreDePlaceVideSurPlateau(int camp) const {
	unsigned int NombrePieceVide = 0;
	if (camp == s.NORD) {
		int ligne = 6;
		char colonne = s.COLGAUCHE;
		for (; s.estDansCamp(colonne, ligne, camp); ++colonne) {
			if (s.getPiece(colonne, ligne) == s.VIDE)
				++NombrePieceVide;
			if (colonne == s.COLDROITE) {
				colonne = s.COLGAUCHE;
				++ligne;
			}
			if (ligne == 9)
				++colonne;
		}
	}
	else {
		int ligne = 1;
		char colonne = s.COLGAUCHE;
		for (; s.estDansCamp(colonne, ligne, camp); ++colonne) {
			if (s.getPiece(colonne, ligne) == s.VIDE)
				++NombrePieceVide;
			if (colonne == s.COLDROITE) {
				colonne = s.COLGAUCHE;
				++ligne;
			}
			if (ligne == 4)
				++colonne;
		}
	}
	return (NombrePieceVide);
}

/**
 * @brief indique le nombre de pièces capable de se déplacer sur le terrain
 * @param[in] camp le camp jouant actuellement
 * @return le nombre de pièces mobiles sur le terrain
 */
int StrategoIHM::getNombreDePieceMobileSurPlateau(int camp) const {
	int nbPiece=0;
	char piece;
	if (camp == s.NORD) {
		for (unsigned int i = 0; i < s.SIZE; ++i) {
			piece = s.getPieceInd(i);
			if (piece == s.MARECHAL + s.MINUS || piece == s.GENERAL + s.MINUS ||
				piece == s.COLONEL + s.MINUS || piece == s.COMMANDANT + s.MINUS
				|| piece == s.CAPITAINE + s.MINUS || piece == s.LIEUTENANT
				+ s.MINUS || piece == s.SERGENT + s.MINUS || piece == s.DEMINEUR
				+ s.MINUS || piece == s.ECLAIREUR + s.MINUS || piece == s.ESPION
				+ s.MINUS)
					++nbPiece;
		}
	}
	else {
		for (unsigned int i = 0; i< s.SIZE; ++i) {
			piece = s.getPieceInd(i);
			if (piece == s.MARECHAL || piece == s.GENERAL || piece == s.COLONEL
				|| piece == s.COMMANDANT || piece == s.CAPITAINE ||
				piece == s.LIEUTENANT || piece == s.SERGENT ||
				piece == s.DEMINEUR || piece == s.ECLAIREUR || piece ==s.ESPION)
					++nbPiece;
		}
	}
	return (nbPiece);
}

/**
 * @brief Indique si la partie est finie, et le vainqueur le cas échant
 * @return 0:partie non finie, 1:Nord vainqueur, 2:Sud vainqueur, 3:Égalité
 */
int StrategoIHM::finDePartie() const {
	char piece;
	bool drapSud = false;
	bool drapNord = false;
	int nbMobNord = getNombreDePieceMobileSurPlateau(s.NORD),
		nbMobSud = getNombreDePieceMobileSurPlateau(s.SUD);

	for (unsigned int i = 0; i < s.SIZE; ++i) {
		piece = s.getPieceInd(i);
		if (piece == s.DRAPEAU)
			drapSud = true;
		if (piece == s.DRAPEAU + s.MINUS)
			drapNord = true;
	}
	if ((!drapNord || nbMobNord == 0) && (!drapSud || nbMobSud == 0))
		return 3; //Égalité
	else if (!drapNord || nbMobNord == 0)
		return 2; //Sud vainqueur
	else if (!drapSud || nbMobSud == 0)
		return 1; //Nord vainqueur
	else
		return 0; //Partie non finie
}

/**
 * @brief active le mode débug
 * @param[in] actif booléen d'activation du débug
 */
void StrategoIHM::setDebug(bool actif) {
	debug = actif;
}

/**
 *@brief indique si le débug est activé ou non
 *@return booléen d'activation du débug
 */
bool StrategoIHM::getDebug() const {
	return (debug);
}

void StrategoIHM::pieceCombatEclaireur(char& colonneO, int& ligneO,
										char direction, unsigned int cases) {
	switch (direction) {
	case 'z' : //Haut
		ligneO += cases;
		break;
	case 'x' : //Bas
		ligneO -= cases;
		break;
	case 'a' : //Haut-gauche
		if ((colonneO-s.COLGAUCHE)%2 == 1)
			ligneO += cases/2;
		else
			ligneO += (cases+1)/2;
		colonneO -= cases;
		break;
	case 'w' : //Bas-gauche
		if ((colonneO-s.COLGAUCHE)%2 == 1)
			ligneO -= cases/2;
		else
			ligneO -= (cases+1)/2;
		colonneO -= cases;
		break;
	case 'e' : //Haut-droite
		if ((colonneO-s.COLGAUCHE)%2 == 1)
			ligneO += cases/2;
		else
			ligneO += (cases+1)/2;
		colonneO += cases;
		break;
	case 'c' : //Bas-droite
		if ((colonneO-s.COLGAUCHE)%2 == 1)
			ligneO -= cases/2;
		else
			ligneO -= (cases+1)/2;
		colonneO += cases;
		break;
	default :
		return;
	}
}
