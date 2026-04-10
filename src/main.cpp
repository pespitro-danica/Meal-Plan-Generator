#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include "functions.hpp"
using namespace std;

//global variable
string filename;
ofstream outputFile;
ifstream inputFile;
int choice, age, BMR, goal, myGoal;
char resp, sex;
double weight, height, activity;

//main
int main() {
	//prompt menu for user to make a choice from 1-5
	//this menu will keep looking until the program exits
	do {
		//display menu
		cout << "Main Menu:\n";
		cout << "\t1. List Food and Calories\n";
		cout << "\t2. Calculate TDEE\n";
		cout << "\t3. Write a file: Meal Plan\n";
		cout << "\t4. Read a file: Display Final Meal Plan\n";
		cout << "\t5. Exit the program\n";
		cout << "**NOTE: See Food and Calories List first to see possible choices**\n";

		//prompt user for choice
		while (true) {
			cout << "Please enter your choice (1-5): ";
			cin >> choice;

			if (cin.fail() || choice < 1 || choice > 5) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid input! Please enter a number between 1 and 5." << endl;
			}
			else {
				cin.ignore(1000, '\n');
				break;
			}
		}
		//Struct of Breakfast, Lunch, and Dinner foods and its calories
		vector<Meal> breakfast = {
				{"Bacon, Eggs, and Butter toast", 411},
				{"Pancake with Maple Syrup", 320},
				{"Everything bagel with cream cheese", 390},
				{"Acai bowl", 399},
				{"Oatmeal and Fruit cup", 220}
		};

		vector<Meal> lunch = {
				{"Chicken Caesar Salad", 230},
				{"BLT Sandwich", 258},
				{"Mac and Cheese", 360},
				{"Steak Burrito Bowl", 615},
				{"Avocado Veggie Wrap", 426}
		};

		vector<Meal> dinner = {
				{"Spaghetti and Meatballs", 320},
				{"Steak with Mashed Potatoes and Broccoli", 330},
				{"Veggie Pizza", 220},
				{"Shrimp Stir-fry with rice", 405},
				{"Cheese burger with Fries", 490}
		};

		//choice 1: List Food and Calories
		if (choice == 1) {
			//display Breakfast, Lunch, and Dinner meals
			displayMeals(breakfast, "Breakfast List");
			displayMeals(lunch, "Lunch List");
			displayMeals(dinner, "Dinner List");
			//exits case 1 to the main menu
		}
		//choice 2: Calculate TDEE
		else if (choice == 2) {
			cout << "Let's calculate your TDEE!\n";
			cout << "What is your sex?(m or f): ";
			cin >> sex;
			if (sex == 'f') {
				cout << "What is your age? ";
				cin >> age;
				cout << "How much do you weigh in lbs? ";
				cin >> weight;
				cout << "What is your height in inches? ";
				cin >> height;
				cout << endl;
				display();
				cout << "Enter the corresponding number of your daily activity: ";
				cin >> activity;

				BMR = calculateF(age, weight, height);
				cout << "Your TDEE is: " << BMR * activity << endl;
				goal = BMR * activity;
				cout << endl;
			}
			else if (sex == 'm') {
				do {
					cout << "What is your age? ";
					cin >> age;
				} while (age <= 0);
				cout << "How much do you weigh in lbs? ";
				cin >> weight;

				cout << "What is your height in inches? ";
				cin >> height;
				cout << endl;

				display();
				cout << "Enter the corresponding number of your daily activity: ";
				cin >> activity;

				BMR = calculateM(age, weight, height);
				cout << "Your TDEE is: " << BMR * activity << endl;
				goal = BMR * activity;
			}
			//exits case 1 to the main menu
		}

		//choice 3: Write a file: Meal Plan
		else if (choice == 3) {
			//call writeFile function
			cout << "Create a .txt filename: ";
			getline(cin, filename);
			if (!writeFile(filename, outputFile)) {
				continue;
			}

			cout << "\ta. Create meal plan\n";
			cout << "\tb. Randomize a meal plan\n";
			cout << "Please enter how you want to proceed with your meal plan(a or b): ";
			cin >> resp;
			cin.ignore();
			cout << endl;

			string answer;
			if (resp == 'a') {
				while (true) {
					cout << "Would you like to set your own calorie intake goal or your calculated TDEE?(my own or TDEE): ";
					getline(cin, answer);

					if (answer == "my own") {
						cout << "Please enter your calorie intake goal: ";
						cin >> myGoal;
						cin.ignore();
						break;
						cout << endl;
					}
					else if (answer == "TDEE") {
						cout << "Great! Your TDEE is: " << goal << endl;
					}
					else {
						cout << "Invalid option! Please type 'my own' or 'TDEE' only." << endl;
					}
					cout << endl;
				}

				if (answer == "my own" || answer == "TDEE") {
					//display Breakfast, Lunch, and Dinner meals
					displayMeals(breakfast, "Breakfast List");
					displayMeals(lunch, "Lunch List");
					displayMeals(dinner, "Dinner List");

					bool validPlan = false;
					while (!validPlan) {
						int breakfastChoice, lunchChoice, dinnerChoice;

						cout << "Choose a breakfast item (1-5): ";
						cin >> breakfastChoice;
						cout << "Choose a lunch item (1-5): ";
						cin >> lunchChoice;
						cout << "Choose a dinner item (1-5): ";
						cin >> dinnerChoice;

						breakfastChoice--;
						lunchChoice--;
						dinnerChoice--;

						if (breakfastChoice < 0 || breakfastChoice >= breakfast.size() ||
							lunchChoice < 0 || lunchChoice >= lunch.size() ||
							dinnerChoice < 0 || dinnerChoice >= dinner.size()) {
							cout << "One or more meal choices are out of range!" << endl;
							continue;
						}

						int sum = 0;
						displaySum(breakfast[breakfastChoice].calories,
								   lunch[lunchChoice].calories,
								   dinner[dinnerChoice].calories,
								   sum);
						cout << "\nYour custom meal plan:\n";
						cout << breakfast[breakfastChoice].name << ' '
							 << breakfast[breakfastChoice].calories << endl;
						cout << lunch[lunchChoice].name << ' '
							 << lunch[lunchChoice].calories << endl;
						cout << dinner[dinnerChoice].name << ' '
							 << dinner[dinnerChoice].calories << endl;

						cout << "Your total calories for the day is: " << sum << endl;

						int target = (answer == "my own") ? myGoal : goal;
						bool withinRange = isInRange(sum, target);

						if (withinRange) {
							cout << "Your calories are within your goal! " << endl;

							if (target - sum >= 250) {
								cout << "You still have some room for a snack!" << endl;
							}
							//write to file
							outputFile << breakfast[breakfastChoice].name << ' '
									   << breakfast[breakfastChoice].calories << endl;
							outputFile << lunch[lunchChoice].name << ' '
									   << lunch[lunchChoice].calories << endl;
							outputFile << dinner[dinnerChoice].name << ' '
									   << dinner[dinnerChoice].calories << endl;
							outputFile << "Your total calories for the day is: " << sum << endl;

							validPlan = true;
						}
						else {
							cout << "You are out of range! Please choose different meals within your calorie goal!" << endl;
						}
					}
				}
			}

			else if (resp == 'b') {
				cout << "Would you like to set your own calorie intake goal or your calculated TDEE?(my own or TDEE): ";
				getline(cin, answer);
				if (answer == "my own") {
					cout << "Please enter your calorie intake goal: ";
					cin >> myGoal;
					cout << endl;
				}
				else if (answer == "TDEE") {
					cout << "Great! Your TDEE is: " << goal << endl;
				}
				//randomize Breakfast, Lunch, Dinner arrays
				srand(time(0));
				int randIndexBreakfast = rand() % breakfast.size();
				int randIndexLunch = rand() % lunch.size();
				int randIndexDinner = rand() % dinner.size();

				//print randomize meals
				cout << breakfast[randIndexBreakfast].name << ' '
					 << breakfast[randIndexBreakfast].calories << endl;
				cout << lunch[randIndexLunch].name << ' '
					 << lunch[randIndexLunch].calories << endl;
				cout << dinner[randIndexDinner].name << ' '
					 << dinner[randIndexDinner].calories << endl;

				int sum = 0;
				displaySum(breakfast[randIndexBreakfast].calories,
						   lunch[randIndexLunch].calories,
						   dinner[randIndexDinner].calories, sum);
				cout << "Your total calories for the day is: " << sum << endl;

				int target = (answer == "my own") ? myGoal : goal;

				if (isInRange(sum, target)) {
					cout << "Your calories are within your goal! " << endl;

					if (target - sum >= 250) {
						cout << "You also have room for a snack!" << endl;
					}

					//write data to file
					outputFile << breakfast[randIndexBreakfast].name << ' '
							   << breakfast[randIndexBreakfast].calories << endl;
					outputFile << lunch[randIndexLunch].name << ' '
							   << lunch[randIndexLunch].calories << endl;
					outputFile << dinner[randIndexDinner].name << ' '
							   << dinner[randIndexDinner].calories << endl;
				}
				else {
					cout << "You are out of range!";
				}
				outputFile << "Your total calories for the day is: " << sum << endl;
			}
		//close file
		outputFile.close();

	}
		//choice 4: Read a file: Display Final Meal Plan
		else if (choice == 4) {
			//call readFile function
			cout << "Enter a .txt filename: ";
			getline(cin, filename);

			 if (readFile(filename, inputFile)) {
				 //close the file
				 inputFile.close();
			 }
			//exits case 1 to the main menu
		}
		//choice 5: Exit the program
		else if (choice == 5){
			cout << "Data saved..." << endl;
			cout << "Exiting program!" << endl;
		}
	}while(!(choice == 5));

	return 0;
}

