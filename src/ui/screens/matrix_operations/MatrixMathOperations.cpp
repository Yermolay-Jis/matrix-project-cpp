#include "ui/screens/matrix_operations/MatrixMathOperations.h"

MatrixMathOperations::MatrixMathOperations(std::shared_ptr<MatrixModel> matrix_model, std::function<void()> call_back) : matrix_model_(std::move(matrix_model)), call_back_(call_back)
{
    auto matrix_operation_menu = buildMatrixOperationMenu();

    matrix_math_operations_ = ftxui::Container::Tab({
                                                        matrix_operation_menu,
                                                    },
                                                    &matrix_math_operatons_active_view_);
}

ftxui::Element MatrixMathOperations::Render()
{
    return matrix_math_operations_->Render();
}

void MatrixMathOperations::OnEvent(ftxui::Event event)
{
    matrix_math_operations_->OnEvent(event);
}

ftxui::Component MatrixMathOperations::GetFTXUIComponent()
{
    return matrix_math_operations_;
}

ftxui::Component MatrixMathOperations::buildMatrixOperationMenu()
{
    return ftxui::Container::Vertical({ftxui::Button("Addition", [this]
                                                     { matrix_math_operatons_active_view_ = 1; }),

                                       ftxui::Button("Multiplication", [this]
                                                     { matrix_math_operatons_active_view_ = 2; }),

                                       ftxui::Button("Division", [this]
                                                     { matrix_math_operatons_active_view_ = 3; }),

                                       ftxui::Button("Transposition", [this]
                                                     { matrix_math_operatons_active_view_ = 4; }),

                                       ftxui::Button("<-- Back", [this]
                                                     { call_back_(); })

    });
}