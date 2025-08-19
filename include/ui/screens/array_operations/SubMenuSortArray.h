#pragma once
#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"
#include "ui/UIComponent.h"
#include "array_logic/ArrayModel.h"
#include <functional>
#include <utility>
#include <string>

class SubMenuSortArray : public UIComponent
{
public:
    SubMenuSortArray(std::shared_ptr<ArrayModel> model, std::function<void()> call_back_);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override { return true; }
    ftxui::Component GetFTXUIComponent() override;

private:
    ftxui::Component sub_menu_sort_arr_componetnt_;
    int active_view_sort_arr_ = 0;

    float sorting_time_ = 0;

    std::shared_ptr<ArrayModel> array_model_;
    std::function<void()> call_back_;

    ftxui::Component buildSubMenuSortArrayView();
    ftxui::Component buildMergeSortView();
    ftxui::Component buildSTLSortView();
    // ftxui::Component buildComparisonSortView();
};