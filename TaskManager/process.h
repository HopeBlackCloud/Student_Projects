#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <istream>
#include <vector>

namespace pi
{
    struct Process
    {
        int id;
        std::string name;
        std::string state;
        unsigned int uid;
        std::string user_name;
        int parent_id;
        int number_of_process;
        int vm_data;
        int vm_size;
        int fd_size;
        void p_kill();
        void p_pause();
        void p_continue();
        static std::vector<Process> list();
        static std::vector<Process> filter(std::vector<Process> &processes, std::string username);
    };

    std::istream& operator>> (std::istream& is, Process& dt);
}


#endif // PROCESS_H
