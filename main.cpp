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

	//Po.PrintDatabyProcessors(); // Εμφανίζω τις εργασίες του κάθε επεξεργαστή.


	while ( Po.Number_of_Tasks() > 1 ) // Μέχρι να μείνει μια εργασία σε όλους τους επεξεργαστές..
	{

		Po.Find_and_SAVE_the_lowest_values_of_all();

		Po.removing_the_current_minimum_task_by_all_processors();

		//Po.PrintDatabyProcessors();

	}



	//Po.PrintDatabyProcessors();

	Po.Final_Time();

	//Po.Original_PrintDatabyProcessors();





	return 0;
}
