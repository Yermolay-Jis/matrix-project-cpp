#include "ui/screens/matrix_operations/ShowMatrixView.h"
#include <utility>
#include <memory>
#include <functional>

ShowMatrixView::ShowMatrixView(std::shared_ptr<MatrixModel> matrix_model, std::function<void()> call_back) : matrix_model_(std::move(matrix_model)), call_back_(call_back)
{
    auto show_matrix_view = buildShowMatrixView();

    showMatrixView_ = ftxui::Container::Tab({
                                                show_matrix_view,
                                            },
                                            &show_matrix_active_view_);
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

ftxui::Component ShowMatrixView::buildShowMatrixView()
{

    auto title = ftxui::Renderer([&]
                                 { return ftxui::text("Current matrix") | ftxui::bold; });

    auto content = ftxui::Renderer([&]
                                   { 
                                    size_t rows = matrix_model_->GetRows();
                                    size_t cols = matrix_model_->GetCols();
                                    std::stringstream ss;
                                    for (size_t i = 0; i < rows; i++)
                                    {
                                        for (size_t j = 0; j < cols; j++)
                                        {
                                            ss << matrix_model_->GetValueForIndex(i, j) << "   ";
                                        };
                                        ss << "\n";
                                    }
                                    return ftxui::paragraph(ss.str()); });

    return ftxui::Container::Vertical({title,
                                       content,

                                       ftxui::Button("Back", [&]
                                                     { call_back_(); })});
};