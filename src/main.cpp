#include "../include/Header.h"
#include "../include/menuLab_1.h"
#include "../include/menuLab2.h"
#include "../include/menuLab_3.h"
#include "../include/UIComponent.h"
#include "../include/Menu.h"
#include "../include/MenuItem.h"
#include "../include/TextItem.h"
#include "../include/portable_io.h"

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
    auto mainMenu = std::make_shared<Menu>();

    std::shared_ptr<UIComponent> activeComponent = mainMenu;
    std::vector<std::shared_ptr<UIComponent>> navigationStack;

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
    auto menuLab_1 = std::make_shared<MenuLab_1>(navigateBack, navigateTo);

    mainMenu->AddItem(std::make_shared<TextItem>("Main menu"));
    mainMenu->AddItem(std::make_shared<MenuItem>("Laboratory work №1", [navigateTo, menuLab_1]
                                                 { navigateTo(menuLab_1); }));
    // mainMenu->AddItem(std::make_shared<MenuItem>("Laboratory work №2", [&]
    //                                              { navigateTo(menuLab_2); }));
    // mainMenu->AddItem(std::make_shared<MenuItem>("Laboratory work №3", [&]
    //                                              { navigateTo(menuLab_3); }));
    mainMenu->AddItem(std::make_shared<MenuItem>("Exit", [&]
                                                 { screen.Exit(); }));

    auto component = ftxui::Renderer([&]
                                     { return activeComponent->Render(); });
    component = ftxui::CatchEvent(component, [&](ftxui::Event event)
                                  {
        if (event == ftxui::Event::Escape)
        {
            navigateBack();
            return true;
        };
        activeComponent->OnEvent(event);
        return true; });
    screen.Loop(component);
    return 0;
}