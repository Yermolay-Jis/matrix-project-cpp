#pragma once
#include "Header.h"
#include "UIComponent.h"

class TextItem : public UIComponent
{
private:
    std::string label_;

public:
    explicit TextItem(std::string label);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
};