#define _CRT_SECURE_NO_WARNINGS

#if defined(_WIN32) | defined(__WIN32__) | defined(__WIN32) | defined(_WIN64) | defined(__WIN64)
#include <windows.h>
#else defined(__linux__)

#endif

// C/C++ includes
#include <cmath>
#include <cstdint>
//#include <cstdio>
//#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
//#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
//#include <sys/stat.h>

// custom includes
#include "num2string.h"
#include "file_parser.h"
#include "make_dir.h"
#include "get_current_time.h"
#include "get_platform.h"
#include "console_colors.h"



// ----------------------------------------------------------------------------------------

//const std::string red("\x1b[0;31m");

void init(std::string &user_dir)
{
    int32_t status = make_dir(user_dir, ".todo");
    if (status < 0)
        std::cout << "Error creating .todo folder: " << status << std::endl;
}

// ----------------------------------------------------------------------------------------
int main(int argc, char** argv)
{

    std::fstream todo_stream, done_stream;

    std::string user_dir;

    // get the user root directory where the files will be located
#if defined(_WIN32) | defined(__WIN32__) | defined(__WIN32) | defined(_WIN64) | defined(__WIN64)
    user_dir = path_check(get_env_variable("USERPROFILE"));

    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    unsigned long mode = 0;
    GetConsoleMode(console_handle, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;   
    SetConsoleMode(console_handle, mode);

#else defined(__linux__)
    user_dir = path_check(get_env_variable("HOME"));
#endif

    const std::string todo_root = user_dir + ".todo";
    const std::string todo_file = todo_root + "/todo.txt";
    const std::string done_file = todo_root + "/done.txt";
    const std::string report_file = todo_root + "/report.txt";

    // check for the root .todo directory
    if (!existence_check(todo_root))
        init(user_dir);

    todo_stream.open(todo_file, (ios::in | ios::out | ios::app));
    done_stream.open(done_file, (ios::in | ios::out | ios::app));

    // todo format
    // index, add date, due date, task



    //std::cout << color(blue, black) << "red test" << reset << std::endl;
    //std::cout << "test 2" << std::endl;
    //std::cout << bright_color(blue, black) << "red test" << reset << std::endl;

    todo_stream.close();
    done_stream.close();

    std::cin.ignore();

}   // end of main
