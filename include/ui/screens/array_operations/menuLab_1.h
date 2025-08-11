#pragma once
#include "array_logic/ArrayModel.h"
#include "ui/UIComponent.h"
#include "ui/screens/array_operations/CreateArrayView.h"
#include "ui/screens/array_operations/FillArrayView.h"
#include <string>
#include <utility>
#include <functional>

// class MenuLab_1 : public Menu
// {
// private:
//     enum class ViewMode
//     {
//         MenuMode,
//         InputMode,
//         SetSizeArrayMode,
//         PopulateArrayMode,
//         SolutionMode
//     };

//     ViewMode activeMode_ = ViewMode::MenuMode;
//     ViewMode returnToMode_;
//     ArrayModel arrayModel_;

//     size_t newSize_ = 0;

//     std::string userInputBuffer_;
//     std::string promptMessage_ = "Enter the value:";
//     std::string errorMessage_;
//     std::function<void(std::string)> on_input_submit_;
//     void promptForValue(std::string, std::function<void(std::string)>);

// public:
//     MenuLab_1(const std::function<void()> &navigateBack, const std::function<void(std::shared_ptr<UIComponent>)> &navigateTo);
//     ftxui::Element Render() override;
//     void handleSetSizeArray(size_t newSize);

//     void handlePopulateArray();
//     void handleSolutionTask();
//     void handleSaveArrayAs();
//     void handleLoadArray();
// };

class MenuLab_1 : public UIComponent
{
public:
    MenuLab_1(std::function<void()> navigateBack,
              std::function<void(const std::shared_ptr<UIComponent> &)> navigateTo);

    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override;
    ftxui::Component GetFTXUIComponent() override;

private:
    ftxui::Component component_;

    // enum View
    // {
    //     Menu,
    //     CreateArray,
    // };
    int active_view_ = 0;
    std::string user_input_buffer_;
    size_t new_size_ = 0;
    std::string error_message_;
    std::shared_ptr<ArrayModel> array_model_;

    std::shared_ptr<CreateArrayView> createArrayView_;
    std::shared_ptr<FillArrayView> fillArrayView_;

    ftxui::Component buildMainMenuView(std::function<void(const std::shared_ptr<UIComponent> &)> navigateTo, std::function<void()> navigateBack);
    ftxui::Component buildCreateArrayView();
    ftxui::Component buildFillArrayView();
};

void menuLab_1();
void subMenuLab1(std::string nameFile);

void info();
void inputEl();
void solution1();
void outputEl();
// void clearArr(double *);

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
