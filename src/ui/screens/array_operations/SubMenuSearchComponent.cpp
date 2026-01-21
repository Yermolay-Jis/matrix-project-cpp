#include "ui/screens/array_operations/SubMenuSearchComponent.h"
#include "ui/components/InfoComponent.h"
#include "io/sorting/MergeSort.h"
#include <chrono>
#include <algorithm>

SubMenuSearchComponent::SubMenuSearchComponent(std::shared_ptr<std::map<std::string, ArrayModel>> model, std::function<void()> call_back) : models_(model), call_back_(call_back)
{
    auto inputNameView = buildInputNameView();
    auto subMenuSearchComponentView = buildSubMenuSearchComponent();
    auto binarySearchView = buildBinarySearchView();
    auto linearSearchView = buildLinearSearchView();
    auto aboutComparisonSearchView = buildAboutComparisonSearchView();
    auto comparisonSearchView = buildComparisonSearchView();

    sub_menu_search_arr_component_ = ftxui::Container::Tab({inputNameView,
                                                            subMenuSearchComponentView,
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
                      { active_view_search_arr_ = 2; }),

        ftxui::Button("Linear search", [this]
                      { active_view_search_arr_ = 3; }),

        ftxui::Container::Horizontal({

            ftxui::Button("(?)", [this]
                          { active_view_search_arr_ = 4; }),
            ftxui::Button("Approval of two search", [this]
                          { active_view_search_arr_ = 5; })

        }),
        ftxui::Button("<-- Back", [this]
                      { call_back_(); })

    });
};

ftxui::Component SubMenuSearchComponent::buildBinarySearchView()
{

    auto name_window = ftxui::Renderer([this]
                                       { return ftxui::vbox({ftxui::text("Binary search") | ftxui::bold,
                                                             ftxui::separator()}); });

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
                                    ftxui::paragraph(R"(Time of completing --> )" + std::to_string(binary_search_time_) + " us"),
                                    ftxui::separator()});
            }
            else
            {
                return ftxui::vbox({ftxui::separator(),
                                    ftxui::text("The user number " + last_value_+ " is unfined!"),
                                    ftxui::paragraph(R"(Time of completing --> )" + std::to_string(binary_search_time_) + " us"),
                                    ftxui::separator()

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
                                                        auto array = models_->at(user_input_name_);
                                                        auto data = array.getArray();
                                                         try
                                                         {
                                                            auto array_search = array.getArray();
                                                            int value = std::stoi(user_input_buffer_);
                                                            if (!std::is_sorted(array_search.begin(), array_search.end())) {
                                                                std::sort(array_search.begin(), array_search.end());                                                           
                                                            }
                                                             
                                                            auto start = std::chrono::high_resolution_clock::now();
                                                            is_search_ = std::binary_search(array_search.begin(), array_search.end(), value);
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
                                                        active_view_search_arr_ = 1; })});
};

ftxui::Component SubMenuSearchComponent::buildLinearSearchView()
{

    auto name_window = ftxui::Renderer([this]
                                       { return ftxui::vbox({ftxui::text("Linear search") | ftxui::bold,
                                                             ftxui::separator()}); });

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

        return ftxui::vbox({
                    ftxui::text("Current array: " + ss.str()),
                    ftxui::separator()
        }); });

    auto message = ftxui::Renderer([this]
                                   {
         if (search_perfomed_)
        {
            if (is_search_)
            {
                return ftxui::vbox({ftxui::separator(),
                                    ftxui::text("The user number " + last_value_+ " succesfully searched!"),
                                    ftxui::paragraph(R"(Time of completing --> )" + std::to_string(linear_search_time_) + " us"),
                                    ftxui::separator()});
            }
            else
            {
                return ftxui::vbox({ftxui::separator(),
                                    ftxui::text("The user number " + last_value_+ " is unfined!"),
                                    ftxui::paragraph(R"(Time of completing --> )" + std::to_string(linear_search_time_) + " us"),
                                    ftxui::separator()

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
                                                        auto array = models_->at(user_input_name_);
                                                        auto data = array.getArray();
                                                         try
                                                         {
                                                            auto array_search = array.getArray();
                                                            int value = std::stoi(user_input_buffer_);
                                                             
                                                            auto start = std::chrono::high_resolution_clock::now();
                                                            auto searched_it = std::find(array_search.begin(), array_search.end(), value);
                                                            auto end = std::chrono::high_resolution_clock::now();

                                                            if (searched_it != array_search.end())
                                                            {
                                                                is_search_ = true;
                                                            }else {
                                                                is_search_ = false;
                                                            };

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
                                                        active_view_search_arr_ = 1; })});
};

ftxui::Component SubMenuSearchComponent::buildAboutComparisonSearchView()
{
    auto Title = ftxui::Renderer([]
                                 { return ftxui::vbox({ftxui::text("About comparison sort") | ftxui::bold,
                                                       ftxui::separator()}); });
    auto Content = ftxui::Renderer([]
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
                                                     { active_view_search_arr_ = 1; })});
}

ftxui::Component SubMenuSearchComponent::buildComparisonSearchView()
{

    auto title = ftxui::Renderer([]
                                 { return ftxui::vbox({

                                       ftxui::text("Comparison search") | ftxui::bold,
                                       ftxui::separator(),
                                   }); });

    auto binary_search = ftxui::Renderer([&]
                                         {  
                                        auto array = models_->at(user_input_name_);
                                        auto data = array.getArray();
                                          std::stringstream ss;
                                          ss << "[";
                                          for (size_t i = 0; i < array.getCapacity(); i++)
                                          {
                                              if (i <array.getCapacity())
                                                  ss << array.getArray()[i];

                                              if (i <array.getCapacity() - 1)
                                                  ss << ", ";
                                          }
                                          ss << "]";
                                          
                                          
                                          return ftxui::vbox({
                                            ftxui::text(ss.str()),
                                            ftxui::text("Binary search time: " + std::to_string(binary_search_time_) + " us"),
                                            ftxui::separator(),
                                      }); });

    auto linear_search = ftxui::Renderer([&]
                                         { return ftxui::vbox({
                                               ftxui::text("Linear search time: " + std::to_string(linear_search_time_) + " us"),
                                           }); });

    auto data_process = ftxui::Renderer([&]
                                        {
        if (search_perfomed_)
        {
            if (is_search_)
            {
                return ftxui::vbox({ftxui::separator(),
                                    ftxui::text("The user number " + last_value_+ " succesfully searched!"),
                                    ftxui::separator()});
            }
            else
            {
                return ftxui::vbox({ftxui::separator(),
                                    ftxui::text("The user number " + last_value_+ " is unfined!"),
                                    ftxui::separator()

                });
            }
        } else {
            return ftxui::vbox({
                                    ftxui::separator(),
                                    ftxui::text("..."),
                                    ftxui::separator()
            });
        } });

    return ftxui::Container::Vertical({title,
                                       binary_search,
                                       linear_search,
                                       data_process,
                                       ftxui::Input(&user_input_buffer_, "Enter value for searching..."),
                                       ftxui::Button("Measure", [&]
                                                     {
                                                        auto array = models_->at(user_input_name_);
                                                        auto data = array.getArray();
                                                         try
                                                         {
                                                             int value = std::stoi(user_input_buffer_);
                                                             auto binary_search_array = array.getArray();

                                                            
                                                             if (!std::is_sorted(binary_search_array.begin(), binary_search_array.end())){
                                                                std::sort(binary_search_array.begin(), binary_search_array.end());
                                                             }
                                                             auto start_binary_search = std::chrono::high_resolution_clock::now();
                                                             is_search_ = std::binary_search(binary_search_array.begin(), binary_search_array.end(), value);
                                                             auto end_binary_search = std::chrono::high_resolution_clock::now();
                                                             binary_search_time_ = std::chrono::duration_cast<std::chrono::microseconds>(end_binary_search - start_binary_search).count();

                                                             auto linear_search_array = array.getArray();
                                                             auto start_linear_search = std::chrono::high_resolution_clock::now();
                                                             std::find(linear_search_array.begin(), linear_search_array.end(), value);
                                                             auto end_linear_search = std::chrono::high_resolution_clock::now();

                                                             linear_search_time_ = std::chrono::duration_cast<std::chrono::microseconds>(end_linear_search - start_linear_search).count();
                                                             search_perfomed_ = true;
                                                             last_value_ = user_input_buffer_;
                                                         }
                                                         catch (const std::exception &e)
                                                         {
                                                             error_message_ = e.what();
                                                         };
                                                         user_input_buffer_.clear(); }),
                                       ftxui::Button("<-- Back", [&]
                                                     { active_view_search_arr_ = 1; 
                                                        search_perfomed_ = false;
                                                        user_input_buffer_.clear(); })});
};

ftxui::Component SubMenuSearchComponent::buildInputNameView()
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
                                                         active_view_search_arr_ = 1; })

    });
}