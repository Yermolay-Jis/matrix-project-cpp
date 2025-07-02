#pragma once

typedef enum enColor
{
	CL_BLACK,
	CL_LIGHT_RED,
	CL_LIGHT_WHITE
} COLORS, �����;

static enColor DefBkColor = enColor::CL_BLACK;

void setColor(short int pnTextColor, short int pnBKColor = DefBkColor);
void SetDefBkColor(short pnBkColor);
void cursorVision(bool value);
void creator();

COORD GetCursorPosition();
void SetCursorPosition(short x, short y);
void SetCursorCols(short cols);
void Text(HDC hdc, int indentX, int indentY, std::string title, COLORREF textColor, COLORREF BG, int size);
