#include "process.h"

#include <dirent.h>
#include <pwd.h>
#include <signal.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

// Utility functions inside an anonymous namespace.
namespace
{
    // Splits the given input string using the given delimeter char and returns
    // the split tokens as a vector.
    std::vector<std::string> split(const std::string& input, char delimiter)
    {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream token_stream(input);

        while (std::getline(token_stream, token, delimiter))
        {
            tokens.push_back(token);
        }
		
        return tokens;
    }

    // Trims the whitespace characters from the given input string
    // and returns the trimmed string.
    std::string trim(const std::string& input)
    {
        std::string s(input);
        s.erase(0, s.find_first_not_of(" \n\r\t"));
        s.erase(s.find_last_not_of(" \n\r\t") + 1);
        return s;
    }

    // Reads the contents of the given input stream into a string.
    std::string read_to_end(std::istream& in)
    {
        std::string s;
        char buffer[4096];

        while (in.read(buffer, sizeof(buffer)))
        {
            s.append(buffer, sizeof(buffer));
        }

        s.append(buffer, in.gcount());
        return s;
    }

    // Returns all the process ids by reading the folders with numerical names
    // under the /proc folder.
    std::vector<int> get_process_ids()
    {
        std::regex process_id("^[0-9]+$");
        std::vector<int> process_ids;
        auto* proc_dir = opendir("/proc");

        if (proc_dir)
        {
            auto* dir_entry = readdir(proc_dir);

            while (dir_entry != nullptr)
            {
                if (dir_entry->d_type == DT_DIR)
                {
                    std::string dir_name(dir_entry->d_name);

                    if (std::regex_match(dir_name, process_id))
                    {
                        process_ids.emplace_back(std::stoi(dir_name));
                    }
                }

                dir_entry = readdir(proc_dir);
            }

            closedir(proc_dir);
        }

        return process_ids;
    }

    // Returns the process with the given process id.
    // If the given process id doesn't exist then returns a default constructed Process struct.
    pi::Process get_process(int process_id)
    {
        std::string proc_status_path("/proc/" + std::to_string(process_id) + "/status");
        std::ifstream proc_status(proc_status_path);
        pi::Process process;
        proc_status >> process;
        return process;
    }
}

// *** Process Struct's Member Functions *** //

// Kills this process instance.
void pi::Process::p_kill()
{
    ::kill(static_cast<pid_t>(id), SIGKILL);
}

// Pause this process instance.
void pi::Process::p_pause()
{
    ::kill(static_cast<pid_t>(id), SIGSTOP);
}

// Continue
void pi::Process::p_continue()
{
    ::kill(static_cast<pid_t>(id), SIGCONT);
}

// Returns all processes.
std::vector<pi::Process> pi::Process::list()
{
    std::vector<pi::Process> processes;
    auto process_ids = get_process_ids();

    for (const auto& pid : process_ids)
    {
        processes.emplace_back(get_process(pid));
    }

    return processes;
}

// Returns filtered processes.
std::vector<pi::Process> pi::Process::filter(std::vector<pi::Process> &processes, std::string username)
{
    std::vector<pi::Process> filtered_processes;
    std::copy_if(processes.begin(), processes.end(), std::back_inserter(filtered_processes),
    [&username] (const pi::Process& process) { return !process.user_name.compare(username); });

    return filtered_processes;
}

// Input stream to process operator.
// /proc/{pid}/status file parsing happens here.
std::istream& pi::operator>>(std::istream& is, Process& process)
{
    auto proc_status = read_to_end(is);
    auto lines = split(proc_status, '\n');

    for(const auto& line: lines)
    {
        auto key_value_pair = split(line, ':');

        if (key_value_pair.size() == 2)
        {
            auto key = trim(key_value_pair.at(0));
            auto value = trim(key_value_pair.at(1));

            if (key == "Name")
            {
                process.name = value;
            }
            else if (key == "Pid")
            {
                process.id = std::stoi(value);
            }
            else if (key == "PPid")
            {
                process.parent_id = std::stoi(value);
            }
            else if (key == "Uid")
            {
                auto uids = split(value, '\t');
                process.uid = std::stoi(uids.at(0));
                auto pw = ::getpwuid(static_cast<uid_t>(process.uid));

                if (pw)
                {
                    process.user_name = std::string(pw->pw_name);
                }
            }
            else if (key == "State")
            {
                process.state = std::string(value);
            }
            else if (key == "Threads")
            {
                process.number_of_process = std::stoi(value);
            }
            else if (key == "VmData")
            {
                process.vm_data = std::stoi(value);
            }
            else if (key == "VmSize")
            {
                process.vm_size = std::stoi(value);
            }
            else if (key == "FDSize")
            {
                process.fd_size = std::stoi(value);
            }
        }
    }

    return is;
}




