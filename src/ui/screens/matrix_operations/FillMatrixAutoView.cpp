#include "ui/screens/matrix_operations/FillMatrixAutoView.h"
#include "matrix_logic/MatrixAutoFiller.h"

FillMatrixAutoView::FillMatrixAutoView(std::shared_ptr<MatrixModel> matrix_model, std::function<void()> call_back) : matrix_model_(std::move(matrix_model)), call_back_(call_back)
{
    auto autoSetMatrixValueView = buildAutoSetMatrixView();

    fill_matrix_auto_view_ = ftxui::Container::Tab({autoSetMatrixValueView}, &fill_matrix_auto_active_view_);
}

ftxui::Element FillMatrixAutoView::Render()
{
    return fill_matrix_auto_view_->Render();
}

void FillMatrixAutoView::OnEvent(ftxui::Event event)
{
    fill_matrix_auto_view_->OnEvent(event);
}

ftxui::Component FillMatrixAutoView::GetFTXUIComponent()
{
    return fill_matrix_auto_view_;
}

ftxui::Component FillMatrixAutoView::buildAutoSetMatrixView()
{
    auto name_page = ftxui::Renderer([&]
                                     { return ftxui::text("Fill matrix auto") | ftxui::bold; });

    auto current_matrix = ftxui::Renderer([&]
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

    return ftxui::Container::Vertical({name_page,
                                       current_matrix,
                                       ftxui::Button("Set", [&]
                                                     {
                          MatrixAutoFiller filler(0, 100);
                          filler.AutoFill(matrix_model_); }),

                                       ftxui::Button("Finish", [&]
                                                     { call_back_(); })

    });
}