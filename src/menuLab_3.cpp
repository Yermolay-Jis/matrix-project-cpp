#include "../include/menuLab_3.h"
#include "../include/menuLab_1.h"
#include "../include/matrix.h"

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
				SPACEBACK(30);
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
				SPACEBACK(30);
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

void Matrix::fillMatrix(size_t rows, size_t cols, size_t x, size_t y)
{
	if (!(matrix == nullptr || rows <= 0 || cols <= 0))
	{
		std::cout << "\n   ���������� ������� �������� " << rows << " x " << cols << ":\n\n";
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				outTableMatrixGraf(hdc, matrix, rows, cols, 400, 120, 50, 50, 16, 15);
				CURSOR(x, y);
				SPACEBACK(30);
				std::cout << "   [" << i << "][" << j << "] = ";
				std::cin >> matrix[i][j];
				if (std::cin.fail() || std::cin.bad())
				{
					const size_t MAX_LINE_IGNORE = 256;
					std::cin.clear();
					std::cin.ignore(MAX_LINE_IGNORE, '\n');
					j--;
					continue;
				}
			}
		}
		setColor(10, 0);
		std::cout << "   ������� ������� ���������!" << std::endl;
		Sleep(1000);
		setColor(7, 0);
	}
	else
	{
		std::cout << "   ����� ���� �����..." << std::endl;
	}
}

void Matrix::changeEl(Matrix &matrix, size_t rows, size_t cols)
{
	size_t nRow = setRow();
	size_t nCol = setCol();
	if (!(nRow < 0 || nRow > rows) && !(nCol < 0 || nCol > cols))
	{

		double newValue;
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				if (i == nRow - 1 && j == nCol - 1)
				{
					std::cout << "   ������� ����� �������� ��������:\n";
					std::cin >> newValue;
					matrix.matrix[i][j] = newValue;
					break;
				}
			}
		}
		setColor(10, 0);
		std::cout << "\n\n   ������� ������� �������!" << std::endl;
		Sleep(1000);
		setColor(7, 0);
	}
	else
	{
		std::cerr << "   ������� �������������� �������� ������ � �������" << std::endl;
	}
}

Matrix matrix, reserveMatrix;

void clearLine(size_t x_0, size_t y_0, size_t x, size_t y)
{
	cursorVision(true);
	for (int i = x_0; i < x; i++)
	{
		for (int j = y_0; j < y; j++)
		{
			std::cin.clear();
			SPACEBACK(30);
			CURSOR(j, i);
		}
	};
	cursorVision(false);
}

void info2()
{
	setColor(14, 0);
	CURSOR(3, 2);
	std::cout << "�������: \n";
	setColor(15, 0);
	CURSOR(3, 3);
	std::cout << "��� ������� 5 � 6 ���������� ��� ��������� �� ������� �������� � ������������\n "
			  << "   ��������� ��������� � ������ ������.� ������ ������� � ������� �� �������������\n"
			  << "   ���� �������� ������� ������ � ��������� ��������";
	setColor(14, 0);
}

void solution(Matrix &matrix)
{
	if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0))
	{
		info2();
		std::cout << "\n   ��������� �������: ";
		outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 800, 10, 50, 50, 16, 15);
		size_t n = 0;
		int sizeArr = matrix.rows;
		double *colsNumb = new double[sizeArr];
		for (size_t i = 0; i < matrix.rows; i++)
		{
			double maxItem = matrix.matrix[i][0];
			size_t col = 0;
			for (size_t j = 0; j < matrix.cols; j++)
			{
				if (matrix.matrix[i][j] > maxItem)
				{
					maxItem = matrix.matrix[i][j];
					col = j;
				}
			}
			colsNumb[n] = col;
			n++;
		}

		double maxEl;
		bool swapped = true;
		;
		size_t j = 0;
		while (swapped)
		{
			swapped = false;
			for (size_t i = 0; i < sizeArr - 1; i++)
			{
				if (colsNumb[i] > colsNumb[i + 1])
				{
					double temp = colsNumb[i];
					colsNumb[i] = colsNumb[i + 1];
					colsNumb[i + 1] = temp;
					swapped = true;
				}
			}
		}

		if (sizeArr > 1)
		{
			size_t idx = 0;
			for (size_t i = 0; i < sizeArr; i++)
			{
				bool duplicate = false;
				for (size_t j = 0; j < idx; j++)
				{
					if (colsNumb[j] == colsNumb[i])
					{
						duplicate = true;
						break;
					}
				}
				if (!duplicate)
				{
					colsNumb[idx] = colsNumb[i];
					idx++;
				}
			}
			sizeArr = idx;
		}

		LINES(10);
		std::cout << "   ������ �������� � ������� ����"
				  << "\n   ������� ������������ �������� : " << std::endl;

		for (size_t i = 0; i < sizeArr; i++)
		{
			std::cout << "   " << colsNumb[i] + 1;
		}
		std::cout << std::endl;

		std::cout << "\n   ���������: " << std::endl;
		for (size_t i = 0; i < sizeArr; i++)
		{
			for (size_t j = 0; j < matrix.cols; j++)
			{
				if (j == colsNumb[i])
				{
					double term = matrix.matrix[0][j];
					matrix.matrix[0][j] = matrix.matrix[matrix.rows - 1][j];
					matrix.matrix[matrix.rows - 1][j] = term;
				}
			}
		}
		outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 800, 350, 50, 50, 16, 15);
	}
	else
	{
		std::cerr << "\n   ������� �� ���� �������...";
	}
}

Matrix createMatrix(size_t rows, size_t cols)
{
	Matrix matrix(rows, cols);
	return matrix;
}

// std::string getNameFile()
// {
// 	setColor(15, 0);
// 	std::string fileName;
// 	std::cout << "\n   ������� ��� �����: ";
// 	setColor(10, 0);
// 	std::cin >> fileName;
// 	if (std::cin.fail() || std::cin.bad())
// 	{
// 		while (std::cin.fail() || std::cin.bad())
// 		{
// 			std::cin >> fileName;
// 		}
// 	}
// 	setColor(14, 0);
// 	return fileName;
// }

void writeMatrixTxt(Matrix &matrix)
{
	outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
	std::string nameFile = getNameFile();
	std::ifstream file_bin_test(nameFile);
	bool file_bin_exist = file_bin_test.good();
	file_bin_test.close();
	std::ios_base::openmode mode = std::ios::out;

	if (file_bin_exist)
	{
		std::cout << "\n\n   ������� ���� ��� ��������?\t1 - ��";
		UCHAR ch = _getch();
		if (ch == '1')
		{
			mode = std::ios::app;
		}
	}

	std::ofstream file(nameFile, mode);
	LINES(3);
	CURSOR(3, 5);
	for (size_t i = 0; i < matrix.rows; i++)
	{
		for (size_t j = 0; j < matrix.cols; j++)
		{
			file << matrix.matrix[i][j] << " ";
		}
		file << "\n";
	}
	file.clear();
	file.close();
	std::cout << "\n\n   ������ ������� �������� � ���� => ";
	setColor(10, 0);
	std::cout << nameFile << std::endl;
}

// void writeMatrixBin(Matrix& matrix) {
//	//outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
//	std::string nameFile = getNameFile();
//	std::ifstream file_bin_test(nameFile);
//	bool file_bin_exist = file_bin_test.good();
//	std::ios_base::openmode mode = std::ios::out;
//
//	if (file_bin_exist) {
//		std::cout << "\n\n   ������� ���� ��� ��������?\t1 - ��";
//		UCHAR ch = _getch();
//		if (ch == '1') {
//			size_t rows = 0, cols = 0;
//
//			std::ifstream file(nameFile, std::ios::binary);
//			file.read(reinterpret_cast<char*>(&rows), sizeof(size_t));
//			file.read(reinterpret_cast<char*>(&cols), sizeof(size_t));
//			size_t newRows = rows + matrix.rows;
//			size_t newCols = cols > matrix.cols ? cols : matrix.cols;
//			file.close();
//
//
//			Matrix combainedMatrix, matrixFromFile;
//			std::ifstream infile(nameFile, std::ios::binary);
//			combainedMatrix.rows = matrix.rows;
//			combainedMatrix.cols = matrix.cols;
//
//			combainedMatrix.matrix = new double* [combainedMatrix.rows];
//			for (size_t i = 0; i < combainedMatrix.rows; i++) {
//				combainedMatrix.matrix[i] = new double[combainedMatrix.cols];
//				for (size_t j = 0; j < rows; j++) {
//					combainedMatrix.matrix[i][j] = matrix.matrix[i][j];
//				}
//
//			}
//
//			if (!infile.read(reinterpret_cast<char*>(&matrixFromFile.rows), sizeof(size_t)) || !infile.read(reinterpret_cast<char*>(&matrixFromFile.cols), sizeof(size_t))) {
//				std::cerr << "   ������: ��������� ���������� ����";
//				infile.close();
//				combainedMatrix.rows = matrix.rows;
//				combainedMatrix.cols = matrix.cols;
//
//				if (combainedMatrix.rows > 0 && combainedMatrix.cols > 0) {
//					combainedMatrix.matrix = new double* [combainedMatrix.rows];
//					for (size_t i = 0; i < combainedMatrix.rows; i++) {
//						combainedMatrix.matrix[i] = new double[combainedMatrix.cols];
//						for (size_t j = 0; j < combainedMatrix.cols; j++) {
//							combainedMatrix.matrix[i][j] = matrix.matrix[i][j];
//						}
//					}
//				}
//				else {
//					combainedMatrix.matrix = nullptr;
//				}
//			}
//			else {
//				if (matrixFromFile.rows > 0 && matrixFromFile.cols > 0) {
//					matrixFromFile.matrix = new double* [matrixFromFile.rows];
//					for (size_t i = 0; i < matrixFromFile.rows; i++) {
//						matrixFromFile.matrix[i] = new double[matrixFromFile.cols];
//						if (!infile.read(reinterpret_cast<char*>(matrixFromFile.matrix[i]), matrixFromFile.cols * sizeof(double))) {
//							std::cerr << "   Error writing value from file";
//							break;
//						}
//					}
//
//				}
//			}
//
//
//			/*std::cout << "OK";
//			system("pause");*/
//
//			/*for (size_t i = 0; i < saveMatrix.rows; i++) {
//				for (size_t j = 0; j < saveMatrix.cols; j++) {
//					newMatrix.matrix[i][j] = saveMatrix.matrix[i][j];
//				}
//			}*/
//
//
//
//			/*size_t r = 0, c = 0;
//			for (size_t i = 0; i < matrix.rows; i++) {
//				for (size_t j = 0; j < matrix.cols; j++) {
//					newMatrix.matrix[saveMatrix.rows + i][j] = matrix.matrix[i][j];
//					c++;
//				}
//				r++;
//			}
//			std::cout << "   Rows :" << newRows << "   Cols :" << newCols << "\n\n";
//
//			for (size_t i = 0; i < saveMatrix.rows; i++) {
//				for (size_t j = 0; j < saveMatrix.cols; j++) {
//					matrix.matrix[i][j] = saveMatrix.matrix[i][j];
//				std::cout << "\n";
//			}
//			outTableMatrixGraf(hdc, newMatrix.matrix, newMatrix.rows, newMatrix.cols, 400, 120, 50, 50, 16, 15);
//
//			_getch();
//		}*/
//			}
//	} else {
//
//
//			std::ofstream file(nameFile, mode | std::ios::binary);
//			LINES(3);
//			CURSOR(3, 5);
//			file.write(reinterpret_cast<char*>(&matrix.rows), sizeof(size_t));
//			file.write(reinterpret_cast<char*>(&matrix.cols), sizeof(size_t));
//			for (size_t i = 0; i < matrix.rows; i++)
//			{
//				for (size_t j = 0; j < matrix.cols; j++)
//				{
//					file.write(reinterpret_cast<char*>(&matrix.matrix[i][j]), sizeof(matrix.matrix[i][j]));
//				}
//			}
//			file.clear();
//			file.close();
//			std::cout << "\n\n   ������ ������� �������� � ���� => ";
//			setColor(10, 0);
//			std::cout << nameFile << std::endl;
//	}
//
// }

size_t manual_max(size_t a, size_t b)
{
	return (a > b) ? a : b;
}

void writeMatrixBin(Matrix &matrixToAdd)
{
	std::string nameFile = getNameFile();
	Matrix combinedMatrix;
	bool proceed_to_write_combined_matrix = false;

	std::ifstream file_check(nameFile, std::ios::binary);
	bool file_bin_exist = file_check.good();
	file_check.close();

	if (file_bin_exist)
	{
		std::cout << "\n���� '" << nameFile << "' ����������. ���������� ������? (y/n): ";
		char ch;
		std::cin >> ch;
		while (std::cin.get() != '\n')
			;

		if (ch == 'y' || ch == 'Y')
		{
			Matrix matrixFromFile;
			std::ifstream infile(nameFile, std::ios::binary);

			if (!infile.is_open())
			{
				std::cerr << "������: �� ������� ������� ���� '" << nameFile << "' ��� ������. ����� ������� ����� ������� � ������� ��� ����������.\n";
			}
			else
			{
				if (!infile.read(reinterpret_cast<char *>(&matrixFromFile.rows), sizeof(size_t)) ||
					!infile.read(reinterpret_cast<char *>(&matrixFromFile.cols), sizeof(size_t)))
				{
					std::cerr << "������: �� ������� ��������� ������� �� ����� '" << nameFile << "'. ����� ������� ����� ������� � ������� ��� ����������.\n";
				}
				else
				{
					bool read_data_ok = true;
					if (matrixFromFile.rows > 0 && matrixFromFile.cols > 0)
					{
						matrixFromFile.matrix = new double *[matrixFromFile.rows];
						for (size_t i = 0; i < matrixFromFile.rows; ++i)
						{
							matrixFromFile.matrix[i] = new double[matrixFromFile.cols];
							if (!infile.read(reinterpret_cast<char *>(matrixFromFile.matrix[i]), matrixFromFile.cols * sizeof(double)))
							{
								std::cerr << "������ ��� ������ ������ ������ " << i << " �� ����� '" << nameFile << "'.\n";
								read_data_ok = false;
								break;
							}
						}
					}
					else
					{
						matrixFromFile.matrix = nullptr;
					}

					if (read_data_ok)
					{
						combinedMatrix.rows = matrixFromFile.rows + matrixToAdd.rows;
						if (matrixFromFile.cols == 0 && matrixToAdd.cols == 0)
						{
							combinedMatrix.cols = 0;
						}
						else
						{
							combinedMatrix.cols = manual_max(matrixFromFile.cols, matrixToAdd.cols);
						}

						if (combinedMatrix.rows > 0)
						{
							combinedMatrix.matrix = new double *[combinedMatrix.rows];
							for (size_t i = 0; i < combinedMatrix.rows; ++i)
							{
								if (combinedMatrix.cols > 0)
								{
									combinedMatrix.matrix[i] = new double[combinedMatrix.cols];
									for (size_t j = 0; j < combinedMatrix.cols; ++j)
									{
										combinedMatrix.matrix[i][j] = 0.0; // �������
									}
								}
								else
								{
									combinedMatrix.matrix[i] = nullptr;
								}
							}
						}
						else
						{
							combinedMatrix.matrix = nullptr;
						}

						if (matrixFromFile.matrix && matrixFromFile.rows > 0 && matrixFromFile.cols > 0)
						{
							for (size_t i = 0; i < matrixFromFile.rows; ++i)
							{
								for (size_t j = 0; j < matrixFromFile.cols; ++j)
								{
									if (j < combinedMatrix.cols)
										combinedMatrix.matrix[i][j] = matrixFromFile.matrix[i][j];
								}
							}
						}

						if (matrixToAdd.matrix && matrixToAdd.rows > 0 && matrixToAdd.cols > 0)
						{
							for (size_t i = 0; i < matrixToAdd.rows; ++i)
							{
								for (size_t j = 0; j < matrixToAdd.cols; ++j)
								{
									if (j < combinedMatrix.cols)
										combinedMatrix.matrix[matrixFromFile.rows + i][j] = matrixToAdd.matrix[i][j];
								}
							}
						}
						proceed_to_write_combined_matrix = true;
					}
					else
					{
						std::cerr << "�������� �������� ��-�� ������ ������. ����� ������� ����� ������� � ������� ��� ����������.\n";
					}
				}
				infile.close();
			}
		}
		else
		{
			std::cout << "���� ����� ����������� ����� ��������.\n";
		}
	}
	else
	{
		std::cout << "��������� ����� ����.\n";
	}

	if (!proceed_to_write_combined_matrix)
	{

		combinedMatrix.rows = matrixToAdd.rows;
		combinedMatrix.cols = matrixToAdd.cols;
		if (combinedMatrix.rows > 0)
		{
			combinedMatrix.matrix = new double *[combinedMatrix.rows];
			for (size_t i = 0; i < combinedMatrix.rows; ++i)
			{
				if (combinedMatrix.cols > 0)
				{
					combinedMatrix.matrix[i] = new double[combinedMatrix.cols];
					if (matrixToAdd.matrix && matrixToAdd.matrix[i])
					{
						for (size_t j = 0; j < combinedMatrix.cols; ++j)
						{
							combinedMatrix.matrix[i][j] = matrixToAdd.matrix[i][j];
						}
					}
					else
					{
						for (size_t j = 0; j < combinedMatrix.cols; ++j)
						{
							combinedMatrix.matrix[i][j] = 0.0;
						}
					}
				}
				else
				{
					combinedMatrix.matrix[i] = nullptr;
				}
			}
		}
		else
		{
			combinedMatrix.matrix = nullptr;
		}
		proceed_to_write_combined_matrix = true;
	}
	if (proceed_to_write_combined_matrix)
	{
		std::ofstream outfile(nameFile, std::ios::out | std::ios::binary | std::ios::trunc);
		if (!outfile.is_open())
		{
			std::cerr << "������: �� ������� ������� ���� '" << nameFile << "' ��� ������.\n";
		}
		else
		{
			outfile.write(reinterpret_cast<const char *>(&combinedMatrix.rows), sizeof(size_t));
			outfile.write(reinterpret_cast<const char *>(&combinedMatrix.cols), sizeof(size_t));

			bool write_ok = true;
			if (combinedMatrix.matrix && combinedMatrix.rows > 0 && combinedMatrix.cols > 0)
			{
				for (size_t i = 0; i < combinedMatrix.rows; ++i)
				{
					if (combinedMatrix.matrix[i])
					{
						if (!outfile.write(reinterpret_cast<const char *>(combinedMatrix.matrix[i]), combinedMatrix.cols * sizeof(double)))
						{
							std::cerr << "������ ��� ������ ������ ������ " << i << " � ���� '" << nameFile << "'.\n";
							write_ok = false;
							break;
						}
					}
					else
					{
						std::cerr << "���������� ������: ������ " << i << " � combinedMatrix ����� null ��� cols > 0.\n";
						write_ok = false;
						break;
					}
				}
			}
			outfile.close();

			if (outfile.fail() && write_ok)
			{
				std::cerr << "��������� ������ ��� ������ ��� �������� ����� '" << nameFile << "'.\n";
				write_ok = false;
			}

			if (write_ok)
			{
				std::cout << "������� ������� �������� � ����: " << nameFile << "\n";
				std::cout << "�������� �������: " << combinedMatrix.rows << "x" << combinedMatrix.cols << "\n";
			}
			else
			{
				std::cout << "������ ������� � ���� " << nameFile << " �� �������.\n";
			}
		}
	}
	else
	{
		std::cout << "������ � ���� ��������, ��� ��� ������� ��� ������ �� ���� ������������.\n";
	}
}

void readMatrixTxt(Matrix &matrix)
{
	std::string nameFile = getNameFile();
	std::ifstream file(nameFile, std::ios::binary);
	bool indicator = file.is_open() ? true : false;

	if (indicator)
	{
		std::cout << "\n   ���� ������" << std::endl;
		std::ifstream file(nameFile);
		size_t rows = 0, cols = 0;

		// Calculating the numbers of rows and columns in the matrix
		try
		{
			std::string line;
			bool cols_determined = false;

			while (std::getline(file, line))
			{
				if (line.empty() || line.find_first_not_of("\n\r\t\b\f") == std::string::npos)
				{
					continue;
				}
				rows++;
			}

			file.open(nameFile);
			file.clear();
			file.seekg(0, std::ios::beg);
			while (std::getline(file, line))
			{
				std::stringstream ss(line);
				std::string word;
				size_t current_cols = 0;
				while (ss >> word)
				{
					current_cols++;
				}
				if (current_cols > 0)
				{
					if (!cols_determined)
					{
						cols = current_cols;
						cols_determined = true;
					}
					else
					{
						if (current_cols > cols)
						{
							cols = current_cols;
						}
					}
					cols = current_cols;
				}
				/*if (cols == 0)
				{
					std::cerr << "Error, first line is empty!";
					cols = 0;
				}*/
				ss.clear();
			}
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: " << e.what();
		}

		// Recording an elements in the matrix
		matrix.changeSize(rows, cols);
		/*for (size_t i = 0; i < matrix.rows; i++) {
			delete matrix.matrix[i];
		}
		delete[] matrix.matrix;
		try {
			matrix.matrix = new double* [rows];
			for (size_t i = 0; i < rows; i++) { matrix.matrix[i] = new double[cols](); }
		}
		catch (const std::bad_alloc& e) { std::cerr << "Error: " << e.what(); }*/

		file.open(nameFile);
		file.clear();
		file.seekg(0, std::ios::beg);
		std::string data;
		size_t i = 0;

		while (std::getline(file, data))
		{
			if (data.empty() || data.find_first_not_of("\n\v\r\b\t") == std::string::npos)
			{
				continue;
			}
			std::stringstream ss(data);
			double value = 0;
			std::string item;
			size_t charProcessed = 0;
			size_t j = 0;

			while (ss >> item)
			{
				try
				{
					for (size_t i = 0; i < item.length(); i++)
					{
						if (item[i] == '.')
						{
							item[i] = separate;
						}
						if (!((item[i] >= '0' && item[i] <= '9') || item[i] == '+' || item[i] == '-' || item[i] == 'e' || item[i] == 'E' || item[i] == '.' || item[i] == ','))
						{
							value = 0;
						};
					}
					value = std::stod(item, &charProcessed);
					matrix.matrix[i][j] = value;

					j++;
				}
				catch (const std::exception)
				{
					setColor(4, 0);
					std::cerr << "\n\n\n\n   ������: ���������������� ������� � ������ => "
							  << i + 1 << " � ������� =>" << j + 1 << " ��� ������� �� 0." << std::endl
							  << "   ���������� �������� �������� � �������� ���� ������" << std::endl;
					setColor(7, 0);
				}
				catch (const std::invalid_argument &e)
				{
					std::cerr << "\n\n\n\n   Error: " << e.what();
				}
				catch (const std::out_of_range &e)
				{
					std::cerr << "\n\n\n\n   Error: " << e.what();
				}
			}
			i++;
		}

		// Output an elements
		char key;
		do
		{
			system("cls");
			std::cout << "   1 - �������\n   2 - ������ ��������\n\n"
					  << std::endl;
			outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);

			key = _getch();

			if (key == '1')
			{
				system("cls");
				solution(matrix);
				_getch();
			}
			else if (key == '2')
			{
				system("cls");
				outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
				matrix.changeEl(matrix, matrix.rows, matrix.cols);
				std::ofstream file(nameFile, std::ios::trunc);
				for (size_t i = 0; i < matrix.rows; i++)
				{
					for (size_t j = 0; j < matrix.cols; j++)
					{
						file << matrix.matrix[i][j] << " ";
					}
					file << "\n";
				}
				outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
				_getch();
			}
			else if (key == 27)
			{
				return;
			}
			else
			{
				std::cerr << "   ����������� �������...";
				return;
			}
		} while (key != 27);
	}
	else
	{
		std::cerr << "\n   ������ ����� ���..." << std::endl;
	}
}

void readMatrixBin(Matrix &matrix)
{
	std::string nameFile = getNameFile();
	std::ifstream file(nameFile);
	bool indicator = file.is_open() ? true : false;

	if (indicator)
	{
		std::cout << "\n   ���� ������" << std::endl;

		size_t rows = 0, cols = 0;
		// std::string nameFile = getNameFile();
		std::ifstream file(nameFile, std::ios::binary);

		// Calculating the numbers of rows and columns in the matrix

		file.read(reinterpret_cast<char *>(&rows), sizeof(size_t));
		file.read(reinterpret_cast<char *>(&cols), sizeof(size_t));

		matrix.changeSize(rows, cols);

		for (size_t i = 0; i < rows; i++)
		{
			file.read(reinterpret_cast<char *>(matrix.matrix[i]), cols * sizeof(double));
			if (!file)
			{
				std::cerr << "   �� ������� �������� ��� ������ " << i << std::endl;
				std::cerr << "   ����������� ����: " << (cols * sizeof(double)) << "  ���������� " << file.gcount() << std::endl;
			}
		}
		file.close();

		outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);

		// Output an elements

		char key;
		do
		{
			system("cls");
			std::cout << "   1 - �������\n   2 - ������ ��������\n\n"
					  << std::endl;
			outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);

			key = _getch();

			if (key == '1')
			{
				system("cls");
				solution(matrix);
				_getch();
			}
			else if (key == '2')
			{
				system("cls");
				outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
				matrix.changeEl(matrix, matrix.rows, matrix.cols);
				std::ofstream file(nameFile, std::ios::binary | std::ios::trunc);
				file.write(reinterpret_cast<char *>(&matrix.rows), sizeof(size_t));
				file.write(reinterpret_cast<char *>(&matrix.cols), sizeof(size_t));
				for (size_t i = 0; i < matrix.rows; i++)
				{
					for (size_t j = 0; j < matrix.cols; j++)
					{
						file.write(reinterpret_cast<char *>(&matrix.matrix[i][j]), sizeof(matrix.matrix[i][j]));
					}
				}
				outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
				_getch();
			}
			else if (key == 27)
			{
				return;
			}
			else
			{
				std::cerr << "   ����������� �������...";
				return;
			}
		} while (key != 27);
	}
	else
	{
		std::cerr << "\n   ������ ����� ���..." << std::endl;
	}
}

void clearSpace(Matrix &matrix)
{
	if (!(matrix.matrix == nullptr || matrix.rows == 0 || matrix.cols == 0))
	{
		for (size_t i = 0; i < matrix.rows; i++)
		{
			for (size_t j = 0; j < matrix.cols; j++)
			{
				matrix.matrix[i][j] = 0;
			}
		}
		setColor(10, 0);
		std::cout << "   ������������ �������!" << std::endl;
	}
	else
	{
		setColor(4, 0);
		std::cout << "   ������� �� ���� �������..." << std::endl;
	}
	setColor(7, 0);
}

void readMatrixFile(Matrix &matrix)
{
	std::cout << "   �������� ��� ����� ��� ����������" << std::endl;
	std::cout << "   1 - ��������� ����\n   2 - �������� ����";
	size_t key = _getch();
	if (key == '1')
	{
		system("cls");
		readMatrixTxt(matrix);
	}
	else if (key == '2')
	{
		std::cout << "   1 - �������\n   2 - ������ ��������\n"
				  << std::endl;
		system("cls");
		readMatrixBin(matrix);
	}
	else
	{
		return;
	}
}

void saveMatrixFile(Matrix &matrix)
{
	if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0))
	{
		std::cout << "   �������� ��� ����� ��� ����������" << std::endl;
		std::cout << "   1 - ��������� ����\n   2 - �������� ����" << std::endl;
		size_t key = _getch();
		if (key == '1')
		{
			system("cls");
			writeMatrixTxt(matrix);
			_getch();
		}
		else if (key == '2')
		{
			writeMatrixBin(matrix);
			_getch();
		}
		else
		{
			return;
		}
	}
	else
	{
		std::cerr << "   ����� ���� �����...";
		_getch();
	}
}

void copyMatrix(Matrix &matrix, Matrix &reserveMatrix)
{
	reserveMatrix.changeSize(matrix.rows, matrix.cols);
	for (size_t i = 0; i < matrix.rows; i++)
	{
		for (size_t j = 0; j < matrix.cols; j++)
		{
			reserveMatrix.matrix[i][j] = matrix.matrix[i][j];
		}
	}
}

void insertMatrix(Matrix &matrix, Matrix &reserveMatrix)
{
	if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0))
	{
		char ch;
		do
		{
			system("cls");
			std::cout << "\n\n   1 - ��������� �������\n   2 - �������� ������� �� ����������� �������\n   3 - ������������ � ������� ����������� �������\n\n   4 - �������� ������\n   5 - ������� �������\n   6 - �������� ������ � �������\n\n   7 - ������� ������\n   8 - ������� �������\n   9 - ������� ������ � �������\n\n   0 - ���������������\n\n\n";
			outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
			ch = _getch();
			switch (ch)
			{
			case '1':
			{
				reserveMatrix.changeSize(matrix.rows, matrix.cols);
				for (size_t i = 0; i < reserveMatrix.rows; i++)
				{
					for (size_t j = 0; j < reserveMatrix.cols; j++)
					{
						reserveMatrix.matrix[i][j] = matrix.matrix[i][j];
					}
				}
				setColor(10, 0);
				std::cout << "   ������� �������� " << matrix.rows << " x " << matrix.cols << " ���������";
				Sleep(1000);
				clearLine(7, 0, 8, 15);
				BACK(30);
				setColor(7, 0);
				break;
			}
			case '2':
			{
				if (!(reserveMatrix.matrix == nullptr || reserveMatrix.rows <= 0 || reserveMatrix.cols <= 0))
				{
					size_t oldRows = matrix.rows;
					size_t oldCols = matrix.cols;
					matrix.changeSize(reserveMatrix.rows, reserveMatrix.cols);
					for (size_t i = 0; i < matrix.rows; i++)
					{
						for (size_t j = 0; j < matrix.cols; j++)
						{
							matrix.matrix[i][j] = reserveMatrix.matrix[i][j];
						}
					}
					setColor(10, 0);
					std::cout << "   ������� �������� " << oldRows << " x " << oldCols << " �������� �� �����������,"
							  << " �������� " << reserveMatrix.rows << " x " << reserveMatrix.cols;
					Sleep(3000);
					setColor(7, 0);
				}
				else
				{
					std::cout << "   ����������� ����������� �������...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}
				break;
			}
			case '3':
			{
				if (!(reserveMatrix.matrix == nullptr || reserveMatrix.rows <= 0 || reserveMatrix.cols <= 0))
				{
					int newCols = reserveMatrix.cols > matrix.cols ? reserveMatrix.cols : matrix.cols;
					int newRows = matrix.rows + reserveMatrix.rows;
					Matrix copySaveMatrix(reserveMatrix.rows, reserveMatrix.cols);

					size_t oldRows = matrix.rows;
					size_t oldCols = matrix.cols;

					size_t nLine = 0, nCol = 0; // ���������� ��� ��������� �������

					// Copied reserveMatrix
					copyMatrix(reserveMatrix, copySaveMatrix);

					// Copied matrix
					copyMatrix(matrix, reserveMatrix);

					// fill current matrix value from reservMatrix (copied old matrix.matrix)
					matrix.changeSize(newRows, newCols);
					for (size_t i = 0; i < reserveMatrix.rows; i++)
					{
						for (size_t j = 0; j < reserveMatrix.cols; j++)
						{
							matrix.matrix[i][j] = reserveMatrix.matrix[i][j];
						}
					}

					bool swapped;
					for (size_t i = reserveMatrix.rows; i < matrix.rows; i++)
					{
						swapped = false;
						if (!(nLine == copySaveMatrix.rows))
						{
							swapped = true;
						};
						nCol = 0;
						for (size_t j = 0; j < matrix.cols; j++)
						{
							if (swapped == true && nCol != copySaveMatrix.cols)
							{
								matrix.matrix[i][j] = copySaveMatrix.matrix[nLine][nCol];
								nCol++;
							}
							else
							{
								matrix.matrix[i][j] = 0;
							}
						}
						nLine++;
					}
					setColor(10, 0);
					std::cout << "   ������� �������� " << oldRows << " x " << oldCols << " �������� �� �����������,"
							  << " �������� " << copySaveMatrix.rows << " x " << copySaveMatrix.cols;
					Sleep(3000);
					setColor(7, 0);
				}
				else
				{
					std::cout << "   ����������� ����������� �������...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}
				break;
			}
			case '4':
			{
				if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0))
				{
					char kb;
					int newLine1;
					int nLines;
					std::cout << "   ������� ����� ��������?" << std::endl;
					;
					std::cin >> nLines;
					size_t newRows = matrix.rows + nLines;
					Matrix saveCurrentMatrix;
					copyMatrix(matrix, saveCurrentMatrix);
					matrix.changeSize(newRows, matrix.cols);

					std::cout << "   ������� ����� ������ ����� �������\n ����� ��������� ����� ������" << std::endl;
					ClearCin;
					std::cin >> newLine1;
					if (!(newLine1 >= 0 && newLine1 < matrix.rows + 1) || std::cin.fail())
					{
						std::cerr << "\n   ������� ���������� ����� ������";
						Sleep(400);
						break;
					}

					size_t r = 0, c = 0;
					for (size_t i = 0; i < newLine1; i++)
					{
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++)
						{
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}

					for (size_t i = newLine1 + nLines; i < matrix.rows; i++)
					{
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++)
						{
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}

					std::cout << "   ���������?\n   1 - ��" << std::endl;
					kb = _getch();
					if (kb == '1')
					{

						std::cout << "   ������� ����� ��������" << std::endl;
						for (size_t i = newLine1; i < newLine1 + nLines; i++)
						{
							for (size_t j = 0; j < matrix.cols; j++)
							{
								outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
								int newValue;
								std::cout << "   ����� �������� [" << i + 1 << "][" << j + 1 << "] = ";
								std::cin >> newValue;
								matrix.matrix[i][j] = newValue;
							}
						}
					}

					setColor(10, 0);
					std::cout << "   ������� � ����� �������� " << matrix.rows << " x " << matrix.cols << " �������a";
					Sleep(3000);
					setColor(7, 0);
				}
				else
				{
					std::cout << "   ����������� ����������� �������...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}
				break;
			}
			case '5':
			{
				if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0))
				{
					char kb;
					int newLine1;
					int nLines;
					std::cout << "   ������� �������� ��������?" << std::endl;
					std::cin >> nLines;
					size_t newCols = matrix.cols + nLines;
					Matrix saveCurrentMatrix;
					copyMatrix(matrix, saveCurrentMatrix);
					matrix.changeSize(matrix.rows, newCols);

					std::cout << "   ������� ����� ������� ����� ��������\n   ����� ��������� ����� �������" << std::endl;
					ClearCin;
					std::cin >> newLine1;
					if (!(newLine1 >= 0 && newLine1 < matrix.cols + 1) || std::cin.fail())
					{
						std::cerr << "\n   ������� ���������� ����� ������";
						Sleep(400);
						break;
					}

					size_t r = 0, c = 0;
					for (size_t i = 0; i < saveCurrentMatrix.rows; i++)
					{
						c = 0;
						for (size_t j = 0; j < newLine1; j++)
						{
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}
					r = 0;
					for (size_t i = 0; i < saveCurrentMatrix.rows; i++)
					{
						c = newLine1;
						for (size_t j = newLine1 + nLines; j < matrix.cols; j++)
						{
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}

					std::cout << "   ���������?\n   1 - ��" << std::endl;
					kb = _getch();
					if (kb == '1')
					{
						std::cout << "   ������� ����� ��������" << std::endl;
						for (size_t i = 0; i < matrix.rows; i++)
						{
							for (size_t j = newLine1; j < newLine1 + nLines; j++)
							{
								outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
								int newValue;
								std::cout << "   ����� �������� [" << j + 1 << "][" << i + 1 << "] = ";
								std::cin >> newValue;
								matrix.matrix[i][j] = newValue;
							}
						}
					}

					setColor(10, 0);
					std::cout << "   ������� � ����� �������� " << matrix.rows << " x " << matrix.cols << " �������a";
					Sleep(3000);
					setColor(7, 0);
				}
				else
				{
					std::cout << "   ����������� ����������� �������...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}
				break;
			}
			case '6':
			{
				if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0))
				{
					char kb;
					int newLine1;
					int nLines;
					std::cout << "   ������� ����� ��������?" << std::endl;
					std::cin >> nLines;
					size_t newRows = matrix.rows + nLines;
					Matrix saveCurrentMatrix;
					copyMatrix(matrix, saveCurrentMatrix);
					matrix.changeSize(newRows, matrix.cols);

					std::cout << "   ������� ����� ������ ����� �������\n   ����� ��������� ����� ������" << std::endl;
					ClearCin;
					std::cin >> newLine1;
					if (!(newLine1 >= 0 && newLine1 < matrix.rows + 1))
					{
						std::cerr << "\n   ������� ���������� ����� ������";
						Sleep(400);
						break;
					}

					size_t r = 0, c = 0;
					for (size_t i = 0; i < newLine1; i++)
					{
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++)
						{
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}

					for (size_t i = newLine1 + nLines; i < matrix.rows; i++)
					{
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++)
						{
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}

					std::cout << "   ���������?\n   1 - ��" << std::endl;
					kb = _getch();
					if (kb == '1')
					{

						std::cout << "   ������� ����� ��������" << std::endl;
						for (size_t i = newLine1; i < newLine1 + nLines; i++)
						{
							for (size_t j = 0; j < matrix.cols; j++)
							{
								outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
								int newValue;
								std::cout << "   ����� �������� [" << i + 1 << "][" << j + 1 << "] = ";
								std::cin >> newValue;
								std::cout << std::endl;
								if (std::cin.fail() || std::cin.bad())
								{
									const size_t MAX_LINE_IGNORE = 256;
									std::cin.clear();
									std::cin.ignore(MAX_LINE_IGNORE, '\n');
									j--;
									continue;
								}
								matrix.matrix[i][j] = newValue;
							}
						}
					}
					outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);

					int newLine2;
					int nLines2;
					std::cout << "   ������� �������� ��������?" << std::endl;
					std::cin >> nLines2;
					size_t newCols = matrix.cols + nLines2;
					Matrix saveCurrentMatrix2;
					copyMatrix(matrix, saveCurrentMatrix2);
					matrix.changeSize(matrix.rows, newCols);

					std::cout << "   ������� ����� ������� ����� ��������\n   ����� ��������� ����� �������" << std::endl;
					ClearCin;
					std::cin >> newLine2;
					if (!(newLine2 >= 0 && newLine2 < matrix.cols + 1))
					{
						std::cerr << "\n   ������� ���������� ����� ������";
						Sleep(400);
						break;
					}

					r = 0, c = 0;
					for (size_t i = 0; i < saveCurrentMatrix2.rows; i++)
					{
						c = 0;
						for (size_t j = 0; j < newLine2; j++)
						{
							matrix.matrix[i][j] = saveCurrentMatrix2.matrix[r][c];
							c++;
						}
						r++;
					}
					r = 0;
					for (size_t i = 0; i < saveCurrentMatrix2.rows; i++)
					{
						c = newLine2;
						for (size_t j = newLine2 + nLines2; j < matrix.cols; j++)
						{
							matrix.matrix[i][j] = saveCurrentMatrix2.matrix[r][c];
							c++;
						}
						r++;
					}

					std::cout << "   ���������?\n   1 - ��" << std::endl;
					kb = _getch();
					if (kb == '1')
					{
						std::cout << "   ������� ����� ��������" << std::endl;
						for (size_t i = 0; i < matrix.rows; i++)
						{
							for (size_t j = newLine1; j < newLine1 + nLines; j++)
							{
								outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
								int newValue;
								std::cout << "   ����� �������� [" << j + 1 << "][" << i + 1 << "] = ";
								std::cin >> newValue;
								if (std::cin.fail() || std::cin.bad())
								{
									const size_t MAX_LINE_IGNORE = 256;
									std::cin.clear();
									std::cin.ignore(MAX_LINE_IGNORE, '\n');
									j--;
									continue;
								}
								matrix.matrix[i][j] = newValue;
							}
						}
					}

					setColor(10, 0);
					std::cout << "   ������� � ����� �������� " << matrix.rows << " x " << matrix.cols << " �������a";
					Sleep(3000);
					setColor(7, 0);
				}
				else
				{
					std::cout << "   ����������� ����������� �������...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}
				break;
			}

			case '7':
			{
				if (!(matrix.matrix == nullptr || matrix.rows <= 1 || matrix.cols <= 1))
				{
					std::cout << "   ������� ����� ������ ������ ����� �������" << std::endl;
					int deleteEl;
					std::cin >> deleteEl;
					size_t newRows = matrix.rows - 1;
					Matrix saveCurrentMatrix;
					copyMatrix(matrix, saveCurrentMatrix);
					matrix.changeSize(newRows, matrix.cols);

					size_t r = 0, c = 0;
					for (size_t i = 0; i < deleteEl - 1; i++)
					{
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++)
						{
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}
					r++;
					for (size_t i = deleteEl - 1; i < matrix.rows; i++)
					{
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++)
						{
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}

					setColor(10, 0);
					std::cout << "   ������� � ����� �������� " << matrix.rows << " x " << matrix.cols << " �������a";
					Sleep(3000);
					setColor(7, 0);
				}
				else
				{
					std::cout << "   ������� ��������� ������ �������...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}
				break;
			}
			case '8':
			{
				if (!(matrix.matrix == nullptr || matrix.rows <= 1 || matrix.cols <= 1))
				{
					std::cout << "   ������� ����� ������ ������ ����� �������" << std::endl;
					int deleteEl;
					std::cin >> deleteEl;
					size_t newCols = matrix.cols - 1;
					Matrix saveCurrentMatrix;
					copyMatrix(matrix, saveCurrentMatrix);
					matrix.changeSize(matrix.rows, newCols);

					size_t r = 0, c = 0;
					for (r = 0; r < saveCurrentMatrix.rows; r++)
					{
						c = 0;
						for (size_t j = 0; j < deleteEl - 1; j++)
						{
							matrix.matrix[r][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						c++;
						for (size_t j = deleteEl - 1; j < matrix.cols; j++)
						{
							matrix.matrix[r][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
					}

					setColor(10, 0);
					std::cout << "   ������� � ����� �������� " << matrix.rows << " x " << matrix.cols << " �������a";
					Sleep(3000);
					setColor(7, 0);
				}
				else
				{
					std::cout << "   ������� ��������� ������ �������...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}
				break;
			}
			case '9':
			{
				if (!(matrix.matrix == nullptr || matrix.rows <= 1 || matrix.cols <= 1))
				{
					std::cout << "   ������� ����� ������ ������ ����� �������" << std::endl;
					int deleteEl;
					std::cin >> deleteEl;
					size_t newRows = matrix.rows - 1;
					Matrix saveCurrentMatrix;
					copyMatrix(matrix, saveCurrentMatrix);
					matrix.changeSize(newRows, matrix.cols);

					size_t r = 0, c = 0;
					for (size_t i = 0; i < deleteEl - 1; i++)
					{
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++)
						{
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}
					r++;
					for (size_t i = deleteEl - 1; i < matrix.rows; i++)
					{
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++)
						{
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}

					std::cout << "   ������� ����� ������ ������ ����� �������" << std::endl;
					int deleteEl2;
					std::cin >> deleteEl2;
					size_t newCols = matrix.cols - 1;
					Matrix saveCurrentMatrix2;
					copyMatrix(matrix, saveCurrentMatrix2);
					matrix.changeSize(matrix.rows, newCols);

					r = 0, c = 0;
					for (r = 0; r < saveCurrentMatrix2.rows; r++)
					{
						c = 0;
						for (size_t j = 0; j < deleteEl2 - 1; j++)
						{
							matrix.matrix[r][j] = saveCurrentMatrix2.matrix[r][c];
							c++;
						}
						c++;
						for (size_t j = deleteEl2 - 1; j < matrix.cols; j++)
						{
							matrix.matrix[r][j] = saveCurrentMatrix2.matrix[r][c];
							c++;
						}
					}

					setColor(10, 0);
					std::cout << "   ������� � ����� �������� " << matrix.rows << " x " << matrix.cols << " �������a";
					Sleep(3000);
					setColor(7, 0);
				}
				else
				{
					std::cout << "   ������� ��������� ������ �������...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}

				break;
			}

			case '0':
			{
				if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0))
				{
					size_t originalRows = matrix.rows;
					size_t originalCols = matrix.cols;

					Matrix transporantMatrix(originalCols, originalRows);
					for (size_t i = 0; i < originalRows; i++)
					{
						for (size_t j = 0; j < originalCols; j++)
						{
							transporantMatrix.matrix[j][i] = matrix.matrix[i][j];
						}
					}

					matrix.changeSize(originalCols, originalRows);
					for (size_t i = 0; i < matrix.rows; i++)
					{
						for (size_t j = 0; j < matrix.cols; j++)
						{
							matrix.matrix[i][j] = transporantMatrix.matrix[i][j];
						}
					}
				}
				else
				{
					std::cerr << "   ������� �� ���� �������..." << std::endl;
				}
			}

			case 27:
				break;
			default:
				std::cerr << "\n   ������� ��������� �������";
				break;
			}

		} while (ch != 27);
	}
	else
	{
		std::cout << "   ������� �� �������..." << std::endl;
		_getch();
	}
};

void fillMatrixMenu(Matrix &matrix)
{
	if (!(matrix.matrix == nullptr || matrix.rows == 0 || matrix.cols == 0))
	{
		char ch;
		do
		{
			system("cls");
			info2();
			std::cout << "\n\n   1 - ��������� ��������� �������\n   2 - ��������� �� �������\n   esc - �����\n\n";
			outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
			ch = _getch();

			switch (ch)
			{
			case '1':
				matrix.fillMatrix(matrix.rows, matrix.cols, 3, 15);
				break;
			case '2':
				matrix.changeEl(matrix, matrix.rows, matrix.cols);
				break;
			case 27:
				break;
			default:
				std::cout << "   �������� ������� �� ������������" << std::endl;
				break;
			}
		} while (ch != 27);
	}
	else
	{
		std::cout << "   M������ �� ���� �������..." << std::endl;
		_getch();
	}
}

void outTableMatrixGraf(HDC hdc,
						double **matrix, // ������� ����� double
						size_t rows, size_t cols,
						int startX, int startY,		   // ��������� ���������� �������
						int cellWidth, int cellHeight, // ������� ������
						int headerFontSize = 16,	   // ������ ������ ����������
						int dataFontSize = 15)		   // ������ ������ ������
{
	if (hdc == NULL)
	{
		return;
	}
	if (matrix == nullptr || rows <= 0 || cols <= 0)
	{
		std::cout << "   ����� ���� �����..." << std::endl;
		return;
	}
	else
	{

		if (cellWidth <= 0 || cellHeight <= 0)
		{
			return;
		}

		char textBuffer[64];   // ����� ��� ���������� �������� �����, ��������������� � ������
		char formatString[16]; // ����� ��� ������ ������� (��������, "%.2f")

		// ������� ������ ������� ��� double �� ������ ��������� precision
		sprintf_s(formatString, sizeof(formatString), "%%.%df", 2); // ��������, ���� precision=2, �� formatString ����� "%.2f"

		// --- ��������� ������� ---
		HFONT hFontHeaders = CreateFontA(headerFontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
										 RUSSIAN_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
										 DEFAULT_QUALITY, FF_DONTCARE | VARIABLE_PITCH, "Terminal");

		HFONT hFontData = CreateFontA(dataFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
									  RUSSIAN_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
									  DEFAULT_QUALITY, FF_DONTCARE | VARIABLE_PITCH, "Terminal");

		// --- ��������� ���� ��� ����� ---
		HPEN hPenGrid = CreatePen(PS_SOLID, 1, RGB(255, 255, 255)); // ������-����� ����

		// ��������� ������ GDI �������, ����� ����� ������������

		COLORREF cellFillColor = RGB(150, 150, 150);

		HBRUSH hcellBrush = CreateSolidBrush(cellFillColor);
		HBRUSH hOldFont = (HBRUSH)SelectObject(hdc, hcellBrush);
		HPEN hOldPen = (HPEN)SelectObject(hdc, GetStockObject(BLACK_PEN));

		int oldBkMode = SetBkMode(hdc, RGB(157, 56, 188));
		SetBkMode(hdc, RGB(192, 192, 192)); // ������ ��� ������ ����������

		// --- 1. ������ ������ �������� (���������) ---
		if (hFontHeaders)
			SelectObject(hdc, hFontHeaders);   // �������� ����� ��� ����������
		SetTextColor(hdc, RGB(255, 255, 255)); // �����-����� ���� ��� ����������

		for (int j = 0; j < cols; ++j)
		{
			int x_header_col = startX + cellWidth + j * cellWidth; // X-���������� ������ ��������� �������
			int y_header_col = startY;							   // Y-���������� ������ ��������� �������

			sprintf_s(textBuffer, sizeof(textBuffer), "%d", j + 1); // ����������� ����� ������� � ������

			SIZE textSize;
			GetTextExtentPoint32A(hdc, textBuffer, strlen(textBuffer), &textSize); // ������ ������ ������
			// ������� ����� �� ������ ������ ���������
			TextOutA(hdc,
					 x_header_col + (cellWidth - textSize.cx) / 2,
					 y_header_col + (cellHeight - textSize.cy) / 2,
					 textBuffer, strlen(textBuffer));
		}

		// --- 2. ������ ������ ����� (���������) ---
		// ����� � ���� ������ ��� ���������� ��� �����������
		for (int i = 0; i < rows; ++i)
		{
			int x_header_row = startX;								 // X-���������� ������ ��������� ������
			int y_header_row = startY + cellHeight + i * cellHeight; // Y-���������� ������ ��������� ������

			sprintf_s(textBuffer, sizeof(textBuffer), "%d", i + 1); // ����������� ����� ������ � ������

			SIZE textSize;
			GetTextExtentPoint32A(hdc, textBuffer, strlen(textBuffer), &textSize);
			TextOutA(hdc,
					 x_header_row + (cellWidth - textSize.cx) / 2,
					 y_header_row + (cellHeight - textSize.cy) / 2,
					 textBuffer, strlen(textBuffer));
		}

		// --- 3. ������ ������ ������� � ����� ---
		if (hFontData)
			SelectObject(hdc, hFontData);	   // �������� ����� ��� ������
		SetTextColor(hdc, RGB(255, 255, 255)); // ������ ���� ��� ������
		if (hPenGrid)
			SelectObject(hdc, hPenGrid); // �������� ���� ��� ��������� �����

		for (int i = 0; i < rows; ++i)
		{

			if (matrix[i] == nullptr)
			{ // ��������, ��� ������ ������� ��������
				// ����� �������� ����� ������ ��� ������ ����������
				continue;
			}
			for (int j = 0; j < cols; ++j)
			{
				int cellX = startX + cellWidth + j * cellWidth;	  // X-���������� ������� ������ ������
				int cellY = startY + cellHeight + i * cellHeight; // Y-���������� ������� ������ ������

				// ����������� ����� double �� ������� � ������
				sprintf_s(textBuffer, sizeof(textBuffer), formatString, matrix[i][j]);

				// ������ ����� ������ (���� ���� ��� ����� �������)
				if (hPenGrid)
				{
					Rectangle(hdc, cellX, cellY, cellX + cellWidth, cellY + cellHeight);
				}

				SIZE textSize;
				GetTextExtentPoint32A(hdc, textBuffer, strlen(textBuffer), &textSize);

				// ������� ����� (������) �� ������ ������
				TextOutA(hdc,
						 cellX + (cellWidth - textSize.cx) / 2,
						 cellY + (cellHeight - textSize.cy) / 2,
						 textBuffer, strlen(textBuffer));
			}
		}

		// --- ������� GDI �������� ---
		SetBkMode(hdc, oldBkMode);
		SelectObject(hdc, hOldFont); // ��������������� ������ �����
		if (hFontHeaders)
			DeleteObject(hFontHeaders); // ������� ��������� �����
		if (hFontData)
			DeleteObject(hFontData); // ������� ��������� �����

		SelectObject(hdc, hOldPen); // ��������������� ������ ����
		if (hPenGrid)
			DeleteObject(hPenGrid); // ������� ��������� ����
	}
}

void menuLab_3()
{
	setlocale(LC_ALL, "rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	SetDefBkColor(CL_BLACK);

	size_t key;

	do
	{
		system("cls");

		Text(hdc, 50, 0, "���� ������������ ������ �3 - 4", RGB(255, 255, 255), RGB(0, 0, 0), 25);
		Text(hdc, 50, 50, "0 - ������� ������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 100, "1 - ������ ������� �������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 150, "2 - ��������� �������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 200, "3 - �������� ������� �������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 250, "4 - ���������/��������/������������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 300, "5 - ��������� ������� � �����", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 350, "6 - ������� �� ���������� �� �����", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 400, "7 - ������� �� ���������� �� ������ �������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 450, "8 - ������� ������������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 500, "9 - �������� ����������", RGB(255, 255, 255), RGB(15, 5, 77), 25);

		Text(hdc, 50, 550, "ESC - �����", RGB(255, 255, 255), RGB(157, 56, 188), 25);

		key = _getch();

		switch (key)
		{
		case '0':
			// information about the task
			system("cls");
			info2();
			std::cout << "\n\n   ";
			system("pause");
			break;
		case '1':
		{
			// size
			system("cls");
			info2();
			setColor(14, 0);
			std::cout << "\n\n   ������������� ������� �������" << std::endl;
			setColor(15, 0);
			size_t newRows = setRow();
			size_t newCols = setCol();
			if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0 || newRows < matrix.rows || newCols < matrix.cols))
			{

				std::cout << "   1 - ��������� ������?" << std::endl;
				if (_getch() == '1')
				{
					Matrix helpMatrix;
					copyMatrix(matrix, helpMatrix);
					matrix.changeSize(newRows, newCols);
					for (size_t i = 0; i < helpMatrix.rows; i++)
					{
						for (size_t j = 0; j < helpMatrix.cols; j++)
						{
							matrix.matrix[i][j] = helpMatrix.matrix[i][j];
						}
					}
				}
				else
				{
					matrix.changeSize(newRows, newCols);
				}
			}
			else
			{
				matrix.changeSize(newRows, newCols);
			}
			setColor(10, 0);
			std::cout << "   ������� �������� " << newRows << " x " << newCols << " ������� �������" << std::endl;
			setColor(7, 0);
			std::cout << "\n\n   ";
			system("pause");
			break;
		}
		case '2':
		{
			// fill matrix
			system("cls");
			fillMatrixMenu(matrix);
			break;
		}
		case '3':
			// print current matrix
			system("cls");
			outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 10, 5, 50, 50);
			_getch();
			break;
		case '4':
			// insert / current
			system("cls");
			insertMatrix(matrix, reserveMatrix);
			break;
		case '5':
			// save matrix
			system("cls");
			saveMatrixFile(matrix);
			break;
		case '6':
			// solution with value from file
			system("cls");
			readMatrixFile(matrix);
			// solution(matrix);
			break;
		case '7':
			system("cls");
			solution(matrix);
			_getch();
			break;
		case '8':
			// clear space
			system("cls");
			clearSpace(matrix);
			_getch();
			break;
		case '9':
			// check directory
			system("cls");
			system("dir");
			_getch();
			break;
		case 27:
			break;
		default:
			std::cout << "\n������� ����������� �������" << std::endl;
		}
		setColor(7, 0);
	} while (key != 27);
}
