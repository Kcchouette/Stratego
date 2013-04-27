/**
 * @file main.cpp
 * Projet de CDP ~ Stratego
 * @author Jérémy CANAT, Warren DARD, Benjamin DAUPHIN et Anthony SOBREIRA
 */

#include <iostream>
using namespace std;
#include "StrategoIHM.h"

int main() {
	cout << "Test de Stratego" << endl;
	Stratego::tester();
	cout << "Test de StrategoIHM" << endl << endl;
	StrategoIHM::tester();
	StrategoIHM ihm;
}
