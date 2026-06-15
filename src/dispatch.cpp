#include "dispatch.hpp"
#include "executor.hpp"

void command_dispatch(const std::vector<std::string>& tokens)
{
	if (tokens[0] == "exit")
	{
		std::exit(0);
	}
	else if (tokens[0] == "pwd")
	{
		// Print working directory, maybe add builtin folder for cd, pwd, etc...
	}
	else if (tokens[0] == "cd")
	{
	
	}
	else if (tokens[0] == "ls" || tokens[0] == "echo" || 
			tokens[0]== "cat" || tokens[0] == "whoami" || 
            tokens[0] == "date")
	{
		execute_external(tokens);
	}
	else
	{
		std::cout << tokens[0] << ": command not found" << '\n';
	}
}
