/*
 * main.cpp
 *
 *  Created on: G-lts Team Lab
 *      Author: Tas-sos
 */

#include <iostream>
#include "Problem.h"


using namespace std;


int main (void)
{
	Problem Po;


	Po.getDataFromFile(); // Διαβάζω τα δεδομένα ( τους χρόνους ) από το αρχείο.

//	Po.PrintDatabyProcessors(); // Εμφανίζω τις εργασίες του κάθε επεξεργαστή.

	Po.MinMin(); // Αλγόριθμος Min-Min.
//	Po.MaxMin(); // Αλγόριθμος Max-Min.








	return 0;
}

