#include "Header.h"
#include "MyFunction.h"
#include "menuLab_1.h"




// Функция удаления файла
void removeFile(std::string nameFile) {
	std::cout << "Удаление...\n";
	Sleep(800);
	system("cls");
	if (std::remove(nameFile.c_str()) == 0) {
		std::cout << "Файл " << nameFile << " успешно удален\n\n\Enter - ОК\n";
	}
	else {
		std::cerr << "Ошибка удаления";
		std::perror("Причина");
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
		std::cout << "   1 - удалить файл\t 2 - создать новый\t Esc - выйти\n\n";
	}
	else {
		std::cout << "   2 - создать новый\t\tEsc - выйти\n\n";
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
			std::cout << "\n   Введена неизвестная команда" << std::endl;
			//_getch();

			setColor(7, 0);
		};
	} while (_getch() != 27);
}