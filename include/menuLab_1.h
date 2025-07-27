#pragma once
#include "Header.h"
#include "ArrayModel.h"
#include "../include/UIComponent.h"
#include "../include/Menu.h"
#include "../include/MenuItem.h"
#include "../include/TextItem.h"

class MenuLab_1 : public Menu
{
private:
    enum class ViewMode
    {
        MenuMode,
        InputMode,
        SetSizeArrayMode,
        PopulateArrayMode,
        SolutionMode
    };

    ViewMode activeMode_ = ViewMode::MenuMode;
    ViewMode returnToMode_;
    ArrayModel arrayModel_;

    size_t receivedValue_;
    bool getValue_ = false;
    std::string inputString_ = "";
    std::string promptMessage_ = "Enter the value:";
    std::string errorMessage_;
    ftxui::Component inputComponent_ = ftxui::Input(&inputString_, promptMessage_);
    void promptForGetValue();

public:
    MenuLab_1(const std::function<void()> &navigateBack, const std::function<void(std::shared_ptr<UIComponent>)> &navigateTo);
    ftxui::Element Render() override;
    void handleSetSizeArray();

    void handlePopulateArray();
    void handleSolutionTask();
    void handleSaveArrayAs();
    void handleLoadArray();
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
