#pragma once
#ifndef FILL_MATRIX_VIEW_H_
#define FILL_MATRIX_VIEW_H_

#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "matrix_logic/matrix.h"
#include "ui/UIComponent.h"
#include <memory>
#include <functional>
#include <utility>

class FillMatrixView : public UIComponent
{
public:
    FillMatrixView(std::shared_ptr<MatrixModel> matrix_model, std::function<void()> call_back);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override { return true; };
    ftxui::Component GetFTXUIComponent() override;

private:
    ftxui::Component fill_matrix_view_;

    int fill_matrix_active_view_ = 0;

    std::string user_input_row_ = "0";
    std::string user_input_col_ = "0";
    std::string user_input_value_ = "";
    std::string error_message_;
    bool is_error_ = false;
    std::string last_value_;

    size_t current_row_ = 0;
    size_t current_col_ = 0;

    std::string name_input_ = "Enter the value by index";
    bool is_input_for_index_ = false;

    ftxui::Component current_input_;
    int curren_active_input_ = 0;

    std::shared_ptr<MatrixModel>
        matrix_model_;
    std::function<void()> call_back_;

    ftxui::Component buildSetValueMatrixView();
    ftxui::Component buildFinishView();
};

#endif