/* functions.hpp */

#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Meal {
	string name;
	int calories;
};

//function prototypes
bool writeFile(string filename, ofstream& outputFile);
bool readFile(string filename, ifstream& inputFile);

double calculateF(int a, double b, double c);
double calculateM(int a, double b, double c);

void display();
void displayMeals(const vector<Meal>&, const string&);
void displaySum(int a, int b, int c, int& sum);
bool isInRange(int, int);

#endif /* FUNCTIONS_HPP_ */
