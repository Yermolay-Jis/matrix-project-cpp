#include "ui/screens/array_operations/SubMenuSearchComponent.h"
#include "ui/components/InfoComponent.h"
#include "io/sorting/MergeSort.h"
#include <chrono>
#include <algorithm>

SubMenuSearchComponent::SubMenuSearchComponent(std::shared_ptr<ArrayModel> model, std::function<void()> call_back) : array_model_(std::move(model)), call_back_(std::move(call_back))
{
    auto subMenuSearchComponent = buildSubMenuSearchComponent();
    auto binarySearchView = buildBinarySearchView();
    auto linearSearchView = buildLinearSearchView();
    auto aboutComparisonSearchView = buildAboutComparisonSearchView();
    auto comparisonSearchView = buildComparisonSearchView();

    sub_menu_search_arr_component_ = ftxui::Container::Tab({subMenuSearchComponent,
                                                            binarySearchView,
                                                            linearSearchView,
                                                            aboutComparisonSearchView,
                                                            comparisonSearchView},
                                                           &active_view_search_arr_);
};

ftxui::Element SubMenuSearchComponent::Render()
{
    return sub_menu_search_arr_component_->Render();
};

void SubMenuSearchComponent::OnEvent(ftxui::Event event)
{
    sub_menu_search_arr_component_->OnEvent(event);
};

ftxui::Component SubMenuSearchComponent::GetFTXUIComponent()
{
    return sub_menu_search_arr_component_;
};

ftxui::Component SubMenuSearchComponent::buildSubMenuSearchComponent()
{
    return ftxui::Container::Vertical({

        ftxui::Renderer([this]
                        { return ftxui::text("Search elements in array") | ftxui::bold; }),

        ftxui::Button("Binary search", [this]
                      { active_view_search_arr_ = 1; }),

        ftxui::Button("Linear search", [this]
                      { active_view_search_arr_ = 2; }),

        ftxui::Container::Horizontal({

            ftxui::Button("(?)", [=]
                          { active_view_search_arr_ = 3; }),
            ftxui::Button("Approval of two search", [this]
                          { active_view_search_arr_ = 4; })

        }),
        ftxui::Button("<-- Back", [this]
                      { call_back_(); })

    });
};

ftxui::Component SubMenuSearchComponent::buildBinarySearchView()
{

    auto name_window = ftxui::Renderer([this]
                                       { return ftxui::vbox({ftxui::text("Merge sort") | ftxui::bold,
                                                             ftxui::separator()}); });

    auto current_array = ftxui::Renderer([this]
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

        return ftxui::vbox({
                    ftxui::text("Current array: " + ss.str()),
                    ftxui::separator()
        }); });

    auto message = ftxui::Renderer([&]
                                   {
        if (search_perfomed_)
        {
            if (is_search_)
            {
                return ftxui::vbox({ftxui::separator(),
                                    ftxui::text("The user number " + last_value_+ " succesfully searched!"),
                                    ftxui::paragraph(R"(   Time of completing --> )" + std::to_string(binary_search_time_) + " us")});
            }
            else
            {
                return ftxui::vbox({ftxui::separator(),
                                    ftxui::text("The user number " + last_value_+ " is unfined!"),
                                    ftxui::paragraph(R"(Time of completing --> )" + std::to_string(binary_search_time_) + " us")

                });
            }
        } else {
            return ftxui::vbox({
                                    ftxui::separator(),
                                    ftxui::text("..."),
                                    ftxui::separator()
            });
        } });

    return ftxui::Container::Vertical({name_window,
                                       current_array,
                                       message,
                                       ftxui::Input(&user_input_buffer_, "Enter the element for searching here"),
                                       ftxui::Button("Search", [&]
                                                     {
                                                         try
                                                         {
                                                            auto array = array_model_->getArray();
                                                            int value = std::stoi(user_input_buffer_);
                                                            if (!std::is_sorted(array.begin(), array.end())) {
                                                                std::sort(array.begin(), array.end());                                                           
                                                            }
                                                             
                                                            auto start = std::chrono::high_resolution_clock::now();
                                                            is_search_ = std::binary_search(array.begin(), array.end(), value);
                                                            auto end = std::chrono::high_resolution_clock::now();

                                                            last_value_ = user_input_buffer_;
                                                            search_perfomed_ = true;
                                                            binary_search_time_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
                                                         }
                                                         catch (const std::exception &e)
                                                         {
                                                             error_message_ = e.what();
                                                         };
                                                        user_input_buffer_.clear(); }),

                                       ftxui::Button("<-- Back", [this]
                                                     { 
                                                        search_perfomed_ = false;
                                                        user_input_buffer_.clear();
                                                        active_view_search_arr_ = 0; })});
};

ftxui::Component SubMenuSearchComponent::buildLinearSearchView()
{
    auto name_window = ftxui::Renderer([this]
                                       { return ftxui::text("STL sort") | ftxui::bold; });

    auto current_array = ftxui::Renderer([this]
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

        return ftxui::text("Current array: " + ss.str() + " Current sorting time:  " + std::to_string(linear_search_time_) + " ms"); });

    return ftxui::Container::Vertical({

        name_window,
        current_array,
        ftxui::Button("Sort", [&]
                      {
            auto array = array_model_->getArray();
            auto start = std::chrono::high_resolution_clock::now();
              std::sort(array.begin(), array.end());
            auto end = std::chrono::high_resolution_clock::now();
            linear_search_time_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            linear_search_time_ /= 1000;
            for (size_t i = 0; i < array.size(); i++)
            {
                array_model_->setItemForIndex(i, array[i]);
            } }),

        ftxui::Button("<-- Back", [this]
                      { active_view_search_arr_ = 0; })});
};

ftxui::Component SubMenuSearchComponent::buildAboutComparisonSearchView()
{
    auto Title = ftxui::Renderer([this]
                                 { return ftxui::vbox({ftxui::text("About comparison sort") | ftxui::bold,
                                                       ftxui::separator()}); });
    auto Content = ftxui::Renderer([this]
                                   { return ftxui::vbox({ftxui::text("This section provides a practical performance analysis by benchmarking a custom algorithm implementation against the C++ standard library's baseline."),
                                                         ftxui::text(""),
                                                         ftxui::text("* Algorithms Under Test :"),

                                                         ftxui::text(""),
                                                         ftxui::text("Merge Sort : A custom implementation of the Merge Sort algorithm, known for its stable, predictable O(n log n) time complexity."),

                                                         //  ftxui::text(""),
                                                         ftxui::text("std::sort : The C ++ Standard Library's sort function. This is typically a hybrid algorithm called Introsort, which combines the strengths of Quicksort, Heapsort,  and Insertion Sort to offer excellent average - case performance and avoid worst - case scenarios."),

                                                         ftxui::text(""),
                                                         ftxui::text("* Key Metrics for Comparison :"),

                                                         ftxui::text(""),
                                                         ftxui::text("Execution Time : The wall - clock time required for each algorithm to completely sort the array.This is the most direct measure of performance."),

                                                         ftxui::text(""),
                                                         ftxui::text("* Memory Usage :"),

                                                         ftxui::text(""),
                                                         ftxui::text("While Merge Sort requires O(n) auxiliary space for its merging process,"),
                                                         ftxui::text("std::sort is largely an in - place sort, using O(log n) stack space. Highlighting this difference shows a great understanding of space complexity."),

                                                         ftxui::text(""),
                                                         ftxui::text("* Expected Outcome :"),

                                                         ftxui::text(""),
                                                         ftxui::text("You will likely observe that std::sort is significantly faster.This exercise serves to demonstrate the powerful optimizations present in standard libraries and"),
                                                         ftxui::text("provides a tangible measure of your own implementation's performance."),
                                                         ftxui::separator()}); });
    return ftxui::Container::Vertical({Title,
                                       Content,
                                       ftxui::Button("<-- Back", [this]
                                                     { active_view_search_arr_ = 0; })});
}

ftxui::Component SubMenuSearchComponent::buildComparisonSearchView()
{
    auto title = ftxui::Renderer([&]
                                 { return ftxui::vbox({

                                       ftxui::text("Comparison sort") | ftxui::bold,
                                       ftxui::separator(),
                                   }); });

    auto merge_sort = ftxui::Renderer([&]
                                      {  
                                          std::stringstream ss;
                                          ss << "[";
                                          for (size_t i = 0; i < array_model_->getCapacity(); i++)
                                          {
                                              if (i < array_model_->getCapacity())
                                                  ss << array_model_->getArray()[i];

                                              if (i < array_model_->getCapacity() - 1)
                                                  ss << ", ";
                                          }
                                          ss << "]";
                                          
                                          
                                          return ftxui::vbox({
                                            ftxui::text(ss.str()),
                                            ftxui::text("Merge sort time: " + std::to_string(binary_search_time_) + " ms"),
                                            ftxui::separator(),
                                      }); });

    auto stl_sort = ftxui::Renderer([&]
                                    {
                                          std::stringstream ss;
                                          ss << "[";
                                          for (size_t i = 0; i < array_model_->getCapacity(); i++)
                                          {
                                              if (i < array_model_->getCapacity())
                                                  ss << array_model_->getArray()[i];

                                              if (i < array_model_->getCapacity() -  1)
                                                  ss << ", ";
                                          }
                                          ss << "]";
                                          
                                          
                                          return ftxui::vbox({
                                            ftxui::text(ss.str()),
                                            ftxui::text("STL sort time: " + std::to_string(linear_search_time_) + " ms"),
                                      }); });

    auto separator = ftxui::Renderer([&]
                                     { return ftxui::separator(); });

    return ftxui::Container::Vertical({title,
                                       merge_sort,
                                       separator,
                                       stl_sort,
                                       separator,
                                       ftxui::Button("Measure", [&]
                                                     {
                                                         auto start_merge_sort = std::chrono::high_resolution_clock::now();
                                                         auto merge_array = mergeSort(array_model_->getArray());
                                                         auto end_merge_sort = std::chrono::high_resolution_clock::now();
                                                         binary_search_time_= std::chrono::duration_cast<std::chrono::microseconds>(end_merge_sort - start_merge_sort).count();
                                                         binary_search_time_/= 100;
                                                        for (size_t i = 0; i < array_model_->getCapacity(); i++)
                                                        {
                                                             array_model_->setItemForIndex(i, merge_array[i]);
                                                        }

                                                         auto sort_array = array_model_->getArray();
                                                         auto start_stl_sort = std::chrono::high_resolution_clock::now();
                                                         std::sort(sort_array.begin(), sort_array.end());
                                                         auto end_stl_sort = std::chrono::high_resolution_clock::now();
                                                         linear_search_time_ = std::chrono::duration_cast<std::chrono::microseconds>(end_stl_sort - start_stl_sort).count();
                                                         linear_search_time_ /= 100;
                                                          for (size_t i = 0; i < array_model_->getCapacity(); i++)
                                                         {
                                                             array_model_->setItemForIndex(i, sort_array[i]);
                                                         } }),
                                       ftxui::Button("<-- Back", [&]
                                                     { active_view_search_arr_ = 0; })});
};
