#include "redirection.hpp"
#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

int execute_redirection(const ParsedCommand& command)
{
    std::vector<char*> argv;

    argv.reserve(command.command.size() + 1);

    for (const auto& str : command.command)
    {
        argv.push_back(const_cast<char*>(str.c_str()));
    }

    argv.push_back(nullptr);

    pid_t pid{fork()};

    if (pid < 0)
    {
        std::perror("fork failed");
        return 1;
    }

    if (pid == 0)
    {
        // Output redirection: >
        if (command.has_output_redirect)
        {
            int fd{open(command.output_file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644)};

            if (fd < 0)
            {
                std::perror("open failed");
                std::exit(1);
            }

            dup2(fd, STDOUT_FILENO);
            close(fd);
        }

        // Input redirection: <
        if (command.has_input_redirect)
        {
            int fd{open(command.input_file.c_str(), O_RDONLY)};

            if (fd < 0)
            {
                std::perror("open failed");
                std::exit(1);
            }

            dup2(fd, STDIN_FILENO);
            close(fd);
        }

        execvp(argv[0], argv.data());

        std::perror("execvp failed");
        std::exit(1);
    }

    int status{};
    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
    {
        return WEXITSTATUS(status);
    }

    return 1;
}
