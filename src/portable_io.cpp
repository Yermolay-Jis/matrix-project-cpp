#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>

#elif (__linux__) || (__APPLE__)
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#error "ERROR: Your os not supported!"

#endif

char get_char_non_blocking()
{
#ifdef _WIN32
    return _getch();
#else
    struct termios, new_settings, old_settings;
    char ch;
    tcgetattr(STDIN_FILENO, &old_settings);

    new_settings = old_settings;
    new_settings.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, SCANNOW, &new_settings);
    ch = getchar();

    tcsetattr(STDIN_FILENO, SCANNOW, &old_settings);

#endif
};

void system_pause_function()
{
    std::cout << "   Для продолжения нажмите любую клавишу..." << std::endl;
    get_char_non_blocking();
}