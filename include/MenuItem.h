#pragma once
#include "Header.h"
#include "UIComponent.h"

class MenuItem : public UIComponent
{
private:
    std::string label_;
    bool is_selected_ = false;
    std::function<void()> action_;

public:
    explicit MenuItem(std::string label, std::function<void()> action_ = nullptr);

    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;

    void SetSelected(bool selected);
};