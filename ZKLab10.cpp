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
void populateArray(MovieData * list[], fstream&, int);

int main() {
	fstream inputFile;
	string fileName;
	const int SIZE = 30;
	MovieData* movieArr[SIZE];
	cout << "Enter the file name of Movie Data File for input: ";
	cin >> fileName;
	if (!openFileIn(inputFile, fileName)) {
		cerr << "ERROR! Cannot open file for output" << endl;
		exit(-2);
	}
	
	populateArray(movieArr, inputFile, SIZE);
	
	return EXIT_SUCCESS;
}

void populateArray(MovieData* list[], fstream& inFile, int size) {
	for (auto &i : list[int size]) {
		
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


