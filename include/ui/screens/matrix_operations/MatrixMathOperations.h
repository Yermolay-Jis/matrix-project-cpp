#pragma once
#ifndef MATRIX_MATH_OPERATIONS_H_
#define MATRIX_MATH_OPERATIONS_H_

#include <functional>
#include <utility>
#include <memory>
#include "ui/UIComponent.h"
#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"
#include "matrix_logic/matrix.h"

class MatrixMathOperations : public UIComponent
{
public:
    MatrixMathOperations(std::shared_ptr<MatrixModel> matrix_model, std::function<void()> call_back);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    ftxui::Component GetFTXUIComponent() override;
    bool IsSelectable() override { return true; };

private:
    ftxui::Component matrix_math_operations_;
    int matrix_math_operatons_active_view_ = 0;

    std::shared_ptr<MatrixModel> matrix_model_;
    std::function<void()> call_back_;

    ftxui::Component buildMatrixOperationMenu();
};

#endif