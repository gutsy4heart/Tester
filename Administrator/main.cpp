#include "Administrator.h"
#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>
using namespace std;
enum colormenu {
	BLACK,
	BLUE,
	GREEN,
	AQUA,
	RED,
	PURPLE,
	YELLOW,
	WHITE,
	GRAY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_AQUA,
	LIGHT_RED,
	LIGHT_PURPLE,
	LIGHT_YELLOW,
	BRIGHT_WHITE
};
void displayTesterAnimation() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int backColor = GREEN;
	int foreColor = BLACK;
	WORD wcolor(((backColor & 0x0f) << 4) + (foreColor & 0x0F));
	SetConsoleTextAttribute(hConsole, wcolor);
	for (size_t i = 0; i < 1; i++)
	{
		WORD wcolor(((backColor & 0x0f) << 4) + (foreColor & 0x0F));
		SetConsoleTextAttribute(hConsole, wcolor);
		cout << "\t\t\t\t\t\t\t    #                                    " << endl;
		cout << "\t\t\t\t\t\t\t   # #      #####     #    #   #   #    # " << endl;
		cout << "\t\t\t\t\t\t\t  #   #     #    #    ##  ##   #   ##   # " << endl;
		cout << "\t\t\t\t\t\t\t #     #    #    #    # ## #   #   # #  # " << endl;
		cout << "\t\t\t\t\t\t\t #######    #    #    #    #   #   #  # # " << endl;
		cout << "\t\t\t\t\t\t\t #     #    #    #    #    #   #   #   ## " << endl;
		cout << "\t\t\t\t\t\t\t #     #    #####     #    #   #   #    # " << endl;
		cout << '\n';

	}
}
int main() {
	displayTesterAnimation();
	Admin ad;
	AdminFeatures add;
	//ad.AdminMenu();

	add.CategoryMenu();
}