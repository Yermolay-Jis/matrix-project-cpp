#pragma once
#ifndef FILL_ARRAY_VIEW_H_
#define FILL_ARRAY_VIEW_H_

#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ui/UIComponent.h"
#include "array_logic/ArrayModel.h"
#include <functional>
#include <utility>
#include <map>

class FillArrayView : public UIComponent
{
private:
    ftxui::Component fill_array_component_;

    std::function<void()> call_back_;
    std::shared_ptr<std::map<std::string, ArrayModel>> models_;

    std::string error_message_ = "";
    std::string user_input_buffer_ = "";
    std::string user_input_name_ = "";
    std::string msg_ = "Enter the name of array";

    bool is_error = false;

    int active_view_fill_array_ = 0;
    int new_value_ = 0;
    size_t current_index_ = 0;

    ftxui::Component buildInputNameView();
    ftxui::Component buildInputView();
    ftxui::Component buildResultView();

public:
    FillArrayView(std::shared_ptr<std::map<std::string, ArrayModel>> model, std::function<void()> call_back);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override { return true; };
    ftxui::Component GetFTXUIComponent() override;
};

#endif