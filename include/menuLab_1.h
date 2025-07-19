#pragma once
#include "Header.h"
#include "../include/UIComponent.h"
#include "../include/Menu.h"
#include "../include/MenuItem.h"
#include "../include/TextItem.h"

class MenuLab_1 : public Menu
{
public:
    MenuLab_1(const std::function<void()> &navigateBack);
};

void menuLab_1();
void subMenuLab1(std::string nameFile);

void info();
void inputEl();
void solution1();
void outputEl();
void clearArr(double *);

void inpFile();
void outFile();

// void outTableGraf(double *, int, int, std::string, std::string, HDC, size_t);

int setSizeArr();

std::string getNameFile();
void replaceElFile();
bool is_number(std::string);

extern size_t sizeArr;
extern double *arr;
// extern HDC hdc;
extern char separate;
