#include "ui/screens/array_operations/SubMenuSortArray.h"
#include "ui/components/InfoComponent.h"
#include "io/sorting/MergeSort.h"
#include <chrono>
#include <algorithm>

SubMenuSortArray::SubMenuSortArray(std::shared_ptr<ArrayModel> model, std::function<void()> call_back) : array_model_(std::move(model)), call_back_(std::move(call_back))
{
    auto subMenuSortArrayView = buildSubMenuSortArrayView();
    auto mergeSortView = buildMergeSortView();

    auto stlSortView = buildSTLSortView();

    // auto comparisonSortView = buildComparisonSortView();

    sub_menu_sort_arr_componetnt_ = ftxui::Container::Tab({
                                                              subMenuSortArrayView,
                                                              mergeSortView,
                                                              stlSortView,
                                                              //    comparisonSortView
                                                          },
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
                      { active_view_sort_arr_ = 1; }),

        ftxui::Button("STL sort", [this]
                      { active_view_sort_arr_ = 2; }),

        ftxui::Container::Horizontal({

            ftxui::Button("(?)", [=]
                          {
                                std::string taskTitle = "Task:";
                                std::string taskContent = "An array of numbers is given from x_1 to x_n.\nFind the sum elements fr";
                                auto infoWindow = std::make_shared<InfoComponent>(taskTitle, taskContent, call_back_); }),
            ftxui::Button("Approval of two sorts", [this] {})

        }),
        ftxui::Button("<-- Back", [this]
                      { call_back_(); })

    });
};

ftxui::Component SubMenuSortArray::buildMergeSortView()
{
    auto name_window = ftxui::Renderer([this]
                                       { return ftxui::text("Merge sort") | ftxui::bold; });

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

        return ftxui::text("Current array: " + ss.str() + " Current sorting time:  " + std::to_string(sorting_time_) + " ms"); });

    return ftxui::Container::Vertical({

        name_window,
        current_array,
        ftxui::Button("Sort", [&]
                      {
            auto array = array_model_->getArray();
            auto start = std::chrono::high_resolution_clock::now();
            //   std::sort(array.begin(), array.end());
            array = mergeSort(array);
            auto end = std::chrono::high_resolution_clock::now();
            sorting_time_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            sorting_time_ /= 1000;
            for (size_t i = 0; i < array.size(); i++)
            {
                array_model_->setItemForIndex(i, array[i]);
            } }),

        ftxui::Button("<-- Back", [this]
                      { active_view_sort_arr_ = 0; })});
};

ftxui::Component SubMenuSortArray::buildSTLSortView()
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

        return ftxui::text("Current array: " + ss.str() + " Current sorting time:  " + std::to_string(sorting_time_) + " ms"); });

    return ftxui::Container::Vertical({

        name_window,
        current_array,
        ftxui::Button("Sort", [&]
                      {
            auto array = array_model_->getArray();
            auto start = std::chrono::high_resolution_clock::now();
              std::sort(array.begin(), array.end());
            auto end = std::chrono::high_resolution_clock::now();
            sorting_time_ = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            sorting_time_ /= 1000;
            for (size_t i = 0; i < array.size(); i++)
            {
                array_model_->setItemForIndex(i, array[i]);
            } }),

        ftxui::Button("<-- Back", [this]
                      { active_view_sort_arr_ = 0; })});
};

// ftxui::Component SubMenuSortArray::buildComparisonSortView() {};
