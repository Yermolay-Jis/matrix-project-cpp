#pragma once
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
class UIComponent
{
public:
    virtual ftxui::Element Render() = 0;
    virtual void OnEvent(ftxui::Event event) = 0;
    virtual bool IsSelectable() { return false; };
    virtual ftxui::Component GetFTXUIComponent() = 0;
    virtual ~UIComponent() = default;
};