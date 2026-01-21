#include "ui/screens/array_operations/ShowLibraryArrayView.h"
#include <iomanip>

ShowLibraryArrayView::ShowLibraryArrayView(std::shared_ptr<std::map<std::string, ArrayModel>> model, std::function<void()> call_back) : models_(model), call_back_(call_back)
{
    auto showArrayWindow = buildShowLibraryArrayView();

    show_array_component_ = ftxui::Container::Tab({showArrayWindow}, &active_view_show_array_);
};

ftxui::Element ShowLibraryArrayView::Render()
{
    return show_array_component_->Render();
};

void ShowLibraryArrayView::OnEvent(ftxui::Event event)
{
    show_array_component_->OnEvent(event);
};

ftxui::Component ShowLibraryArrayView::GetFTXUIComponent()
{
    return show_array_component_;
};

ftxui::Component ShowLibraryArrayView::buildShowLibraryArrayView()
{
    auto library_array = ftxui::Renderer([this]()
                                         {
                                            std::vector<ftxui::Element> rows;
                                            const int w_num = 20;
                                            const int w_name = 20; 
                                            const int w_size = 20;
                                            const int w_data = 40;
                                            std::stringstream ss_header;


                                            ss_header << std::left << std::setw(w_num) << "Number" <<  std::setw(w_name) << "Name" << std::setw(w_size) << "Size" << std::setw(w_data)  << "Data";
                                            ftxui::Element header = ftxui::vbox({
                                                ftxui::text(ss_header.str()), 
                                                ftxui::separator(),
                                            });
                                            rows.push_back(header);

                                             size_t number = 1;
                                             for (const auto& [name, array] : *models_)
                                             {
                                                std::stringstream ss;
                                                 ss << std::left << std::setw(w_num) << number <<  std::setw(w_name) << name << std::setw(w_size) << array.getSize() <<  "[ ";
                                                 for (size_t i = 0; i < array.getSize(); i++)
                                                 {
                                                     std::vector<int> data = array.getArray();
                                                     ss << data[i];
                                                     if (i < array.getSize() - 1)
                                                         ss << ", ";
                                                 }
                                                 ss << "]";
                                                 number++;
                                                 ftxui::Element line = ftxui::text(ss.str());
                                                 rows.push_back(line);
                                             }

                                             return ftxui::vbox({

                                                 ftxui::separator(),
                                                 ftxui::vbox(std::move(rows)),
                                                 ftxui::separator()}); });

    return ftxui::Container::Vertical({

        library_array,
        ftxui::Button("<-- Back", [this]
                      { error_message_.clear();
                        call_back_(); })

    });
}