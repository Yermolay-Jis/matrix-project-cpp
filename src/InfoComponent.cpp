#include "../include/InfoComponent.h"

InfoComponent::InfoComponent(std::string title, std::string content, std::function<void()> on_exit) : title_(std::move(title)), content_(std::move(content)), on_exit_(std::move(on_exit)) {};

ftxui::Element InfoComponent::Render()
{
    return ftxui::vbox({ftxui::text(title_),
                        ftxui::separator(),
                        ftxui::paragraph(content_),
                        ftxui::separator()});
};

void InfoComponent::OnEvent(ftxui::Event event)
{
    if (event == ftxui::Event::Escape || event == ftxui::Event::Character('q'))
    {
        on_exit_();
    };
};