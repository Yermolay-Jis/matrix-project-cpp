#include "ui/screens/array_operations/FillArrayView.h"

FillArrayView::FillArrayView(std::shared_ptr<ArrayModel> model, std::function<void()> call_back) : array_model_(std::move(model)), call_back_(std::move(call_back))
{
    auto inputView = buildInputView();
    auto resultView = buildResultView();
    fill_array_component_ = ftxui::Container::Tab({inputView,
                                                   resultView},
                                                  &active_view_fill_array_);
};

ftxui::Element FillArrayView::Render()
{
    return this->fill_array_component_->Render();
};

void FillArrayView::OnEvent(ftxui::Event event)
{
    this->fill_array_component_->OnEvent(event);
};

ftxui::Component FillArrayView::GetFTXUIComponent()
{
    return this->fill_array_component_;
};

ftxui::Component FillArrayView::buildInputView()
{

    auto fill_array_content = ftxui::Renderer([&]
                                              {
        std::stringstream ss;
        ss << "[";
        for (size_t i = 0; i < array_model_->getSizeArray() - 1; i++)
        {
            auto array = array_model_->getArray();
            if (i < array_model_->getSizeArray() && array[i] != 0)
            {
                ss << array[i];
            }else {
                ss << "_";
            }

           if (i < array_model_->getSizeArray() - 1) {
                ss << ", ";
           } 
        }
        ss << "]";

//  ftxui::text("Please, enter the number for current index --> " + std::to_string(this->current_index_));
        return ftxui::text("Current array: " + ss.str()); });

    return ftxui::Container::Vertical({fill_array_content,
                                       ftxui::Input(&user_input_buffer_, "Enter number here"), // Связываем поле ввода с нашим буфером
                                       ftxui::Button("Submit", [this]
                                                     {
                                                         try
                                                         {
                                                             this->new_value_ = std::stoi(user_input_buffer_);
                                                         }
                                                         catch (const std::exception &e)
                                                         {
                                                             // Если пользователь ввел не число:
                                                             this->error_message_ = "Invalid input. Must be a number.";
                                                             this->call_back_();
                                                         }
                                                         this->array_model_->setItemForIndex(current_index_, new_value_);
                                                         this->error_message_.clear();
                                                         if (this->current_index_ >= this->array_model_->getSizeArray() - 1)
                                                         {
                                                             this->active_view_fill_array_ = 1;
                                                             this->current_index_ = 0;
                                                         }
                                                         else
                                                         {
                                                             this->current_index_++;
                                                         }
                                                         this->user_input_buffer_.clear(); // Очищаем поле ввода в любом случае
                                                     })});
};

ftxui::Component FillArrayView::buildResultView()
{

    auto result_button = ftxui::Button("OK", [this]
                                       {this->active_view_fill_array_ = 0; 
                                        this->call_back_(); });
    auto result_text = ftxui::Renderer([this]
                                       { return ftxui::vbox(
                                                    ftxui::text("The size of the array has been successfully changed to: " + std::to_string(new_value_)),
                                                    ftxui::separator()) |
                                                ftxui::border; });
    return ftxui::Container::Vertical({result_text,
                                       result_button});
};