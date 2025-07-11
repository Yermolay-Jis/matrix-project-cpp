#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include <filesystem>
#include <functional>
#include <vector>
#include <memory>
#include <stack>
#include <utility>

#define Xpos 500
#define CURSOR(row, col) SetCursorPosition(row, col)
#define SPACE(n)                \
    for (int i = 0; i < n; i++) \
    std::cout << " "
#define BACK(n)                 \
    for (int i = 0; i < n; i++) \
    std::cout << "\b"
#define SPACEBACK(n) \
    SPACE(n);        \
    BACK(n)
#define LINES(n)                \
    for (int i = 0; i < n; i++) \
    std::cout << std::endl
#define ClearCin                      \
    if (std::cin.rdbuf()->in_avail()) \
    std::cin.ignore()
#define CURSORCOLS(n) SetCursorCols(n)
#define CURSORPOS GetCursorPosition()
