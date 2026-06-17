#include "dispatch.hpp"
#include "executor.hpp"

void command_dispatch(const ParsedCommand& command)
{
    if (command.command.empty())
    {
        return;
    }
    if (command.command[0] == "exit")
    {
        std::exit(0);
    }
    else if (command.command[0] == "cd")
    {
        try
        {
            if (command.command.size() < 2)
            {
                const char* home{std::getenv("HOME")};

                if (home == nullptr)
                {
                    std::cerr << "cd: HOME not set\n";
                    return;
                }
                std::filesystem::current_path(home);
                return;
            }
            if (command.command.size() > 2)
            {
                std::cerr << "cd: too many arguments\n";
                return;
            }

            std::filesystem::current_path(command.command[1]);
        }

        catch (const std::filesystem::filesystem_error& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    else if (command.has_pipe)
    {
        execute_pipe(command);
    }
    else if (command.has_output_redirect ||
            command.has_input_redirect)
    {
        execute_redirection(command);
    }
    else
    {
        int result{execute_external(command.command)};

        if (result != 0)
        {
            std::cout << command.command[0] << ": command not found" << '\n';
        }
    }
}
