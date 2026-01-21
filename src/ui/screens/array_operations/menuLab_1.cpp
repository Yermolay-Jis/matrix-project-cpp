#include "ui/screens/array_operations/menuLab_1.h"
#include "ui/components/InfoComponent.h"
#include "array_logic/ArrayModel.h"
#include "io/portable_io.h"
#include "ui/screens/array_operations/CreateArrayView.h"
#include "ui/screens/array_operations/ShowLibraryArrayView.h"
#include "ui/screens/array_operations/FillArrayView.h"
#include <string>
#include <functional>
#include <utility>
#include <algorithm>

char separate = ',';
size_t sizeArr = 10;
double *arr = new double[sizeArr];

MenuLab_1::MenuLab_1(std::function<void()> navigateBack)
{
	models_ = std::make_shared<std::map<std::string, ArrayModel>>();

	auto main_menu_view = buildMainMenuView(navigateBack);

	auto create_array_view = buildCreateArrayView();

	auto fill_array_view = buildFillArrayView();

	auto fill_array_random_view = buildFillArrayRandomView();

	auto show_library_array = buildShowLibraryArrayView();

	auto sub_menu_sort_array_view = buildSubMenuSortArrayView();

	auto sub_menu_search_component_view = buildSubMenuSearchComponentView();

	component_ = ftxui::Container::Tab(
		{main_menu_view,
		 create_array_view,
		 fill_array_view,
		 fill_array_random_view,
		 show_library_array,
		 sub_menu_sort_array_view,
		 sub_menu_search_component_view},

		&active_view_);
}

ftxui::Element MenuLab_1::Render()
{
	if (!error_message_.empty())
	{
		return ftxui::vbox({
			ftxui::text(error_message_) | ftxui::color(ftxui::Color::Red),
			ftxui::separator(),
			component_->Render(),
		});
	}
	return component_->Render();
}

void MenuLab_1::OnEvent(ftxui::Event event)
{
	component_->OnEvent(event);
}

bool MenuLab_1::IsSelectable()
{
	return true;
};

ftxui::Component MenuLab_1::GetFTXUIComponent()
{
	return component_;
}

ftxui::Component MenuLab_1::buildMainMenuView(std::function<void()> navigateBack)
{
	auto menu_title = ftxui::Renderer([]
									  { return ftxui::text("Working with arrays") | ftxui::bold | ftxui::center; });
	return ftxui::Container::Vertical({menu_title,
									   ftxui::Button(">Create a new array", [this]
													 {
            							error_message_.clear(); 
            							active_view_ = 1; }),

									   ftxui::Button("Fill in the array manually", [this]
													 {
										error_message_.clear();
										active_view_ = 2; }),

									   ftxui::Button("Fill in the array with random numbers", [this]
													 {
										error_message_.clear();
										active_view_ = 3; }),

									   ftxui::Button("My library array", [this]
													 {
										error_message_.clear();
										active_view_ = 4; }),

									   ftxui::Button("Sort the array", [this]
													 {
										error_message_.clear();
										active_view_ = 5; }),

									   ftxui::Button("Find an element", [this]
													 {
										error_message_.clear();
										active_view_ = 6; }),
									   ftxui::Button("<-- Back to the main menu", navigateBack)});
};

ftxui::Component MenuLab_1::buildCreateArrayView()
{
	createArrayView_ = std::make_shared<CreateArrayView>(models_, [this]
														 { active_view_ = 0; });
	return createArrayView_->GetFTXUIComponent();
};

ftxui::Component MenuLab_1::buildFillArrayView()
{
	fillArrayView_ = std::make_shared<FillArrayView>(models_, [this]
													 { active_view_ = 0; });
	return fillArrayView_->GetFTXUIComponent();
}

ftxui::Component MenuLab_1::buildShowLibraryArrayView()
{
	showLibraryArrayView_ = std::make_shared<ShowLibraryArrayView>(models_, [this]
																   { active_view_ = 0; });
	return showLibraryArrayView_->GetFTXUIComponent();
}

ftxui::Component MenuLab_1::buildFillArrayRandomView()
{
	fillArrayRandomView_ = std::make_shared<FillArrayRandomView>(models_, [this]
																 { active_view_ = 0; });
	return fillArrayRandomView_->GetFTXUIComponent();
}

ftxui::Component MenuLab_1::buildSubMenuSortArrayView()
{
	subMenuSortArrayView_ = std::make_shared<SubMenuSortArray>(models_, [this]
															   { active_view_ = 0; });
	return subMenuSortArrayView_->GetFTXUIComponent();
};

ftxui::Component MenuLab_1::buildSubMenuSearchComponentView()
{
	subMenuSearchComponentView_ = std::make_shared<SubMenuSearchComponent>(models_, [this]
																		   { active_view_ = 0; });
	return subMenuSearchComponentView_->GetFTXUIComponent();
}