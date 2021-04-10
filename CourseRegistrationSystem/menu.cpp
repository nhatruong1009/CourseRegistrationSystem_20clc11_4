#include <iostream>

using namespace std;

void userTypeMenu();
void studentMenu();
void staffMenu();


void userTypeMenu()
{

	int so;
	cout << "-------------USER TYPE---------------" << endl;
	cout << "  1. Student" << endl;
	cout << "  2. Academic Staff" << endl;
	do
	{
		cout << "Your choice: ";
		cin >> so;
		switch (so)
		{
		case 1:
			studentMenu();
			return;
		case 2:
			staffMenu();
			return;

		}

	} while (1);
}
void studentMenu()
{
	int so;
	cout << "-------------STUDENT---------------" << endl;
	cout << "  1. Log In" << endl;
	cout << "  2. Register" << endl;
	cout << "  3. Back" << endl;
	do
	{
		cout << "Your choice: ";
		cin >> so;
		switch (so)
		{
		case 1:
			cout << "   Ban da chon 1" << endl;
			return;
		case 2:
			cout << "   Ban da chon 2" << endl;
			return;
		case 3:
			userTypeMenu();
			return;
		}
	} while (1);
}
void staffMenu()
{
	int so;
	cout << "-------------STAFF---------------" << endl;
	cout << "  1. Create a csvt" << endl;
	cout << "  2. Export scoreboard" << endl;
	cout << "  3. Back" << endl;
	do
	{
		cout << "Your choice: ";
		cin >> so;
		switch (so)
		{
		case 1:
			return;
		case 2:

			return;
		case 3:
			userTypeMenu();
		}
	} while (1);
}