/*
Author: 
Date: April 13th. 2020
Prog: Lab10.cpp
Descr:
This program will demonstrate the use of structured data 
and enumerated data types
*/


#include <iostream>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

enum Genre { HISTORYMUSIC = 1, HISTORYROMANCE, RELIGIOUSDRAMA, SCIFI, SPACEOPERA, SUPERHEROCOMICS }genre;

struct MovieData {
	string title = "";
	double grossEarnings = 0;
	int releaseYear = 0;
	Genre subject = HISTORYMUSIC;
};


// function prototypes
bool openFileIn(fstream&, string);
void populateArray(MovieData  list[], fstream&, int);
MovieData getMovie(int);
void showMovie(MovieData);
void bubbleSort(MovieData[], int);

int main() {
	fstream inputFile;
	string fileName;
	const int SIZE = 30;
	MovieData movieArr[SIZE];
	int movieInput = 0;
	cout << "Enter the file name of Movie Data File for input: ";
	cin >> fileName;
	if (!openFileIn(inputFile, fileName)) {
		cerr << "ERROR! Cannot open file for output" << endl;
		exit(-2);
	}
	cout << "How many movies would you like to add? (0 = none): ";
	cin >> movieInput;
	cin.ignore();
	populateArray(movieArr, inputFile, SIZE);
	if (movieInput >= 1) 
		for (int i = 0; i < movieInput; i++) {
			movieArr[i++] = getMovie(movieInput);
		}
	bubbleSort(movieArr, SIZE);
	

	cout << "Earnings" << setw(20) << "Genre" << setw(45) << "Title" << setw(20) << "Year" << endl;
	cout << "========" << setw(30) << "===============" << setw(40) << "==========" << setw(17) << "=======" << endl;
	for (int i = 0; i < SIZE; i++) {
		showMovie(movieArr[i]);
		
	}
	return EXIT_SUCCESS;
}

void populateArray(MovieData list[], fstream& inFile, int size) {
	string title = "";
	string earnings = "";
	string year = "";
	int genre = 0;
	for (int index = 0; index < size; index++) {
		if (inFile.peek() == '\n') {
			inFile.ignore();
		}
		getline(inFile, title, '#');
		
		getline(inFile, earnings, '#');
		getline(inFile, year, '#');
		inFile >> genre;
		
		MovieData movie;
		movie.title = title;
		movie.grossEarnings = stod(earnings);
		movie.releaseYear = stoi(year);
		movie.subject = static_cast<Genre>(genre);
		list[index] = movie;
	}
	
}

MovieData getMovie(int movieInput) {
	MovieData movie;
	int genre;
	for (int i = 0; i < movieInput; i++) {
		cout << "What is the title of the movie? ";
		getline(cin, movie.title);
		cout << "What is the worldwide gross earning (in billions)? ";
		cin >> movie.grossEarnings;
		cout << "What is the release year? ";
		cin >> movie.releaseYear;
		cout << "Movie genres:\n"
			<< " 1 - Historical Musical\n 2 - Historical Romance\n 3 - Religious Drama\n 4 - Science Fiction\n 5 - Space Opera\n 6 - Superhero Comics" << endl;
		cout << "What is the number of the movie genre? ";
		cin >> genre;
		movie.subject = static_cast<Genre>(genre);
		cin.ignore();
	}
	return movie;
}

void showMovie(MovieData m) {
	const char movieGenre[][25] = { "", "Historical Musical", "Historical Romance", "Religious Drama", "Science Fiction", "Space Opera", "Superhero Comics" };
	cout << setprecision(3) << m.grossEarnings << setw(33) << movieGenre[m.subject] << setw(40) << m.title << setw(15) << m.releaseYear << endl;
	
}


void bubbleSort(MovieData list[], int size) {
	int maxElement, index;
	for (maxElement = size - 1; maxElement > 0; maxElement--) {
		for (index = 0; index < maxElement; index++) {
			if (list[index].grossEarnings < list[index + 1].grossEarnings) { // see if current is greater then next
				MovieData temp = list[index];			// swap values in memory
				list[index] = list[index + 1];	// swap values in memory
				list[index + 1] = temp;			// swap values in memory
			}
		}
	}
}



// ********************************************************
// **
// **   Function Name:  openFileIn
// **   Parameters:     file stream input, a string of the file name
// **   Returns:		returns if the file opened successfully
// **                   
// ********************************************************

bool openFileIn(fstream& file, string name) {
	bool status;
	file.open(name, ios::in); // appened to existing contents
	if (file.fail())
		status = false; // PROBLEMS
	else
		status = true; // everything OK
	return status;
}

