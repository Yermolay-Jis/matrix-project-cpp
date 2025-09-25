#include "math_utils.h"

void setColor(short int pnTextColor, short int pnBKColor) {
    // HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    // SetConsoleTextAttribute(hStdOut, (WORD)((pnBKColor & 0x000F) << 4) | (pnTextColor & 0x000F));
};
void SetDefBkColor(short pnBkColor)
{
    DefBkColor = (enColor)pnBkColor;
};

// COORD GetCursorPosition()
// {
// 	CONSOLE_SCREEN_BUFFER_INFO lpCursorInfo;
// 	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lpCursorInfo);
// 	return lpCursorInfo.dwCursorPosition;
// }

void SetCursorPosition(short x, short y)
{
    // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // COORD coord;
    // coord.X = x;
    // coord.Y = y;

    // SetConsoleCursorPosition(hConsole, coord);
}

void SetCursorCols(short cols)
{
    // COORD coord = GetCursorPosition();
    // SetCursorPosition(coord.Y, cols);
}

void cursorVision(bool value)
{
    // HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
    // CONSOLE_CURSOR_INFO cursorInfo;
    // GetConsoleCursorInfo(hndl, &cursorInfo);
    // cursorInfo.bVisible = value == true ? TRUE : FALSE;
}
