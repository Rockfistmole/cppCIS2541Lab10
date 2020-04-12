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
#include <vector>
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
void populateArray(vector <MovieData>, fstream&);
MovieData getMovie(int);
void showMovie(MovieData);
void bubbleSort(vector<MovieData>);


int main() {
	fstream inputFile;
	string fileName;
	vector <MovieData> movieVect(30);
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
	if (movieInput){
		for (unsigned int i = 0; i < movieInput; i++) {
			movieVect[i] = getMovie(movieInput);
		}
	}
	populateArray(movieVect, inputFile);
	
	bubbleSort(movieVect);


	cout << "Earnings" << setw(20) << "Genre" << setw(45) << "Title" << setw(20) << "Year" << endl;
	cout << "========" << setw(30) << "===============" << setw(40) << "==========" << setw(17) << "=======" << endl;
	for (unsigned int i = 0; i < movieVect.size(); i++) {
		showMovie(movieVect.at(i));
	}
	return EXIT_SUCCESS;
}

void populateArray(vector<MovieData> vect, fstream& inFile) {
	string title = "";
	string earnings = "";
	string year = "";
	int genre = 0;
	for (int index = 0; index < vect.size() ;index++) {
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
		vect.emplace_back(movie);
	}
}

MovieData getMovie(int movieInput) {
	MovieData movie;
	int genre;
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
	
	return movie;
}

void showMovie(MovieData m) {
	const char movieGenre[][25] = { "", "Historical Musical", "Historical Romance", "Religious Drama", "Science Fiction", "Space Opera", "Superhero Comics" };
	cout << setprecision(3) << m.grossEarnings << setw(33) << movieGenre[m.subject] << setw(40) << m.title << setw(15) << m.releaseYear << endl;
	
}


void bubbleSort(vector<MovieData> vect) {
	int maxElement, index;
	for (maxElement = vect.size() - 1; maxElement > 0; maxElement--) {
		for (index = 0; index < maxElement; index++) {
			if (vect[index].grossEarnings < vect[index + 1].grossEarnings) { // see if current is greater then next
				MovieData temp = vect[index];			// swap values in memory
				vect[index] = vect[index + 1];	// swap values in memory
				vect[index + 1] = temp;			// swap values in memory
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

