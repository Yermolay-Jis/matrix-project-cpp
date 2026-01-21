#include "ui/screens/array_operations/FillArrayView.h"

FillArrayView::FillArrayView(std::shared_ptr<std::map<std::string, ArrayModel>> model, std::function<void()> call_back) : models_(model), call_back_(call_back)
{
    auto input_name_view = buildInputNameView();
    auto input_view = buildInputView();
    auto result_view = buildResultView();
    fill_array_component_ = ftxui::Container::Tab({input_name_view,
                                                   input_view,
                                                   result_view},
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
                                                  auto array = models_->at(user_input_name_);
                                                  auto data = array.getArray();
                                                  std::stringstream ss;
                                                  ss << "[";
                                                  for (size_t i = 0; i < array.getCapacity(); i++)
                                                  {
                                                      if (i < data.capacity())
                                                          ss << data[i];

                                                      if (i < array.getCapacity() - 1)
                                                          ss << ", ";
                                                  }
                                                  ss << "]";

                                                  return ftxui::text("Current array: " + ss.str() + "   Current capacity: " + std::to_string(data.capacity()) + "   Current size: " + std::to_string(data.size())); });

    return ftxui::Container::Vertical({fill_array_content,
                                       ftxui::Input(&user_input_buffer_, "Enter number here"), // Связываем поле ввода с нашим буфером
                                       ftxui::Button("Submit", [this]
                                                     {
                                                         auto array = models_->at(user_input_name_);
                                                         auto data = array.getArray();
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
                                                         array.pushItem(new_value_);
                                                         error_message_.clear();
                                                         if (current_index_ >= array.getCapacity() - 1)
                                                         {
                                                             active_view_fill_array_ = 2;
                                                             current_index_ = 0;
                                                         }
                                                         else
                                                         {
                                                             current_index_++;
                                                         }
                                                         user_input_buffer_.clear(); // Очищаем поле ввода в любом случае
                                                     })

    });
};

ftxui::Component FillArrayView::buildResultView()
{

    auto current_arr = ftxui::Renderer([&]
                                       {
        auto &array = models_->at(user_input_name_);
        auto data = array.getArray();
         std::stringstream ss;
        ss << "[ ";
        for (size_t i = 0; i < array.getCapacity(); i++)
        {
            ss << data[i];
            if (i < array.getCapacity() - 1)
            {
                ss << ", ";
            };
        };
        ss << " ]";
        return ftxui::text("Result array --> " + ss.str()) | ftxui::border; });

    auto result_button = ftxui::Button("OK", [this]
                                       {active_view_fill_array_ = 0; 
                                        call_back_(); });
    auto result_text = ftxui::Renderer([&]
                                       {
                                        auto &array = models_->at(user_input_name_);
                                        auto data = array.getArray();
                                        return ftxui::vbox(
                                                    ftxui::text("The array with size " + std::to_string(array.getCapacity()) + ", was succefully filled")) |
                                                ftxui::border; });
    return ftxui::Container::Vertical({result_text,
                                       current_arr,
                                       result_button});
};

ftxui::Component FillArrayView::buildInputNameView()
{
    return ftxui::Container::Vertical({ftxui::Renderer([this]()
                                                       {
                                                           auto color_bg = is_error == true ? ftxui::bgcolor(ftxui::Color::Red1) : ftxui::bgcolor(ftxui::Color::White);
                                                           return ftxui::text(msg_) | color_bg; }),

                                       ftxui::Input(&user_input_name_, "The name of array is..."),

                                       ftxui::Button("Next", [this]()
                                                     {
                                                         auto it = models_->find(user_input_name_);
                                                         if (it == models_->end())
                                                         {
                                                             msg_ = "The array with name '" + user_input_name_ + "' is't exist. Please enter the correct name of array.";
                                                             is_error = true;
                                                             return;
                                                         }
                                                         msg_ = "Enter the name of array";
                                                         is_error = false;
                                                         active_view_fill_array_ = 1; })

    });
}