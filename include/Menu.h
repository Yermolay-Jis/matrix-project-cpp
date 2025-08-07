#pragma once
#include "Header.h"
#include "UIComponent.h"
#include "MenuItem.h"

class Menu : public UIComponent
{
private:
    std::vector<std::shared_ptr<UIComponent>> items_;
    int index_active_item_ = 0;
    int FindActiveItemNext();
    int FindActiveItemPrevious();

public:
    Menu() = default;

    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;

    void AddItem(std::shared_ptr<UIComponent> item);
};