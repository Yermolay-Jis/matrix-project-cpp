#include "ui/screens/array_operations/CreateArrayView.h"

CreateArrayView::CreateArrayView(std::shared_ptr<ArrayModel> model, std::function<void()> call_back) : array_model_(std::move(model)), call_back_(std::move(call_back))
{
    auto InputView = buildInputView();
    auto ResultView = buildResultView();

    create_array_component_ = ftxui::Container::Tab({InputView,
                                                     ResultView},
                                                    &active_view_create_array_);
};

ftxui::Component CreateArrayView::buildInputView()
{
    return ftxui::Container::Vertical({ftxui::Input(&user_input_buffer_, "Enter number here"), // Связываем поле ввода с нашим буфером
                                       ftxui::Button("Submit", [&]
                                                     {
                                                         try
                                                         {
                                                             new_size_ = std::stoi(user_input_buffer_);
                                                             array_model_->setCapacity(new_size_);
                                                             error_message_.clear();
                                                             active_view_create_array_ = 1;
                                                         }
                                                         catch (const std::exception &e)
                                                         {
                                                             // Если пользователь ввел не число:
                                                             error_message_ = "Invalid input. Must be a number.";
                                                             call_back_();
                                                         }
                                                         user_input_buffer_.clear(); // Очищаем поле ввода в любом случае
                                                     })});
};

ftxui::Component CreateArrayView::buildResultView()
{

    auto result_button = ftxui::Button("OK", [this]
                                       {active_view_create_array_ = 0; 
                                        call_back_(); });
    auto result_text = ftxui::Renderer([this]
                                       { return ftxui::vbox(
                                                    ftxui::text("The size of the array has been successfully changed to: " + std::to_string(new_size_)),
                                                    ftxui::separator()) |
                                                ftxui::border; });
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