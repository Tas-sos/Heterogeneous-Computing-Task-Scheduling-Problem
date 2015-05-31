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

	Po.PrintDatabyProcessors(); // Εμφανίζω τις εργασίες του κάθε επεξεργαστή.

	while ( Po.Number_of_Tasks() > 1 ) // Μέχρι να μείνει μια εργασία σε όλους τους επεξεργαστές..
	{


		Po.Find_and_SAVE_the_lowest_values_of_all_the_processors(); // Βρίσκω τις εργασίες με τις ελάχιστες τιμές από όλους τους επεξεργαστές.

		Po.Print_MinTasks(); // Εμφανίζω από τον κάθε ένα επεξεργαστή την διεργασία με τον μικρότερο χρόνο.

		//	cout << "Στον επεξεργαστή " << Po.Finding_Pos_of_MINimum_Task_by_MinTasks() << " υπάρχει ο μικρότερος χρόνος διεργασίας." << endl;

		Po.removing_the_current_minimum_task_by_all_processors(); /* Διαγράφω από ΌΛΟΥΣ ( αδιακρίτως ) τους επεξεργαστές, την εργασία που βρήκα πριν
		με τον μικρότερο χρόνο από όλες τις άλλες. Έπειτα όμως στον ΜΌΝΟ επεξεργαστή που βρήκα την εργασία αυτή, στις υπόλοιπες προσθέτω τον χρόνο της.*/

		Po.PrintDatabyProcessors();

	}

	Po.Final_Time();





	return 0;
}

