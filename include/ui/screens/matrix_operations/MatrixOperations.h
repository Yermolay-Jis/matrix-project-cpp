#pragma once
#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"
#include "matrix_logic/matrix.h"
#include "ui/screens/matrix_operations/ShowMatrixView.h"
#include "ui/screens/matrix_operations/CreateMatrixView.h"
#include "ui/screens/matrix_operations/FillMatrixView.h"
#include "ui/UIComponent.h"
#include <functional>
#include <utility>

class MatrixOperations : public UIComponent
{
public:
    MatrixOperations();
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    ftxui::Component GetFTXUIComponent() override;
    bool IsSelectable() override { return true; };

private:
    ftxui::Component matrix_operations_;
    std::shared_ptr<MatrixModel> matrix_model_;

    std::shared_ptr<CreateMatrixView> createMatrixView_;
    std::shared_ptr<ShowMatrixView> showMatrixView_;
    std::shared_ptr<FillMatrixView> fillMatrixView_;
    // std::shared_ptr<AutoFillMatrixView> autoFillMatrixView_;

    int matrix_operations_active_view_ = 0;

    ftxui::Component buildMatrixMainMenuView();
    ftxui::Component buildCreateMatrixView();
    ftxui::Component buildShowMatrixView();
    ftxui::Component buildFillMatrixView();
    ftxui::Component buildAutoFillMatrixView();
};