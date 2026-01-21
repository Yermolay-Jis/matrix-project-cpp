#pragma once
#ifndef CREATE_MATRIX_VIEW_H_
#define CREATE_MATRIX_VIEW_H_

#include <utility>
#include <map>
#include <functional>
#include <string>
#include <utility>
#include "ui/UIComponent.h"
#include "matrix_logic/matrix.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"

class CreateMatrixView : public UIComponent
{
public:
    CreateMatrixView(std::map<std::string, MatrixModel> &workspace, std::function<void()> call_back);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override { return true; };
    ftxui::Component GetFTXUIComponent() override;

private:
    ftxui::Component create_matrix_;
    std::map<std::string, MatrixModel> &workspace_;
    std::function<void()> call_back_;

    int create_matrix_active_view_ = 0;

    std::string user_input_name_ = "";
    std::string user_input_rows_ = "";
    std::string user_input_cols_ = "";
    std::string error_message_ = "";

    bool is_fill_zero_ = false;
    bool is_create_matrix_ = true;

    ftxui::Component buildEnterSizeMatrixView();
    ftxui::Component buildMatrixZeroFillView();
    ftxui::Component buildResultMatrixView();
};

#endif