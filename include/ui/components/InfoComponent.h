#pragma once
#include "ui/UIComponent.h"

class InfoComponent : public UIComponent
{
private:
    std::string title_;
    std::string content_;
    std::function<void()> on_exit_;
    ftxui::Component GetFTXUIComponent();

public:
    InfoComponent(std::string title, std::string content, std::function<void()> on_exit);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
};