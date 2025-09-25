#include "ui/screens/array_operations/menuLab_1.h"
#include "ui/components/InfoComponent.h"
#include "array_logic/ArrayModel.h"
#include "io/portable_io.h"
#include "ui/screens/array_operations/CreateArrayView.h"
#include "ui/screens/array_operations/ShowArrayView.h"
#include "ui/screens/array_operations/FillArrayView.h"
#include <string>
#include <functional>
#include <utility>
#include <algorithm>

char separate = ',';
size_t sizeArr = 10;
double *arr = new double[sizeArr];
static double min_el;
static int index;
// static HDC hdc = GetDC(GetConsoleWindow());
static std::string nameFile;

int sizeBuckupArr1 = 10, sizeBuckupArr2 = 10;
static double *buckupArr1 = new double[sizeBuckupArr1]();
static double *buckupArr2 = new double[sizeBuckupArr2]();

void info()
{
	std::cout << "Условие: \n";
	std::cout << "Дан массив x_1 ..., x_n";
	std::cout << "Найти сумму элементов от x_1 до x_min\n\n";
}

void solution1()
{
	// �������
	std::cout << "\n   минимальный элемент = ";
	min_el = arr[0];
	index = -1;
	for (size_t i = 0; i < sizeArr; i++)
	{
		if (arr[i] < min_el)
		{
			min_el = arr[i];
			index = i;
		}
	}
	std::cout << min_el;
}

void outputEl()
{
	// ����� �����������

	std::cout << "\n   Массив: ";
	for (size_t i = 0; i < sizeArr; i++)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << "\n\n   Сумма чисел от начала массива до минмального элемента " << "( "
			  << min_el << " ) = ";
	double sum = 0;
	for (int i = 0; i < index; i++)
	{
		sum += arr[i];
	}
	std::cout << sum << std::endl;
	// setColor(7, 0);
}

void clearArr(double *arr)
{
	// �������
	if (arr != nullptr)
	{
		delete[] arr;
		arr = nullptr;
	}
}

// int setSizeArr()
// {
// 	setColor(15, 0);
// 	std::cout << "   Изменение размера массива" << std::endl;
// 	CURSOR(3, 2);
// 	unsigned int key;
// 	setColor(7, 0);
// 	std::cout << "   Изменить размер?" << "\n\n   1 - да   2 - нет";
// 	key = get_char_non_blocking();
// 	if (key == '1')
// 	{
// 		LINES(1);
// 		std::cout << "\n   Введите новый размер: ";
// 		std::cin >> sizeArr;
// 		arr = new double[sizeArr]{};

// 		setColor(10, 0);
// 		std::cout << "   Размер массива успешно изменен!\n\n";
// 		setColor(7, 0);
// 		std::cout << "\n\n   нажмите ESC, чтобы выйти...";
// 		return sizeArr;
// 	}
// 	else
// 	{
// 		throw std::runtime_error("\n\n   нажмите ESC чтобы выйти...");
// 	}
// }

std::string getNameFile()
{
	std::string nameFile;
	std::cout << "\n   Введите имя файла: ";
	// std::cin >> nameFile;
	std::cin >> nameFile;
	if (std::cin.fail() || std::cin.bad())
	{
		while (std::cin.fail() || std::cin.bad())
		{

			std::cin >> nameFile;
		}
	}
	return nameFile;
}

MenuLab_1::MenuLab_1(std::function<void()> navigateBack,
					 std::function<void(const std::shared_ptr<UIComponent> &)> navigateTo)
{

	array_model_ = std::make_shared<ArrayModel>();

	auto main_menu_view = buildMainMenuView(navigateTo, navigateBack);

	auto create_array_view = buildCreateArrayView();

	auto fill_array_view = buildFillArrayView();

	auto fill_array_random_view = buildFillArrayRandomView();

	auto show_array_view = buildShowArrayView();

	auto sub_menu_sort_array_view = buildSubMenuSortArrayView();

	auto sub_menu_search_component_view = buildSubMenuSearchComponentView();

	component_ = ftxui::Container::Tab(
		{main_menu_view,
		 create_array_view,
		 fill_array_view,
		 fill_array_random_view,
		 show_array_view,
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

ftxui::Component MenuLab_1::buildMainMenuView(std::function<void(const std::shared_ptr<UIComponent> &)> navigateTo, std::function<void()> navigateBack)
{
	auto menu_title = ftxui::Renderer([&]
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

									   ftxui::Button("Show an array on the screen", [this]
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
	createArrayView_ = std::make_shared<CreateArrayView>(array_model_, [&]
														 { active_view_ = 0; });
	return createArrayView_->GetFTXUIComponent();
};

ftxui::Component MenuLab_1::buildFillArrayView()
{
	fillArrayView_ = std::make_shared<FillArrayView>(array_model_, [&]
													 { active_view_ = 0; });
	return fillArrayView_->GetFTXUIComponent();
}

ftxui::Component MenuLab_1::buildShowArrayView()
{
	showArrayView_ = std::make_shared<ShowArrayView>(array_model_, [this]
													 { active_view_ = 0; });
	return showArrayView_->GetFTXUIComponent();
}

ftxui::Component MenuLab_1::buildFillArrayRandomView()
{
	fillArrayRandomView_ = std::make_shared<FillArrayRandomView>(array_model_, [this]
																 { active_view_ = 0; });
	return fillArrayRandomView_->GetFTXUIComponent();
}

ftxui::Component MenuLab_1::buildSubMenuSortArrayView()
{
	subMenuSortArrayView_ = std::make_shared<SubMenuSortArray>(array_model_, [this]
															   { active_view_ = 0; });
	return subMenuSortArrayView_->GetFTXUIComponent();
};

ftxui::Component MenuLab_1::buildSubMenuSearchComponentView()
{
	subMenuSearchComponentView_ = std::make_shared<SubMenuSearchComponent>(array_model_, [this]
																		   { active_view_ = 0; });
	return subMenuSearchComponentView_->GetFTXUIComponent();
}

void menuLab_1()
{

	if (arr == nullptr)
	{
		arr = new double[sizeArr];
	}

	// size_t key;

	// do
	// {
	// 	// system("cls");

	// 	// Text(hdc, 50, 0, "���� ������������ ������ �1", RGB(255, 255, 255), RGB(0, 0, 0), 25);
	// 	// Text(hdc, 50, 50, "0 - ������� � �������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
	// 	// Text(hdc, 50, 100, "1 - ������� � ��������� ������ ������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
	// 	// Text(hdc, 50, 150, "2 - ������� �� ���������� � ����", RGB(255, 255, 255), RGB(15, 5, 77), 25);
	// 	// Text(hdc, 50, 250, "3 - ������� �� ���������� �� �����", RGB(255, 255, 255), RGB(15, 5, 77), 25);
	// 	// Text(hdc, 50, 300, "4 - ������� �� ����� � ��������� ������ ������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
	// 	// Text(hdc, 50, 350, "5 - ������ �������� �������� � ����� �� �������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
	// 	// Text(hdc, 50, 450, "6 - ������ ������ ������������� �������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
	// 	// Text(hdc, 50, 500, "7 - �������� ����������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
	// 	// Text(hdc, 50, 550, "ESC - �����", RGB(255, 255, 255), RGB(157, 56, 188), 25);

	// 	key = get_char_non_blocking();

	// 	switch (key)
	// 	{
	// 	case '0':
	// 		// system("cls");
	// 		info();
	// 		CURSOR(3, 7);

	// 		system_pause_function();
	// 		// system("cls");
	// 		inputEl(),
	// 			solution1(),
	// 			outputEl();
	// 		setColor(7, 0);
	// 		std::cout << "\n\n   нажмите ESC чтобы выйти...";
	// 		CURSOR(3, 14);
	// 		get_char_non_blocking();
	// 		break;
	// 	case '1':
	// 		// system("cls");
	// 		info();
	// 		CURSOR(3, 8);
	// 		;
	// 		system_pause_function();
	// 		system("cls");
	// 		inputEl();
	// 		solution1();
	// 		outputEl();
	// 		LINES(3);
	// 		// outTableGraf(arr, sizeArr, sizeArr < 10 ? sizeArr : 10, "��������� ����� ������", "X", hdc, 1);
	// 		setColor(7, 0);
	// 		// Text(hdc, 40, 400, "ESC - �����", RGB(255, 255, 255), RGB(157, 56, 188), 25);
	// 		get_char_non_blocking();
	// 		break;
	// 	case '2':
	// 		inpFile();
	// 		setColor(7, 0);
	// 		std::cout << "\n\n   нажмите ESC чтобы выйти...";
	// 		get_char_non_blocking();
	// 		break;
	// 	case '3':
	// 		system("cls");
	// 		outFile();
	// 		setColor(7, 0);
	// 		std::cout << "\n\n   нажмите ESC чтобы выйти...";
	// 		get_char_non_blocking();
	// 		break;
	// 	case '4':
	// 		system("cls");
	// 		info();
	// 		outFile();
	// 		LINES(1);
	// 		// outTableGraf(arr, sizeArr, sizeArr < 10 ? sizeArr : 10, "��������� ����� ������", "X", hdc, 1);
	// 		setColor(7, 0);
	// 		// Text(hdc, 40, 550, "ESC - �����", RGB(255, 255, 255), RGB(157, 56, 188), 25);
	// 		get_char_non_blocking();
	// 		break;
	// 	case '5':
	// 		system("cls");
	// 		replaceElFile();
	// 		setColor(7, 0);
	// 		get_char_non_blocking();
	// 		break;
	// 	case '6':
	// 		system("cls");
	// 		setSizeArr();
	// 		setColor(7, 0);
	// 		get_char_non_blocking();
	// 		break;
	// 	case '7':
	// 		system_directory();
	// 		setColor(7, 0);
	// 		std::cout << "\n\n   нажмите ESC чтобы выйти...";
	// 		get_char_non_blocking();
	// 		break;
	// 	case 27:
	// 		break;
	// 	default:
	// 		std::cout << "\n������� ����������� �������" << std::endl;
	// 	}

	// 	setColor(7, 0);
	// } while (key != 27);
	// clearArr(arr);
	// system("cls");
}