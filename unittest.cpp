/**
 * @file unittest.cpp
 * Projet de CDP ~ Stratego
 * @author Jérémy CANAT, Warren DARD, Benjamin DAUPHIN et Anthony SOBREIRA
 */
#include "unittest.h"

void assertTrue(bool x, const std::string& s) {
	assertEquals(x, true, s);
}

void assertFalse(bool x, const std::string& s) {
	assertEquals(x, false, s);
}
