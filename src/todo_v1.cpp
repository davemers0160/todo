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


// ----------------------------------------------------------------------------------------

//inline std::ostream& red(std::ostream& stream)
//{
//    if (_internal::is_colorized(stream))
//    {
//#if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
//        stream << "\033[31m";
//#elif defined(TERMCOLOR_OS_WINDOWS)
//        _internal::win_change_attributes(stream,
//            FOREGROUND_RED
//        );
////#endif
//    }
//    return stream;
//}

const std::string red("\033[0;31m");
const std::string reset("\033[0m");

// ----------------------------------------------------------------------------------------
int main(int argc, char** argv)
{

    std::ofstream todo_stream, done_stream;

    std::string user_dir;

    // get the user root directory where the files will be located
#if defined(_WIN32) | defined(__WIN32__) | defined(__WIN32) | defined(_WIN64) | defined(__WIN64)
    user_dir = path_check(get_env_variable("USERPROFILE"));
#else defined(__linux__)
    user_dir = path_check(get_env_variable("HOME"));
#endif

    const std::string todo_root = user_dir + ".todo";
    const std::string todo_file = todo_root + "/todo.txt";
    const std::string done_file = todo_root + "/done.txt";

    // check for the root .todo directory
    bool todo_exists = existence_check(todo_root);

    std::cout << user_dir << std::endl;

    std::cout << red << "test" << std::endl;

    CONSOLE_SCREEN_BUFFER_INFO p;
    HANDLE consolehwnd = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(consolehwnd, &p);


    cout << "this text is not colorized\n";
    SetConsoleTextAttribute(consolehwnd, FOREGROUND_RED);
    cout << "this text shows as red\n";
    SetConsoleTextAttribute(consolehwnd, FOREGROUND_BLUE);
    cout << "this text shows as blue\n";

    SetConsoleTextAttribute(consolehwnd, p.wAttributes);
    cout << "this text shows as blue\n";




    std::cin.ignore();

}   // end of main
