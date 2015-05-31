/*
 * Problem.h
 *
 *  Created on: G-lts Team Lab
 *      Author: Tas-sos
 */

#include <queue> // Δήλωση ουράς.
#include <vector>
#include <utility> // Για τα pairs.

using namespace std;


#ifndef PROBLEM_H_
#define PROBLEM_H_


class Problem {

private :


	int processors_number;

	int min_value;
	int min_pos;

	int max_value;
	int max_pos;



	vector < vector <int > > processors {}; /* Vector που αποτελείτε από vectors.
	Πίνακας με θέσεις οι οποίες θα αναπαριστούν έπειτα και θα είναι τόσες όσοι και οι επεξεργαστές του προβλήματος.
	Κάθε θέση/επεξεργαστής, περιέχει ένα vector. Εδώ θα κρατάω ποιες διεργασίες έχουν μπει σε ποιον επεξεργαστεί. */


	pair<int,int> * MinTasks; /* Δυναμικός πίνακας ο οποίος σε κάθε θέση του θα κρατάει 2 πράγματα
	την τιμή της εργασίας με το μικρότερο κόστος & την θέση της στον επεξεργαστή. */




	/* ==================================== Ιδιωτικοί μέθοδοι. ==================================== */


	void Find_MIN_Value_and_PoS_by_Processor(int);
	/* Μέθοδος η οποία :
	 * 		- Παίρνει έναν ακέραιο αριθμό ( int ) ο οποίος έχει σκοπό να δείχνει σε ποιον επεξεργαστή αναφέρετε.
	 * 		- Βρίσκει την ΜΙΚΡΌΤΕΡΗ τιμή ( την αποθηκεύει στην ιδιότητα min_value )
	 * 		  και την θέση της ( την αποθηκεύει στην ιδιότητα min_pos )
	 * 		  που υπάρχει σε κάποια συγκεκριμένη cpu ( int ).
	 */


	void Find_MAX_Value_and_PoS_by_Processor(int);
	/* Μέθοδος η οποία :
	 * 		- Παίρνει έναν ακέραιο αριθμό ( int ) ο οποίος έχει σκοπό να δείχνει σε ποιον επεξεργαστή αναφέρετε.
	 * 		- Βρίσκει την ΜΕΓΑΛΎΤΕΡΗ τιμή ( την αποθηκεύει στην ιδιότητα max_value )
	 * 		  και την θέση της ( την αποθηκεύει στην ιδιότητα max_pos )
	 * 		  που υπάρχει σε κάποια συγκεκριμένη cpu ( int ).
	 */




public:

	Problem();
	/* Μέθοδος η οποία :
	 * 			- Ζητάει από τον χρήστη τον αριθμό των επεξεργαστών. Με την ΣΎΜΒΑΣΗ των +1 παραπάνω επεξεργαστών.
	 * 			- Επαναορίζω το μέγεθος της βάσης, του βασικού vector που η κάθε θέση/επεξεργαστής θα είναι ένα vector
	 * 					& το κάνει = processors_number ( με τον αριθμό των επεξεργαστών δηλαδή ) .
	 */


	void getDataFromFile();
	/* Μέθοδος η οποία :
	 * 		- Ανοίγει το αρχείο με τα δεδομένα του προβλήματος ( τους χρόνους των εργασιών σε κάθε επεξεργαστή) και τα φορτώνει στις κατάλληλες δομές.
	 *
	 * 	Αναλυτικότερα : Στον πίνακα processors που έχει τόσες θέσεις όσοι και οι επεξεργαστές, και που η κάθε θέση/επεξεργαστής είναι ένα vector.
	 *  Όπως διαβάζει τους χρόνους τους βάζει τον έναν μετά τον άλλο στους κατάλληλους επεξεργαστές. Αυτό γίνεται επαναληπτικά μέχρι να τελειώσουν
	 *  οι διεργασίες.
	 */


	void PrintDatabyProcessors();
	/* Μέθοδος η οποία :
	 * 		- Εμφανίζει για κάθε επεξεργαστή :
	 * 									- Τις εργασίες που έχει.
	 * 									- & τον χρόνο που χρειάζεται η κάθε εργασία.
	 */


	void Find_and_SAVE_the_lowest_values_of_all_the_processors();
	/* Μέθοδος η οποία :
	 * 		- Βρίσκει για όλους του επεξεργαστές την χαμηλότερη σε χρόνο διεργασία που έχουν και ποια διεργασία είναι ( την θέση της ).
	 * 		  Αποθηκεύουν αυτές τις δύο τιμές στις θέσεις ( pairs ) του πίνακα "MinTasks".
	 */


	void Print_MinTasks();
	/* Μέθοδος η οποία :
	 * 		- Εμφανίζει τα περιεχόμενα του δυναμικού πίνακα MinTaskS.
	 * 	Συγκεκριμένα θα πρέπει να εμφανίζει την ΤΙΜΉ και την ΘΈΣΗ των εργασιών με την μικρότερη τιμή από κάθε επεξεργαστή.
	 */


	int Finding_Pos_of_MINimum_Task_by_MinTasks();
	/* Μέθοδος η οποία :
	 * 		- Βρίσκει και επιστρέφει την θέση/!*-ΕΠΕΞΕΡΓΑΣΤΉ-*! στον πίνακα MinTaskS που η εργασία του, έχει τον μικρότερο ΧΡΌΝΟ.
	 */


	void removing_the_current_minimum_task_by_all_processors();
	/* Μέθοδος η οποία :
	 * 		- Αφαιρεί την τρέχουσα ελάχιστη σε χρόνο διεργασία που έχει βρεθεί σε σύγκριση με όλους τους επεξεργαστές.
	 * 		Αφαιρεί λοιπόν την εργασία αυτή, από ΌΛΟΥΣ τους επεξεργαστές.
	 * 		Τον χρόνο όμως που απαιτούσε, στον επεξεργαστή της, τον ΠΡΟΣΘΈΤΕΙ σε ΌΛΕΣ τις εναπομείναντες εργασίες του επεξεργαστή της .
	 */


	int Number_of_Tasks();
	/* Μέθοδος η οποία :
	 * 		- Βρίσκει και επιστρέφει τον αριθμό των εργασιών που έχουν όλοι οι επεξεργαστές.
	 */


	void Final_Time();
	/* Μέθοδος η οποία :
	 * 		- Θα καλείτε κατά κύριο λόγο στο τέλος.
	 * 		- Εμφανίζει σε ποιον επεξεργαστή υπάρχει καθώς και τον χρόνο, η εργασία με τον μικρότερο χρόνο από όλους τους επεξεργαστές.
	 */

















	virtual ~Problem();
};

#endif /* PROBLEM_H_ */
