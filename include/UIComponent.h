#pragma once
#include "Header.h"

class UIComponent
{
public:
    virtual ftxui::Element Render() = 0;
    virtual void OnEvent(ftxui::Event event) = 0;
    virtual ~UIComponent() = default;
};