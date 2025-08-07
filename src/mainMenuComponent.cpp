#include "../include/mainMenuComponent.h"

MainMenuComponent::MainMenuComponent(std::function<void()> exitAction, std::function<void(const std::shared_ptr<UIComponent> &)> navigateTo)
{
    auto navigateBackToMainMenu = [&]
    {
        navigateTo(std::make_shared<MainMenuComponent>(exitAction, navigateTo));
    };
    menuLab_1 = std::make_shared<MenuLab_1>(navigateBackToMainMenu, navigateTo);

    auto menu_name_text = ftxui::text("Main menu");
    auto menu_name_component = ftxui::Renderer([&]
                                               { return menu_name_text; });
    main_menu_component_ = ftxui::Container::Vertical({menu_name_component,

                                                       ftxui::Button("About programmists", [&]
                                                                     {
            std::string taskTitle = "About me:";
            std::string taskContent = "An array of numbers is given from x_1 to x_n.\nFind the sum elements fr";
            auto infoWindow = std::make_shared<InfoComponent>(taskTitle, taskContent, navigateBackToMainMenu);
            navigateTo(infoWindow); }),
                                                       ftxui::Button("Laboratory work #1", [&]
                                                                     { navigateTo(menuLab_1); }),
                                                       ftxui::Button("Exit", exitAction)

    });
};

ftxui::Element MainMenuComponent::Render()
{
    return this->main_menu_component_->Render();
};

void MainMenuComponent::OnEvent(ftxui::Event event)
{
    this->main_menu_component_->OnEvent(event);
}