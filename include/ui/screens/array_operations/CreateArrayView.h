#pragma once
#ifndef CREATE_ARRAY_VIEW_H_
#define CREATE_ARRAY_VIEW_H_

#include "ftxui/component/component.hpp"
#include "ftxui/dom/elements.hpp"
#include "ui/UIComponent.h"
#include "array_logic/ArrayModel.h"

class CreateArrayView : public UIComponent
{
public:
    CreateArrayView(std::shared_ptr<ArrayModel> model, std::function<void()> call_back);
    ftxui::Element Render() override;
    void OnEvent(ftxui::Event event) override;
    bool IsSelectable() override { return true; };
    ftxui::Component GetFTXUIComponent() override;

private:
    ftxui::Component create_array_component_;
    int active_view_create_array_ = 0;
    std::string user_input_buffer_;
    size_t new_size_ = 0;
    std::string error_message_;
    std::shared_ptr<ArrayModel> array_model_;

    std::function<void()> call_back_;

    ftxui::Component buildInputView();
    ftxui::Component buildResultView();
};

#endif