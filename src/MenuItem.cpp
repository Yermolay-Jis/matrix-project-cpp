#include "../include/MenuItem.h"

MenuItem::MenuItem(std::string label, std::function<void()> action) : label_(label), action_(action) {};

ftxui::Element MenuItem::Render()
{
    ftxui::Element element = ftxui::text(label_);
    if (is_selected_)
    {
        element = element | ftxui::bgcolor(ftxui::Color::White);
    }
    return element;
};

void MenuItem::OnEvent(ftxui::Event event)
{
    if (action_ && event == ftxui::Event::Return)
    {
        action_();
    };
};

bool MenuItem::IsSelectable()
{
    return true;
};

void MenuItem::SetSelected(bool selected)
{
    is_selected_ = selected;
};