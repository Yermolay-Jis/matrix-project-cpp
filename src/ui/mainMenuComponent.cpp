#include "ui/mainMenuComponent.h"
#include <ftxui/component/component.hpp>
#include <functional>
#include <string>
#include <vector>
#include <utility>

MainMenuComponent::MainMenuComponent(std::function<void()> navigateBack, std::function<void(const std::shared_ptr<UIComponent> &)> navigateTo, std::function<void()> exitAction) : navigateTo_(navigateTo), navigateBack_(navigateBack)
{
    menuLab_1_ = std::make_shared<MenuLab_1>(navigateBack_, navigateTo_);
    matrixOperations_ = std::make_shared<MatrixOperations>(navigateBack_);

    menu_name_component_ = ftxui::Renderer([&]
                                           { return ftxui::text("Main menu") | ftxui::center | ftxui::bold; });
    main_menu_component_ = ftxui::Container::Vertical({menu_name_component_,
                                                       ftxui::Button("About programm", [&]
                                                                     {
        std::string taskTitle = "About programm";
        std::string taskContent = R"(

This console-based tool is a portfolio project demonstrating a range of skills in C++ development, from low-level data manipulation to high-level software architecture.

* Purpose:

    To build a functional and robust command-line application for common operations involving arrays, matrices, and file handling, while adhering to modern software engineering best practices.

* Key Features:

    Array Operations: Create, filling, viewing, sorting, searching for elements and statistics.

    Matrix Operations: Perform basic matrix manipulations.

    File I/O: Read from and write data to text and binary files.

    Interactive Menu: A user-friendly console interface for easy navigation.

* Technical Stack & Principles:

    Language: C++ (STL)

    Build Tool: CMake

    UI Library: FTXUI

    Version Control: Git / GitHub

* Core Philosophy:

    Object-Oriented Programming (OOP)

    SOLID Principles

    GRASP Patterns

    Composition and Separation of Responsibilities

This project reflects a deep dive into creating well-designed, testable, and maintainable software from the ground up.)";

        auto infoWindow = std::make_shared<InfoComponent>(taskTitle, taskContent, navigateBack_);
        navigateTo_(infoWindow); }),
                                                       ftxui::Button("Working with arrays", [&]
                                                                     { navigateTo_(menuLab_1_); }),
                                                       ftxui::Button("Working with matrixs", [&]
                                                                     { navigateTo_(matrixOperations_); }),
                                                       ftxui::Button("File operations", [] {}),
                                                       ftxui::Button("Exit", exitAction)});
};

ftxui::Element MainMenuComponent::Render()
{
    return main_menu_component_->Render();
};

void MainMenuComponent::OnEvent(ftxui::Event event)
{
    main_menu_component_->OnEvent(event);
};

ftxui::Component MainMenuComponent::GetFTXUIComponent()
{
    return main_menu_component_;
}