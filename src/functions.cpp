/*
 * functions.cpp
 *
 */

#include "functions.hpp"
using namespace std;

//function implementation
bool writeFile(string filename, ofstream& outputFile) {
	//open file
	outputFile.open(filename);

	//open file validation
	if (!outputFile) {
		cerr << "Error! Could not open the file!";
		return false;
	}
	else {
		cout << "Open file successful...\n";
		return true;
	}
}

bool readFile(string filename, ifstream& inputFile) {
	//open file
	inputFile.open(filename);

	//open file validation
	if (!inputFile) {
		cerr << "Error! Reading data file failed!";
		return false;
	}

	string line;
	while (getline(inputFile, line)) {
		cout << line << endl;
	}
	cout << endl;
	return true;
}

double calculateF(int a, double b, double c) {
	return 655 + (9.6 * (b / 2.2)) + (1.8 * (c * 2.54)) - (4.7 * a);
}

double calculateM(int a, double b, double c) {
	return 66 + (13.7 * (b / 2.2)) + (5 * (c * 2.54)) - (6.8 * a);
}

void display() {
	cout << "Sedentary(little to no exercise/office job) = 1.2\n";
	cout << "Lightly Active(light exercise 1-3 days/week) = 1.375\n";
	cout << "Moderately Active(moderate exercise 3-5 days/week) = 1.55\n";
	cout << "Very Active(heavy exercise 6-7 days/week) = 1.725\n";
	cout << "Extremely Active(very heavy exercise, hard labor job, training 2x/day) = 1.9\n";
	cout << endl;
}

void displayMeals(const vector<Meal>& meals, const string& title) {
	cout << title << endl;
	for (int i = 0; i < meals.size(); i++) {
		cout << i + 1 << ". "
			 << left << setw(45) << meals[i].name
			 << "Calories: " << meals[i].calories << endl;
	}
	cout << endl;
}

void displaySum(int a, int b, int c, int& sum) {
	sum = a + b + c;
}

bool isInRange(int total, int target) {
	return total <= target;
}



