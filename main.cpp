#include "menuLab_1.h"
#include "menuLab2.h"
#include "menuLab_3.h"

using namespace std;

int main(int argc, char ** argv)
{
    HDC hdc = GetDC(GetConsoleWindow());
    setlocale(LC_ALL, "rus");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    cout << argc << endl;
    cout << argv[0] << endl;
    size_t key;

    do {
        system("cls");
        Text(hdc, Xpos, 0, "Главное меню", RGB(255, 255, 255), RGB(0, 0, 0), 50);
        Text(hdc, Xpos, 100, "0 -  Информация о программисте", RGB(255, 255, 255), RGB(15, 5, 77), 25);
        Text(hdc, Xpos, 150, "1 -  Лабораторная работа №1", RGB(255, 255, 255), RGB(15, 5, 77), 25);
        Text(hdc, Xpos, 200, "2 - Лабораторная работа №2", RGB(255, 255, 255), RGB(15, 5, 77), 25);
        Text(hdc, Xpos, 250, "3 -  Лабораторная работа №3", RGB(255, 255, 255), RGB(15, 5, 77), 25);
        Text(hdc, Xpos, 300, "ESC - выйти из программы", RGB(255, 255, 255), RGB(157, 56, 188), 25);



        key = _getch();

        switch (key)
        {
        case '0':
            creator();
            break;
        case '1':
            menuLab_1();
            break;
        case '2':
            menuLab_2();
            break;
        case '3':
            menuLab_3();
            break;
        default:
            break;
        }
    } while (key != 27);

    return 0;

}


