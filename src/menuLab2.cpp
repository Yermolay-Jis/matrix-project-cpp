#include "../include/menuLab2.h"
#include "../include/menuLab_1.h"

static std::string nameFile;
static bool indicator;


void writeBinFile() {
	system("cls");
	CURSOR(3, 3);
	setColor(6, 0);
	std::cout << "������ ������ � ����";

	setColor(15, 0);
	LINES(2);
	std::cout << "   ������� ��� �����: "; 
	std::cin >> nameFile;
	if (std::cin.fail() || std::cin.bad()) { while (std::cin.fail() || std::cin.bad()) { std::cin >> nameFile; } }
	ClearCin;

	std::ifstream file_bin_test(nameFile);
	bool file_bin_exist = file_bin_test.good();
	file_bin_test.close();
	std::ios_base::openmode mode = std::ios::out;

	if (file_bin_exist) {
		std::cout << "\n\n   ������� ���� ��� ��������?\t1 - ��";
		char ch = _getch();
		if (ch == '1') { mode = std::ios::app; }
	}
	std::ofstream file(nameFile, mode);
	if (!file.is_open()) { std::cerr << "   Error: file is not opened"; };
	if (sizeArr == 0) { std::cerr << "   Error: file is empty! "; return; }

	system("cls");
	inputEl();
	for (int i = 0; i < sizeArr; i++) {
		file.write(reinterpret_cast<char*>(&arr[i]), sizeof(arr[i])); // Write element of array
	}

	file.flush();
	file.close();
	LINES(1);

	setColor(7, 0);
	std::cout << "   ������ ������� �������� � ���� => ";
	SPACEBACK(1);
	setColor(10, 0);
	std::cout << nameFile;
	CURSOR(0, 0);
}

void readBinFile() {
	setColor(14, 0);
	nameFile = getNameFile();
	
	

	std::cout << "\n";
	setColor(15, 0);

	std::ifstream file(nameFile, std::ios::binary);
	indicator = file ? true : false;
	std::string comment = file.is_open() ? "   ���� ������� ������\n\n" : "   ������, ������ ����� ���\n\n";
	std::cout << comment << std::endl;


	if (indicator == true) {

		double data = 0;
		size_t numberEl = 0;
		size_t i = 0;

		while (file.read(reinterpret_cast<char*>(&data), sizeof(data))) {
			numberEl++;
		}
		if (numberEl == 0) { std::cout << "���� ����"; }
		else { std::cout << "\n\n   ���������� ������ � �����: " << numberEl << std::endl;}



		try {
			arr = new double[numberEl];
			sizeArr = numberEl;
		}
		catch (const std::bad_alloc& e) {
			std::cerr << "������: " << e.what();
		};


		file.clear();
		file.seekg(0, std::ios::beg);

		if (!file) {
			std::cerr << "   ����������� ������: �� ������� �������� � ������ �����\n";
			std::cerr << "   ��������� ������ eof()" << file.eof() << " fail = " << file.fail() << " bad() = " << file.bad();
		}

		while (i < sizeArr && file.read(reinterpret_cast<char*>(&arr[i]), sizeof(data))) { i++; }
		file.close();


		solution1();
		outputEl();
	}

	

}

void replaceElBinFile() {
	readBinFile();

	if (indicator == true) { // if file is open
		std::cout << "\n   �������� �������� ��������?\n\n   1 - ��\t2 - ���" << std::endl;
		size_t key = _getch();

		if (key == '1') {
			system("cls");

			Text(hdc, 50, 17, "������ �� �����:", RGB(255, 255, 255), RGB(0, 0, 0), 15);
			CURSOR(3, 0);
			outTableGraf(arr, sizeArr, sizeArr < 10 ? sizeArr : 10, "", "i", hdc, 0);

			size_t replaceElIdx;
			CURSOR(3, 12);
			Text(hdc, 50, 150, "������� ����� �������� �������� ������ �������� (0, 1, 2, ...)", RGB(255, 255, 255), RGB(0, 0, 0), 15);
			std::cin >> replaceElIdx;
			if (replaceElIdx >= sizeArr || replaceElIdx < 0 || std::cin.fail() || std::cin.bad()) {
				Text(hdc, 50, 200, "������: �������� � ����� �������� �� ����������!", RGB(255, 0, 0), RGB(0, 0, 0), 15);
				while (replaceElIdx >= sizeArr || replaceElIdx < 0 || std::cin.fail() || std::cin.bad()) {
					CURSOR(3, 14);
					SPACEBACK(30);
					std::cin.clear();
					std::cin.ignore(250, '\n');
					std::cin >> replaceElIdx;
				}
				for (size_t i = 17; i < 500; i++) {
					Text(hdc, i, 200, " ", RGB(12,12,12), RGB(12,12,12), 15);
				};
			}
			CURSOR(3, 14);

			double replaceEl;
			for (size_t i = 0; i < sizeArr; i++) { // Search elements in array for replace
				if (i == replaceElIdx) {
					replaceElIdx = i;
					replaceEl = arr[i];
					break;
				}
			}
			Text(hdc, 50, 200, "������� � �������� ", RGB(255, 255, 255), RGB(12, 12, 12), 15);
			Text(hdc, 185, 200, std::to_string(replaceElIdx), RGB(0, 255, 0), RGB(12, 12, 12), 15);
			Text(hdc, 200, 200, " ������� ������ => ", RGB(255, 255, 255), RGB(12, 12, 12), 15);
			std::ostringstream oss;
			oss << std::fixed << std::setprecision(2) << arr[replaceElIdx];
			Text(hdc, 325, 200, oss.str(), RGB(0, 255, 0), RGB(12, 12, 12), 15);

			double newElement;

			CURSOR(3, 14);
			SPACEBACK(2);
			std::cin.clear();
			Text(hdc, 50, 225, "������� ����� �������� ��� ����� ��������:", RGB(255, 255, 255), RGB(12, 12, 12), 15);
			CURSOR(3, 15);
			setColor(15, 0);
			std::cin >> newElement;

			arr[replaceElIdx] = newElement;


			// Write an item to a file that the user chooses
			double item = 0;
			std::fstream file(nameFile, std::ios::binary | std::ios::in | std::ios::out);
			std::streampos currentPos;
			size_t gap = 0;
			while (true) {
				try {
					currentPos = file.tellg();
					if (!file.read(reinterpret_cast<char*>(&item), sizeof(double))) {
						if (file.eof()) { std::cerr << "   ������� �� ������ � �����" << std::endl; }
						else { std::cerr << "   ������ ������ �� �����" << std::endl; break;  }
					}
					if (item == replaceEl && gap == replaceElIdx) { // Item that the has been find
						item = newElement;
						file.seekg(0, std::ios::beg);
						file.seekp(currentPos);
						file.write(reinterpret_cast<char*>(&newElement), sizeof(double));
						file.flush();
						break;
					}
					gap++;
				}
				catch (const std::exception& e) { std::cerr << "Error: " << e.what(); }
			}
			file.close();

			Text(hdc, 50, 250, "���������� ������:", RGB(255, 255, 255), RGB(12, 12, 12), 15);
			size_t n = 50;
			for (size_t i = 0; i < sizeArr; i++) { 
				std::ostringstream oss;
				oss << std::fixed << std::setprecision(2) << arr[i];
				Text(hdc, n, 300, oss.str(), RGB(255, 255, 255), RGB(12, 12, 12), 15);
				n += 50;
			}
		}
		else { std::cout << "\n\n   ������� ESC ����� �����..."; }
	}
}

void menuLab_2() {

	if (arr == nullptr) {
		arr = new double[sizeArr];
	}

	setlocale(LC_ALL, "rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	size_t key;

	do {
		system("cls");

		Text(hdc, 50, 0, "���� ������������ ������ �2", RGB(255, 255, 255), RGB(0, 0, 0), 25);
		Text(hdc, 50, 50, "0 - ������� � �������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 100, "1 - ������� � ��������� ������ ������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 150, "2 - ������� �� ���������� � �������� ����", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 250, "3 - ������� �� ���������� �� ��������� �����", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 300, "4 - ������� �� ��������� ����� � ��������� ������ ������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 350, "5 - ������ �������� �������� � �������� ����� �� �������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 450, "6 - ������ ������ ������������� �������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 500, "7 - �������� ����������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 550, "ESC - �����", RGB(255, 255, 255), RGB(157, 56, 188), 25);


		key = _getch();

		switch (key) {
		case '0':
			system("cls");
			info();
			CURSOR(3, 7);
			system("pause");
			system("cls");
			inputEl(),
			solution1(),
			outputEl();
			CURSOR(3, 14);
			_getch();
			break;
		case '1':
			system("cls");
			info();
			CURSOR(3, 8);
			system("pause");
			system("cls");
			Text(hdc, 500, 25, "��������� ����� ������", RGB(255, 255, 255), RGB(12, 12, 12), 25);
			inputEl();
			solution1();
			LINES(5);
			outTableGraf(arr, sizeArr, sizeArr < 10 ? sizeArr : 10 , "", "X", hdc, 1);
			_getch();
			break;
		case '2':
			writeBinFile();
			_getch();
			break;
		case '3':
			system("cls");
			readBinFile();
			_getch();
			break;
		case '4':
			system("cls");
			info();
			readBinFile();
			LINES(1);
			outTableGraf(arr, sizeArr, sizeArr < 10 ? sizeArr : 10, "��������� ����� ������", "X", hdc, 1);
			_getch();
			break;
		case '5':
			system("cls");
			replaceElBinFile();
			_getch();
			break;
		case '6':
			system("cls");
			setSizeArr();
			break;
		case '7':
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
	clearArr(arr);
}