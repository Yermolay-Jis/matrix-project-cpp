#pragma once
#include "ui/UIComponent.h"
#include "ui/screens/array_operations/menuLab_1.h"
#include "ui/components/InfoComponent.h"
#include <functional>
#include <utility>

class MainMenuComponent : public UIComponent
{
public:
    MainMenuComponent(std::function<void()> navigateBack, std::function<void(const std::shared_ptr<UIComponent> &)> navigateTo, std::function<void()> exitAction);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override { return true; };
    ftxui::Component GetFTXUIComponent() override;

private:
    ftxui::Component main_menu_component_;
    std::shared_ptr<MenuLab_1> menuLab_1_;
    ftxui::Component menu_name_component_;
    std::function<void(const std::shared_ptr<UIComponent> &)> navigateTo_;
    std::function<void()> navigateBack_;
};