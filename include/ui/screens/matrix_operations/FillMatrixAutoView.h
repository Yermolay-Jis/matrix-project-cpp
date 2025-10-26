#pragma once
#ifndef FILL_MATRIX_AUTO_VIEW_H_
#define FILL_MATRIX_AUTO_VIEW_H_

#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include <functional>
#include <memory>
#include <utility>
#include "ui/UIComponent.h"
#include "matrix_logic/matrix.h"

class FillMatrixAutoView : public UIComponent
{
public:
    FillMatrixAutoView(std::shared_ptr<MatrixModel> matrix_model, std::function<void()> call_back);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override { return false; };
    ftxui::Component GetFTXUIComponent() override;

private:
    ftxui::Component fill_matrix_auto_view_;
    int fill_matrix_auto_active_view_ = 0;

    std::shared_ptr<MatrixModel> matrix_model_;
    std::function<void()> call_back_;

    ftxui::Component buildAutoSetMatrixView();
};

#endif