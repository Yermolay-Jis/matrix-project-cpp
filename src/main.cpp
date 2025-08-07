#include "../include/Header.h"
#include "../include/menuLab_1.h"
#include "../include/menuLab2.h"
#include "../include/menuLab_3.h"
#include "../include/UIComponent.h"
#include "../include/Menu.h"
#include "../include/MenuItem.h"
#include "../include/portable_io.h"
#include "../include/mainMenuComponent.h"

int main()
{
    // cout << argc << endl;
    // cout << argv[0] << endl;
    // size_t key;

    // do
    // {
    //     // system("cls");
    //     // Text(hdc, Xpos, 100, "0 -  Информация о программисте", RGB(255, 255, 255), RGB(15, 5, 77), 25);
    //     // Text(hdc, Xpos, 150, "1 -  Лабораторная работа №1", RGB(255, 255, 255), RGB(15, 5, 77), 25);
    //     // Text(hdc, Xpos, 200, "2 - Лабораторная работа №2", RGB(255, 255, 255), RGB(15, 5, 77), 25);
    //     // Text(hdc, Xpos, 250, "3 -  Лабораторная работа №3", RGB(255, 255, 255), RGB(15, 5, 77), 25);
    //     // Text(hdc, Xpos, 300, "ESC - выйти из программы", RGB(255, 255, 255), RGB(157, 56, 188), 25);

    //     key = get_char_non_blocking();

    //     switch (key)
    //     {
    //     case '0':
    //         creator();
    //         break;
    //     case '1':
    //         menuLab_1();
    //         break;
    //     case '2':
    //         menuLab_2();
    //         break;
    //     case '3':
    //         menuLab_3();
    //         break;
    //     default:
    //         break;
    //     }
    // } while (key != 27);

    auto screen = ftxui::ScreenInteractive::Fullscreen();

    std::vector<std::shared_ptr<UIComponent>> navigationStack;
    std::shared_ptr<UIComponent> activeComponent;

    auto navigateTo = [&](const std::shared_ptr<UIComponent> &component)
    {
        navigationStack.push_back(activeComponent);
        activeComponent = component;
    };
    auto navigateBack = [&]
    {
        if (!navigationStack.empty())
        {
            activeComponent = navigationStack.back();
            navigationStack.pop_back();
        }
    };
    auto exitAction = [&]
    {
        screen.Exit();
    };

    auto mainMenu = std::make_shared<MainMenuComponent>(exitAction, navigateTo);
    navigateTo(mainMenu);

    auto component = ftxui::Renderer([&]
                                     { return activeComponent->Render(); });
    auto event_catcher = ftxui::CatchEvent(component, [&](ftxui::Event event)
                                           {
        if (event == ftxui::Event::Escape)
        {
            navigateBack();
            return true;
        };
        activeComponent->OnEvent(event);
        return false; });
    screen.Loop(event_catcher);
    return 0;
}