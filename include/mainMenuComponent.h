#pragma once
#include "Header.h"
#include "UIComponent.h"
#include "menuLab_1.h"
#include "InfoComponent.h"

class MainMenuComponent : public UIComponent
{
public:
    MainMenuComponent(std::function<void()> exitAction, std::function<void(const std::shared_ptr<UIComponent> &)> navigateTo);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override { return true; };

private:
    ftxui::Component main_menu_component_;
    std::shared_ptr<MenuLab_1> menuLab_1;
};