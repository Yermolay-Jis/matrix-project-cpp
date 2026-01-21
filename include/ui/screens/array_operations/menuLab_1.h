#pragma once
#ifndef ARRAY_OPERATION_H_
#define ARRAY_OPERATION_H_

#include "array_logic/ArrayModel.h"
#include "ui/UIComponent.h"
#include "ui/screens/array_operations/CreateArrayView.h"
#include "ui/screens/array_operations/FillArrayView.h"
#include "ui/screens/array_operations/FillArrayRandomView.h"
#include "ui/screens/array_operations/ShowLibraryArrayView.h"
#include "ui/screens/array_operations/SubMenuSortArray.h"
#include "ui/screens/array_operations/SubMenuSearchComponent.h"
#include <string>
#include <utility>
#include <functional>
#include <map>

class MenuLab_1 : public UIComponent
{
public:
    MenuLab_1(std::function<void()> navigateBack);

    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override;
    ftxui::Component GetFTXUIComponent() override;

private:
    ftxui::Component component_;
    int active_view_ = 0;
    std::string user_input_buffer_;
    size_t new_size_ = 0;
    std::string error_message_;

    std::shared_ptr<std::map<std::string, ArrayModel>> models_;

    std::shared_ptr<CreateArrayView> createArrayView_;
    std::shared_ptr<FillArrayView> fillArrayView_;
    std::shared_ptr<ShowLibraryArrayView> showLibraryArrayView_;
    std::shared_ptr<FillArrayRandomView> fillArrayRandomView_;
    std::shared_ptr<SubMenuSortArray> subMenuSortArrayView_;
    std::shared_ptr<SubMenuSearchComponent> subMenuSearchComponentView_;

    ftxui::Component buildMainMenuView(std::function<void()> navigateBack);
    ftxui::Component buildCreateArrayView();
    ftxui::Component buildFillArrayView();
    ftxui::Component buildFillArrayRandomView();
    ftxui::Component buildShowLibraryArrayView();
    ftxui::Component buildSubMenuSortArrayView();
    ftxui::Component buildSubMenuSearchComponentView();
};

#endif