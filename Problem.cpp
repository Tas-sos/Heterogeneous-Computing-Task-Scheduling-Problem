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


using namespace std;


Problem::Problem()
{

	// Αρχικοποίηση στις ιδιότητες του αντικειμένου.

	min_value = -1;
	min_posTASK = -1;
	min_posCPU = -1;

	posa_tasks_eminan = -1;

	processors_number = 0;
	tasks_number = 0;

	cout << "Δώσε τον αριθμό των εργασιών. ";
	cout << "Εργασίες : "; cin >> tasks_number;

	posa_tasks_eminan = tasks_number;

	cout << "Δώσε τον αριθμό των επεξεργαστών. ";
	cout << "Επεξεργαστές : "; cin >> processors_number;


	Tasks_and_processors = new double * [ tasks_number ](); // Φτιάχνω τις γραμμές του δυναμικού πίνακα.

	for (int i = 0; i < tasks_number; i++) // Φτιάχνω τις στήλες του δυναμικού πίνακα για όλες τις γραμμές..
		Tasks_and_processors[i] = new double [processors_number]; // Η κάθε γραμμή θα έχει "processors_number" στήλες.



	Total_processors_Time = new double [processors_number] () ;
	texon_minmum_xroni_apo_ta_MI_dromologoumena_Task = new pair<double, int> [tasks_number] ();

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

		// Θα διαβάσω "processors_number" τιμές από το αρχείο..Για κάθε Task δηλαδή διαβάζω τους χρόνους του στους διαφορετικούς επεξεργαστές.
		for ( int cpu=0;( (cpu < processors_number) && (getline(fl, line_buffer)) ) ; cpu++ )
		{
			double value = atof ( line_buffer.c_str() );
			Tasks_and_processors[task][cpu] = value ;	/* Μετατρέπω σε πραγματικό αριθμό ( double ) αυτό που διαβάζω και
																			το προσθέτω έπειτα στην λίστα (της θέσης)/του επεξεργαστή i . */

			//printf("Εργασία #%d \t %lf \t cpu #%d \n", task , Tasks_and_processors[task][cpu]+1 , cpu );
		}

	}

	fl.close();
}





void	Problem::PrintDatabyProcessors() // Εμφάνιση στοιχείων των ΜΗ δρομολογούμενων διεργασιών.
{

	for ( int task = 0 ; task < tasks_number; task++  )
	{
		if ( Tasks_and_processors[task][0] == -1 ) // Αν σε κάποιο task από την πρώτη κιόλας cpu βρω τιμή -1 πάει να πει πως αφαιρέθηκε - δρομολογήθηκε..
			continue; // Οπότε δεν την εμφανίζω, πάω στην επόμενη διεργασία. ;)

		cout << endl << "\t\t Task #" << task+1 << endl;
		cout << "----------|---------------------------|\n";


		for ( int cpu = 0; cpu < processors_number; cpu++ )
			{
			printf ( "Cpu #%d    |\t %lf \t %lf \n" ,cpu+1 , Tasks_and_processors[task][cpu], Total_processors_Time[cpu] ) ;
			printf ("----------|---------------------------|\n");
			}

	}

}





void Problem::MinMin() // Ο αλγόριθμος Min-Min.
{

//	PrintDatabyProcessors();

	for (int task = 0; Number_of_Tasks() ; task++ )
	{
		Euresi_elaxiston_timon_apo_ta_mi_dromologoumena_tasks();
		Find_min_by_min();
		removing_the_current_minimum_task_by_all_processors();

//		cout << "\n==========================================================\n";
//		PrintDatabyProcessors();
	}

	Final_Min_Min_Time();

}





void Problem::MaxMin() // Ο αλγόριθμος Max-Min.
{

//	PrintDatabyProcessors();

	for (int task = 0; Number_of_Tasks() ; task++ )
	{

		Euresi_elaxiston_timon_apo_ta_mi_dromologoumena_tasks();
		Find_max_by_min(); // Τώρα εδώ θα βρίσκη την *μέγιστη* από τις ελάχιστες. :)
		removing_the_current_minimum_task_by_all_processors();


//		cout << "\n==========================================================\n";
//		PrintDatabyProcessors();
	}
	Final_Max_Min_Time(); // Και στο τέλος επίσης θέλουμε την *μέγιστη" από τις ελάχιστες. :)

}

































/* ==================================== Ιδιωτικοί μέθοδοι. ==================================== */


// 	For Min-Min.


void	Problem::Euresi_elaxiston_timon_apo_ta_mi_dromologoumena_tasks()
{ /* Θα βρίσκω για όλες τις ΔΙΕΡΓΑΣΊΕΣ σε ποιον επεξεργαστή έχουν τον ελάχιστον χρόνο.
 ( Συνυπολογίζοντας *το χρόνο που χρειάζεται ο επεξεργαστής*, για τις ΉΔΗ δρομολογούμενες σε αυτόν διεργασίες ) . */

	for ( int task = 0; task < tasks_number ; task ++ ) // Για κάθε διεργασία λοιπόν..
	{

		if ( Tasks_and_processors[task][0] == -1 ) /* Αν βρει διεργασία που ΈΧΕΙ δρομολογηθεί.. ( σε κάποιον επεξεργαστή ).
											Άρα στον πίνακα "Tasks_and_processors" η διεργασία αυτή θα έχει σε κάθε επεξεργαστή -1. */
			continue; // πάνε στην επόμενη ΔΙΕΡΓΑΣΊΑ..

		// Αλλιώς αν δεν έχει δρομολογηθεί όμως... αρχικοποιούμε πως και καλά ο *αρχικός* μικρότερος χρόνο είναι στον πρώτο επεξεργαστή.
		min_value = Tasks_and_processors[task][0] + Total_processors_Time[0]; // Ο χρόνος της (συνυπολογίζοντας και τον χρόνο των διεργασιών που έχουν δρομολογηθεί σε αυτόν τον επεξεργαστή).
		min_posTASK = task; // Ποια διεργασία είναι.
		min_posCPU = 0; // Σε ποιον επεξεργαστή.


		// Για να βρω τώρα την μικρότερη τιμή.
		for ( int cpu = 1; cpu < processors_number ; cpu++ ) // Από την δεύτερη οπότε cpu και "σαπέρα" :P
		{

			if ( min_value > (Tasks_and_processors[task][cpu] + Total_processors_Time[cpu]) )
			{
				min_value = Tasks_and_processors[task][cpu] + Total_processors_Time[cpu];
				min_posTASK = task;
				min_posCPU = cpu;

			}

		}

		// Οπότε τώρα για την διεργασία που βρήκα την ελάχιστη τιμή της. Πηγαίνω στον πίνακα στην θέση - διεργασία..
		texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[min_posTASK].first = min_value; // κρατάω στο πρώτο μέρος τον χρόνο
		texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[min_posTASK].second = min_posCPU; // στο δεύτερο μέρος σε ποια CPU είναι..

	}

//	cout << "Οι ελάχιστες τιμές από κάθε εργασία είναι : " << endl;
//
//	for (int i = 0 ; i< tasks_number; i++)
//		cout << "Task #" << i+1 << "\t->  " << texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[i].first << endl;
//
}





void Problem::Find_min_by_min()
{
	int task_Po = 0;
	// Επειδή μπορεί και η πρώτη θέση του πίνακα να μην έχει τιμή ( -1 ) - ( *εξηγώ παρακάτω γιατί.. ). Οπότε μέχρι να βρει..
	for ( int task_Po = 0 ; task_Po < tasks_number; task_Po++  )
		if ( texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[task_Po].first != -1 )
		{
			min_value = texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[task_Po].first; // "Ελάχιστος" χρόνος.
			min_posCPU = texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[task_Po].second; // Σε ποιον ΕΠΕΞΕΡΓΑΣΤΉ είναι ο "ελάχιστος" χρόνος.
			min_posTASK = task_Po; // Ποια διεργασία είναι αυτή με τον "ελάχιστο" χρόνο.
			break; // Έτσι και βρω μια.. τελείωση η αποστολή αυτής της loop. :)
		}


	// Για όλες τις ελάχιστες τιμές του πίνακα.. ( που είναι τόσες όσες και οι εναπομείναντες αδρομολόγιτες διεργασίες ).
	for ( int task = task_Po ; task < tasks_number; task++  ) // Από εκεί που αρχικοποίησα και κάτω.. :)...
	{
		if ( ( texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[task].first != -1 ) && (min_value > texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[task].first) ) // Πρώτα να μην είναι -1
			{
			min_value = texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[task].first; // Minimum-Time.
			min_posCPU = texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[task].second; // Minimum-CPU.
			min_posTASK = task; // Minimum-Task.
			}

	}

//	cout << "Ο ελάχιστος χρόνος από τους ελάχιστους είναι ο: " << min_value << " της " << min_posTASK+1;
//	cout <<" διεργασίας στον " << min_posCPU+1 << " επεξεργαστή." << endl;
//
	Total_processors_Time[min_posCPU] = min_value; /* Βάζω πλέον αυτή την ελάχιστη τιμή στον επεξεργαστή "min_posCPU",
	στον πίνακα που κρατάω τους συνολικούς χρόνους που θα έχουν οι επεξεργαστές με τις δρομολογημένες διεργασίες. */


	// "Καθαρίζω" τον πίνακα που κρατάει τις τρέχουσες ελάχιστες τιμές..
	for ( int i = 0; i<tasks_number; i++)
		texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[i].first = -1;

	/* Έτσι πλέον και εδώ που σιγά σιγά θα έχει όλο και λιγότερες τιμές ( λόγο των δρομολογημένων διεργασιών που πλέον "δε θα παίζουν").
	   Για τις θέσεις/διεργασίες που θα μένουν άδειες, θα τις σημαδεύω με -1 ώστε να μην τις λαμβάνω έπειτα υπόψιν. :) */

}





void	Problem::removing_the_current_minimum_task_by_all_processors()
{

	for ( int cpu = 0; cpu < processors_number; cpu++ ) // Αφαιρώ την δρομολογημένη πλέον εργασία, από όλους του επεξεργαστές.
		Tasks_and_processors[min_posTASK][cpu] = -1 ;


	posa_tasks_eminan--; // Αφαιρώ ένα task ( για να ξέρω πόσα μου μένουν - για να τελειώσω ).

}





bool	Problem::Number_of_Tasks()
{
	return posa_tasks_eminan > 0;
}





void	Problem::Final_Min_Min_Time()
{
	cout << endl;
	cout << "|===================================================================================|" << endl;
	cout << "|\tΟ επεξεργαστής " << min_posCPU+1 << " έχει τον ελάχιστο χρόνο, ο οποίος είναι : ";
	printf ("%lf  \n", Total_processors_Time[min_posCPU] );
	cout << "|===================================================================================|" << endl;

}




// 	For Max-Min.

void Problem::Find_max_by_min()
{
	int task_Po = 0;
	for ( int task_Po = 0 ; task_Po < tasks_number; task_Po++  ) // Επειδή μπορεί και η πρώτη θέση του πίνακα να μην έχει τιμή ( -1 ). Μέχρι να βρει..
		if ( texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[task_Po].first != -1 )
		{
			min_value = texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[task_Po].first; // "Ελάχιστος" χρόνος.
			min_posCPU = texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[task_Po].second; // Σε ποιον ΕΠΕΞΕΡΓΑΣΤΉ είναι ο "ελάχιστος" χρόνος.
			min_posTASK = task_Po; // Ποια διεργασία "Ελάχιστος" χρόνος.
			break; // Έτσι και βρω μια.. τελείωση η αποστολή αυτής της loop. :)
		}


	// για όλες τις ελάχιστες τιμές.. ( που είναι τόσες όσες και οι εναπομείναντες αδρομολόγιτες διεργασίες ).
	for ( int task = task_Po ; task < tasks_number; task++  ) // Από εκεί που αρχικοποίησα και κάτω.. :)...
	{
		if ( ( texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[task].first != -1 ) && (min_value < texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[task].first) ) // Πρώτα να μην είναι -1
			{				// Η μόνη διαφορά με τον Min-Min σε αυτό το κομμάτι κώδικα είναι αυτή  ^ εδώ. Πλέον εδώ βρίσκει την μεγαλύτερη!
			min_value = texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[task].first;
			min_posCPU = texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[task].second;
			min_posTASK = task;
			}

	}

//	cout << "Ο ελάχιστος χρόνος από τους ελάχιστους είναι ο: " << min_value << " της " << min_posTASK+1;
//	cout <<" διεργασίας στον " << min_posCPU+1 << " επεξεργαστή." << endl;
//
	Total_processors_Time[min_posCPU] = min_value; /* Βάζω πλέον αυτή την ελάχιστη τιμή στον επεξεργαστή "min_posCPU",
	στον πίνακα που κρατάω τους συνολικούς χρόνους που θα έχουν οι επεξεργαστές με τις δρομολογημένες διεργασίες. */


	// "Καθαρίζω" τον πίνακα που κρατάει τις τρέχουσες ελάχιστες τιμές..
	for ( int i = 0; i<tasks_number; i++)
		texon_minmum_xroni_apo_ta_MI_dromologoumena_Task[i].first = -1;

	/* Έτσι πλέον και εδώ που σιγά σιγά θα έχει όλο και λιγότερες τιμές ( λόγο των δρομολογημένων διεργασιών που πλέον "δε θα παίζουν").
	   Για τις θέσεις/διεργασίες που θα μένουν άδειες, θα τις σημαδεύω με -1 ώστε να μην τις λαμβάνω έπειτα υπόψιν. :) */

}





void	Problem::Final_Max_Min_Time() // Εδώ τώρα θέλω, από όλους τους επεξεργαστές που έχουν δρομολογηθεί πλέον όλες οι διεργασίες
{ // σύμφωνα με τον Max-Min αλγόριθμο, από αυτούς του επεξεργαστές, τον επεξεργαστή που έχει τον *μεγαλύτερο" χρόνο.

	double max = Total_processors_Time[0];
	int max_cpu_pos = 0;

	for ( int cpu = 1; cpu < processors_number; cpu++ )
		if ( max < Total_processors_Time[cpu] )
		{
			max = Total_processors_Time[cpu];
			max_cpu_pos = cpu;
		}


	cout << endl;
	cout << "|===================================================================================|" << endl;
	cout << "|\tΟ επεξεργαστής " << max_cpu_pos+1 << " έχει τον μέγιστο χρόνο, ο οποίος είναι : ";
	printf ("%lf  \n", Total_processors_Time[max_cpu_pos] );
	cout << "|===================================================================================|" << endl;


}



























Problem::~Problem() {

	for (int i = 0; i < tasks_number; i++)
		delete[] Tasks_and_processors[i];

	delete[] Tasks_and_processors;


	delete[] Total_processors_Time;
	delete[] texon_minmum_xroni_apo_ta_MI_dromologoumena_Task;



}

