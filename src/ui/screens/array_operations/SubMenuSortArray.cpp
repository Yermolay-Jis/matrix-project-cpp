#include "ui/screens/array_operations/SubMenuSortArray.h"
#include "ui/components/InfoComponent.h"
#include "io/sorting/MergeSort.h"
#include <chrono>
#include <algorithm>

SubMenuSortArray::SubMenuSortArray(std::shared_ptr<std::map<std::string, ArrayModel>> model, std::function<void()> call_back) : models_(model), call_back_(call_back)
{
    auto inputNameView = buildInputNameView();
    auto subMenuSortArrayView = buildSubMenuSortArrayView();
    auto mergeSortView = buildMergeSortView();
    auto aboutComparisonSortView = buildAboutComparisonSortView();
    auto stlSortView = buildSTLSortView();
    auto comparisonSortView = buildComparisonSortView();

    sub_menu_sort_arr_componetnt_ = ftxui::Container::Tab({inputNameView,
                                                           subMenuSortArrayView,
                                                           mergeSortView,
                                                           stlSortView,
                                                           aboutComparisonSortView,
                                                           comparisonSortView},
                                                          &active_view_sort_arr_);
};

ftxui::Element SubMenuSortArray::Render()
{
    return sub_menu_sort_arr_componetnt_->Render();
};

void SubMenuSortArray::OnEvent(ftxui::Event event)
{
    sub_menu_sort_arr_componetnt_->OnEvent(event);
};

ftxui::Component SubMenuSortArray::GetFTXUIComponent()
{
    return sub_menu_sort_arr_componetnt_;
};

ftxui::Component SubMenuSortArray::buildSubMenuSortArrayView()
{
    return ftxui::Container::Vertical({

        ftxui::Renderer([this]
                        { return ftxui::text("Sort array") | ftxui::bold; }),

        ftxui::Button("Merge sort", [this]
                      { active_view_sort_arr_ = 2; }),

        ftxui::Button("STL sort", [this]
                      { active_view_sort_arr_ = 3; }),

        ftxui::Container::Horizontal({

            ftxui::Button("(?)", [this]
                          { active_view_sort_arr_ = 4; }),
            ftxui::Button("Approval of two sorts", [this]
                          { active_view_sort_arr_ = 5; })}),
        ftxui::Button("<-- Back", [this]
                      { call_back_(); })

    });
};

ftxui::Component SubMenuSortArray::buildMergeSortView()
{

    auto name_window = ftxui::Renderer([this]
                                       { return ftxui::text("Merge sort") | ftxui::bold; });

    auto current_array = ftxui::Renderer([&]
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

        return ftxui::text("Current array: " + ss.str() + " Current sorting time:  " + std::to_string(merge_sort_time_) + " ms"); });

    return ftxui::Container::Vertical({

        name_window,
        current_array,
        ftxui::Button("Sort", [&]
                      {
            auto array = models_->at(user_input_name_);
            auto data = array.getArray();
            auto array_sort = array.getArray();
            auto start = std::chrono::high_resolution_clock::now();
            array_sort = mergeSort(array_sort);
            auto end = std::chrono::high_resolution_clock::now();
            merge_sort_time_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            merge_sort_time_ /= 1000;
            for (size_t i = 0; i < array_sort.size(); i++)
            {
                array.setItemForIndex(i, array_sort[i]);
            } }),

        ftxui::Button("<-- Back", [this]
                      { active_view_sort_arr_ = 1; })});
};

ftxui::Component SubMenuSortArray::buildSTLSortView()
{

    auto name_window = ftxui::Renderer([this]
                                       { return ftxui::text("STL sort") | ftxui::bold; });

    auto current_array = ftxui::Renderer([&]
                                         {
        auto array = models_->at(user_input_name_);
        auto data = array.getArray();
        auto array_sort = array.getArray();
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

        return ftxui::text("Current array: " + ss.str() + " Current sorting time:  " + std::to_string(stl_sort_time_) + " ms"); });

    return ftxui::Container::Vertical({

        name_window,
        current_array,
        ftxui::Button("Sort", [&]
                      {
            auto array = models_->at(user_input_name_);
            auto data = array.getArray();
            auto array_sort = array.getArray();
            auto start = std::chrono::high_resolution_clock::now();
              std::sort(array_sort.begin(), array_sort.end());
            auto end = std::chrono::high_resolution_clock::now();
            stl_sort_time_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            stl_sort_time_ /= 1000;
            for (size_t i = 0; i < data.size(); i++)
            {
                array.setItemForIndex(i, data[i]);
            } }),

        ftxui::Button("<-- Back", [this]
                      { active_view_sort_arr_ = 1; })});
};

ftxui::Component SubMenuSortArray::buildAboutComparisonSortView()
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
                                                     { active_view_sort_arr_ = 1; })});
}

ftxui::Component SubMenuSortArray::buildComparisonSortView()
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
                                          for (size_t i = 0; i < merge_sort_array_.getCapacity(); i++)
                                          {
                                              if (i < merge_sort_array_.getCapacity())
                                                  ss << merge_sort_array_.getArray()[i];

                                              if (i < merge_sort_array_.getCapacity() - 1)
                                                  ss << ", ";
                                          }
                                          ss << "]";
                                          
                                          
                                          return ftxui::vbox({
                                            ftxui::text(ss.str()),
                                            ftxui::text("Merge sort time: " + std::to_string(merge_sort_time_) + " ms"),
                                            ftxui::separator(),
                                      }); });

    auto stl_sort = ftxui::Renderer([&]
                                    {
                                          std::stringstream ss;
                                          ss << "[";
                                          for (size_t i = 0; i < stl_sort_array_.getCapacity(); i++)
                                          {
                                              if (i < stl_sort_array_.getCapacity())
                                                  ss << stl_sort_array_.getArray()[i];

                                              if (i < stl_sort_array_.getCapacity() -  1)
                                                  ss << ", ";
                                          }
                                          ss << "]";
                                          
                                          
                                          return ftxui::vbox({
                                            ftxui::text(ss.str()),
                                            ftxui::text("STL sort time: " + std::to_string(stl_sort_time_) + " ms"),
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
                                                         auto merge_array = mergeSort(merge_sort_array_.getArray());
                                                         auto end_merge_sort = std::chrono::high_resolution_clock::now();
                                                         merge_sort_time_ = std::chrono::duration_cast<std::chrono::microseconds>(end_merge_sort - start_merge_sort).count();
                                                         merge_sort_time_ /= 100;
                                                        for (size_t i = 0; i < stl_sort_array_.getCapacity(); i++)
                                                        {
                                                             merge_sort_array_.setItemForIndex(i, merge_array[i]);
                                                        }

                                                         auto sort_array = stl_sort_array_.getArray();
                                                         auto start_stl_sort = std::chrono::high_resolution_clock::now();
                                                         std::sort(sort_array.begin(), sort_array.end());
                                                         auto end_stl_sort = std::chrono::high_resolution_clock::now();
                                                         stl_sort_time_ = std::chrono::duration_cast<std::chrono::microseconds>(end_stl_sort - start_stl_sort).count();
                                                         stl_sort_time_ /= 100;
                                                          for (size_t i = 0; i < stl_sort_array_.getCapacity(); i++)
                                                         {
                                                             stl_sort_array_.setItemForIndex(i, sort_array[i]);
                                                         } }),
                                       ftxui::Button("<-- Back", [&]
                                                     { active_view_sort_arr_ = 1; })});
};

ftxui::Component SubMenuSortArray::buildInputNameView()
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
                                                         merge_sort_array_ = models_->at(user_input_name_);
                                                         stl_sort_array_ = models_->at(user_input_name_);
                                                         active_view_sort_arr_ = 1; })

    });
}