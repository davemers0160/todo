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
//#include <sys/stat.h>

// custom includes
#include "num2string.h"
#include "file_parser.h"
#include "make_dir.h"
#include "get_current_time.h"
#include "get_platform.h"
#include "console_colors.h"

class todo_task
{
public:

    struct tm task_start, task_due;

    uint32_t priority;
    uint64_t index;

    std::string task_description;

    todo_task() = default;

    todo_task(uint32_t p_, uint64_t i_, std::string td_) : priority(p_), index(i_), task_description(td_)
    {
        time_t rawtime;
        time(&rawtime);
        task_start = *localtime(&rawtime);

        // add two weeks to the task start date
        rawtime += 1209600;
        task_due = *localtime(&rawtime);
    }

    todo_task(uint32_t p_, uint64_t i_, std::string td_, struct tm te_) : priority(p_), index(i_), task_description(td_), task_due(te_)
    {
        time_t rawtime;
        time(&rawtime);
        task_start = *localtime(&rawtime);
    }

    // ----------------------------------------------------------------------------------------

    void print_task(void)
    {
        std::string c;
        time_t now = time(0);

        if (mktime(&task_due) < now)
            c = red;
        else
        {
            if (priority == 0)
                c = red;
            else if (priority == 1)
                c = yellow;
            else
                c = green;
        }

        std::cout << def_color(c) << *this << std::endl;
    }

    inline friend std::ostream& operator<< (
        std::ostream& out,
        const todo_task &item
        )
    {
        out << item.priority << ", " << item.index << ", ";
        out << (1900 + item.task_start.tm_year) << item.task_start.tm_mon << item.task_start.tm_mday << ", ";
        out << (1900 + item.task_due.tm_year) << item.task_due.tm_mon << item.task_due.tm_mday << ", ";
        out << item.task_description;
        return out;
    }

};  // end of todo_task






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
    // priority index, add date, due date, task
    std::string sdate,stime;
    get_current_time(sdate, stime);

    todo_task todo;
    auto t = time(NULL);
    todo_task todo2(0, 0, "test of the todo task class", *localtime(&t));

    std::cout << todo << std::endl;
    std::cout << todo2 << std::endl;

    todo2.print_task();

    std::cout << sdate << "_" << stime << std::endl;

    //std::cout << color(blue, black) << "red test" << reset << std::endl;
    //std::cout << "test 2" << std::endl;
    //std::cout << bright_color(blue, black) << "red test" << reset << std::endl;

    todo_stream.close();
    done_stream.close();

    std::cin.ignore();

}   // end of main
