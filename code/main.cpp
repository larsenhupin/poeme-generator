#include <conio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "cvm.h"

int eachSave = 0;
std::string data[20] = {""};
std::string line;
int y = 0;

#define KEY_DOWN 80


//Prototypes
void keyboardOutput();
void saveInFiles();
int numberOfLines();
void printFullPoem();
void FlushTampons();

int main()
{
	//TODO: fix utf-8 problems
	SetConsoleOutputCP(CP_UTF8);
	//setvbuf(stdout, nullptr, _IOFBF, 1000);
	std::ifstream database;
	database.open("database_random.txt");
	

	if (database.is_open())
	{
		while (getline(database, line))
		{
			FlushTampons();
			gotoxy(0, y);
			clreol();
			std::cout << line ;

			keyboardOutput();
		}
		
		printFullPoem();

		database.close();
	}
	else
		std::cout << "Unable to open file";

	int numOfLines = numberOfLines();

	saveInFiles();
	_getch();

	return(0); 
}

void printFullPoem()
{
	gotoxy(0, 10);
	for (int i = 1; i <= eachSave; i++)
		std::cout << data[i] << "\n";
}

void saveInFiles()
{
	std::ofstream myfile;
	myfile.open("output.txt", std::ios::app);

	for (int i = 0; i <= eachSave; i++)
	{
		myfile << data[i] << "\n";
	}
	myfile.close();
}

void keyboardOutput()
{
	char a;
	bool myBool = false;

	while (!myBool)
	{
		a = _getch();
		switch (a)
		{
		case KEY_DOWN: myBool = true;
			break;
		case 's':
			eachSave++;
			data[eachSave] = line;

			gotoxy(0, y);
			std::cout << data[eachSave];
			y++;
			break;
		case 'q':
			myBool = false;
			//return; Doesn't work
			break;
		}
	}
}

int numberOfLines()
{
	int number_of_lines = 0;
	std::string line;
	std::ifstream myfile("output.txt");

	while (std::getline(myfile, line))
		++number_of_lines;
	//std::cout << "Number of lines in text file: " << number_of_lines;
	myfile.close();
	return number_of_lines;
}
void FlushTampons()
{
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	while (_kbhit()) _getch();
}



//serait cool une option pour choisir le poème au masculin ou au féminin