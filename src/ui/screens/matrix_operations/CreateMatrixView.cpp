#include "ui/screens/matrix_operations/CreateMatrixView.h"
#include "matrix_logic/matrix.h"

CreateMatrixView::CreateMatrixView(std::shared_ptr<MatrixModel> matrix_model, std::function<void()> call_back) : matrix_model_(std::move(matrix_model)), call_back_(call_back)
{
    auto enter_size_matrix_view = buildEnterSizeMatrixView();

    auto matrix_zero_fill_view = buildMatrixZeroFillView();

    auto result_matrix_view = buildResultMatrixView();

    create_matrix_ = ftxui::Container::Tab({
                                               enter_size_matrix_view,
                                               matrix_zero_fill_view,
                                               result_matrix_view,
                                           },
                                           &create_matrix_active_view_);
};

ftxui::Element CreateMatrixView::Render()
{
    return create_matrix_->Render();
};

void CreateMatrixView::OnEvent(ftxui::Event event)
{
    create_matrix_->OnEvent(event);
};

ftxui::Component CreateMatrixView::GetFTXUIComponent()
{
    return create_matrix_;
};

ftxui::Component CreateMatrixView::buildEnterSizeMatrixView()
{
    auto title = ftxui::Renderer([this]
                                 { return ftxui::text("Enter the value of size for matrix (rows/cols)") | ftxui::bold; });

    return ftxui::Container::Vertical({title,
                                       ftxui::Input(&user_input_rows_, "Enter the rows"),
                                       ftxui::Input(&user_input_cols_, "Enter the cols"),
                                       ftxui::Button("Next", [&]
                                                     { create_matrix_active_view_ = 1; })});
};

ftxui::Component CreateMatrixView::buildMatrixZeroFillView()
{
    auto title = ftxui::Renderer([this]
                                 { return ftxui::text("Do you want to fill zeroes of the matrix?") | ftxui::bold; });

    return ftxui::Container::Vertical({title,
                                       ftxui::Checkbox("Fill of the zero", &is_fill_zero_),
                                       ftxui::Checkbox("Create of the matrix", &is_create_matrix_),
                                       ftxui::Button("Next", [&]
                                                     {
                                                         if (is_create_matrix_)
                                                         {
                                                             if (!(user_input_rows_.empty() || user_input_cols_.empty()))
                                                             {
                                                                 size_t user_rows = std::stoi(user_input_rows_);
                                                                 size_t user_cols = std::stoi(user_input_cols_);
                                                                 matrix_model_->CreateMatrix(user_rows, user_cols);

                                                                 auto matrix = matrix_model_->GetMatrix();
                                                                 if (is_fill_zero_)
                                                                 {
                                                                     for (size_t i = 0; i < user_rows; i++)
                                                                     {
                                                                         for (size_t j = 0; j < user_cols; j++)
                                                                         {
                                                                             matrix_model_->SetForIndex(0, i, j);
                                                                         }
                                                                     }
                                                                 }
                                                             }
                                                             else
                                                             {
                                                                 error_message_ = "User rows or cols is empty!";
                                                             };
                                                         }

                                                         create_matrix_active_view_ = 2;
                                                         user_input_cols_.clear();
                                                         user_input_rows_.clear(); })

    });
};

ftxui::Component CreateMatrixView::buildResultMatrixView()
{
    auto error = ftxui::Renderer([this]
                                 {
                                     if (error_message_.empty())
                                     {
                                         return ftxui::text(error_message_);
                                     }
                                     else
                                     {
                                         return ftxui::text(error_message_) | ftxui::bgcolor(ftxui::Color::Red1) | ftxui::color(ftxui::Color::White) | ftxui::bold;
                                     } });
    auto result_matrix = ftxui::Renderer([this]
                                         {size_t rows = matrix_model_->GetRows();
                                             size_t cols = matrix_model_->GetCols();
                                             std::stringstream ss;
                                             for (size_t i = 0; i < rows; i++)
                                             {
                                                 for (size_t j = 0; j < cols; j++)
                                                 {
                                                     ss  << matrix_model_->GetValueForIndex(i, j) << "   ";
                                                 };
                                                 ss << "\n";
                                             }
                                             return ftxui::paragraph(ss.str()); });
    auto title = ftxui::Renderer([this]
                                 { return ftxui::vbox({
                                       ftxui::text("Result matrix") | ftxui::bold,
                                   }); });

    return ftxui::Container::Vertical({error,
                                       title,
                                       result_matrix,
                                       ftxui::Button("Finish", [&]
                                                     {
                                                         call_back_();
                                                         create_matrix_active_view_ = 0;
                                                        error_message_.clear(); })

    });
};