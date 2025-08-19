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
    return fill_array_component_->Render();
};

void FillArrayView::OnEvent(ftxui::Event event)
{
    fill_array_component_->OnEvent(event);
};

ftxui::Component FillArrayView::GetFTXUIComponent()
{
    return fill_array_component_;
};

ftxui::Component FillArrayView::buildInputView()
{

    auto fill_array_content = ftxui::Renderer([&]
                                              {

         auto array = array_model_->getArray();
        std::stringstream ss;
        ss << "[";
        for (size_t i = 0; i < array_model_->getCapacity(); i++)
        {
            if (i < array.capacity())
                ss << array[i];



           if (i < array_model_->getCapacity() - 1) 
                ss << ", ";
        }
        ss << "]";

//  ftxui::text("Please, enter the number for current index --> " + std::to_string(current_index_));

        return ftxui::text("Current array: " + ss.str() + "   Current capacity: " + std::to_string(array.capacity()) + "   Current size: " + std::to_string(array.size())); });
    return ftxui::Container::Vertical({fill_array_content,
                                       ftxui::Input(&user_input_buffer_, "Enter number here"), // Связываем поле ввода с нашим буфером
                                       ftxui::Button("Submit", [this]
                                                     {
                                                         try
                                                         {
                                                             new_value_ = std::stoi(user_input_buffer_);
                                                         }
                                                         catch (const std::exception &e)
                                                         {
                                                             // Если пользователь ввел не число:
                                                             error_message_ = "Invalid input. Must be a number.";
                                                             call_back_();
                                                         }
                                                         array_model_->pushItem(new_value_);
                                                         error_message_.clear();
                                                         if (current_index_ >= array_model_->getCapacity() - 1)
                                                         {
                                                             active_view_fill_array_ = 1;
                                                             current_index_ = 0;
                                                         }
                                                         else
                                                         {
                                                             current_index_++;
                                                         }
                                                         user_input_buffer_.clear(); // Очищаем поле ввода в любом случае
                                                     })});
};

ftxui::Component FillArrayView::buildResultView()
{
    auto current_arr = ftxui::Renderer([&]
                                       {
        auto array = array_model_->getArray();
         std::stringstream ss;
        ss << "[ ";
        for (size_t i = 0; i < array_model_->getCapacity(); i++)
        {
            ss << array[i];
            if (i < array_model_->getCapacity() - 1)
            {
                ss << ", ";
            };
        };
        ss << " ]";
        return ftxui::text("Result array --> " + ss.str()) | ftxui::border; });

    auto result_button = ftxui::Button("OK", [this]
                                       {active_view_fill_array_ = 0; 
                                        call_back_(); });
    auto result_text = ftxui::Renderer([this]
                                       { return ftxui::vbox(
                                                    ftxui::text("The array with size " + std::to_string(array_model_->getCapacity()) + ", was succefully filled")) |
                                                ftxui::border; });
    return ftxui::Container::Vertical({result_text,
                                       current_arr,
                                       result_button});
};