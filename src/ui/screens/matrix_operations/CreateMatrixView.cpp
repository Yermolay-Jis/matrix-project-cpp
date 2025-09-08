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
                                       ftxui::Input("Enter the rows", &user_input_rows_),
                                       ftxui::Input("Enter the cols", &user_input_cols_),
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
                                                     { create_matrix_active_view_ = 2; })});
};

ftxui::Component CreateMatrixView::buildResultMatrixView()
{
    auto title = ftxui::Renderer([this]
                                 { return ftxui::text("Result matrix") | ftxui::bold; });

    auto result_matrix = ftxui::Renderer([this]
                                         { return ftxui::text(matrix_model_->MatrixFormat()); });
    return ftxui::Container::Vertical({title,
                                       result_matrix,
                                       ftxui::Button("Finish", [&]
                                                     { 
                                                        if (is_create_matrix_) {
                                                            size_t user_rows = std::stoull(user_input_rows_);
                                                            size_t user_cols = std::stoull(user_input_cols_);
                                                            matrix_model_->CreateMatrix(user_rows, user_cols);

                                                            auto matrix = matrix_model_->GetMatrix();
                                                            if (is_fill_zero_) {
                                                                for (size_t i = 0 ; i < user_rows; i++) {
                                                                    for (size_t j = 0; j < user_cols; j++) {
                                                                       (*matrix)[i][j] = 0; 
                                                                    }
                                                                }
                                                            }
                                                        }
                                                        
                                                        call_back_(); })

    });
};