#include "Header.h"
#include "MyFunction.h"
#include "menuLab_1.h"




// ������� �������� �����
void removeFile(std::string nameFile) {
	std::cout << "��������...\n";
	Sleep(800);
	system("cls");
	if (std::remove(nameFile.c_str()) == 0) {
		std::cout << "���� " << nameFile << " ������� ������\n\n\Enter - ��\n";
	}
	else {
		std::cerr << "������ ��������";
		std::perror("�������");
	}
}



void subMenuLab1(std::string nameFile) {

	setlocale(LC_ALL, "rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	SetDefBkColor(CL_BLACK);
	setColor(14, 0);

	/*std::cout << "\n\n|------------------------------------------------------------|\n\n";
	if (indicator == true) {
		std::cout << "   1 - ������� ����\t 2 - ������� �����\t Esc - �����\n\n";
	}
	else {
		std::cout << "   2 - ������� �����\t\tEsc - �����\n\n";
	}*/

	do {


		

		switch (_getch()) {
		case '1':
			/*if (indicator == true) {system("cls");*/ removeFile(nameFile);
			break;
		case '2':
			system("cls");
			inpFile();
			break;
		case 27:
			break;
		default:
			std::cout << "\n   ������� ����������� �������" << std::endl;
			//_getch();

			setColor(7, 0);
		};
	} while (_getch() != 27);
}