#include "menuLab_3.h"
#include "menuLab_1.h"
#include "matrix.h"


size_t setRow() {
	size_t rows;
	try {
		std::cout << "   Введите строку(-ки) (rows): ";
		std::cin >> rows;
		if (std::cin.bad() || std::cin.fail()) {
			while (std::cin.bad() || std::cin.fail()) {
				SPACEBACK(30);
				const size_t MAX_LINE_IGNORE = 256;
				std::cin.clear();
				std::cin.ignore(MAX_LINE_IGNORE, '\n');
				std::cout << "   Введите строку(-ки) (rows): ";
				std::cin >> rows;
			}
		}
	}
	catch (const std::exception& e) { std::cerr << "Error: " << e.what(); }
	return rows;
}

size_t setCol() {

	size_t cols;

	try {
		std::cout << "   Введите столбец(-цы) (cols): ";
		std::cin >> cols;
		if (std::cin.bad() || std::cin.fail()) {
			while (std::cin.bad() || std::cin.fail()) {
				SPACEBACK(30);
				const size_t MAX_LINE_IGNORE = 256;
				std::cin.clear();
				std::cin.ignore(MAX_LINE_IGNORE, '\n');
				std::cout << "   Введите столбец(-цы) (cols): ";
				std::cin >> cols;
			}
		}
	}
	catch (const std::exception& e) { std::cerr << "Error: " << e.what(); }
	return cols;
}

void Matrix::fillMatrix(size_t rows, size_t cols, size_t x, size_t y) {
	if (!(matrix == nullptr || rows <= 0 || cols <= 0)) {
		std::cout << "\n   Заполнение матрицы размером " << rows << " x " << cols << ":\n\n";
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				outTableMatrixGraf(hdc, matrix, rows, cols, 400, 120, 50, 50, 16, 15);
				CURSOR(x, y);
				SPACEBACK(30);
				std::cout << "   [" << i << "][" << j << "] = ";
				std::cin >> matrix[i][j];
				if (std::cin.fail() || std::cin.bad()) {
					const size_t MAX_LINE_IGNORE = 256;
					std::cin.clear();
					std::cin.ignore(MAX_LINE_IGNORE, '\n');
					j--;
					continue;
				}
			}
		}
		setColor(10, 0);
		std::cout << "   Матрица успешно заполнена!" << std::endl;
		Sleep(1000);
		setColor(7, 0);
	}
	else {
		std::cout << "   Здесь пока пусто..." << std::endl;
		
	}
}


void Matrix::changeEl(Matrix &matrix, size_t rows, size_t cols) {
	size_t nRow = setRow();
	size_t nCol = setCol();
	if (!(nRow < 0 || nRow > rows) && !(nCol < 0 || nCol > cols)) {

		double newValue;
		for (size_t i = 0; i < rows; i++) {
			for (size_t j = 0; j < cols; j++) {
				if (i == nRow - 1 && j == nCol - 1) {
					std::cout << "   Введите новое значение элемента:\n";
					std::cin >> newValue;
					matrix.matrix[i][j] = newValue;
					break;
				}
			}
		}
		setColor(10, 0);
		std::cout << "\n\n   Элемент усаешно изменен!" << std::endl;
		Sleep(1000);
		setColor(7, 0);
	}
	else {
		std::cerr << "   Введите действительные значения строки и столбца" << std::endl;
	}
}


Matrix matrix, reserveMatrix;



void clearLine(size_t x_0, size_t y_0, size_t x, size_t y) {
	cursorVision(true);
	for (int i = x_0; i < x; i++) {
		for (int j = y_0; j < y; j++) {
			std::cin.clear();
			SPACEBACK(30);
			CURSOR(j, i);
		}
	};
	cursorVision(false);
}



void info2() {
	setColor(14, 0);
	CURSOR(3, 2);
	std::cout << "Условие: \n";
	setColor(15, 0);
	CURSOR(3, 3);
	std::cout << "Для матрицы 5 х 6 образовать ряд состоящий из номеров столбцов с максимальным\n "
		<< "   элементом найденным в каждой строке.В каждом столбце с номером из образованного\n"
		<< "   ряда поменять местами первый и последний элементы";
	setColor(14, 0);
}




void solution(Matrix &matrix)
{
	if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0)) {
		info2();
		std::cout << "\n   Начальная матрица: ";
		outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 800, 10, 50, 50, 16, 15);
		size_t n = 0;
		int sizeArr = matrix.rows;
		double* colsNumb = new double[sizeArr];
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
		bool swapped = true;;
		size_t j = 0;
		while (swapped) {
			swapped = false;
			for (size_t i = 0; i < sizeArr - 1; i++) {
				if (colsNumb[i] > colsNumb[i + 1]) {
					double temp = colsNumb[i];
					colsNumb[i] = colsNumb[i + 1];
					colsNumb[i + 1] = temp;
					swapped = true;
				}
			}
		}

		if (sizeArr > 1) {
			size_t idx = 0;
			for (size_t i = 0; i < sizeArr; i++) {
				bool duplicate = false;
				for (size_t j = 0; j < idx; j++) {
					if (colsNumb[j] == colsNumb[i]) {
						duplicate = true;
						break;
					}
				}
				if (!duplicate) {
					colsNumb[idx] = colsNumb[i];
					idx++;
				}
			}
			sizeArr = idx;

		}

		LINES(10);
		std::cout << "   Номера столбцов в которых были"
			<< "\n   найдены максимальные элементы : " << std::endl;
		

		for (size_t i = 0; i < sizeArr; i++)
		{
			std::cout << "   " << colsNumb[i] + 1;
		}
		std::cout << std::endl;
		
		std::cout << "\n   Результат: " << std::endl;
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
	else {
		std::cerr << "\n   Матрица не была создана...";
	}
}

Matrix createMatrix(size_t rows, size_t cols) {
		Matrix matrix(rows, cols);
		return matrix;
}


static std::string getNameFile() {
	setColor(15, 0);
	std::string fileName;
	std::cout << "\n   Введите имя файла: ";
	setColor(10, 0);
	std::cin >> fileName;
	if (std::cin.fail() || std::cin.bad()) {
		while (std::cin.fail() || std::cin.bad()) { std::cin >>	fileName;}
	}
	setColor(14, 0);
	return fileName;

}




void writeMatrixTxt(Matrix& matrix)
{
	outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
	std::string nameFile = getNameFile();
	std::ifstream file_bin_test(nameFile);
	bool file_bin_exist = file_bin_test.good();
	file_bin_test.close();
	std::ios_base::openmode mode = std::ios::out;

	if (file_bin_exist) {
		std::cout << "\n\n   Открыть файл для дозаписи?\t1 - да";
		UCHAR ch = _getch();
		if (ch == '1') { mode = std::ios::app; }
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
	std::cout << "\n\n   Данные успешно записаны в файл => ";
	setColor(10, 0);
	std::cout << nameFile << std::endl;
}

//void writeMatrixBin(Matrix& matrix) {
//	//outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
//	std::string nameFile = getNameFile();
//	std::ifstream file_bin_test(nameFile);
//	bool file_bin_exist = file_bin_test.good();
//	std::ios_base::openmode mode = std::ios::out;
//
//	if (file_bin_exist) {
//		std::cout << "\n\n   Открыть файл для дозаписи?\t1 - да";
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
//				std::cerr << "   Ошибка: неудалось прочеитать файл";
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
//			std::cout << "\n\n   Данные успешно записаны в файл => ";
//			setColor(10, 0);
//			std::cout << nameFile << std::endl;
//	}
//	
//}

   



size_t manual_max(size_t a, size_t b) {
	return (a > b) ? a : b;
}

void writeMatrixBin(Matrix& matrixToAdd) {
	std::string nameFile = getNameFile();
	Matrix combinedMatrix; 
	bool proceed_to_write_combined_matrix = false; 

	std::ifstream file_check(nameFile, std::ios::binary);
	bool file_bin_exist = file_check.good();
	file_check.close();

	if (file_bin_exist) {
		std::cout << "\nФайл '" << nameFile << "' существует. Дозаписать данные? (y/n): ";
		char ch;
		std::cin >> ch;
		while (std::cin.get() != '\n');

		if (ch == 'y' || ch == 'Y') {
			Matrix matrixFromFile;
			std::ifstream infile(nameFile, std::ios::binary);

			if (!infile.is_open()) {
				std::cerr << "Ошибка: Не удалось открыть файл '" << nameFile << "' для чтения. Будет создана новая матрица с данными для добавления.\n";
			}
			else {
				if (!infile.read(reinterpret_cast<char*>(&matrixFromFile.rows), sizeof(size_t)) ||
					!infile.read(reinterpret_cast<char*>(&matrixFromFile.cols), sizeof(size_t))) {
					std::cerr << "Ошибка: Не удалось прочитать размеры из файла '" << nameFile << "'. Будет создана новая матрица с данными для добавления.\n";
				}
				else {
					bool read_data_ok = true;
					if (matrixFromFile.rows > 0 && matrixFromFile.cols > 0) {
						matrixFromFile.matrix = new double* [matrixFromFile.rows];
						for (size_t i = 0; i < matrixFromFile.rows; ++i) {
							matrixFromFile.matrix[i] = new double[matrixFromFile.cols];
							if (!infile.read(reinterpret_cast<char*>(matrixFromFile.matrix[i]), matrixFromFile.cols * sizeof(double))) {
								std::cerr << "Ошибка при чтении данных строки " << i << " из файла '" << nameFile << "'.\n";
								read_data_ok = false;
								break;
							}
						}
					}
					else {
						matrixFromFile.matrix = nullptr; 
					}

					if (read_data_ok) {
						combinedMatrix.rows = matrixFromFile.rows + matrixToAdd.rows;
						if (matrixFromFile.cols == 0 && matrixToAdd.cols == 0) {
							combinedMatrix.cols = 0;
						}
						else {
							combinedMatrix.cols = manual_max(matrixFromFile.cols, matrixToAdd.cols);
						}

						if (combinedMatrix.rows > 0) {
							combinedMatrix.matrix = new double* [combinedMatrix.rows];
							for (size_t i = 0; i < combinedMatrix.rows; ++i) {
								if (combinedMatrix.cols > 0) {
									combinedMatrix.matrix[i] = new double[combinedMatrix.cols];
									for (size_t j = 0; j < combinedMatrix.cols; ++j) {
										combinedMatrix.matrix[i][j] = 0.0; // Паддинг
									}
								}
								else {
									combinedMatrix.matrix[i] = nullptr;
								}
							}
						}
						else {
							combinedMatrix.matrix = nullptr;
						}

						if (matrixFromFile.matrix && matrixFromFile.rows > 0 && matrixFromFile.cols > 0) {
							for (size_t i = 0; i < matrixFromFile.rows; ++i) {
								for (size_t j = 0; j < matrixFromFile.cols; ++j) {
									if (j < combinedMatrix.cols)
										combinedMatrix.matrix[i][j] = matrixFromFile.matrix[i][j];
								}
							}
						}

						if (matrixToAdd.matrix && matrixToAdd.rows > 0 && matrixToAdd.cols > 0) {
							for (size_t i = 0; i < matrixToAdd.rows; ++i) {
								for (size_t j = 0; j < matrixToAdd.cols; ++j) {
									if (j < combinedMatrix.cols)
										combinedMatrix.matrix[matrixFromFile.rows + i][j] = matrixToAdd.matrix[i][j];
								}
							}
						}
						proceed_to_write_combined_matrix = true; 
					}
					else {
						std::cerr << "Дозапись отменена из-за ошибки чтения. Будет создана новая матрица с данными для добавления.\n";
					}
				}
				infile.close();
			}
		}
		else {
			std::cout << "Файл будет перезаписан новой матрицей.\n";
		}
	}
	else { 
		std::cout << "Создается новый файл.\n";
	}

	if (!proceed_to_write_combined_matrix) {
		  

		combinedMatrix.rows = matrixToAdd.rows;
		combinedMatrix.cols = matrixToAdd.cols;
		if (combinedMatrix.rows > 0) {
			combinedMatrix.matrix = new double* [combinedMatrix.rows];
			for (size_t i = 0; i < combinedMatrix.rows; ++i) {
				if (combinedMatrix.cols > 0) {
					combinedMatrix.matrix[i] = new double[combinedMatrix.cols];
					if (matrixToAdd.matrix && matrixToAdd.matrix[i]) {
						for (size_t j = 0; j < combinedMatrix.cols; ++j) {
							combinedMatrix.matrix[i][j] = matrixToAdd.matrix[i][j];
						}
					}
					else {
						for (size_t j = 0; j < combinedMatrix.cols; ++j) {
							combinedMatrix.matrix[i][j] = 0.0;
						}
					}
				}
				else {
					combinedMatrix.matrix[i] = nullptr;
				}
			}
		}
		else {
			combinedMatrix.matrix = nullptr;
		}
		proceed_to_write_combined_matrix = true; 
	}
	if (proceed_to_write_combined_matrix) {
		std::ofstream outfile(nameFile, std::ios::out | std::ios::binary | std::ios::trunc); 
		if (!outfile.is_open()) {
			std::cerr << "Ошибка: Не удалось открыть файл '" << nameFile << "' для записи.\n";
		}
		else {
			outfile.write(reinterpret_cast<const char*>(&combinedMatrix.rows), sizeof(size_t));
			outfile.write(reinterpret_cast<const char*>(&combinedMatrix.cols), sizeof(size_t));

			bool write_ok = true;
			if (combinedMatrix.matrix && combinedMatrix.rows > 0 && combinedMatrix.cols > 0) {
				for (size_t i = 0; i < combinedMatrix.rows; ++i) {
					if (combinedMatrix.matrix[i]) {
						if (!outfile.write(reinterpret_cast<const char*>(combinedMatrix.matrix[i]), combinedMatrix.cols * sizeof(double))) {
							std::cerr << "Ошибка при записи данных строки " << i << " в файл '" << nameFile << "'.\n";
							write_ok = false;
							break;
						}
					}
					else {
						std::cerr << "Внутренняя ошибка: строка " << i << " в combinedMatrix равна null при cols > 0.\n";
						write_ok = false;
						break;
					}
				}
			}
			outfile.close();

			if (outfile.fail() && write_ok) {
				std::cerr << "Произошла ошибка при записи или закрытии файла '" << nameFile << "'.\n";
				write_ok = false;
			}

			if (write_ok) {
				std::cout << "Матрица успешно записана в файл: " << nameFile << "\n";
				std::cout << "Итоговые размеры: " << combinedMatrix.rows << "x" << combinedMatrix.cols << "\n";
			}
			else {
				std::cout << "Запись матрицы в файл " << nameFile << " не удалась.\n";
			}
		}
	}
	else {
		std::cout << "Запись в файл отменена, так как матрица для записи не была сформирована.\n";
	}
}

  



void readMatrixTxt(Matrix& matrix) {
	std::string nameFile = getNameFile();
	std::ifstream file(nameFile, std::ios::binary);
	bool indicator = file.is_open() ? true : false;
	

	if (indicator) {
		std::cout << "\n   Файл найден" << std::endl;
		std::ifstream file(nameFile);
		size_t rows = 0, cols = 0;

		// Calculating the numbers of rows and columns in the matrix
		try
		{
			std::string line;
			bool cols_determined = false;

			while (std::getline(file, line))
			{
				if (line.empty() || line.find_first_not_of("\n\r\t\b\f") == std::string::npos) { continue; }
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
				if (current_cols > 0) {
					if (!cols_determined) {
						cols = current_cols;
						cols_determined = true;
					}
					else {
						if (current_cols > cols) {
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
		catch (const std::exception& e) { std::cerr << "Error: " << e.what(); }

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
			if (data.empty() || data.find_first_not_of("\n\v\r\b\t") == std::string::npos) { continue; }
			std::stringstream ss(data);
			double value = 0;
			std::string item;
			size_t charProcessed = 0;
			size_t j = 0;

			while (ss >> item)
			{
				try
				{
					for (size_t i = 0; i < item.length(); i++) {
						if (item[i] == '.') {
							item[i] = separate;
						}
						if (!((item[i] >= '0' && item[i] <= '9') || item[i] == '+' || item[i] == '-' || item[i] == 'e' || item[i] == 'E' || item[i] == '.' || item[i] == ',')) { value = 0; };
					}
					value = std::stod(item, &charProcessed);
					matrix.matrix[i][j] = value;

					j++;
				}
				catch (const std::exception)
				{
					setColor(4, 0);
					std::cerr << "\n\n\n\n   Ошибка: недействительный элемент в строке => "
						<< i + 1 << " и столбце =>" << j + 1 << " был заменен на 0." << std::endl
						<< "   Пожалуйста измените значение и откройте файл заново" << std::endl;
					setColor(7, 0);
				}
				catch (const std::invalid_argument& e) { std::cerr << "\n\n\n\n   Error: " << e.what(); }
				catch (const std::out_of_range& e) { std::cerr << "\n\n\n\n   Error: " << e.what(); }
			}
			i++;
		}

		// Output an elements
		char key;
		do {
			system("cls");
			std::cout << "   1 - Решение\n   2 - Замена значения\n\n" << std::endl;
			outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);

			key = _getch();


			if (key == '1') {
				system("cls");
				solution(matrix);
				_getch();
			}
			else if (key == '2') {
				system("cls");
				outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
				matrix.changeEl(matrix, matrix.rows, matrix.cols);
				std::ofstream file(nameFile, std::ios::trunc);
				for (size_t i = 0; i < matrix.rows; i++) {
					for (size_t j = 0; j < matrix.cols; j++) {
						file << matrix.matrix[i][j] << " ";
					}
					file << "\n";
				}
				outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
				_getch();
			}
			else if (key == 27) { return; }
			else { std::cerr << "   Неизвестная команда..."; return; }
		} while (key != 27);
	}
 else {
	 std::cerr << "\n   Такого файла нет..." << std::endl;
	}
}

void readMatrixBin(Matrix& matrix) {
	std::string nameFile = getNameFile();
	std::ifstream file(nameFile);
	bool indicator = file.is_open() ? true : false;


	if (indicator) {
		std::cout << "\n   Файл найден" << std::endl;



		size_t rows = 0, cols = 0;
		//std::string nameFile = getNameFile();
		std::ifstream file(nameFile, std::ios::binary);

		// Calculating the numbers of rows and columns in the matrix

		file.read(reinterpret_cast<char*>(&rows), sizeof(size_t));
		file.read(reinterpret_cast<char*>(&cols), sizeof(size_t));


		
		
		matrix.changeSize(rows, cols);

		for (size_t i = 0; i < rows; i++) {
			file.read(reinterpret_cast<char*>(matrix.matrix[i]), cols * sizeof(double));
			if (!file) {
				std::cerr << "   Не удалось прочесть для строки " << i << std::endl;
				std::cerr << "   Ожиддалоось байт: " << (cols * sizeof(double)) << "  Прочитанно " << file.gcount() << std::endl;
			}
		}
		file.close();
	

		outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);

		// Output an elements


		char key;
		do {
			system("cls");
			std::cout << "   1 - Решение\n   2 - Замена значения\n\n" << std::endl;
			outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);

			key = _getch();


			if (key == '1') {
				system("cls");
				solution(matrix);
				_getch();
			}
			else if (key == '2') {
				system("cls");
				outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
				matrix.changeEl(matrix, matrix.rows, matrix.cols);
				std::ofstream file(nameFile, std::ios::binary | std::ios::trunc);
				file.write(reinterpret_cast<char*>(&matrix.rows), sizeof(size_t));
				file.write(reinterpret_cast<char*>(&matrix.cols), sizeof(size_t));
				for (size_t i = 0; i < matrix.rows; i++) {
					for (size_t j = 0; j < matrix.cols; j++) {
						file.write(reinterpret_cast<char*>(&matrix.matrix[i][j]), sizeof(matrix.matrix[i][j]));
					}
				}
				outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
				_getch();
			}
			else if (key == 27) { return; }
			else { std::cerr << "   Неизвестная команда..."; return; }
		} while (key != 27);
	}
	else {
		std::cerr << "\n   Такого файла нет..." << std::endl;
	}
}




void clearSpace(Matrix& matrix) {
	if (!(matrix.matrix == nullptr || matrix.rows == 0 || matrix.cols == 0)) {
		for (size_t i = 0; i < matrix.rows; i++) {
			for (size_t j = 0; j < matrix.cols; j++) {
				matrix.matrix[i][j] = 0;
			}
		}
		setColor(10, 0);
		std::cout << "   Пространство очищено!" << std::endl;
	}
	else {
		setColor(4, 0);
		std::cout << "   Матрица не была создана..." << std::endl;
	}
	setColor(7, 0);
}

void readMatrixFile(Matrix& matrix) {
	std::cout << "   Выберете тип файла для сохранения" << std::endl;
	std::cout << "   1 - Текстовый файл\n   2 - Бинарный файл";
	size_t key = _getch();
	if (key == '1') { 
		system("cls");
		readMatrixTxt(matrix);
	}
	else if (key == '2') { 
		std::cout << "   1 - решение\n   2 - замена значения\n" << std::endl;
		system("cls");
		readMatrixBin(matrix);
	}
	else { return; }
}


void saveMatrixFile(Matrix& matrix) {
	if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0)) {
		std::cout << "   Выберите тип файла для сохранения" << std::endl;
		std::cout << "   1 - Текстовый файл\n   2 - Бинарный файл" << std::endl;
		size_t key = _getch();
		if (key == '1') { system("cls"); writeMatrixTxt(matrix);
		_getch();
		}
		else if (key == '2') { writeMatrixBin(matrix); 
		_getch();
		}
		else { return; }
	}
	else {
		std::cerr << "   Здесь пока пусто...";
		_getch();
	}
}


void copyMatrix(Matrix& matrix, Matrix& reserveMatrix) {
	reserveMatrix.changeSize(matrix.rows, matrix.cols);
	for (size_t i = 0; i < matrix.rows; i++) {
		for (size_t j = 0; j < matrix.cols; j++) {
			reserveMatrix.matrix[i][j] = matrix.matrix[i][j];
		}
	}
}



void insertMatrix(Matrix& matrix, Matrix& reserveMatrix) {
	if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0)) {
		char ch;
		do {
			system("cls");
			std::cout << "\n\n   1 - сохранить матрицу\n   2 - изменить текущую на сохраненную матрицу\n   3 - присоединить к текущей сохраненную матрицу\n\n   4 - вставить строку\n   5 - втавить столбец\n   6 - вставить строку и столбец\n\n   7 - удалить строку\n   8 - удалить столбец\n   9 - удалить строку и столбец\n\n   0 - транспонировать\n\n\n";
			outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
			ch = _getch();
			switch (ch) {
			case '1': {
				reserveMatrix.changeSize(matrix.rows, matrix.cols);
				for (size_t i = 0; i < reserveMatrix.rows; i++) {
					for (size_t j = 0; j < reserveMatrix.cols; j++) {
						reserveMatrix.matrix[i][j] = matrix.matrix[i][j];
					}
				}
				setColor(10, 0);
				std::cout << "   Матрица размером " << matrix.rows << " x " << matrix.cols << " сохранена";
				Sleep(1000);
				clearLine(7, 0, 8, 15);
				BACK(30);
				setColor(7, 0);
				break;
			}
			case '2': {
				if (!(reserveMatrix.matrix == nullptr || reserveMatrix.rows <= 0 || reserveMatrix.cols <= 0)) {
					size_t oldRows = matrix.rows;
					size_t oldCols = matrix.cols;
					matrix.changeSize(reserveMatrix.rows, reserveMatrix.cols);
					for (size_t i = 0; i < matrix.rows; i++) {
						for (size_t j = 0; j < matrix.cols; j++) {
							matrix.matrix[i][j] = reserveMatrix.matrix[i][j];
						}
					}
					setColor(10, 0);
					std::cout << "   Матрица размером " << oldRows << " x " << oldCols << " изменена на сохраненную,"
						<< " размером " << reserveMatrix.rows << " x " << reserveMatrix.cols;
					Sleep(3000);
					setColor(7, 0);
				}
				else {
					std::cout << "   Отсутствуют сохраненные матрицы...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}
				break;
			}
			case '3': {
				if (!(reserveMatrix.matrix == nullptr || reserveMatrix.rows <= 0 || reserveMatrix.cols <= 0)) {
					int newCols = reserveMatrix.cols > matrix.cols ? reserveMatrix.cols : matrix.cols;
					int  newRows = matrix.rows + reserveMatrix.rows;
					Matrix copySaveMatrix(reserveMatrix.rows ,reserveMatrix.cols);


					size_t oldRows = matrix.rows;
					size_t oldCols = matrix.cols;

					size_t nLine = 0, nCol = 0; // Нумераторы для резервной матрицы

					//Copied reserveMatrix
					copyMatrix(reserveMatrix, copySaveMatrix);

					//Copied matrix
					copyMatrix(matrix, reserveMatrix);

					//fill current matrix value from reservMatrix (copied old matrix.matrix)
					matrix.changeSize(newRows, newCols);
					for (size_t i = 0; i < reserveMatrix.rows; i++) {
						for (size_t j = 0; j < reserveMatrix.cols; j++) {
							matrix.matrix[i][j] = reserveMatrix.matrix[i][j];
						}
					}

					bool swapped;
					for (size_t i = reserveMatrix.rows; i < matrix.rows; i++) {
						swapped = false;
						if (!(nLine == copySaveMatrix.rows)) {
							swapped = true;
						};
						nCol = 0;
						for (size_t j = 0; j < matrix.cols; j++) {
							if (swapped == true && nCol != copySaveMatrix.cols) {
								matrix.matrix[i][j] = copySaveMatrix.matrix[nLine][nCol];
								nCol++;
							}
							else {
								matrix.matrix[i][j] = 0;
							}
						}
						nLine++;
					}
					setColor(10, 0);
					std::cout << "   Матрица размером " << oldRows << " x " << oldCols << " изменена на сохраненную,"
						<< " размером " << copySaveMatrix.rows << " x " << copySaveMatrix.cols;
					Sleep(3000);
					setColor(7, 0);
				}
				else {
					std::cout << "   Отсутствуют сохраненные матрицы...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}
				break;
			}
			case '4': {
				if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0)) {
					char kb;
					int newLine1;
					int nLines;
					std::cout << "   Сколько строк добавить?" << std::endl;;
					std::cin >> nLines;
					size_t newRows = matrix.rows + nLines;
					Matrix saveCurrentMatrix;
					copyMatrix(matrix, saveCurrentMatrix);
					matrix.changeSize(newRows, matrix.cols);

					std::cout << "   Введите номер строки после которой\n будет вставлена новая строка" << std::endl;
					ClearCin;
					std::cin >> newLine1;
					if (!(newLine1 >= 0 && newLine1 < matrix.rows + 1) || std::cin.fail()) {
						std::cerr << "\n   Введите корректный номер строки";
						Sleep(400);
						break;
					}

					


					size_t r = 0, c = 0;
					for (size_t i = 0; i < newLine1; i++) {
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++) {
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}

					
					for (size_t i = newLine1 + nLines; i < matrix.rows; i++) {
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++) {
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}


					std::cout << "   Заполнить?\n   1 - да" << std::endl;
					kb = _getch();
					if (kb == '1') {

						std::cout << "   Введите новые значения" << std::endl;
						for (size_t i = newLine1; i < newLine1 + nLines; i++) {
							for (size_t j = 0; j < matrix.cols; j++) {
								outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
								int newValue;
								std::cout << "   Новое значение [" << i + 1 << "][" << j + 1<< "] = ";
								std::cin >> newValue;
								matrix.matrix[i][j] = newValue;
							}
						}
					}


					setColor(10, 0);
					std::cout << "   Матрица с новым размером " << matrix.rows << " x " << matrix.cols << " измененa";
					Sleep(3000);
					setColor(7, 0);
				}
				else {
					std::cout << "   Отсутствуют сохраненные матрицы...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}
				break;
			}
			case '5': {
				if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0)) {
					char kb;
					int newLine1;
					int nLines;
					std::cout << "   Сколько столбцов добавить?" << std::endl;
					std::cin >> nLines;
					size_t newCols = matrix.cols + nLines;
					Matrix saveCurrentMatrix;
					copyMatrix(matrix, saveCurrentMatrix);
					matrix.changeSize(matrix.rows, newCols);

					std::cout << "   Введите номер столбца после которого\n   будут вставлены новые столбцы" << std::endl;
					ClearCin;
					std::cin >> newLine1;
					if (!(newLine1 >= 0 && newLine1 < matrix.cols + 1) || std::cin.fail()) {
						std::cerr << "\n   Введите корректный номер строки";
						Sleep(400);
						break;
					}




					size_t r = 0, c = 0;
					for (size_t i = 0; i < saveCurrentMatrix.rows; i++) {
						c = 0;
						for (size_t j = 0; j < newLine1; j++) {
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}
					r = 0;
					for (size_t i = 0; i < saveCurrentMatrix.rows; i++) {
						c = newLine1;
						for (size_t j = newLine1 + nLines; j < matrix.cols; j++) {
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}


				









					std::cout << "   Заполнить?\n   1 - да" << std::endl;
					kb = _getch();
					if (kb == '1') {
						std::cout << "   Введите новые значения" << std::endl;
						for (size_t i = 0; i < matrix.rows; i++) {
							for (size_t j = newLine1; j < newLine1 + nLines; j++) {
								outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
								int newValue;
								std::cout << "   Новое значение [" << j + 1 << "][" << i + 1 << "] = ";
								std::cin >> newValue;
								matrix.matrix[i][j] = newValue;
							}
						}
					}


					setColor(10, 0);
					std::cout << "   Матрица с новым размером " << matrix.rows << " x " << matrix.cols << " измененa";
					Sleep(3000);
					setColor(7, 0);
				}
				else {
					std::cout << "   Отсутствуют сохраненные матрицы...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}
				break;
			}
			case '6': {
				if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0)) {
					char kb;
					int newLine1;
					int nLines;
					std::cout << "   Сколько строк добавить?" << std::endl;
					std::cin >> nLines;
					size_t newRows = matrix.rows + nLines;
					Matrix saveCurrentMatrix;
					copyMatrix(matrix, saveCurrentMatrix);
					matrix.changeSize(newRows, matrix.cols);

					std::cout << "   Введите номер строки после которой\n   будет вставлена новая строка" << std::endl;
					ClearCin;
					std::cin >> newLine1;
					if (!(newLine1 >= 0 && newLine1 < matrix.rows + 1)) {
						std::cerr << "\n   Введите корректный номер строки";
						Sleep(400);
						break;
					}




					size_t r = 0, c = 0;
					for (size_t i = 0; i < newLine1; i++) {
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++) {
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}


					for (size_t i = newLine1 + nLines; i < matrix.rows; i++) {
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++) {
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}


					std::cout << "   Заполнить?\n   1 - да" << std::endl;
					kb = _getch();
					if (kb == '1') {

						std::cout << "   Введите новые значения" << std::endl;
						for (size_t i = newLine1; i < newLine1 + nLines; i++) {
							for (size_t j = 0; j < matrix.cols; j++) {
								outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
								int newValue;
								std::cout << "   Новое значение [" << i + 1 << "][" << j + 1 << "] = ";
								std::cin >> newValue;
								std::cout << std::endl;
								if (std::cin.fail() || std::cin.bad()) {
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
					std::cout << "   Сколько столбцов добавить?" << std::endl;
					std::cin >> nLines2;
					size_t newCols = matrix.cols + nLines2;
					Matrix saveCurrentMatrix2;
					copyMatrix(matrix, saveCurrentMatrix2);
					matrix.changeSize(matrix.rows, newCols);

					std::cout << "   Введите номер столбца после которого\n   будут вставлены новые столбцы" << std::endl;
					ClearCin;
					std::cin >> newLine2;
					if (!(newLine2 >= 0 && newLine2 < matrix.cols + 1)) {
						std::cerr << "\n   Введите корректный номер строки";
						Sleep(400);
						break;
					}




					r = 0, c = 0;
					for (size_t i = 0; i < saveCurrentMatrix2.rows; i++) {
						c = 0;
						for (size_t j = 0; j < newLine2; j++) {
							matrix.matrix[i][j] = saveCurrentMatrix2.matrix[r][c];
							c++;
						}
						r++;
					}
					r = 0;
					for (size_t i = 0; i < saveCurrentMatrix2.rows; i++) {
						c = newLine2;
						for (size_t j = newLine2 + nLines2; j < matrix.cols; j++) {
							matrix.matrix[i][j] = saveCurrentMatrix2.matrix[r][c];
							c++;
						}
						r++;
					}












					std::cout << "   Заполнить?\n   1 - да" << std::endl;
					kb = _getch();
					if (kb == '1') {
						std::cout << "   Введите новые значения" << std::endl;
						for (size_t i = 0; i < matrix.rows; i++) {
							for (size_t j = newLine1; j < newLine1 + nLines; j++) {
								outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
								int newValue;
								std::cout << "   Новое значение [" << j + 1 << "][" << i + 1 << "] = ";
								std::cin >> newValue;
								if (std::cin.fail() || std::cin.bad()) {
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
					std::cout << "   Матрица с новым размером " << matrix.rows << " x " << matrix.cols << " измененa";
					Sleep(3000);
					setColor(7, 0);
				}
				else {
					std::cout << "   Отсутствуют сохраненные матрицы...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}
				break;
			}

			case '7': {
				if (!(matrix.matrix == nullptr || matrix.rows <= 1 || matrix.cols <= 1)) {
					std::cout << "   Введите номер строки котрую нужно удалить" << std::endl;
					int deleteEl;
					std::cin >> deleteEl;
					size_t newRows = matrix.rows - 1;
					Matrix saveCurrentMatrix;
					copyMatrix(matrix, saveCurrentMatrix);
					matrix.changeSize(newRows, matrix.cols);

					size_t r = 0, c = 0;
					for (size_t i = 0; i < deleteEl - 1; i++) {
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++) {
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}
					r++;
					for (size_t i = deleteEl  -1; i < matrix.rows; i++) {
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++) {
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}


					setColor(10, 0);
					std::cout << "   Матрица с новым размером " << matrix.rows << " x " << matrix.cols << " измененa";
					Sleep(3000);
					setColor(7, 0);
				}
				else {
					std::cout << "   Слишком маленький размер матрицы...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}
				break;
			}
			case '8': {
				if (!(matrix.matrix == nullptr || matrix.rows <= 1 || matrix.cols <= 1)) {
					std::cout << "   Введите номер строки котрую нужно удалить" << std::endl;
					int deleteEl;
					std::cin >> deleteEl;
					size_t newCols = matrix.cols - 1;
					Matrix saveCurrentMatrix;
					copyMatrix(matrix, saveCurrentMatrix);
					matrix.changeSize(matrix.rows, newCols);
					

					size_t r = 0, c = 0;
					for (r = 0; r < saveCurrentMatrix.rows; r++) {
						c = 0;
						for (size_t j = 0; j < deleteEl - 1; j++) {
							matrix.matrix[r][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						c++;
						for (size_t j = deleteEl - 1; j < matrix.cols; j++) {
							matrix.matrix[r][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
					}
				
				
					

					setColor(10, 0);
					std::cout << "   Матрица с новым размером " << matrix.rows << " x " << matrix.cols << " измененa";
					Sleep(3000);
					setColor(7, 0);
				}
				else {
					std::cout << "   Слишком маленький размер матрицы...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}
				break;
			}
			case '9': {
				if (!(matrix.matrix == nullptr || matrix.rows <= 1 || matrix.cols <= 1)) {
					std::cout << "   Введите номер строки котрую нужно удалить" << std::endl;
					int deleteEl;
					std::cin >> deleteEl;
					size_t newRows = matrix.rows - 1;
					Matrix saveCurrentMatrix;
					copyMatrix(matrix, saveCurrentMatrix);
					matrix.changeSize(newRows, matrix.cols);

					size_t r = 0, c = 0;
					for (size_t i = 0; i < deleteEl - 1; i++) {
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++) {
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}
					r++;
					for (size_t i = deleteEl - 1; i < matrix.rows; i++) {
						c = 0;
						for (size_t j = 0; j < saveCurrentMatrix.cols; j++) {
							matrix.matrix[i][j] = saveCurrentMatrix.matrix[r][c];
							c++;
						}
						r++;
					}




					std::cout << "   Введите номер строки котрую нужно удалить" << std::endl;
					int deleteEl2;
					std::cin >> deleteEl2;
					size_t newCols = matrix.cols - 1;
					Matrix saveCurrentMatrix2;
					copyMatrix(matrix, saveCurrentMatrix2);
					matrix.changeSize(matrix.rows, newCols);


					r = 0, c = 0;
					for (r = 0; r < saveCurrentMatrix2.rows; r++) {
						c = 0;
						for (size_t j = 0; j < deleteEl2 - 1; j++) {
							matrix.matrix[r][j] = saveCurrentMatrix2.matrix[r][c];
							c++;
						}
						c++;
						for (size_t j = deleteEl2 - 1; j < matrix.cols; j++) {
							matrix.matrix[r][j] = saveCurrentMatrix2.matrix[r][c];
							c++;
						}
					}


					setColor(10, 0);
					std::cout << "   Матрица с новым размером " << matrix.rows << " x " << matrix.cols << " измененa";
					Sleep(3000);
					setColor(7, 0);
				}
				else {
					std::cout << "   Слишком маленький размер матрицы...";
					Sleep(1000);
					clearLine(7, 0, 8, 15);
					BACK(30);
				}

				break;
			}
			
			case '0': {
				if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0)) {
					size_t originalRows = matrix.rows;
					size_t originalCols = matrix.cols;

					Matrix transporantMatrix(originalCols, originalRows);
					for (size_t i = 0; i < originalRows; i++) {
						for (size_t j = 0; j < originalCols; j++) {
							transporantMatrix.matrix[j][i] = matrix.matrix[i][j];
						}
					}

					matrix.changeSize(originalCols, originalRows);
					for (size_t i = 0; i < matrix.rows; i++) {
						for (size_t j = 0; j < matrix.cols; j++) {
							matrix.matrix[i][j] = transporantMatrix.matrix[i][j];
						}
					}
				}
				else {
					std::cerr << "   Матрица не была создана..." << std::endl;
				}
			}
			
			case 27:
				break;
			default:
				std::cerr << "\n   Введите коректную команду";
				break;
			}

		} while (ch != 27);
	}
	else { 
		std::cout << "   Матрица не создана..." << std::endl;
		_getch();
	}
};


void fillMatrixMenu(Matrix& matrix) {
	if (!(matrix.matrix == nullptr || matrix.rows == 0 || matrix.cols == 0)) {
		char ch;
		do {
			system("cls");
			info2();
			std::cout << "\n\n   1 - Полностью заполнить матрицу\n   2 - Заполнить по индексу\n   esc - Назад\n\n";
			outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 400, 120, 50, 50, 16, 15);
			ch = _getch();

			switch (ch) {
			case '1':
				matrix.fillMatrix(matrix.rows, matrix.cols, 3, 15);
				break;
			case '2':
				matrix.changeEl(matrix, matrix.rows, matrix.cols);
				break;
			case 27:
				break;
			default:
				std::cout << "   Выберите команду из предложенных" << std::endl;
				break;
			}
		} while (ch != 27);
	}
	else {
		std::cout << "   Mатрица не была создана..." << std::endl;
		_getch();
	}
}




void outTableMatrixGraf(HDC hdc,
	double** matrix, // Матрица чисел double
	size_t rows, size_t cols,
	int startX, int startY,      // Начальные координаты таблицы
	int cellWidth, int cellHeight, // Размеры ячейки
	int headerFontSize = 16,     // Размер шрифта заголовков
	int dataFontSize = 15)       // Размер шрифта данных
{
	if (hdc == NULL) {
		return; 
	}
	if (matrix == nullptr || rows <= 0 || cols <= 0) {
		std::cout << "   Здесь пока пусто..." << std::endl;
		return; 
	}
	else {

		if (cellWidth <= 0 || cellHeight <= 0) {
			return; 
		}

		char textBuffer[64]; // Буфер для временного хранения чисел, преобразованных в строки
		char formatString[16]; // Буфер для строки формата (например, "%.2f")

		// Создаем строку формата для double на основе параметра precision
		sprintf_s(formatString, sizeof(formatString), "%%.%df", 2); // Например, если precision=2, то formatString будет "%.2f"

		// --- Настройка шрифтов ---
		HFONT hFontHeaders = CreateFontA(headerFontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
			RUSSIAN_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, FF_DONTCARE | VARIABLE_PITCH, "Terminal");

		HFONT hFontData = CreateFontA(dataFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
			RUSSIAN_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, FF_DONTCARE | VARIABLE_PITCH, "Terminal");

		// --- Настройка пера для сетки ---
		HPEN hPenGrid = CreatePen(PS_SOLID, 1, RGB(255, 255, 255)); // Светло-серое перо

		// Сохраняем старые GDI объекты, чтобы потом восстановить

		COLORREF cellFillColor = RGB(150, 150, 150);

		HBRUSH hcellBrush = CreateSolidBrush(cellFillColor);
		HBRUSH hOldFont = (HBRUSH)SelectObject(hdc, hcellBrush);
		HPEN hOldPen = (HPEN)SelectObject(hdc, GetStockObject(BLACK_PEN));

		int oldBkMode = SetBkMode(hdc, RGB(157, 56, 188));
		SetBkMode(hdc, RGB(192, 192, 192)); // Делаем фон текста прозрачным
	

		// --- 1. Рисуем номера столбцов (заголовки) ---
		if (hFontHeaders) SelectObject(hdc, hFontHeaders); // Выбираем шрифт для заголовков
		SetTextColor(hdc, RGB(255, 255, 255)); // Темно-синий цвет для заголовков

		for (int j = 0; j < cols; ++j) {
			int x_header_col = startX + cellWidth + j * cellWidth; // X-координата ячейки заголовка столбца
			int y_header_col = startY;                             // Y-координата ячейки заголовка столбца

			sprintf_s(textBuffer, sizeof(textBuffer), "%d", j + 1); // Преобразуем номер столбца в строку

			SIZE textSize;
			GetTextExtentPoint32A(hdc, textBuffer, strlen(textBuffer), &textSize); // Узнаем размер текста
			// Выводим текст по центру ячейки заголовка
			TextOutA(hdc,
				x_header_col + (cellWidth - textSize.cx) / 2,
				y_header_col + (cellHeight - textSize.cy) / 2,
				textBuffer, strlen(textBuffer));
		}

		// --- 2. Рисуем номера строк (заголовки) ---
		// Шрифт и цвет текста для заголовков уже установлены
		for (int i = 0; i < rows; ++i) {
			int x_header_row = startX;                                // X-координата ячейки заголовка строки
			int y_header_row = startY + cellHeight + i * cellHeight;  // Y-координата ячейки заголовка строки

			sprintf_s(textBuffer, sizeof(textBuffer), "%d", i + 1); // Преобразуем номер строки в строку

			SIZE textSize;
			GetTextExtentPoint32A(hdc, textBuffer, strlen(textBuffer), &textSize);
			TextOutA(hdc,
				x_header_row + (cellWidth - textSize.cx) / 2,
				y_header_row + (cellHeight - textSize.cy) / 2,
				textBuffer, strlen(textBuffer));
		}

		// --- 3. Рисуем данные матрицы и сетку ---
		if (hFontData) SelectObject(hdc, hFontData); // Выбираем шрифт для данных
		SetTextColor(hdc, RGB(255, 255, 255));             // Черный цвет для данных
		if (hPenGrid) SelectObject(hdc, hPenGrid);   // Выбираем перо для рисования сетки

		for (int i = 0; i < rows; ++i) {

			if (matrix[i] == nullptr) { // Проверка, что строка матрицы выделена
				// Можно добавить вывод ошибки или просто пропустить
				continue;
			}
			for (int j = 0; j < cols; ++j) {
				int cellX = startX + cellWidth + j * cellWidth;     // X-координата текущей ячейки данных
				int cellY = startY + cellHeight + i * cellHeight;    // Y-координата текущей ячейки данных

				// Преобразуем число double из матрицы в строку
				sprintf_s(textBuffer, sizeof(textBuffer), formatString, matrix[i][j]);
			
				// Рисуем рамку ячейки (если перо для сетки создано)
				if (hPenGrid) {
					Rectangle(hdc, cellX, cellY, cellX + cellWidth, cellY + cellHeight);
				}

				SIZE textSize;
				GetTextExtentPoint32A(hdc, textBuffer, strlen(textBuffer), &textSize);

				// Выводим текст (данные) по центру ячейки
				TextOutA(hdc,
					cellX + (cellWidth - textSize.cx) / 2,
					cellY + (cellHeight - textSize.cy) / 2,
					textBuffer, strlen(textBuffer));
			}
		}
	

		// --- Очистка GDI объектов ---
		SetBkMode(hdc, oldBkMode);
		SelectObject(hdc, hOldFont); // Восстанавливаем старый шрифт
		if (hFontHeaders) DeleteObject(hFontHeaders); // Удаляем созданный шрифт
		if (hFontData) DeleteObject(hFontData);       // Удаляем созданный шрифт

		SelectObject(hdc, hOldPen); // Восстанавливаем старое перо
		if (hPenGrid) DeleteObject(hPenGrid);         // Удаляем созданное перо
	}
}

	



void menuLab_3() {
	setlocale(LC_ALL, "rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	SetDefBkColor(CL_BLACK);

	size_t key;

	do {
		system("cls");
		

		Text(hdc, 50, 0, "Меню лабораторной работы №3 - 4", RGB(255, 255, 255), RGB(0, 0, 0), 25);
		Text(hdc, 50, 50, "0 - Условие задачи", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 100, "1 - Задать размеры матрицы", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 150, "2 - Заполнить матрицу", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 200, "3 - Просмотр текущей матрицы", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 250, "4 - Сохранить/вставить/присоединить", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 300, "5 - Сохранить матрицу в файле", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 350, "6 - Решение со значениями из файла", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 400, "7 - Решение со значениями из текщей матрицы", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 450, "8 - Очистка пространства", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 500, "9 - Просмотр директории", RGB(255, 255, 255), RGB(15, 5, 77), 25);

		Text(hdc, 50, 550, "ESC - Назад", RGB(255, 255, 255), RGB(157, 56, 188), 25);


		key = _getch();


		switch (key) {
		case '0':
			// information about the task
			system("cls");
			info2();
			std::cout << "\n\n   ";
			system("pause");
			break;
		case '1': {
			//size 
			system("cls");
			info2();
			setColor(14, 0);
			std::cout << "\n\n   Устаноовление размера матрицы" << std::endl;
			setColor(15, 0);
			size_t newRows = setRow();
			size_t newCols = setCol();
			if (!(matrix.matrix == nullptr || matrix.rows <= 0 || matrix.cols <= 0 || newRows < matrix.rows || newCols < matrix.cols)) {

				std::cout << "   1 - Сохранить данные?" << std::endl;
				if (_getch() == '1') {
					Matrix helpMatrix;
					copyMatrix(matrix, helpMatrix);
					matrix.changeSize(newRows, newCols);
					for (size_t i = 0; i < helpMatrix.rows; i++) {
						for (size_t j = 0; j < helpMatrix.cols; j++) {
							matrix.matrix[i][j] = helpMatrix.matrix[i][j];
						}
					}
				}else { matrix.changeSize(newRows, newCols); }
			} else { matrix.changeSize(newRows, newCols); }
			setColor(10, 0);
			std::cout << "   Матрица размером " << newRows << " x " << newCols << " успешно создана" << std::endl;
			setColor(7, 0);
			std::cout << "\n\n   ";
			system("pause");
			break;
		}
		case '2': {
			//fill matrix 
			system("cls");
			fillMatrixMenu(matrix);
			break;
		}
		case '3':
			//print current matrix
			system("cls");
			outTableMatrixGraf(hdc, matrix.matrix, matrix.rows, matrix.cols, 10, 5, 50, 50 );
			_getch();
			break;
		case '4':
			//insert / current
			system("cls");
			insertMatrix(matrix, reserveMatrix);
			break;
		case '5':
			//save matrix
			system("cls");
			saveMatrixFile(matrix);
			break;
		case '6':
			//solution with value from file
			system("cls");
			readMatrixFile(matrix);
			//solution(matrix);
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
			//check directory
			system("cls");
			system("dir");
			_getch();
			break;
		case 27:
			break;
		default:
			std::cout << "\nВведена неизвестная команда" << std::endl;
		}
		setColor(7, 0);
	} while (key != 27);

}
