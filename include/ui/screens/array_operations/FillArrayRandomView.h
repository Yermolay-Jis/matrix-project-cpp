#pragma once
#include "ui/UIComponent.h"
#include "array_logic/ArrayModel.h"
#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"
#include <functional>
#include <utility>

class FillArrayRandomView : public UIComponent
{
public:
    FillArrayRandomView(std::shared_ptr<ArrayModel> model, std::function<void()> call_back);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override { return true; };
    ftxui::Component GetFTXUIComponent() override;

private:
    ftxui::Component fill_array_random_component_;
    int active_view_fill_array_ = 0;

    std::shared_ptr<ArrayModel> array_model_;
    std::function<void()> call_back_;

    ftxui::Component buildResultView();
};