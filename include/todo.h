#ifndef _TODO_H_
#define _TODO_H_

#include <ctime>
#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>
#include <list>

#include "file_parser.h"
#include "get_current_time.h"
#include "console_colors.h"

// ----------------------------------------------------------------------------------------
class todo_task
{
public:

    time_t task_start, task_due;

    uint32_t priority;
    uint64_t index;

    std::string task_description;

    todo_task()
    {
        priority = 0;
        index = 0;
        task_description = "";
        task_start = time(NULL);
        task_due = task_start + 1209600;
    }

    todo_task(uint32_t p_, std::string td_) : priority(p_), task_description(td_)
    {
        //time_t rawtime;
        //time(&rawtime);
        //task_start = *localtime(&rawtime);
        task_start = time(NULL);

        // add two weeks to the task start date
        task_due = task_start + 1209600;
        //task_due = *localtime(&rawtime);
    }

    todo_task(uint32_t p_, time_t te_, std::string td_) : priority(p_), task_due(te_), task_description(td_)
    {
        //time_t rawtime;
        //time(&rawtime);
        //task_start = *localtime(&rawtime);
        task_start = time(NULL);
    }

    todo_task(uint32_t p_, uint64_t i_, time_t ts_, time_t te_, std::string td_) : priority(p_), index(i_), task_start(ts_), task_due(te_), task_description(td_)
    {
        //time_t rawtime;
        //time(&rawtime);
        //task_start = *localtime(&rawtime);
        //task_start = time(NULL);
    }

    void set_index(uint64_t i_) {
        index = i_;
    }


    // ----------------------------------------------------------------------------------------
    void print_task(void)
    {
        std::string c;
        time_t now = time(0);

        if (task_due < now)
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

        std::cout << def_color(c) << *this << reset << std::endl;
    }

    // ----------------------------------------------------------------------------------------
    inline bool operator <(const todo_task& item) const
    {
        return (priority < item.priority);
    }

    // ----------------------------------------------------------------------------------------
    inline friend std::ostream& operator<< (
        std::ostream& out,
        const todo_task& item
        )
    {
        out << item.priority << ", " << item.index << ", ";
        out << get_date(item.task_start, "%Y%m%d") << ", ";
        out << get_date(item.task_due, "%Y%m%d") << ", ";
        out << item.task_description;
        return out;
    }

};  // end of todo_task

// ----------------------------------------------------------------------------------------
void read_todo_file(std::string filename, std::list<todo_task>& v_todo)
{
    std::vector<std::vector<std::string>> params;
    parse_csv_file(filename, params);

    v_todo.clear();

    for (uint64_t idx = 0; idx < params.size(); ++idx)
    {
        try {
            todo_task t(std::stol(params[idx][0]), std::stol(params[idx][1]), convert_date(params[idx][2]), convert_date(params[idx][3]), params[idx][4]);
            v_todo.push_back(t);
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
    }
}

// ----------------------------------------------------------------------------------------
void write_todo_file(std::string filename, std::list<todo_task>& v_todo)
{
    std::ofstream todo_stream;
    todo_stream.open(filename, ios::out);
    
    for (auto& td : v_todo)
        todo_stream << td << std::endl;

    //for (uint64_t idx = 0; idx < v_todo.size(); ++idx)
    //{
    //    auto it = std::next(v_todo.begin(), idx);
    //    todo_stream << *it << std::endl;
    //}

    todo_stream.close();
}

// ----------------------------------------------------------------------------------------
uint64_t get_max_index(std::list<todo_task>& v_todo)
{
    uint64_t index = 0;
    
    for (auto& td : v_todo)
    {
        if (td.index > index)
            index = td.index;
    }
    //for (uint64_t idx = 0; idx < v_todo.size(); ++idx)
    //{
    //    auto it = std::next(v_todo.begin(), idx);
    //    if ((*it).index > index)
    //        index = (*it).index;
    //}
    return index+1;
}

#endif  // _TODO_H_
