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

// void inputEl()
// {
// 	setColor(15, 0);

// 	info();
// 	std::cout << "   Введите элементы массива: \n";
// 	for (size_t i = 0; i < sizeArr; i++)
// 	{
// 		CURSOR(3, 6);
// 		SPACEBACK(30);
// 		setColor(10, 0);

// 		if (i == sizeArr - 1)
// 		{
// 			setColor(12, 0);
// 		}
// 		std::cout << "   x[" << i + 1 << "] = ";
// 		std::cin >> arr[i];

// 		if (std::cin.bad() || std::cin.fail())
// 		{
// 			const size_t MAX_IGNORE_LINE = 256;
// 			std::cin.clear();
// 			std::cin.ignore(MAX_IGNORE_LINE, '\n');
// 			i--;
// 			continue;
// 		}
// 	}
// 	setColor(7, 0);
// 	textIndicator = true;
// }

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

// void inpFile()
// {
// 	// system("cls");
// 	CURSOR(3, 3);
// 	setColor(6, 0);
// 	std::cout << "������ ������ � ����";

// 	nameFile = getNameFile();

// 	std::ifstream file_test(nameFile);
// 	bool file_exist = file_test.good();
// 	file_test.close();
// 	std::ios_base::openmode mode = std::ios::out;

// 	if (file_exist)
// 	{
// 		std::cout << "\n\n   Дозаписать значения в файл?\t1 - да";
// 		char ch = get_char_non_blocking();
// 		if (ch == '1')
// 		{
// 			mode = std::ios::app;
// 		}
// 	}
// 	std::ofstream file(nameFile, mode);

// 	if (!file.is_open())
// 	{
// 		std::cerr << "  Error: file not opened";
// 		return;
// 	};
// 	if (sizeArr == 0)
// 	{
// 		std::cerr << "   Error: file is empty! ";
// 		return;
// 	};

// 	// system("cls");
// 	inputEl();
// 	for (size_t i = 0; i < sizeArr; i++)
// 	{
// 		file << arr[i] << std::endl;
// 	}
// 	file.close();
// 	LINES(1);

// 	setColor(7, 0);
// 	std::cout << "   Массив успешно сохрарнен в файле => ";
// 	SPACEBACK(1);
// 	setColor(10, 0);
// 	std::cout << nameFile;
// }

// void outFile()
// {
// 	nameFile = getNameFile();

// 	std::cout << "\n";
// 	setColor(15, 0);
// 	indicator = false;

// 	std::ifstream file(nameFile);
// 	indicator = file.is_open() ? true : false;
// 	std::string comment = file.is_open() ? "   Файл успешно найден\n\n" : "   Ошибка, такого файла нет\n\n";
// 	std::cout << comment << std::endl;

// 	if (indicator == true)
// 	{
// 		std::string data;
// 		std::string item;
// 		size_t numberEl = 0;
// 		size_t i = 0;

// 		while (std::getline(file, data))
// 		{
// 			if (!data.empty())
// 			{
// 				numberEl++;
// 			}
// 			else
// 			{
// 				continue;
// 			}
// 		}
// 		std::cout << "\n\n   Количество элементов в файле: " << numberEl << std::endl;
// 		if (numberEl == 0)
// 		{
// 			std::cerr << "   Error: file is empty!";
// 			textIndicator = false, indicator = false;
// 			return;
// 		}

// 		saveArr(arr, sizeArr);
// 		arr = new double[numberEl];
// 		sizeArr = numberEl;
// 		std::string line;
// 		file.clear();
// 		file.seekg(0, std::ios::beg);

// 		while (std::getline(file, line))
// 		{
// 			if (line.empty())
// 			{
// 				continue;
// 			}

// 			double value = 0.0, result = 0.0;
// 			size_t charProcessed = 0;
// 			std::stringstream ss(line);
// 			while (ss >> item)
// 			{

// 				try
// 				{
// 					for (size_t i = 0; i < item.length(); i++)
// 					{
// 						if (item[i] == '.')
// 						{
// 							item[i] = separate;
// 						}
// 						if (!((item[i] >= '0' && item[i] <= '9') || item[i] == '+' || item[i] == '-' || item[i] == 'e' || item[i] == 'E' || item[i] == '.' || item[i] == ','))
// 						{
// 							result = 0;
// 						};
// 					}
// 					value = std::stod(item, &charProcessed);
// 					result += value;
// 				}
// 				catch (const std::invalid_argument &e)
// 				{
// 					setColor(12, 0);
// 					std::cerr << "   Error:" << e.what();
// 				}
// 				catch (const std::out_of_range &e)
// 				{
// 					setColor(12, 0);
// 					std::cerr << "   Error: " << e.what() << std::endl;
// 				}
// 				catch (const std::exception &e)
// 				{
// 					setColor(12, 0);
// 					std::cerr << "   Error: " << e.what() << std::endl;
// 				}
// 			}
// 			arr[i] = result;
// 			i++;
// 		}

// 		file.close();

// 		solution1();
// 		outputEl();
// 	}
// }

// void outTableGraf(double *arr, int size, int pnsec, std::string title, std::string psmas, HDC hdc, size_t n)
// {
// 	if (indicator == true || textIndicator == true)
// 	{

// 		HWND hwnd = (HWND)GetStdHandle(STD_OUTPUT_HANDLE);

// 		CONSOLE_FONT_INFO conf{};
// 		GetCurrentConsoleFont(hwnd, false, &conf);
// 		COORD cxy = CURSORPOS;

// 		int indentY = conf.dwFontSize.Y * (cxy.Y + 1),
// 			indentX = 40;

// 		HFONT hfont = CreateFontA(20, 0, 0, 0, FW_BLACK, false, false, false, RUSSIAN_CHARSET,
// 								  OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, VARIABLE_PITCH, "Terminal");
// 		HFONT holdfont = (HFONT)SelectObject(hdc, hfont);

// 		SetTextColor(hdc, RGB(255, 255, 255));
// 		SetBkColor(hdc, RGB(0, 0, 0));
// 		TextOutA(hdc, indentY + 100, indentY, title.c_str(), title.length());
// 		SelectObject(hdc, holdfont);
// 		DeleteObject(hfont);

// 		indentY += 34;
// 		int nsec = size / pnsec + ((size % pnsec > 0) ? 1 : 0);

// 		Rectangle(hdc, indentX, indentY, indentX + pnsec * 5 * conf.dwFontSize.X, indentY + (5 * conf.dwFontSize.Y) * nsec);

// 		for (int i = 0; i < nsec; i++)
// 		{
// 			int nx = indentX,
// 				nx2 = indentX + pnsec * 5 * conf.dwFontSize.X;
// 			MoveToEx(hdc, nx, indentY + i * 5 * conf.dwFontSize.Y + (5 * conf.dwFontSize.Y) / 2, NULL);
// 			LineTo(hdc, nx2, indentY + i * 5 * conf.dwFontSize.Y + (5 * conf.dwFontSize.Y) / 2);
// 			MoveToEx(hdc, nx, indentY + ((i + 1) * 5 * conf.dwFontSize.Y), NULL);
// 			LineTo(hdc, nx2, indentY + ((i + 1) * 5 * conf.dwFontSize.Y));
// 		}

// 		SetTextColor(hdc, RGB(255, 255, 255));
// 		SetBkColor(hdc, RGB(94, 94, 94));

// 		for (int i = 0; i < pnsec; i++)
// 		{
// 			int nx = indentX + (i) * 5 * conf.dwFontSize.X,
// 				ny = indentY;

// 			MoveToEx(hdc, nx, ny, NULL);
// 			LineTo(hdc, nx, ny + (5 * conf.dwFontSize.Y) * nsec);
// 			char txt[30]{};

// 			for (int j = 0; j < nsec; j++)
// 			{
// 				if (j * pnsec + i < size)
// 				{
// 					sprintf_s(txt, "%s%d", psmas.c_str(), j * pnsec + i + n);
// 					SIZE sz{};
// 					GetTextExtentPoint32A(hdc, txt, strlen(txt), &sz);
// 					TextOutA(hdc, nx + (5 * conf.dwFontSize.X - sz.cx) / 2, ny + j * (conf.dwFontSize.Y * 5) + conf.dwFontSize.Y, txt, strlen(txt));
// 					sprintf_s(txt, "%5.1f", arr[j * pnsec + i]);
// 					GetTextExtentPoint32A(hdc, txt, strlen(txt), &sz);
// 					TextOutA(hdc, nx + (5 * conf.dwFontSize.X - sz.cx) / 2, ny + j * (conf.dwFontSize.Y * 5) + 3 * conf.dwFontSize.Y, txt, strlen(txt));
// 				}
// 			}
// 		}
// 		DeleteObject(hfont);
// 	}
// };

// void replaceElFile()
// {
// 	outFile();

// 	if (indicator == true)
// 	{
// 		std::cout << "\n   �������� �������� ��������?\n\n   1 - ��\t2 - ���" << std::endl;
// 		size_t key = get_char_non_blocking();

// 		if (key == '1')
// 		{
// 			// system("cls");

// 			std::cout << "   ������ �� �����:\n";
// 			for (size_t i = 0; i < sizeArr; i++)
// 			{
// 				std::cout << "  " << arr[i];
// 			}

// 			size_t replaceElIdx;
// 			std::cout << "\n\n   ������� ����� �������� �������� ������ �������� (0, 1, 2, ...)" << std::endl
// 					  << "   ";
// 			std::cin >> replaceElIdx;
// 			if (replaceElIdx >= sizeArr || std::cin.fail() || std::cin.bad())
// 			{
// 				std::cerr << "   ������: �������� � ����� �������� �� ����������!" << std::endl;
// 				while (replaceElIdx >= sizeArr || std::cin.fail() || std::cin.bad())
// 				{
// 					CURSOR(3, 6);
// 					SPACEBACK(30);
// 					std::cin.clear();
// 					std::cin.ignore(250, '\n');
// 					// std::cout << "   ������� ����� �������� �������� �������� � �������� �� 0 �� " << sizeArr << std::endl;
// 					std::cin >> replaceElIdx;
// 				}
// 				for (int i = 4; i < 7; i++)
// 				{
// 					for (int j = 0; j < 30; j++)
// 					{
// 						std::cin.clear();
// 						SPACEBACK(30);
// 						CURSOR(j, i);
// 					}
// 				};
// 			}
// 			CURSOR(3, 6);

// 			for (size_t i = 0; i < sizeArr; i++)
// 			{
// 				if (i == replaceElIdx)
// 				{
// 					replaceElIdx = i;
// 					break;
// 				}
// 			}
// 			std::cout << "�������� � �������� ";
// 			setColor(10, 0);
// 			SPACEBACK(30);
// 			std::cout << replaceElIdx;
// 			setColor(14, 0);
// 			SPACEBACK(30);
// 			std::cout << " ������� ������ => ";
// 			setColor(10, 0);
// 			SPACEBACK(30);
// 			std::cout << arr[replaceElIdx];

// 			double newElement;

// 			setColor(14, 0);
// 			std::cout << "\n\n   ������� ����� �������� ��� ����� ��������: \n   ";
// 			setColor(10, 0);
// 			std::cout << arr[replaceElIdx];
// 			setColor(14, 0);
// 			SPACEBACK(30);
// 			std::cout << " => ";
// 			setColor(10, 0);
// 			SPACEBACK(30);
// 			std::cin >> newElement;
// 			setColor(14, 0);

// 			arr[replaceElIdx] = newElement;
// 			std::ofstream file(nameFile, std::ios::trunc);
// 			for (size_t i = 0; i < sizeArr; i++)
// 			{
// 				file << arr[i] << "\n";
// 			}

// 			std::cout << "   ���������� ������:\n";
// 			for (size_t i = 0; i < sizeArr; i++)
// 			{
// 				std::cout << "  " << arr[i];
// 			}
// 		}
// 		else
// 		{
// 			std::cout << "\n\n   ������� ESC ����� �����...";
// 		}
// 	}
// }

// MenuLab_1::MenuLab_1(const std::function<void()> &navigateBack, const std::function<void(std::shared_ptr<UIComponent>)> &navigateTo)
// {

// 	AddItem(std::make_shared<TextItem>("Laboratory work #1"));
// 	AddItem(std::make_shared<MenuItem>("Information", [this, navigateBack, navigateTo]
// 											 {
// 												 std::string taskTitle = "Task:";
// 												 std::string taskContent = "An array of numbers is given from x_1 to x_n.\nFind the sum elements from x_1 to x_min.";
// 												 auto infoWindow = std::make_shared<InfoComponent>(taskTitle, taskContent, navigateBack);
// 												 navigateTo(infoWindow); }));
// 	AddItem(std::make_shared<MenuItem>("Set size in the array", [this]
// 											 { promptForValue("Enter new array size:", [this](std::string userInput)
// 																	{
// 												try {
// 													newSize_ = std::stoul(userInput);
// 													handleSetSizeArray(newSize_);
// 													activeMode_ = ViewMode::SetSizeArrayMode;
// 												} catch (const std::exception& e) {
// 													errorMessage_ = "Invalid input: must be a number.";
// 													activeMode_ = ViewMode::MenuMode;
// 												} }); }));
// 	AddItem(std::make_shared<MenuItem>("Back", navigateBack));
// };

// ftxui::Element MenuLab_1::Render()
// {

// 	switch (activeMode_)
// 	{
// 	case ViewMode::MenuMode:
// 	{
// 		return Menu::Render();
// 	}
// 	case ViewMode::InputMode:
// 	{
// 		ftxui::InputOption options;
// 		options.on_enter = [this]
// 		{
// 		if (on_input_submit_) {
// 			on_input_submit_(userInputBuffer_);
// 		} userInputBuffer_.clear(); };
// 		auto inputComponent = ftxui::Input(&userInputBuffer_, "", options);
// 		return ftxui::vbox(
// 				   ftxui::text(promptMessage_),
// 				   inputComponent) |
// 			   ftxui::border;
// 	}
// 	case ViewMode::SetSizeArrayMode:
// 	{

// 		auto message = ftxui::text("The size of the array has been succesfully changed to: " + std::to_string(newSize_));

// 		const std::vector<double> &array = arrayModel_.getArray();
// 		std::vector<ftxui::Element> resultArrayElements;
// 		for (double element : array)
// 		{
// 			resultArrayElements.push_back(ftxui::text(std::to_string(element)));
// 		};
// 		auto arrayDisplay = ftxui::hbox(resultArrayElements);
// 		auto ok_button = ftxui::Button("   OK   ", [this]
// 									   { activeMode_ = ViewMode::MenuMode; }, ftxui::ButtonOption::Border());

// 		return ftxui::vbox(message,
// 						   ftxui::separator(),
// 						   arrayDisplay,
// 						   ftxui::separator(),
// 						   ok_button | ftxui::center);
// 	}
// 	default:
// 	{
// 		activeMode_ = ViewMode::MenuMode;
// 	}
// 	}
// };

// void MenuLab_1::promptForValue(std::string prompt_message, std::function<void(std::string)> on_submit)
// {
// 	promptMessage_ = prompt_message;
// 	on_input_submit_ = on_submit;
// 	activeMode_ = ViewMode::InputMode;
// };

// void MenuLab_1::handleSetSizeArray(size_t newSize)
// {
// 	arrayModel_.setSizeArray(newSize);
// }

// void MenuLab_1::handlePopulateArray()
// {
// 	std::cout << "Filling in the array" << std::endl;
// 	std::cout << "Enter the elements for the array: \n";
// 	for (size_t i = 0; i < arrayModel_.getSizeArray(); i++)
// 	{
// 		double value;
// 		std::cout << "   x[" << i + 1 << "] = ";
// 		std::cin >> value;

// 		if (std::cin.bad() || std::cin.fail())
// 		{
// 			const size_t MAX_IGNORE_LINE = 256;
// 			std::cin.clear();
// 			std::cin.ignore(MAX_IGNORE_LINE, '\n');
// 			i--;
// 			continue;
// 		}
// 		arrayModel_.setItem(i, value);
// 	};
// 	std::cout << "The array has been succesfully filled";
// }

// void MenuLab_1::handleSolutionTask()
// {
// }

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

	component_ = ftxui::Container::Tab(
		{main_menu_view,
		 create_array_view,
		 fill_array_view,
		 fill_array_random_view,
		 show_array_view,
		 sub_menu_sort_array_view},

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
									   ftxui::Button("Statistics", [this]
													 { 
										error_message_.clear();
										active_view_ = 7; }),
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