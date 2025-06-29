#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>


#define Xpos 500
#define CURSOR(row, col) SetCursorPosition(row, col)
#define SPACE(n) for (int i = 0; i < n; i++) std::cout << " "
#define BACK(n) for (int i = 0; i < n; i++) std::cout << "\b"
#define SPACEBACK(n) SPACE(n); BACK(n)
#define LINES(n) for (int i = 0; i < n; i++) std::cout << std::endl
#define ClearCin if (std::cin.rdbuf()->in_avail()) std::cin.ignore()
#define CURSORCOLS(n) SetCursorCols(n)
#define CURSORPOS GetCursorPosition()

