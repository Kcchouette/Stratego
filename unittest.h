/**
 * @file Stratego.cpp
 * Projet de CDP ~ Stratego
 * @author Jérémy CANAT, Warren DARD, Benjamin DAUPHIN et Anthony SOBREIRA
 * @brief templates pour le test unitaire
 */
#ifndef UNITEST_H
#define UNITEST_H

#include <iostream>
#include <string>

template <typename T>
void assertEquals(const T& x, const T& y, const std::string& s) {
	std::cout << "Test " << s;
	if (x == y)
		std::cout << " a reussi\n";
	else {
		std::cout << " a ECHOUE ###\n";
		std::cout << "|" << x << "| = |" << y << "|" << std::endl;
	}
}

void assertTrue(bool, const std::string&);
void assertFalse(bool, const std::string&);

#endif
