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
#include <utility> // Για τα pairs.
#include <vector>
#include <algorithm> // Για τις αναζητήσεις.
#include <iterator>  // Για το std::distance

using namespace std;


Problem::Problem()
{

	// Αρχικοποίηση στις ιδιότητες του αντικειμένου.

	min_value = -1;
	min_pos = -1;

	max_value = -1;
	max_pos = -1;

	processors_number = 0;

	cout << "Δώσε τον αριθμό των επεξεργαστών. ";
	cout << "Επεξεργαστές : "; cin >> processors_number;

	processors_number++; // Δεν θα χρησιμοποιώ την θέση 0. Για να λέει θέση 1 = Επεξεργαστής 1, Θέση 2 = Επεξεργαστής 2.

	MinTasks = new pair <int, int>[processors_number](); // Ορισμός των θέσεων του δυναμικού πίνακα.

	processors.resize(processors_number); // Αυτός ο πίνακας θα είναι η "βάση" του. Η κάθε θέση/επεξεργαστής, θα περιέχει την λιστα με τους χρόνους του κάθε έργου.


}




void	Problem::getDataFromFile()
{


	ifstream fl;

	fl.open("Data/Braun_et_al/Sample"); // Το πρώτο αρχείο από τον φάκελο /Data/Braun_et_al/

	/* ===================== Έλεγχος ανοίγματος αρχείου ===================== */
	if ( !fl )
	{
		cout << "Σφάλμα : Το αρχείο δεν μπόρεσε να ανοίξει." << endl;
		exit(1);
	}
	/* ===================== -------------------------- ===================== */

	string line_buffer {};

	for ( int i=1; getline(fl, line_buffer); i++  ) // Διαβάζω γραμμή γραμμή, & το περιεχόμενο της γραμμής το πετάω σε ένα προσωρινό buffer -> "line_buffer".
	{ // Ταυτόχρονα έχω και ένα μετρητή που θα μου δείχνει σε ποιον επεξεργαστή & εργασία βρίσκομαι.

		if ( i == processors_number ) // Αν βάλει για την τρέχουσα διεργασία "i" τις τιμές της σε όλους του επεξεργαστές.
			i=1; // Τότε θα πάει ξανά από την αρχή. Δηλ. : Στην ΕΠΌΜΕΝΗ διεργασία η τιμή που έχει στον "i" επεξεργαστή. ;)

		processors[i].push_back( atof( line_buffer.c_str() ) );/* Μετατρέπω σε πραγματικό αριθμό ( double ) αυτό που διαβάζω και
																	το προσθέτω έπειτα στην λίστα (της θέσης)/του επεξεργαστή i . */

	}


	fl.close(); // Κλείσιμο του ρεύματος διαβάσματος του αρχείου.



}




void	Problem::PrintDatabyProcessors()
{
	// Για να δω τι έκανα..
	//cout << " Ο πίνακας - vector 'processors' έχει μέγεθος : " << processors.size() << endl;

	for ( int i = 1; i < processors_number ; i++ ) // Από την 1η θέση και ΌΧΙ από την 0! ( Έχω κάνει μια σύμβαση! Μην την ξεχνάω!! )
	{
		cout << endl << "\t     Επεξεργαστής " << i << endl;
		cout << "----------|-----------------|\n";
		for ( unsigned int k = 0; k < processors[i].size(); k++ )
			{
			printf ( "Εργασία %d |\t %d \t    |\n" ,k+1 , processors[i][k] ) ;
			printf ("----------|-----------------|\n");
			}

	}

}




void	Problem::Find_and_SAVE_the_lowest_values_of_all_the_processors()
{

	for ( unsigned int i = 1; i < processors.size() ; i++ ) // Από την 1η θέση και ΌΧΙ από την 0! ( Έχω κάνει μια σύμβαση! Μην την ξεχνάω!! )
	{ // Για όλους τους επεξεργαστές δηλαδή..
		Find_MIN_Value_and_PoS_by_Processor(i); // Βρες ΠΟΙΑ (min_value) και ΠΟΥ (min_pos) είναι η ελάχιστη διεργασία που έχει αυτός ο επεξεργαστής.
		MinTasks[i] = make_pair( min_value , min_pos ); // Και κράτα αυτές τις τιμές στον πίνακα MinTasks για το επεξεργαστή αυτό.

	}

}




void	Problem::Print_MinTasks()
{
	cout << endl << "Εμφάνιση του MinTaskS" << endl;

	for ( int i = 1; i < processors_number ; i++ ) // Από την 1η θέση και ΌΧΙ από την 0! ( Έχω κάνει μια σύμβαση! Μην την ξεχνάω!! )
	{
		cout << "Επεξεργαστής #" << i << "\t Ελάχιστη τιμή διεργασίας " << MinTasks[i].first << " η διεργασία " << MinTasks[i].second << " (" << MinTasks[i].second+1 << "η)" << endl;
	}
}




int	Problem::Finding_Pos_of_MINimum_Task_by_MinTasks()
{

	int min_time = MinTasks[1].first; // Λέω αρχικά πως στον ΠΡΏΤΟ επεξεργαστή ( 1 διότι έχω κάνει την σύμβαση! ) υπάρχει ο ελάχιστος χρόνος διεργασίας σε σύγκριση και με όλους τους άλλους..
	int pos = 1; // Και ότι στην πρώτη θέση του πίνακα βρίσκεται..

	for ( int i = 2; i < processors_number ; i++ ) // Από την 2η θέση και ΌΧΙ από την 1η! ( Τώρα και για την σύμβαση που έχω κάνει, αλλά και γιατί την 1 την έχω βάλει ως min!
	{
		if ( min_time > MinTasks[i].first )
		{
			min_time = MinTasks[i].first; // Αναθεωρώ ως προς τον καλύτερο χρόνο.
			pos = i; // Παίρνω την θέση.
		}

	}

	return pos;

}




void	Problem::removing_the_current_minimum_task_by_all_processors()
{
	// Έτσι θα βρει τις ελάχιστες τιμές εργασιών σε όλους τους επεξεργαστές και θα αποθηκεύσει τα αποτελέσματα στον πίνακα "MinTasks" .
	//Find_and_SAVE_the_lowest_values_of_all_the_processors();

	int se_pia_cpu = Finding_Pos_of_MINimum_Task_by_MinTasks(); // Έτσι θα βρούμε σε πoιον επεξεργαστή υπάρχει η χαμηλότερη τιμή.

//	cout << endl;
//	cout << "Άρα ήμαστε στον επεξεργαστή " << se_pia_cpu << " με τιμή εργασίας " << MinTasks[se_pia_cpu].first;
//	cout << " που είναι η εργασία " << MinTasks[se_pia_cpu].second << " (" << MinTasks[se_pia_cpu].second+1 << "η)" << endl;


	// Οπότε πάω τώρα και αφαιρώ την εργασία "MinTasks[se_pia_cpu].second" ( που είχε τον μικρότερο χρόνο ) από όλους τους επεξεργαστές.

	for ( int i = 1; i < processors_number ; i++ ) // Από την 1η θέση και ΌΧΙ από την 0! ( Έχω κάνει μια σύμβαση! Μην την ξεχνάω!! )
	{ // Δηλαδή πάω σε όλους τους επεξεργαστές..
		for ( int k = 0; k < processors[i].size(); k++ ) // και σε κάθε επεξεργαστή πάω σε όλες τις εργασίες του
		{
			if ( k == MinTasks[se_pia_cpu].second ) // Όταν βρίσκω τον αριθμό της εργασίας στον επεξεργαστή.. Ο αριθμός με νοιάζει ( ποια εργασία είναι, η 1,2... )
			{
				processors[i].erase (processors[i].begin() + k); // την διαγράφω.
			}

		}

	}

	//PrintDatabyProcessors(); // Βλέπω αν όντως διαγράφηκε η εργασία με τον ελάχιστο χρόνο από όλους του επεξεργαστές.

	// Και πρέπει να προσθέσω όμως στον επεξεργαστή που βρισκόταν η ελάχιστη εργασία, τον χρόνο της, στις υπόλοιπες εργασίες.

	for ( unsigned int k = 0; k < processors[se_pia_cpu].size(); k++ ) //
	{
		processors[se_pia_cpu][k] += MinTasks[se_pia_cpu].first;

	}

	//PrintDatabyProcessors();
	/* Οπότε πλέον ας δω αν όντως έχουν αλλάξει οι χρόνοι στις υπόλοιπες εργασίες ΜΌΝΟ του επεξεργαστή "se_pia_cpu"	που είχε την ελάχιστη σε χρόνο εργασία. */

}




int		Problem::Number_of_Tasks()
{
	return processors[1].size();
}




void	Problem::Final_Time()
{
	Find_and_SAVE_the_lowest_values_of_all_the_processors(); // Ποιος από όλους έχει την καλύτερη τιμή στην τελευταία εργασία.

	int se_pia_cpu = Finding_Pos_of_MINimum_Task_by_MinTasks(); // Έτσι θα βρούμε σε πoιον επεξεργαστή υπάρχει η χαμηλότερη τιμή.

	cout << endl;
	cout << "|=======================================================================|" << endl;
	cout << "|\tΟ επεξεργαστής " << se_pia_cpu << " θα έχει την ελάχιστη εργασία με χρόνο : " << MinTasks[se_pia_cpu].first << "     |" <<endl;
	cout << "|=======================================================================|" << endl;


}






























/* ==================================== Ιδιωτικοί μέθοδοι. ==================================== */



void		Problem::Find_MIN_Value_and_PoS_by_Processor(int cpu)
{
	auto Vmin = min_element( processors[cpu].begin(), processors[cpu].end() ); // c++11
    min_value = *Vmin; // Το αποθηκεύω στην ιδιότητα του αντικειμένου.


    min_pos = find( processors[cpu].begin() , processors[cpu].end() , min_value) - processors[cpu].begin();

    //cout << "min = " << min_value << " στην θέση : " << min_pos << endl;

}




void		Problem::Find_MAX_Value_and_PoS_by_Processor(int cpu)
{
	auto Vmax = max_element( processors[cpu].begin(), processors[cpu].end() ); // c++11
	max_value = *Vmax;


    max_pos = find( processors[cpu].begin() , processors[cpu].end() , max_value) - processors[cpu].begin();

    //cout << "max = " << max_value << " στην θέση : " << max_pos << endl;
}
































Problem::~Problem() {
	delete [] MinTasks;
//	delete [] processor_total;

}

