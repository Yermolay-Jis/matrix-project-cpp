#pragma once
#ifndef SHOW_ARRAY_VIEW_H_
#define SHOW_ARRAY_VIEW_H_

#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"
#include "array_logic/ArrayModel.h"
#include "ui/UIComponent.h"
#include <string>
#include <functional>
#include <map>
#include <memory>

class ShowLibraryArrayView : public UIComponent
{
public:
    ShowLibraryArrayView(std::shared_ptr<std::map<std::string, ArrayModel>> model, std::function<void()> call_back);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override { return true; };
    ftxui::Component GetFTXUIComponent() override;

private:
    ftxui::Component show_array_component_;
    int active_view_show_array_ = 0;

    std::shared_ptr<std::map<std::string, ArrayModel>> models_;
    std::function<void()> call_back_;

    std::string error_message_;
    std::string user_input_buffer_;

    ftxui::Component buildShowLibraryArrayView();
};

#endif