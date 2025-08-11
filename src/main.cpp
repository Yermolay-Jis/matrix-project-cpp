#include "ui/screens/array_operations/menuLab_1.h"
#include "ui/screens/file_operations/menuLab2.h"
#include "ui/screens/matrix_operations/menuLab_3.h"
#include "ui/UIComponent.h"
#include "io/portable_io.h"
#include "ui/mainMenuComponent.h"
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <functional>
#include <vector>
#include <utility>

int main()
{

    auto screen = ftxui::ScreenInteractive::Fullscreen();

    std::vector<std::shared_ptr<UIComponent>> navigationStack;
    std::shared_ptr<UIComponent> activeComponent;

    auto navigateTo = [&](const std::shared_ptr<UIComponent> &component)
    {
        if (activeComponent)
        {
            navigationStack.push_back(activeComponent);
        }
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

    auto mainMenu = std::make_shared<MainMenuComponent>(navigateBack, navigateTo, exitAction);
    activeComponent = mainMenu;
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