#include <iostream>
#include <filesystem>

#if defined(_WIN32)
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