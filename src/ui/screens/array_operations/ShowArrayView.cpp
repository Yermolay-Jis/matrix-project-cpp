#include "ui/screens/array_operations/ShowArrayView.h"

ShowArrayView::ShowArrayView(std::shared_ptr<ArrayModel> model, std::function<void()> call_back) : array_model_(std::move(model)), call_back_(std::move(call_back))
{
    auto showArrayWindow = buildShowArrayView();

    show_array_component_ = ftxui::Container::Tab({showArrayWindow}, &active_view_show_array_);
};

ftxui::Element ShowArrayView::Render()
{
    return this->show_array_component_->Render();
};

void ShowArrayView::OnEvent(ftxui::Event event)
{
    this->show_array_component_->OnEvent(event);
};

ftxui::Component ShowArrayView::GetFTXUIComponent()
{
    return this->show_array_component_;
};

ftxui::Component ShowArrayView::buildShowArrayView()
{
    return ftxui::Container::Vertical({

        ftxui::Renderer([this]
                        {
                            auto array = array_model_->getArray();
                            std::stringstream ss;
                            ss << "[ ";
                            for (size_t i = 0; i < array.capacity(); i++)
                            {

                                if (i < array.capacity())
                                    ss << array[i];
                                if (i < array.capacity() - 1)
                                    ss << ", ";
                            }
                            ss << " ]";
                            return ftxui::text("Current array -->" + ss.str()) | ftxui::border | ftxui::bold; }),
        ftxui::Renderer([this]
                        { return ftxui::text("Current capacity --> " + std::to_string(array_model_->getCapacity())) | ftxui::border | ftxui::bold; }),
        ftxui::Renderer([this]
                        {
                            auto array = array_model_->getArray();
                            return ftxui::text("Current size --> " + std::to_string(array.size()))| ftxui::border | ftxui::bold; }),
        ftxui::Button("Ok", [&]
                      { error_message_.clear();
                        call_back_(); })

    });
}