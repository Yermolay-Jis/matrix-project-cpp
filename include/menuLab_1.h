#pragma once
#include "Header.h"

void menuLab_1();
void subMenuLab1(std::string nameFile);

void info();
void inputEl();
void solution1();
void outputEl();
void clearArr(double *);

void inpFile();
void outFile();

void outTableGraf(double *, int, int, std::string, std::string, HDC, size_t);
void Text(HDC hdc, int indentX, int indentY, std::string title, COLORREF textColor, COLORREF BG, int size);

int setSizeArr();

std::string getNameFile();
void replaceElFile();
bool is_number(std::string);

extern size_t sizeArr;
extern double *arr;
extern HDC hdc;
extern char separate;
