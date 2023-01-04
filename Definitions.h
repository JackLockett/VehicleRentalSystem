#pragma once

class Definitions
{
	#define ClearConsole system("cls");
	#define PressAnyKey cout << "\nPress any key to try again...";
	#define InvalidCharacters cout << "\nInvalid Character(s)";
    #define NumericLimits cin.ignore(numeric_limits<streamsize>::max(), '\n');
};

