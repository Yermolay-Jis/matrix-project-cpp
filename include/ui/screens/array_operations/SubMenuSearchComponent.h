#pragma once
#ifndef SUB_MENU_SEARCH_COMPONENT_H_
#define SUB_MENU_SEARCH_COMPONENT_H_

#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"
#include "ui/UIComponent.h"
#include "ui/components/InfoComponent.h"
#include "array_logic/ArrayModel.h"
#include <functional>
#include <utility>
#include <string>

class SubMenuSearchComponent : public UIComponent
{
public:
    SubMenuSearchComponent(std::shared_ptr<ArrayModel> model, std::function<void()> call_back_);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override { return true; }
    ftxui::Component GetFTXUIComponent() override;

private:
    ftxui::Component sub_menu_search_arr_component_;
    int active_view_search_arr_ = 0;

    std::string user_input_buffer_;
    std::string error_message_;
    std::string last_value_;

    bool is_search_ = false;
    bool search_perfomed_ = false;

    float binary_search_time_ = 0;
    float linear_search_time_ = 0;

    std::shared_ptr<ArrayModel> array_model_;
    std::function<void()> call_back_;

    ftxui::Component buildSubMenuSearchComponent();
    ftxui::Component buildBinarySearchView();
    ftxui::Component buildLinearSearchView();
    ftxui::Component buildAboutComparisonSearchView();
    ftxui::Component buildComparisonSearchView();
};

#endif