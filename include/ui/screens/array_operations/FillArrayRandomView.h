#pragma once
#ifndef FILL_ARRAY_RANDOM_VIEW_H_
#define FILL_ARRAY_RANDOM_VIEW_H_

#include "ui/UIComponent.h"
#include "array_logic/ArrayModel.h"
#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"
#include <functional>
#include <map>
#include <utility>

class FillArrayRandomView : public UIComponent
{
public:
    FillArrayRandomView(std::shared_ptr<std::map<std::string, ArrayModel>> model, std::function<void()> call_back);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override { return true; };
    ftxui::Component GetFTXUIComponent() override;

private:
    ftxui::Component fill_array_random_component_;
    int active_view_fill_array_ = 0;

    std::string user_input_name_ = "";
    std::string msg_ = "Enter the name of array";
    bool is_error = false;

    std::shared_ptr<std::map<std::string, ArrayModel>> models_;
    std::function<void()> call_back_;

    ftxui::Component buildInputNameView();
    ftxui::Component buildResultView();
};

#endif