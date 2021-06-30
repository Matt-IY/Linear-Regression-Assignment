/********************************************************************************
Filename: ass2.c
Version : 1.0
Author : Matt Idone-York
StudentNo : 040912497
Course Name / Number : Numerical Computing CST8233
Lab Sect : 302
Assignment # : 1
Assignment name : Linear regression least-squares method 
Due Date : March 15 2020
Submission Date : March 15 2020
Professor : Hala Own
Purpose : A regression model for predicting the long-term recovery after disharge from
the hospital for severely injured patients using a linear regression least-squares
method.
***********************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;
// data for the input file
class file {
public:
	ifstream fp;
	char filename[25] = "";
	double a = 0, a1 = 0;
	int lines = 0;

	void print();
	void extrapolation();
};

void data();

/***********************************************************
Function name:	main
Purpose:		main function
				Calculates the linear regression
In parameters:	none
Out parameters:	0 for succesful execution
Version:		1.0
Author:			Matt Idone-York
************************************************************/

int main() {
	char option = ' ';
	cout << "LEAST_SQUARES LINEAR REGRESSION" << endl << endl;
	do {
		cout << "MENU\n1. Exponential Fit\n2. Quit" << endl;
		cin >> option;
		// switch for menu
		switch (option) {
		case '1':
			data();
			break;
		case '2':
			cout << "Program Ended";
			break;
		default:
			cout << "Pick Valid Option" << endl;
			break;
		}
	} while (option != '2');
	return 0;
}

/***********************************************************
Function name:	data
Purpose:		reads the file and prints it out. Prints out second menu
In parameters:	none
Out parameters:	none
Version:		1.0
Author:			Matt Idone-York
************************************************************/

void data() {
	char option = ' ';
	file f;
	cout << "Please enter the name of the file to open: ";
	cin >> f.filename;
	f.fp.open(f.filename);
	// checks if it's a valid file
	if (!f.fp.good()) {
		cout << "Error, file not found" << endl;
		return;
	}
	f.print();
	// do while for extrapolation menu
	do {
		cout << endl << "MENU\n1. Extrapolation\n2. Main Menu" << endl;
		cin >> option;
		switch (option) {
		case '1':
			f.extrapolation();
			break;
		case '2':
			cout << "Returning to Main Menu" << endl;
			break;
		default:
			cout << "Invalid Option" << endl;
			break;
		}
	} while (option != '2');
}

/***********************************************************
Function name:	print
Purpose:		prints out the data in the text file, converts it to readable data
In parameters:	none
Out parameters:	none
Version:		1.0
Author:			Matt Idone-York
************************************************************/

void file::print() {
	string strDay, strProIndex, name;
	double proIndex, sumDay = 0, sumProIndex = 0, sumDayProIndex = 0, sumDaySquared = 0, a0;
	int day;
	this->fp >> strDay >> strProIndex;
	cout << strDay << "\t" << strProIndex << endl;
	while (this->fp >> day >> proIndex) {
		cout << fixed << day;
		cout << "\t" << fixed << setprecision(0) << proIndex << endl;

		// calculating the sums of each
		sumDay += day;
		sumProIndex += log(proIndex);
		sumDayProIndex += (day * log(proIndex));
		sumDaySquared += pow(day, 2);

		this->lines++;
	}
	// calculating a1 and a0
	this->a1 = (this->lines * sumDayProIndex - sumDay *sumProIndex) / (this->lines * sumDaySquared - pow(sumDay, 2));
	a0 = (sumProIndex - a1 * sumDay) / this->lines;
	this->a = exp(a0);

	cout << "\nThere are " << this->lines << " records." << endl << endl;
	cout << "Linear Regression Fit: Prognostic_index = " << fixed << setprecision(1) << this->a << "*exp " << fixed << setprecision(3) << this->a1 << "*days)" << endl << endl;
}

/***********************************************************
Function name:	extrapolation
Purpose:		extrapolates the data using a series of formulas
In parameters:	none
Out parameters:	none
Version:		1.0
Author:			Matt Idone-York
************************************************************/

void file::extrapolation() {
	int day;
	double proIndex, indexPrev;
	double rate;

	cout << "\nPlease enter the days to extrapolate to: ";
	if(cin >> day){}
	else if (cin.fail()) {
		cin.clear();
		cout << "Invalid Input";
		return;
	}

	cout << "days = " << day << endl;
	proIndex = this->a * exp(this->a1 * (double)day);
	cout << "Prognostic_index = " << fixed << setprecision(2) << proIndex << endl;
	rate = (this->a * this->a1) * exp(this->a1 * (double)day);
	cout << "rate of decrease = " << fixed << setprecision(3) << rate << endl << endl;
}