#include "ui/screens/matrix_operations/FillMatrixView.h"

FillMatrixView::FillMatrixView(std::shared_ptr<MatrixModel> matrix_model, std::function<void()> call_back) : matrix_model_(std::move(matrix_model)), call_back_(call_back)
{

    auto setValueMatrixView = buildSetValueMatrixView();

    auto finishView = buildFinishView();

    fill_matrix_view_ = ftxui::Container::Tab({
                                                  setValueMatrixView,
                                                  finishView,
                                              },
                                              &fill_matrix_active_view_);
}

ftxui::Element FillMatrixView::Render()
{
    return fill_matrix_view_->Render();
};

void FillMatrixView::OnEvent(ftxui::Event event)
{
    fill_matrix_view_->OnEvent(event);
};

ftxui::Component FillMatrixView::GetFTXUIComponent()
{
    return fill_matrix_view_;
};

ftxui::Component FillMatrixView::buildSetValueMatrixView()
{
    auto error_message = ftxui::Renderer([&]
                                         {
                                              if (is_error_)
                                              {
                                                  return ftxui::text(error_message_) | ftxui::bgcolor(ftxui::Color::Red1) | ftxui::color(ftxui::Color::White) |ftxui::bold;
                                              }
                                              else
                                              {
                                                  return ftxui::text("") ;
                                              } });

    auto title = ftxui::Renderer([this]
                                 { return ftxui::vbox({
                                       ftxui::text("Filling of the matrix") | ftxui::bold,
                                       ftxui::text(""),
                                   }); });

    auto message = ftxui::Renderer([this]
                                   { return ftxui::text("Enter the value for [" + std::to_string(current_row_ + 1) + "][" + std::to_string(current_col_ + 1) + "] --> " + user_input_value_); });

    auto current_matrix = ftxui::Renderer([this]
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
    auto user_input_value = ftxui::Input(&user_input_value_, "Enter the value");
    auto user_input_index = ftxui::Container::Vertical({

        ftxui::Input(&user_input_row_, "Enter the row"),

        ftxui::Input(&user_input_col_, "Enter the col"),
        ftxui::Input(&user_input_value_, "Enter the value"),

    });

    current_input_ = ftxui::Container::Tab({
                                               user_input_value,
                                               user_input_index,
                                           },
                                           &curren_active_input_);

    return ftxui::Container::Vertical({

        error_message,
        title,
        current_matrix,
        message,
        current_input_,
        ftxui::Button("Set", [&]
                      {
                              try
                              {
                                  double user_value = std::stod(user_input_value_);
                                  is_error_= false;
                                  if (is_input_for_index_)
                                  {
                                      current_row_ = std::stoi(user_input_row_);
                                      current_col_ = std::stoi(user_input_col_);
                                      if (!(current_row_ < matrix_model_->GetRows() + 1) || !( current_col_ < matrix_model_->GetCols() + 1 ) || !(current_col_ > 0) || !(current_row_ > 0) )
                                      {
                                          error_message_ = "Error: enter the correct symbol!";
                                          is_error_ = true;
                                          current_row_ = 0;
                                          current_col_ = 0;
                                      }
                                      else
                                      {
                                          matrix_model_->SetForIndex(user_value, current_row_ - 1, current_col_ - 1);
                                          current_col_ = 0;
                                          current_row_ = 0;
                                          user_input_value_.clear();
                                          user_input_row_.clear();
                                          user_input_col_.clear();
                                          is_error_ = false;
                                          error_message_.clear();
                                      };
                                  }
                                  else
                                  {
                                      matrix_model_->SetForIndex(user_value, current_row_, current_col_);
                                      if (current_col_ != matrix_model_->GetCols() - 1)
                                      {
                                          last_value_ = user_input_value_;
                                          user_input_value_.clear();
                                          current_col_++;
                                      }
                                      else
                                      {
                                          current_row_++;
                                          current_col_ = 0;
                                      }
                                      if (current_row_ == matrix_model_->GetRows())
                                      {
                                          current_row_ = 0;
                                          current_col_ = 0;
                                      };
                                  };
                                  }
                                  catch (const std::exception &e)
                                  {
                                      error_message_ = "Error, please enter the current of value!";
                                      is_error_ = true;
                                  } }),

        ftxui::Button(name_input_, [&]
                      {
                if (is_input_for_index_ == false)
                {
                    is_input_for_index_ = true;
                    name_input_ = "Enter values in order";
                    curren_active_input_ = 1;
                    //
                }
                else
                {
                    is_input_for_index_ = false;
                    name_input_ = "Enter the value by index";
                    curren_active_input_ = 0;
                } }),

        ftxui::Button("Next", [&]
                      {
                          curren_active_input_ = 0;
                          fill_matrix_active_view_ = 1; })

    });
}

ftxui::Component FillMatrixView::buildFinishView()
{
    auto title = ftxui::Renderer([this]
                                 { return ftxui::text("Result matrix") | ftxui::bold; });

    auto result_matrix = ftxui::Renderer([this]
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
                                       result_matrix,
                                       ftxui::Button("Finish", [&]
                                                     {
                                                        current_row_ = 0;
                                                        current_col_ = 0;
                                                        fill_matrix_active_view_ = 0; 
                                                        call_back_(); })

    });
};