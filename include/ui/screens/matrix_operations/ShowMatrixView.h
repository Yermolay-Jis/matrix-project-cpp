#pragma once
#ifndef SHOW_MATRIX_VIEW_H_
#define SHOW_MATRIX_VIEW_H_

#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ui/UIComponent.h"
#include "matrix_logic/matrix.h"
#include <utility>
#include <memory>
#include <functional>

class ShowMatrixView : public UIComponent
{
public:
    ShowMatrixView(std::shared_ptr<MatrixModel> matrix_model, std::function<void()> call_back);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override { return true; };
    ftxui::Component GetFTXUIComponent() override;

private:
    ftxui::Component showMatrixView_;

    std::shared_ptr<MatrixModel> matrix_model_;
    std::function<void()> call_back_;
    int show_matrix_active_view_ = 0;

    ftxui::Component buildShowMatrixView();
};

#endif