#include "ui/screens/matrix_operations/MatrixOperations.h"
#include "ui/screens/matrix_operations/CreateMatrixView.h"
#include "ui/screens/matrix_operations/ShowMatrixView.h"
#include "ui/screens/array_operations/menuLab_1.h"
#include "ui/screens/matrix_operations/MatrixMathOperations.h"
#include "matrix_logic/matrix.h"
#include "io/portable_io.h"
#include "io/math/math_utils.h"
#include <utility>
#include <string>
#include <iostream>
#include <functional>
#include <fstream>

size_t setRow()
{
	size_t rows;
	try
	{
		std::cout << "   ������� ������(-��) (rows): ";
		std::cin >> rows;
		if (std::cin.bad() || std::cin.fail())
		{
			while (std::cin.bad() || std::cin.fail())
			{
				const size_t MAX_LINE_IGNORE = 256;
				std::cin.clear();
				std::cin.ignore(MAX_LINE_IGNORE, '\n');
				std::cout << "   ������� ������(-��) (rows): ";
				std::cin >> rows;
			}
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what();
	}
	return rows;
}

size_t setCol()
{

	size_t cols;

	try
	{
		std::cout << "   ������� �������(-��) (cols): ";
		std::cin >> cols;
		if (std::cin.bad() || std::cin.fail())
		{
			while (std::cin.bad() || std::cin.fail())
			{
				const size_t MAX_LINE_IGNORE = 256;
				std::cin.clear();
				std::cin.ignore(MAX_LINE_IGNORE, '\n');
				std::cout << "   ������� �������(-��) (cols): ";
				std::cin >> cols;
			}
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what();
	}
	return cols;
}

size_t manual_max(size_t a, size_t b)
{
	return (a > b) ? a : b;
}

MatrixOperations::MatrixOperations(std::function<void()> navigateBack)
{
	matrix_model_ = std::make_shared<MatrixModel>();

	auto matrix_main_menu_view = buildMatrixMainMenuView(navigateBack);

	auto create_matrix_view = buildCreateMatrixView();

	auto show_matrix_view = buildShowMatrixView();

	auto fill_matrix_view = buildFillMatrixView();

	auto fill_matrix_auto_view = buildFillMatrixAutoView();

	auto matrix_math_operations = buildMatrixMathOperations();

	matrix_operations_ = ftxui::Container::Tab({matrix_main_menu_view,
												create_matrix_view,
												show_matrix_view,
												fill_matrix_view,
												fill_matrix_auto_view,
												matrix_math_operations

											   },
											   &matrix_operations_active_view_);
}

ftxui::Element MatrixOperations::Render()
{
	return matrix_operations_->Render();
};

void MatrixOperations::OnEvent(ftxui::Event event)
{
	matrix_operations_->OnEvent(event);
};

ftxui::Component MatrixOperations::GetFTXUIComponent()
{
	return matrix_operations_;
};

ftxui::Component MatrixOperations::buildMatrixMainMenuView(std::function<void()> navigateBack)
{
	auto menuTitle = ftxui::Renderer([&]
									 { return ftxui::text("Matrix operations") | ftxui::bold; });
	return ftxui::Container::Vertical({menuTitle,
									   ftxui::Button("> Create matrix", [&]
													 { matrix_operations_active_view_ = 1; }),
									   ftxui::Button("Show matrixes", [&]
													 { matrix_operations_active_view_ = 2; }),
									   ftxui::Button("Fill of the matrix", [&]
													 { matrix_operations_active_view_ = 3; }),

									   ftxui::Button("Fill of the matrix auto", [&]
													 { matrix_operations_active_view_ = 4; }),

									   ftxui::Button("Matrix math operations", [&]
													 { matrix_operations_active_view_ = 5; }),

									   ftxui::Button("<-- Back to the main menu", navigateBack)

	});
}

ftxui::Component MatrixOperations::buildCreateMatrixView()
{
	createMatrixView_ = std::make_shared<CreateMatrixView>(workspace_, [this]
														   { matrix_operations_active_view_ = 0; });

	return createMatrixView_->GetFTXUIComponent();
}

ftxui::Component MatrixOperations::buildShowMatrixView()
{
	showMatrixView_ = std::make_shared<ShowMatrixView>(matrix_model_, [&]
													   { matrix_operations_active_view_ = 0; });
	return showMatrixView_->GetFTXUIComponent();
};

ftxui::Component MatrixOperations::buildFillMatrixView()
{
	fillMatrixView_ = std::make_shared<FillMatrixView>(matrix_model_, [&]
													   { matrix_operations_active_view_ = 0; });

	return fillMatrixView_->GetFTXUIComponent();
};

ftxui::Component MatrixOperations::buildFillMatrixAutoView()
{
	fillMatrixAutoView_ = std::make_shared<FillMatrixAutoView>(matrix_model_, [this]
															   { matrix_operations_active_view_ = 0; });
	return fillMatrixAutoView_->GetFTXUIComponent();
}

ftxui::Component MatrixOperations::buildMatrixMathOperations()
{
	matrixMathOperationsView_ = std::make_shared<MatrixMathOperations>(matrix_model_, [this]
																	   { matrix_operations_active_view_ = 0; });

	return matrixMathOperationsView_->GetFTXUIComponent();
}
