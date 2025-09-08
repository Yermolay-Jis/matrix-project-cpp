#include "ui/screens/matrix_operations/ShowMatrixView.h"
#include <utility>
#include <memory>
#include <functional>

ShowMatrixView::ShowMatrixView(std::shared_ptr<MatrixModel> matrix_model, std::function<void()> call_back) : matrix_model_(std::move(matrix_model)), call_back_(call_back) {
                                                                                                             };

ftxui::Element ShowMatrixView::Render()
{
    return showMatrixView_->Render();
};

void ShowMatrixView::OnEvent(ftxui::Event event)
{
    showMatrixView_->OnEvent(event);
}

ftxui::Component ShowMatrixView::GetFTXUIComponent()
{
    return showMatrixView_;
};