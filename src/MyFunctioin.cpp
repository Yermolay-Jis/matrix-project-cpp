#include "../include/Header.h"
#include "../include/MyFunction.h"
#include "portable_io.h"

void setColor(short int pnTextColor, short int pnBKColor) {
	// HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// SetConsoleTextAttribute(hStdOut, (WORD)((pnBKColor & 0x000F) << 4) | (pnTextColor & 0x000F));
};
void SetDefBkColor(short pnBkColor)
{
	DefBkColor = (enColor)pnBkColor;
};

// COORD GetCursorPosition()
// {
// 	CONSOLE_SCREEN_BUFFER_INFO lpCursorInfo;
// 	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lpCursorInfo);
// 	return lpCursorInfo.dwCursorPosition;
// }

void SetCursorPosition(short x, short y)
{
	// HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// COORD coord;
	// coord.X = x;
	// coord.Y = y;

	// SetConsoleCursorPosition(hConsole, coord);
}

void SetCursorCols(short cols)
{
	// COORD coord = GetCursorPosition();
	// SetCursorPosition(coord.Y, cols);
}

void cursorVision(bool value)
{
	// HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
	// CONSOLE_CURSOR_INFO cursorInfo;
	// GetConsoleCursorInfo(hndl, &cursorInfo);
	// cursorInfo.bVisible = value == true ? TRUE : FALSE;
}

void creator()
{
	// system("cls");
	do
	{
		// Text(hdc, 250, 0, "������������������", RGB(255, 255, 255), RGB(0, 0, 0), 25);
		// Text(hdc, 50, 50, "������� ������� ���������, ������� ������ 1����1, ������������ ���� ���� ���", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		// Text(hdc, 50, 75, "����������� ����������������� ��������. ������� ������� �������������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		// Text(hdc, 50, 100, "����� � ������� �� � ��������� � ����������� ���������� ������ �� ��������.", RGB(255, 255, 255), RGB(15, 5, 77), 25);

	} while (get_char_non_blocking() != 27);
	// system("cls");
};

void system_directory()
{
	std::string path_string = ".";

	std::filesystem::path my_path(path_string);

	try
	{
		if (!(std::filesystem::exists(my_path)) || !(std::filesystem::is_directory(my_path)))
		{
			std::cerr << "Error: path is not exist or it is not directory: " << my_path << std::endl;
		}
		std::cout << "Contents of the directory: " << std::filesystem::absolute(my_path).string() << std::endl;
		std::cout << "--------------------------------------------------------------------------" << std::endl;

		for (const auto &entry : std::filesystem::directory_iterator(my_path))
		{
			std::cout << entry.path().filename().string();

			if (entry.is_directory())
			{
				std::cout << "[Folder]" << std::endl;
			}
			else if (entry.is_regular_file())
			{
				std::cout << "[File, " << std::filesystem::file_size(entry.path()) << " bite]" << std::endl;
			}
			else
			{
				std::cout << "[Other]" << std::endl;
			}
		}
	}
	catch (const std::filesystem::filesystem_error &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}