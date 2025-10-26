#include "ui/screens/array_operations/FillArrayRandomView.h"
#include "array_logic/ArrayAutoFiller.h"
#include <string>

FillArrayRandomView::FillArrayRandomView(std::shared_ptr<ArrayModel> model, std::function<void()> call_back) : array_model_(std::move(model)), call_back_(std::move(call_back))
{
    auto resultView = buildResultView();

    fill_array_random_component_ = ftxui::Container::Tab({resultView}, &active_view_fill_array_);
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
    return ftxui::Container::Vertical({

        ftxui::Renderer([this]
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

                            return ftxui::text("Current array: " + ss.str() + "   Current capacity: " + std::to_string(array.capacity()) + "   Current size: " + std::to_string(array.size())); }),

        ftxui::Container::Horizontal({

            ftxui::Button("Generate a new one", [this]
                          {
                                                ArrayAutoFiller filler(0, 100);
                                                filler.autoFill(array_model_); }),

            ftxui::Button("Save", [this]
                          { call_back_(); }),

        })

    });
}