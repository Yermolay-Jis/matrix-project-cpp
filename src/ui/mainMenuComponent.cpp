#include "ui/mainMenuComponent.h"
#include <ftxui/component/component.hpp>
#include <functional>
#include <string>
#include <vector>
#include <utility>
MainMenuComponent::MainMenuComponent(std::function<void()> navigateBack, std::function<void(const std::shared_ptr<UIComponent> &)> navigateTo, std::function<void()> exitAction) : navigateTo_(navigateTo), navigateBack_(navigateBack)
{
    this->menuLab_1_ = std::make_shared<MenuLab_1>(navigateBack_, navigateTo_);

    this->menu_name_component_ = ftxui::Renderer([&]
                                                 { return ftxui::text("Main menu") | ftxui::center | ftxui::bold; });
    this->main_menu_component_ = ftxui::Container::Vertical({menu_name_component_,
                                                             ftxui::Button("About programm", [&]
                                                                           {
        std::string taskTitle = "About programm";
        std::string taskContent = "An array of numbers is given from x_1 to x_n.\nFind the sum elements fr";
        auto infoWindow = std::make_shared<InfoComponent>(taskTitle, taskContent, navigateBack_);
        navigateTo_(infoWindow); }),
                                                             ftxui::Button("Working with arrays", [&]
                                                                           { navigateTo_(this->menuLab_1_); }),
                                                             ftxui::Button("Working with matrixs", [] {}),
                                                             ftxui::Button("File operations", [] {}),
                                                             ftxui::Button("Exit", exitAction)});
};

ftxui::Element MainMenuComponent::Render()
{
    return this->main_menu_component_->Render();
};

void MainMenuComponent::OnEvent(ftxui::Event event)
{
    this->main_menu_component_->OnEvent(event);
};

ftxui::Component MainMenuComponent::GetFTXUIComponent()
{
    return main_menu_component_;
}