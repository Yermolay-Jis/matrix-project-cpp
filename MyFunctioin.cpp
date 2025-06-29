#include "Header.h"
#include "MyFunction.h"

HDC hdc = GetDC(GetConsoleWindow());


void setColor(short int pnTextColor, short int pnBKColor) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((pnBKColor & 0x000F) << 4) | (pnTextColor & 0x000F));
};
void SetDefBkColor(short pnBkColor) {
	DefBkColor = (enColor)pnBkColor;
};



COORD GetCursorPosition() {
	CONSOLE_SCREEN_BUFFER_INFO lpCursorInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lpCursorInfo);
	return lpCursorInfo.dwCursorPosition;
}

void SetCursorPosition(short x, short y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(hConsole, coord);

}

void SetCursorCols(short cols) {
	COORD coord = GetCursorPosition();
	SetCursorPosition(coord.Y, cols);
}


void cursorVision(bool value) {
	HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hndl, &cursorInfo);
	cursorInfo.bVisible = value == true ? TRUE : FALSE;
}


void creator() {
	system("cls");
	do {
		Text(hdc, 250, 0, "САМОХАРАКТЕРИСТИКА", RGB(255, 255, 255), RGB(0, 0, 0), 25);
		Text(hdc, 50, 50, "Лукинов Ермолай Андреевич, студент группы 1бИВТ1, характеризую себя себя как", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 75, "увлеченного программированием человека. Обладаю прочной теоритической", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 100, "базой в области ИТ и стремлюсь к постоянному применению знаний на практике.", RGB(255, 255, 255), RGB(15, 5, 77), 25);

	} while (_getch() != 27);
	system("cls");
	
};