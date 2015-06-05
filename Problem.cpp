/*
 * Problem.cpp
 *
 *  Created on: G-lts Team Lab
 *      Author: Tas-sos
 */

#include "Problem.h"
#include <fstream> // Για τα αρχεία.
#include <iostream>
#include <cstdlib> // Για το exti(1).
#include <string> // Κυρίως για το διάβασμα των πραγματικών αριθμών και την μετατροπή τους από strint -> Double.


using namespace std;


Problem::Problem()
{

	// Αρχικοποίηση στις ιδιότητες του αντικειμένου.

	min_value = -1; // Κρατάει την ελάχιστη "υποτιθέμενη - ενός βήματος μπροστά" τιμή.
	min_original_value = -1; // Κρατάει την πραγματική τιμή της ελάχιστης εργασίας που βρέθηκε με βάση την "min_value".
	min_posTASK = -1; // Σε ποια εργασία-γραμμή του πίνακα, είναι η ελάχιστη εργασία.
	min_posCPU = -1; // Σε ποιον επεξεργαστή-στήλη του πίνακα, υπάρχει η ελάχιστη εργασία.

	posa_tasks_eminan = -1; // Κρατάει τον αριθμό των εργασιών που απομένουν ( έπειτα από την εύρεση μιας ελάχιστης εργασίας, μειώνεται κατά 1 )


	processors_number = 0; // Κρατάει τον αριθμό των επεξεργαστών.
	tasks_number = 0; // Κρατάει τον αριθμό των εργασιών.

	cout << "Δώσε τον αριθμό των εργασιών. ";
	cout << "Εργασίες : "; cin >> tasks_number;

	posa_tasks_eminan = tasks_number;

	cout << "Δώσε τον αριθμό των επεξεργαστών. ";
	cout << "Επεξεργαστές : "; cin >> processors_number;


	// ================================== Ο πίνακας στον οποίο θα  γίνονται αλλαγές. ==================================
	Tasks_and_processors = new double * [ tasks_number ](); // Φτιάχνω τις γραμμές του δυναμικού πίνακα.

	for (int i = 0; i < tasks_number; i++) // Φτιάχνω τις στήλες του δυναμικού πίνακα για όλες τις γραμμές..
		Tasks_and_processors[i] = new double [processors_number]; // Η κάθε γραμμή θα έχει "processors_number" στήλες.



	// Και σε αυτόν τον ίδιο πίνακα θα κρατάω -*ΑΠΕΙΡΑΧΤΕΣ*- τις τιμές από όλες τις εργασίες.
	Origina__Tasks_and_processors = new double * [ tasks_number ]();
	for (int i = 0; i < tasks_number; i++)
		Origina__Tasks_and_processors[i] = new double [processors_number];

}




void	Problem::getDataFromFile()
{

	ifstream fl;

	fl.open("Data/Braun_et_al/u_c_hihi.0"); // Αρχεία από τον φάκελο /Data/Braun_et_al/

	/* ===================== Έλεγχος ανοίγματος αρχείου ===================== */
	if ( !fl )
	{
		cout << "Σφάλμα : Το αρχείο δεν μπόρεσε να ανοίξει." << endl;
		exit(1);
	}
	/* ===================== -------------------------- ===================== */

	cout << "Έλεγχος αρχείου ................................... [OK]" <<endl;

	string line_buffer {};

	for ( int task=0; task < tasks_number ; task++  ) // Για "tasks_number" φορές..
	{

		// Θα διαβάσω "processors_number" τιμές από το αρχείο..
		for ( int cpu=0;( (cpu < processors_number) && (getline(fl, line_buffer)) ) ; cpu++ )
		{
			double value = atof ( line_buffer.c_str() ); // Μετατρέπω αρχικά σε πραγματικό αριθμό ( double ) αυτό που διαβάζω ( που είναι σε string ).

			Tasks_and_processors[task][cpu] = value ; // Το εκχωρώ έπειτα στην εργασία "task" του επεξεργαστή "cpu", στο πίνακα όπου οι τιμές του θα αλλάζουν .
			Origina__Tasks_and_processors[task][cpu] = value; // αλλά ΚΑΙ στον πίνακα που οι τιμές του δεν θα αλλάξουν.

			//printf("Εργασία #%d \t %lf \t cpu #%d \n", task , Tasks_and_processors[task][cpu]+1 , cpu );
		}
	}


	fl.close(); // Κλείσιμο του ρεύματος διαβάσματος του αρχείου.
}




void	Problem::Find_and_SAVE_the_lowest_values_of_all()
{

	int task_f = 0;
	for ( task_f = 0; task_f < tasks_number ; task_f++ ) // Για να αρχικοποιώ κάθε φορά την ελάχιστη τιμή..
	{
		for ( int cpu = 0; cpu < processors_number ; cpu++ )
			{
				min_value = Tasks_and_processors[task_f][cpu];
				min_original_value = Origina__Tasks_and_processors[task_f][cpu]; // Για να κρατήσω την original τιμή του.

				min_posTASK = task_f;
				min_posCPU = cpu;

				if ( min_value != -1 )
					break;
			}

		if ( min_value != -1 )
			break;
	} // Τέλος αρχικοποίησης ελάχιστης τιμής..



	// Για να βρω τώρα την τυχόν μικρότερη τιμή.
	for ( int task = task_f; task < tasks_number ; task++ ) // Από εκεί που βρήκα την ελάχιστη τιμή και κάτω..
	{
		for ( int cpu = 0; cpu < processors_number; cpu++ )
		{
			if ( (Tasks_and_processors[task][cpu] != -1) && (min_value > Tasks_and_processors[task][cpu]) )
			{
				min_value = Tasks_and_processors[task][cpu];
				min_original_value = Origina__Tasks_and_processors[task][cpu];
				min_posTASK = task;
				min_posCPU = cpu;

			}
		}
	}

	/*cout << "Η μικρότερη τιμή είναι : " << min_value << " στην θέση (" << min_posTASK << "," << min_posCPU << "). ";
	cout << "Δηλαδή στον επεξεργαστή " << min_posCPU+1 << " η εργασία " << min_posTASK+1 << endl;

	cout << "[F]: min_original_value = " << min_original_value << endl;
	*/

}




void	Problem::removing_the_current_minimum_task_by_all_processors()
{
	for ( int task = 0; task < tasks_number ; task++ ) // Για ΌΛΕΣ τις εργασίες στον επεξεργαστή που βρέθηκε η εργασία με την χαμηλότερη τιμή..
		if ( Tasks_and_processors[task][min_posCPU] != -1) // Στις εργασίες αυτές που απομένουν ακόμη ( διότι αυτές με -1 σημαίνει πως αφαιρέθηκαν ).
				Tasks_and_processors[task][min_posCPU] += min_original_value; /* Πρόσθεσε τον χρόνο της μικρότερης εργασίας.
				Τον ΠΡΑΓΜΑΤΙΚΌ χρόνο της όμως & ΟΧΙ τον χρόνο που έχει μαζί με τις τυχόν άλλες εργασίες που μπορεί να έχουν προστεθεί και σε εκείνη. -!*!S.O.S.!*!-  */


	for ( int cpu = 0; cpu < processors_number; cpu++ ) // Έπειτα αφαιρώ την εργασία αυτή από όλους του επεξεργαστές.
		Tasks_and_processors[min_posTASK][cpu] = -1 ;


	posa_tasks_eminan--; // Αφαιρώ ένα task ( για να ξέρω πόσα μου μένουν - για να τελειώσω ).

}




int		Problem::Number_of_Tasks()
{
	return posa_tasks_eminan;
}




void	Problem::Final_Time()
{
	Find_and_SAVE_the_lowest_values_of_all();

	cout << endl;
	cout << "|===================================================================================|" << endl;
	cout << "|\tΟ επεξεργαστής " << min_posCPU+1 << " θα έχει την ελάχιστη εργασία με χρόνο : ";
	printf ("%lf  \n", Tasks_and_processors[min_posTASK][min_posCPU] );
	cout << "|===================================================================================|" << endl;


}




void	Problem::PrintDatabyProcessors() // Για να δω τι έκανα..
{

	for ( int task = 0 ; task < tasks_number; task++  )
	{
		if ( Tasks_and_processors[task][0] == -1 ) // Αν σε κάποιo task από την πρώτη κιόλας cpu βρω τιμή -1 ( που πάει να πει πως αφαιρέθηκε )
			continue; // Οπότε δεν την εμφανίζω.. πάω στην επόμενη. ;)


		cout << endl << "\t\t Task #" << task+1 << endl;
		cout << "----------|------------------------------------------|\n";


		for ( int cpu = 0; cpu < processors_number; cpu++ )
			{
			printf ( "Cpu #%d    |\t %lf \tOfficial => %lf \n" ,cpu+1 , Tasks_and_processors[task][cpu], Origina__Tasks_and_processors[task][cpu] ) ;
			printf ("----------|------------------------------------------|\n");
			}
	}

}




void	Problem::Original_PrintDatabyProcessors()
{
	// Για να δω τι έκανα..
	for ( int task = 0 ; task < tasks_number; task++  )
	{
		if ( Origina__Tasks_and_processors[task][0] == -1 ) // Αν σε κάποιo task από την πρώτη κιόλας cpu βρω τιμή -1 πάει να πει πως αφαιρέθηκε
			continue; // Οπότε δεν την εμφανίζω.. πάω στην επόμενη. ;)

		cout << endl << "\t\t Task #" << task+1 << endl;
		cout << "----------|---------------------------|\n";


		for ( int cpu = 0; cpu < processors_number; cpu++ )
			{
			printf ( "Cpu #%d    |\t %lf \n" ,cpu+1 , Origina__Tasks_and_processors[task][cpu] ) ;
			printf ("----------|---------------------------|\n");
			}

	}

}








































Problem::~Problem() {

	for (int i = 0; i < tasks_number; i++)
		delete[] Tasks_and_processors[i];

	delete[] Tasks_and_processors;



	for (int i = 0; i < tasks_number; i++)
			delete[] Origina__Tasks_and_processors[i];

		delete[] Origina__Tasks_and_processors;



}













