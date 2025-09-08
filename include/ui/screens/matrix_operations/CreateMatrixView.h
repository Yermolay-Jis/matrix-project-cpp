#pragma once
#include <utility>
#include "ui/UIComponent.h"
#include "matrix_logic/matrix.h"
#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"

class CreateMatrixView : public UIComponent
{
public:
    CreateMatrixView(std::shared_ptr<MatrixModel> matrix_model, std::function<void()> call_back);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override { return true; };
    ftxui::Component GetFTXUIComponent() override;

private:
    ftxui::Component create_matrix_;
    std::shared_ptr<MatrixModel> matrix_model_;
    std::function<void()> call_back_;

    int create_matrix_active_view_ = 0;

    std::string user_input_rows_ = "";
    std::string user_input_cols_ = "";
    std::string error_message_;

    bool is_fill_zero_ = false;
    bool is_create_matrix_ = false;

    ftxui::Component buildEnterSizeMatrixView();
    ftxui::Component buildMatrixZeroFillView();
    ftxui::Component buildResultMatrixView();
};