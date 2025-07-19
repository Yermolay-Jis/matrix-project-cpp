#include "../include/TextItem.h"

TextItem::TextItem(std::string label) : label_(label) {};

ftxui::Element TextItem::Render()
{
    auto element = ftxui::text(label_);
    return element;
};

void TextItem::OnEvent(ftxui::Event event)
{
    (void)event;
}