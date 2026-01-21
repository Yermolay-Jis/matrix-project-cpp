#pragma once
#ifndef SUB_MENU_SORT_ARRAY_H_
#define SUB_MENU_SORT_ARRAY_H_

#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"
#include "ui/UIComponent.h"
#include "ui/components/InfoComponent.h"
#include "array_logic/ArrayModel.h"
#include <functional>
#include <utility>
#include <string>
#include <map>

class SubMenuSortArray : public UIComponent
{
public:
    SubMenuSortArray(std::shared_ptr<std::map<std::string, ArrayModel>> model, std::function<void()> call_back_);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override { return true; }
    ftxui::Component GetFTXUIComponent() override;

private:
    ftxui::Component sub_menu_sort_arr_componetnt_;
    int active_view_sort_arr_ = 0;

    float merge_sort_time_ = 0;
    float stl_sort_time_ = 0;

    std::string msg_ = "";
    std::string user_input_name_ = "";

    bool is_error = false;

    std::shared_ptr<std::map<std::string, ArrayModel>> models_;
    ArrayModel merge_sort_array_;
    ArrayModel stl_sort_array_;
    std::function<void()> call_back_;

    ftxui::Component buildInputNameView();
    ftxui::Component buildSubMenuSortArrayView();
    ftxui::Component buildMergeSortView();
    ftxui::Component buildSTLSortView();
    ftxui::Component buildAboutComparisonSortView();
    ftxui::Component buildComparisonSortView();
};

#endif