#define _CRT_SECURE_NO_WARNINGS

#if defined(_WIN32) | defined(__WIN32__) | defined(__WIN32) | defined(_WIN64) | defined(__WIN64)
#include <windows.h>
#else defined(__linux__)

#endif

// C/C++ includes
#include <cmath>
#include <cstdint>
#include <ctime>
//#include <cstdio>
//#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
//#include <chrono>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

//#include <sys/stat.h>

// custom includes
#include "todo.h"
#include "num2string.h"
#include "file_parser.h"
#include "make_dir.h"
#include "get_current_time.h"
#include "get_platform.h"

/*

options:

--list

--add <priority> <due date> <task description>

--done <index>


*/

// ----------------------------------------------------------------------------------------

void parse_inputs(int argc, char** argv, uint8_t &cmd, todo_task &task)
{
    uint32_t idx;

    try {
        for (idx = 1; idx < argc; ++idx)
        {
            std::string arg(argv[idx]);
            if ((arg.compare("--add") == 0) && (argc >= 5))
            {
                cmd = 0;

                task = todo_task((uint32_t)std::stol(argv[idx + 1]), convert_date(argv[idx + 2]), (std::string)(argv[idx + 3]));
                //throw std::runtime_error("--add option requires");
            }
            else if ((arg.compare("--list") == 0))
            {
                cmd = 1;
            }
            else if ((arg.compare("--done") == 0) && (argc >=2))
            {
                cmd = 2;
                task.set_index((uint64_t)std::stol(argv[idx + 1]));
            }

        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return;
    }
    
}   // end of parse_inputs

// ----------------------------------------------------------------------------------------

void init(std::string &user_dir)
{
    int32_t status = make_dir(user_dir, ".todo");
    if (status < 0)
        std::cout << "Error creating .todo folder: " << status << std::endl;
}

// ----------------------------------------------------------------------------------------
int main(int argc, char** argv)
{
    uint64_t idx;

    std::fstream todo_stream, done_stream;
    std::list <todo_task> todo_list, done_list;
    todo_task tmp_todo;

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

    uint8_t cmd = 0;
    parse_inputs(argc, argv, cmd, tmp_todo);

    switch (cmd)
    {
    case 0:
        read_todo_file(todo_file, todo_list);
        tmp_todo.set_index(get_max_index(todo_list));
        todo_list.push_back(tmp_todo);
        todo_list.sort();
        write_todo_file(todo_file, todo_list);
        break;

    case 1:
        read_todo_file(todo_file, todo_list);
        todo_list.sort();

        for (auto& td : todo_list)
            td.print_task();

        break;

    case 2:

        break;

    default:
        break;
    }




    //std::cin.ignore();
    int bp = 0;

}   // end of main
