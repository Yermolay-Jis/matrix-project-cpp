#include "ui/screens/array_operations/FillArrayRandomView.h"
#include "array_logic/ArrayAutoFiller.h"
#include <string>

FillArrayRandomView::FillArrayRandomView(std::shared_ptr<std::map<std::string, ArrayModel>> model, std::function<void()> call_back) : models_(model), call_back_(call_back)
{
    auto result_view = buildResultView();

    auto input_name = buildInputNameView();

    fill_array_random_component_ = ftxui::Container::Tab({input_name,
                                                          result_view},
                                                         &active_view_fill_array_);
};

ftxui::Element FillArrayRandomView::Render()
{
    return fill_array_random_component_->Render();
};

void FillArrayRandomView::OnEvent(ftxui::Event event)
{
    fill_array_random_component_->OnEvent(event);
};

ftxui::Component FillArrayRandomView::GetFTXUIComponent()
{
    return fill_array_random_component_;
};

ftxui::Component FillArrayRandomView::buildResultView()
{
    return ftxui::Container::Vertical({ftxui::Renderer([this]
                                                       {
                            auto &array = models_->at(user_input_name_);
                            auto data = array.getArray();
                            std::stringstream ss;
                            ss << "[";
                            for (size_t i = 0; i < array.getSize(); i++)
                            {
                                if (i < array.getSize())
                                    ss << data[i];

                                if (i < array.getSize() - 1)
                                    ss << ", ";
                            }
                            ss << "]";

                            return ftxui::text("Current array: " + ss.str() + "   Current capacity: " + std::to_string(data.capacity()) + "   Current size: " + std::to_string(data.size())); }),
                                       ftxui::Container::Horizontal({
                                           ftxui::Button("Generate a new one", [this]
                                                         {
                              ArrayAutoFiller filler(0, 100);
                              auto &array = models_->at(user_input_name_);
                              filler.autoFill(array); }),

                                           ftxui::Button("Save", [this]
                                                         { call_back_(); }),

                                       })});
}

ftxui::Component FillArrayRandomView::buildInputNameView()
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