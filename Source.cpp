#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <conio.h>
#include <iomanip>
#include <Windows.h>

using namespace std;

void printMenu();
int getRandNumberBetween(int min, int max);
void loadingAnimation();
void printStartingScreen();


int main()
{
	fstream scores;
	const int SIZE_60 = 60,
		PLAY = 1,
		DISLAY = 2,
		RESET = 3,
		SAVE = 4,
		QUIT = 5;
	string name, names[SIZE_60];
	int id[SIZE_60], balances[SIZE_60], winnings[SIZE_60],
		fund,
		winning,
		count,
		numberOfPlayers,
		dice1, dice2,
		choice,
		sum,
		sum2;
	bool isExistingPlayer, isR, continueGame;
	char roll, choice1, isEnough;

	srand(time(0));

	printStartingScreen();

	scores.open("scores.txt", ios::in);

	if (scores.fail())
	{
		cout << "Error opening the file.\nExiting...";
		system("pause > NUL");
		exit(1);
	}
	cout << "\n\n\t\t         Please, enter your Name: ";
	getline(cin, name);

	count = 0;
	isExistingPlayer = false;
	while (scores >> id[count] >> names[count] >> balances[count] >> winnings[count])
	{
		if (name == names[count])
		{
			isExistingPlayer = true;
			fund = balances[count];
			winning = winnings[count];
		}
		numberOfPlayers = count + 1;
		count++;
	}

	//scores.close();

	if (isExistingPlayer)
	{
		system("cls");
		cout
			<< "\n\n\n\t   Welcome back, " << name
			<< ", here is your last score: " << fund + winning;
		system("pause > NUL");
	}
	else
	{
		fund = 1000;
		winning = 0;
	}

	do {
		isEnough = false;

		system("cls");

		printMenu();

		cout << "\t\tMake a choice (1-5): ";
		cin >> choice;

		while (choice < PLAY || choice > QUIT)
		{
			cout << "\nInvalid choice! Please, try again: ";
			cin >> choice;
		}

		switch (choice)
		{
		case PLAY:

			continueGame = true;
			while (continueGame)
			{
				system("cls");

				cout << "\n\nPress R/r to Roll the Dice: ";
				roll = _getch();

				isR = false;
				if (roll == 'R' || roll == 'r')
					isR = true;

				while (!isR)
				{
					cout << "\nInvalid Option! Please, press R/r to roll the dice ... ";
					roll = _getch();
					if (roll == 'R' || roll == 'r')
						isR = true;
				}

				dice1 = rand() % 6 + 1;
				dice2 = rand() % 6 + 1;
				sum = dice1 + dice2;

				cout << "\nYour number is: " << sum;


				if (sum == 7 || sum == 11)
				{
					winning += 100;
					cout
						<< "\nCongratulations! You Won 100$!\n"
						<< "\nNow your balance is " << fund + winning;
					system("pause > NUL");
				}
				else if (sum == 2 || sum == 3 || sum == 12)
				{
					fund -= 100;
					cout
						<< "\nYou lost 100$"
						<< "\nNow you balance is " << fund + winning;
				}
				else
				{
					cout << "\nRoll " << sum << " again to win";

					do {
						cout << "\n\nPress R/r to Roll the Dice: ";
						roll = _getch();

						isR = false;
						if (roll == 'R' || roll == 'r')
							isR = true;

						while (!isR)
						{
							cout << "\nInvalid Option! Please, press R/r to roll the dice ... ";
							roll = _getch();
							if (roll == 'R' || roll == 'r')
								isR = true;
						}

						dice1 = rand() % 6 + 1;
						dice2 = rand() % 6 + 1;
						sum2 = dice1 + dice2;

						cout << "\nYour number is: " << sum2;
						
						
					} while (sum2 != 7 && sum2 != sum);

					if (sum2 == sum)
					{
						winning += 100;
						cout
							<< "\nCongratulations! You Won 100$!\n"
							<< "Now your balance is " << fund + winning << endl;
					}
					else if (sum2 == 7)
					{
						fund -= 100;
						cout
							<< "\nYou lost 100$"
							<< "Now you balance is " << fund + winning;
					}
				}
				


				cout << "\nDo you want to continue the game? (Y/N) ";
				cin.clear();
				choice1 = _getch();

				while (!cin.fail() && choice1 != 'y' && choice1 != 'Y' && choice1 != 'N' && choice1 != 'n')
				{
					cout << "\nInvalid choice! Try Again: ";
					cin.clear();
					choice1 = _getch();
				}

				if (choice1 == 'N' || choice1 == 'n')
					continueGame = false;
			}

			break;

		case DISLAY:
			system("cls");
			cout << "\n\t  Your Available Funds is " << fund + winning << "$.";
			system("pause > NUL");
			break;

		case RESET:

			system("pause > NUL");
			cout << "\nAre you sure? (Y/N) ";
			cin.clear();
			choice1 = _getch();

			while (!cin.fail() && choice1 != 'y' && choice1 != 'Y' && choice1 != 'N' && choice1 != 'n')
			{
				cout << "\nInvalid choice! Try Again: ";
				cin.clear();
				choice1 = _getch();
			}
			if (winning <= 0)
			{
				cout << "\nYou don't have winnings to reset it!";
				system("pause > NUL");
			}
			else if (winning > 0)
			{
				winning = 0;
				cout << "\nSuccess! Now your balance is " << fund + winning;
				system("pause > NUL");
			}
			break;
		case SAVE:

			if (isExistingPlayer)
			{

				fstream scores;
				scores.open("scores.txt", ios::app | ios::out);

				if (!scores)
				{
					cout << "Error opening the file.\nExiting...";
					system("pause > NUL");
					exit(1);
				}


				count = 0;
				
		

				while (scores >> id[count] >> names[count] >> balances[count] >> winnings[count])
				{
					if (name == names[count])
					{
						scores << id[count] << names[count] << fund << winning;

					}
					count++;

				}
				

				system("pause > NUL");
				scores.close();
				
			}
			else
			{
				fstream scores;
				scores.open("scores.txt", ios::app);

				if (scores.fail())
				{
					cout << "Error opening the file.\nExiting...";
					system("pause > NUL");
					exit(1);
				}
				else {

					scores << numberOfPlayers + 1 << " " << name << " " << fund << " " << winning;
					scores.close();
					cout << "\nSuccess!";
					Sleep(200);
					system("pause < NUL");

				}
			}
			break;
		case QUIT:


			cout << "\nAre you sure? (Y/N) ";
			cin.clear();
			choice1 = _getch();

			while (!cin.fail() && choice1 != 'y' && choice1 != 'Y' && choice1 != 'N' && choice1 != 'n')
			{
				cout << "\nInvalid choice! Try Again: ";
				cin.clear();
				choice1 = _getch();
			}

			if (choice1 == 'y' || choice1 == 'Y')
				isEnough = true;
			break;

		}
	} while (!isEnough);
	return 0;
}


void printMenu()
{
	cout
		<< "\n==============================   C R A P S  ==================================\n\n\n"
		<< "\t\t\t   1. Play the Game \n"
		<< "\t\t\t   2. Display Available Funds \n"
		<< "\t\t\t   3. Reset Winnings to Zero \n"
		<< "\t\t\t   4. Save Name and Score \n"
		<< "\t\t\t   5. Quit \n\n";
}

int getRandNumberBetween(int min, int max)
{
	
	int num = (rand() % (max - min + 1)) + min;
	return num;
}

/*void loadingAnimation()
{
	for (int i = 0; i < 5; i++)
	{
		Sleep(400);
		std::cout << ". " << flush;

	}
}
*/
void printStartingScreen()
{
	cout
		<< "\t\t                   *                  \n"
		<< "\t\t                 *****                \n"
		<< "\t\t               *********              \n"
		<< "\t\t             *****   *****            \n"
		<< "\t\t          *******************         \n"
		<< "\t\t       ************************       \n"
		<< "\t\t     ******   ****   ***   *******    \n"
		<< "\t\t       ************************       \n"
		<< "\t\t          *******************         \n"
		<< "\t\t             *****   ******           \n"
		<< "\t\t               *********              \n"
		<< "\t\t                 *****                \n"
		<< "\t\t                   *                  \n";

	cout << "\n\n\t\t\t   WELCOME TO CRAPS!\n";
}
/*
int getDiceValueBetween(int num1, int num2)
{

system("cls");

cout << "Your First Dice Value is ";    // should make a function performing it
for (int i = 0; i < 5; i++)
{
Sleep(400);
std::cout << ". " << flush;
}
dice1 = getRandNumberBetween(num1, num2);
cout << dice1 << endl;

cout << "Your Second Dice Value is ";
for (int i = 0; i < 5; i++)
{
Sleep(400);
std::cout << ". " << flush;
}
dice2 = getRandNumberBetween(num1, num2);
cout << dice2 << endl;

sum = dice1 + dice2;

}
*/


/*

1) I should read the user name
2) Check if I have it in the file
3) If I have

*/