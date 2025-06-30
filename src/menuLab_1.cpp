#include "../include/Header.h"
#include "../include/MyFunction.h"
#include "../include/menuLab_1.h"

char separate = ',';
int sizeArr = 10;
double* arr = new double[sizeArr];
static double min_el;
static int index;
static HDC hdc = GetDC(GetConsoleWindow());
static std::string nameFile;
static bool indicator = true;
static bool textIndicator;


double sizeBuckupArr1 = 10, sizeBuckupArr2 = 10;
static double* buckupArr1 = new double[sizeBuckupArr1]();
static double* buckupArr2 = new double[sizeBuckupArr2]();


void Text(HDC hdc, int indentX, int indentY, std::string title, COLORREF textColor, COLORREF BG, int size) {

	CONSOLE_SCREEN_BUFFER_INFO  csbi;
	HFONT hfontText = CreateFontA(size, 0, 0, 0, FW_BOLD, false, false, false, RUSSIAN_CHARSET,
		OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, VARIABLE_PITCH, "Terminal");

	GetConsoleScreenBufferInfo(hdc, &csbi);

	WORD originalAttributes = csbi.wAttributes;
	HFONT holdfont = (HFONT)SelectObject(hdc, hfontText);


	SetTextColor(hdc, textColor);
	SetBkColor(hdc, BG);
	TextOutA(hdc, indentX, indentY, title.c_str(), title.length());


	SetConsoleTextAttribute(hdc, originalAttributes);

	DeleteObject(hfontText);
}

static void saveArr(double* svArr, double size) {

	if (size <= 1) { return; }
	sizeBuckupArr1 = size;
	for (size_t i = 0; i < size; i++) {
		buckupArr1[i] = svArr[i];
	}
}

void info() {
	setColor(14, 0);
	CURSOR(3, 2);
	std::cout << "�������: \n";
	CURSOR(3, 3);
	std::cout << "��� ������ x_1 ..., x_n";
	CURSOR(3, 4);
	std::cout << "����� ����� �������� �� �_1 �� �_min\n\n";
}

void inputEl() {
	setColor(15, 0);

	info();
	std::cout << "   ������� �������� �������: \n";
	for (int i = 0; i < sizeArr; i++) {
		CURSOR(3, 6);
		SPACEBACK(30);
		setColor(10, 0);



		if (i == sizeArr - 1) {
			setColor(12, 0);
		}
		std::cout << "   x[" << i + 1 << "] = ";
		std::cin >> arr[i];
		

		if (std::cin.bad() || std::cin.fail()) {
			const size_t MAX_IGNORE_LINE = 256;
			std::cin.clear();
			std::cin.ignore(MAX_IGNORE_LINE, '\n');
			i--;
			continue;
		}

	}
	setColor(7, 0);
	textIndicator = true;
}

void solution1() {
	setColor(15, 0);
	// �������
	std::cout << "\n   ����������� ������� = ";
	min_el = arr[0];
	index = -1;
	for (int i = 0; i < sizeArr; i++) {
		if (arr[i] < min_el) {
			min_el = arr[i];
			index = i;
		}
	}
	std::cout << min_el;
}

void outputEl() {
	//����� �����������

	std::cout << "\n   ������: ";
	for (int i = 0; i < sizeArr; i++) {
		std::cout << arr[i] << " ";
	}
	setColor(14, 0);
	std::cout << "\n\n   ����� ��������� ������� �� ������������ �������� " << "( "
		<< min_el << " ) = ";
	double sum = 0;
	for (int i = 0; i < index; i++) {
		sum += arr[i];
	}
	std::cout << sum << std::endl;
	//setColor(7, 0);
}

void clearArr(double* arr) {
	// �������
	if (arr != nullptr) {
		delete[] arr;
		arr = nullptr;
	}
}

int setSizeArr() {
	setColor(15, 0);
	std::cout << "   ���������� ������� �������" << std::endl;
	CURSOR(3, 2);
	unsigned int key;
	setColor(7, 0);
	std::cout << "   ������� ������?" << "\n\n   1 - ��   2 - ���";
	key = _getch();
	if (key == '1') {
		LINES(1);
		std::cout << "\n   ������� ������ �������: ";
		std::cin >> sizeArr;
		arr = new double[sizeArr] {};

		setColor(10, 0);
		std::cout << "   ������ ������� ������� �������!\n\n";
		setColor(7, 0);
		std::cout << "\n\n   ������� ESC, ����� �����...";
		return sizeArr;
	}
	else {
		std::cout << "\n\n   ������� ESC ����� �����...";
	}
}

std::string getNameFile() {
	setColor(15, 0);
	std::string nameFile;
	std::cout << "\n   ������� ��� �����: ";
	setColor(10, 0);
	//std::cin >> nameFile;
	std::cin >> nameFile;
	if (std::cin.fail() || std::cin.bad()) {
		while (std::cin.fail() || std::cin.bad()) {

			std::cin >> nameFile;
		}
	}
	setColor(14, 0);
	return nameFile;

}

void inpFile() {
	system("cls");
	CURSOR(3, 3);
	setColor(6, 0);
	std::cout << "������ ������ � ����";

	nameFile = getNameFile();

	std::ifstream file_test(nameFile);
	bool file_exist = file_test.good();
	file_test.close();
	std::ios_base::openmode mode = std::ios::out;

	if (file_exist) {
		std::cout << "\n\n   ���������� �������� � ����?\t1 - ��";
		char ch = _getch();
		if (ch == '1') { mode = std::ios::app; }
	}
	std::ofstream file(nameFile, mode);

	if (!file.is_open()) { std::cerr << "  Error: file not opened"; return; };
	if (sizeArr == 0) { std::cerr << "   Error: file is empty! "; return; };

	system("cls");
	inputEl();
	for (size_t i = 0; i < sizeArr; i++) {
		file << arr[i] << std::endl;
	}
	file.close();
	LINES(1);
	
	setColor(7, 0);
	std::cout << "   ������ ������� �������� � ���� => ";
	SPACEBACK(1);
	setColor(10, 0);
	std::cout << nameFile;
}

void outFile() {
	nameFile = getNameFile();

	std::cout << "\n";
	setColor(15, 0);
	indicator = false;

	std::ifstream file(nameFile);
	indicator = file.is_open() ? true : false;
	std::string comment = file.is_open() ? "   ���� ������� ������\n\n" : "   ������, ������ ����� ���\n\n";
	std::cout << comment << std::endl;


	if (indicator == true) {
		std::string data;
		std::string item;
		size_t numberEl = 0;
		size_t i = 0;

		while (std::getline(file, data)) {
			if (!data.empty()) {
				numberEl++;
			}
			else { continue;}
		}
		std::cout << "\n\n   ���������� ������ � �����: " << numberEl << std::endl;
		if (numberEl == 0) { std::cerr << "   Error: file is empty!"; textIndicator = false, indicator = false; return; }

		saveArr(arr, sizeArr);
		arr = new double[numberEl];
		sizeArr = numberEl;
		std::string line;
		file.clear();
		file.seekg(0, std::ios::beg);

		while (std::getline(file, line)) {
			if (line.empty()) {
				continue;
			}

			double value = 0.0, result = 0.0;
			size_t charProcessed = 0;
			std::stringstream ss(line);	
			while (ss >> item) { 

				try {
					for (size_t i = 0; i < item.length(); i++) {
						if (item[i] == '.') { 
							item[i] = separate; 
						}
						if (!((item[i] >= '0' && item[i] <= '9') || item[i] == '+' || item[i] == '-' || item[i] == 'e' || item[i] == 'E' || item[i] == '.' || item[i] == ',')) { result = 0; };
					}
					value = std::stod(item, &charProcessed); 
					result += value;

				}
				catch (const std::exception) {
					setColor(12, 0);
					std::cerr << "   ������: ������� � ������ " << i + 1<< " ����� ���������������� �������� � ��� ������� �� 0. �������� ������� � �������� ���� ������" << std::endl;
				}
				catch (const std::invalid_argument) {
					setColor(12, 0);
					std::cerr << "   ������: ��������������� �������� " << std::endl;
				}
				catch (const std::out_of_range) {
					setColor(12, 0);
					std::cerr << "   ������: ����� �� ������� ������� �������" << std::endl;
				}
			}
			arr[i] = result;
			i++;
		}
	
		file.close();

		solution1();
		outputEl();
	}

}

void outTableGraf(double* arr, int size, int pnsec, std::string title, std::string psmas, HDC hdc, size_t n) 
{
	if (indicator == true || textIndicator == true) {

		HWND hwnd = (HWND)GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_FONT_INFO conf{};
		GetCurrentConsoleFont(hwnd, false, &conf);
		COORD cxy = CURSORPOS;

		int indentY = conf.dwFontSize.Y * (cxy.Y + 1),
			indentX = 40;

		HFONT hfont = CreateFontA(20, 0, 0, 0, FW_BLACK, false, false, false, RUSSIAN_CHARSET,
			OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, VARIABLE_PITCH, "Terminal");
		HFONT holdfont = (HFONT)SelectObject(hdc, hfont);


		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(0, 0, 0));
		TextOutA(hdc, indentY + 100, indentY, title.c_str(), title.length());
		SelectObject(hdc, holdfont);
		DeleteObject(hfont);

		indentY += 34;
		int nsec = size / pnsec + ((size % pnsec > 0) ? 1 : 0);


		HPEN hpen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
		LOGBRUSH lgbr{ PS_SOLID, RGB(94, 94, 94), 0 };
		HBRUSH hbrush = CreateBrushIndirect(&lgbr);
		HANDLE oldbrush = SelectObject(hdc, hbrush),
			oldpen = SelectObject(hdc, hpen);

		Rectangle(hdc, indentX, indentY, indentX + pnsec * 5 * conf.dwFontSize.X, indentY + (5 * conf.dwFontSize.Y) * nsec);

		for (int i = 0; i < nsec; i++) {
			int nx = indentX,
				nx2 = indentX + pnsec * 5 * conf.dwFontSize.X;
			MoveToEx(hdc, nx, indentY + i * 5 * conf.dwFontSize.Y + (5 * conf.dwFontSize.Y) / 2, NULL);
			LineTo(hdc, nx2, indentY + i * 5 * conf.dwFontSize.Y + (5 * conf.dwFontSize.Y) / 2);
			MoveToEx(hdc, nx, indentY + ((i + 1) * 5 * conf.dwFontSize.Y), NULL);
			LineTo(hdc, nx2, indentY + ((i + 1) * 5 * conf.dwFontSize.Y));
		}

		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkColor(hdc, RGB(94, 94, 94));

		for (int i = 0; i < pnsec; i++) {
			int nx = indentX + (i) * 5 * conf.dwFontSize.X,
				ny = indentY;

			MoveToEx(hdc, nx, ny, NULL);
			LineTo(hdc, nx, ny + (5 * conf.dwFontSize.Y) * nsec);
			char txt[30]{};

			for (int j = 0; j < nsec; j++) {
				if (j * pnsec + i < size) {
					sprintf_s(txt, "%s%d", psmas.c_str(), j * pnsec + i + n);
					SIZE sz{};
					GetTextExtentPoint32A(hdc, txt, strlen(txt), &sz);
					TextOutA(hdc, nx + (5 * conf.dwFontSize.X - sz.cx) / 2, ny + j * (conf.dwFontSize.Y * 5) + conf.dwFontSize.Y, txt, strlen(txt));
					sprintf_s(txt, "%5.1f", arr[j * pnsec + i]);
					GetTextExtentPoint32A(hdc, txt, strlen(txt), &sz);
					TextOutA(hdc, nx + (5 * conf.dwFontSize.X - sz.cx) / 2, ny + j * (conf.dwFontSize.Y * 5) + 3 * conf.dwFontSize.Y, txt, strlen(txt));

				}
			}
		}
		DeleteObject(hfont);
	}
};

void replaceElFile() {
	outFile();

	if (indicator == true) {
		std::cout << "\n   �������� �������� ��������?\n\n   1 - ��\t2 - ���" << std::endl;
		size_t key = _getch();

		if (key == '1') {
			system("cls");

			std::cout << "   ������ �� �����:\n";
			for (int i = 0; i < sizeArr; i++) {
				std::cout << "  " << arr[i];
			}

			unsigned replaceElIdx;
			std::cout << "\n\n   ������� ����� �������� �������� ������ �������� (0, 1, 2, ...)" << std::endl << "   ";
			std::cin >> replaceElIdx;
			if (replaceElIdx >= sizeArr  || replaceElIdx < 0 || std::cin.fail() || std::cin.bad()) {
				std::cerr << "   ������: �������� � ����� �������� �� ����������!" << std::endl;
				while (replaceElIdx >= sizeArr || replaceElIdx < 0 || std::cin.fail() || std::cin.bad()) {
					CURSOR(3, 6);
					SPACEBACK(30);
					std::cin.clear();
					std::cin.ignore(250, '\n');
					//std::cout << "   ������� ����� �������� �������� �������� � �������� �� 0 �� " << sizeArr << std::endl;
					std::cin >> replaceElIdx;
				}
				for (int i = 4; i < 7; i++) {
					for (int j = 0; j < 30; j++) {
						std::cin.clear();
						SPACEBACK(30);
						CURSOR(j, i);
					}
				};
			}
			CURSOR(3, 6);



			double replaceEl;
			for (int i = 0; i < sizeArr; i++) {
				if (i == replaceElIdx) {
					replaceElIdx = i;
					replaceEl = arr[i];
					break;
				}
			}
			std::cout << "�������� � �������� ";
			setColor(10, 0);
			SPACEBACK(30);
			std::cout << replaceElIdx;
			setColor(14, 0);
			SPACEBACK(30);
			std::cout << " ������� ������ => ";
			setColor(10, 0);
			SPACEBACK(30);
			std::cout << arr[replaceElIdx];

			double newElement;

			setColor(14, 0);
			std::cout << "\n\n   ������� ����� �������� ��� ����� ��������: \n   ";
			setColor(10, 0);
			std::cout << arr[replaceElIdx];
			setColor(14, 0);
			SPACEBACK(30);
			std::cout << " => ";
			setColor(10, 0);
			SPACEBACK(30);
			std::cin >> newElement;
			setColor(14, 0);

			arr[replaceElIdx] = newElement;
			std::ofstream file(nameFile, std::ios::trunc);
			for (int i = 0; i < sizeArr; i++) {
				file << arr[i] << "\n";
			}


			std::cout << "   ���������� ������:\n";
			for (int i = 0; i < sizeArr; i++) {
				std::cout << "  " << arr[i];
			}


		}
		else {
			std::cout << "\n\n   ������� ESC ����� �����...";
		}

	}
}


void menuLab_1() {

	if (arr == nullptr) {
		arr = new double[sizeArr];
	}

	setlocale(LC_ALL, "rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	SetDefBkColor(CL_BLACK);

	size_t key;

	do {
		system("cls");

		Text(hdc, 50, 0, "���� ������������ ������ �1", RGB(255, 255, 255), RGB(0, 0, 0), 25);
		Text(hdc, 50, 50, "0 - ������� � �������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 100, "1 - ������� � ��������� ������ ������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 150, "2 - ������� �� ���������� � ����", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 250, "3 - ������� �� ���������� �� �����", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 300, "4 - ������� �� ����� � ��������� ������ ������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
		Text(hdc, 50, 350, "5 - ������ �������� �������� � ����� �� �������", RGB(255, 255, 255), RGB(15, 5, 77), 25);
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
				setColor(7, 0);
				std::cout << "\n\n   ������� ESC, ����� �����...";
				CURSOR(3, 14);
				_getch();
				break;
			case '1':
				system("cls");
				info();
				CURSOR(3, 8);
				system("pause");
				system("cls");
				inputEl();
				solution1();
				outputEl();
				LINES(3);
				outTableGraf(arr, sizeArr, sizeArr<10? sizeArr:10, "��������� ����� ������", "X", hdc, 1);
				setColor(7, 0);
				Text(hdc, 40, 400, "ESC - �����", RGB(255, 255, 255), RGB(157, 56, 188), 25);
				_getch();
				break;
			case '2':
				inpFile();
				setColor(7, 0);
				std::cout << "\n\n   ������� ESC, ����� �����...";
				_getch();
				break;
			case '3':
				system("cls");
				outFile();
				setColor(7, 0);
				std::cout << "\n\n   ������� ESC, ����� �����...";
				_getch();
				break;
			case '4':
				system("cls");
				info();
				outFile();
				LINES(1);
				outTableGraf(arr, sizeArr, sizeArr < 10 ? sizeArr : 10, "��������� ����� ������", "X", hdc, 1);
				setColor(7, 0);
				Text(hdc, 40, 550, "ESC - �����", RGB(255, 255, 255), RGB(157, 56, 188), 25);
				_getch();
				break;
			case '5':
				system("cls");
				replaceElFile();
				setColor(7, 0);
				_getch();
				break;
			case '6':
				system("cls");
				setSizeArr();
				setColor(7, 0);
				_getch();
				break;
			case '7':
				system("dir");
				setColor(7, 0);
				std::cout << "\n\n   ������� ESC, ����� �����...";
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
	system("cls");

}