#include "ui/screens/array_operations/CreateArrayView.h"

CreateArrayView::CreateArrayView(std::shared_ptr<std::map<std::string, ArrayModel>> model, std::function<void()> call_back) : models_(model), call_back_(call_back)
{
    auto InputView = buildInputView();
    auto ResultView = buildResultView();

    create_array_component_ = ftxui::Container::Tab({InputView,
                                                     ResultView},
                                                    &active_view_create_array_);
};

ftxui::Component CreateArrayView::buildInputView()
{
    return ftxui::Container::Vertical({

        ftxui::Renderer([]()
                        { return ftxui::text("Name of array"); }),
        ftxui::Input(&user_input_name_, "Name array is..."),
        ftxui::Renderer([]()
                        { return ftxui::text("Size of the array"); }),
        ftxui::Input(&user_input_buffer_, "Size array is..."), // Связываем поле ввода с нашим буфером
        ftxui::Button("Submit", [this]
                      {
                          try
                          {
                              new_name_ = user_input_name_;
                              new_size_ = std::stoi(user_input_buffer_);
                              ArrayModel array;
                              array.setSize(new_size_);
                              models_->insert({new_name_, array});
                              error_message_.clear();
                              active_view_create_array_ = 1;
                          }
                          catch (const std::exception &e)
                          {
                              // Если пользователь ввел не число:
                              error_message_ = e.what();
                              call_back_();
                          }
                          user_input_buffer_.clear(); // Очищаем поле ввода в любом случае
                      })});
};

ftxui::Component CreateArrayView::buildResultView()
{

    auto result_button = ftxui::Button("OK", [this]
                                       {
                                        auto array = models_->at(new_name_);                                        
                                        active_view_create_array_ = 0; 
                                        call_back_(); });

    auto result_text = ftxui::Renderer([this]()
                                       {
                                        
                                        auto result_array = [this]()
                                        {
                                            std::string result = "";
                                            auto array = models_->at(new_name_);
                                            auto data = array.getArray();
                                            for (size_t i = 0; i < new_size_; i++)
                                            {
                                                result += std::to_string(data[i]);
                                                if (i < new_size_ - 1)
                                                    result += ", ";
                                            }
                                            return result;
                                        };
                                        std::string arr_text = "Result array: [ " + result_array() + " ]";
                                        return ftxui::vbox(
                                             ftxui::text("The name: " + new_name_),
                                             ftxui::separator(),
                                             ftxui::text("The size: " + std::to_string(new_size_)),
                                             ftxui::text(arr_text)); });
    return ftxui::Container::Vertical({result_text,
                                       result_button});
};

ftxui::Element CreateArrayView::Render()
{
    return create_array_component_->Render();
};

void CreateArrayView::OnEvent(ftxui::Event event)
{
    create_array_component_->OnEvent(event);
};

ftxui::Component CreateArrayView::GetFTXUIComponent()
{
    return create_array_component_;
}