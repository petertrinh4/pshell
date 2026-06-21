#include "pipe.hpp"
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

int execute_pipe(const ParsedCommand& command)
{

    if (command.command.empty() || command.piped_command.empty())
    {
        std::cerr << "pipe: invalid command\n";
        return 1;
    }

    std::vector<char*> argv1; // Left hand side of pipe
    argv1.reserve(command.command.size() + 1);

    for (const auto& str : command.command)
    {
        argv1.push_back(const_cast<char*>(str.c_str()));
    }

    argv1.push_back(nullptr);

    std::vector<char*> argv2; // Right hand side of pipe
    argv2.reserve(command.piped_command.size() + 1);

    for (const auto& str : command.piped_command)
    {
        argv2.push_back(const_cast<char*>(str.c_str()));
    }

    argv2.push_back(nullptr);

    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        std::perror("pipe failed");
        return 1;
    }

    pid_t pid1{fork()};

    if (pid1 < 0)
    {
        std::perror("fork failed");
        return 1;
    }

    if (pid1 == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[0]);
        close(pipefd[1]);

        execvp(argv1[0], argv1.data());

        std::perror("execvp failed");
        std::exit(1);
    }

    pid_t pid2{fork()};

    if (pid2 < 0)
    {
        std::perror("fork failed");
        return 1;
    }

    if (pid2 == 0)
    {
        dup2(pipefd[0], STDIN_FILENO);

        close(pipefd[0]);
        close(pipefd[1]);

        execvp(argv2[0], argv2.data());

        std::perror("execvp failed");
        std::exit(1);
    }

    close(pipefd[0]);
    close(pipefd[1]);

    int status{};

    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);

    return 0;
}
