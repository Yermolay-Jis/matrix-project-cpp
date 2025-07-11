#include "../include/Menu.h"

ftxui::Element Menu::Render()
{
    std::vector<ftxui::Element> items;
    for (size_t i = 0; i < items_.size(); i++)
    {
        auto element = std::dynamic_pointer_cast<MenuItem>(items_[i]);
        if (element)
        {
            element->SetSelected(i == index_active_item_);
        };
        items.push_back(items_[i]->Render());
    };
    return ftxui::vbox(items);
};

void Menu::OnEvent(ftxui::Event event)
{
    if (items_.empty())
    {
        return;
    };

    if (event == ftxui::Event::Return)
    {
        items_[index_active_item_]->OnEvent(event);
    };

    if (event == ftxui::Event::ArrowDown || event == ftxui::Event::Character("j"))
    {
        index_active_item_++;
    };

    if (index_active_item_ >= items_.size())
    {
        index_active_item_ = 0;
    }

    if (event == ftxui::Event::ArrowUp || event == ftxui::Event::Character("k"))
    {
        index_active_item_--;
    };
    ;

    if (index_active_item_ < 0)
    {
        index_active_item_ = items_.size() - 1;
    };
};

void Menu::AddItem(std::shared_ptr<UIComponent> item)
{
    items_.push_back(item);
};
