#include<iostream>
#include<vector>
#include<string>
#include<Windows.h>
#include"Tester.h"
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
    int backColor = WHITE;
    int foreColor = BLACK;
    WORD wcolor(((backColor & 0x0f) << 4) + (foreColor & 0x0F));
    SetConsoleTextAttribute(hConsole, wcolor);
}

void MenuMain(OpenType& t);

int main() {
	OpenType t;
    displayTesterAnimation();
    MenuMain(t);

}