#include "dispatch.hpp"
#include "executor.hpp"

void command_dispatch(const std::vector<std::string>& tokens)
{
    if (tokens.empty())
    {
        return;
    }
    if (tokens[0] == "exit")
    {
        std::exit(0);
    }
    else if (tokens[0] == "cd")
    {
        try
        {
            if (tokens.size() < 2)
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
            if (tokens.size() > 2)
            {
                std::cerr << "cd: too many arguments\n";
                return;
            }

            std::filesystem::current_path(tokens[1]);
        }

        catch (const std::filesystem::filesystem_error& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    else
    {
        int result{execute_external(tokens)};

        if (result != 0)
        {
            std::cout << tokens[0] << ": command not found" << '\n';
        }
    }
}
