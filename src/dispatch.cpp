#include "dispatch.hpp"

void command_dispatch(const std::vector<std::string>& tokens)
{
	if (tokens[0] == "exit")
	{
		std::exit(0);
	}
	else if (tokens[0] == "pwd")
	{
		// Print working directory
	}
	else
	{
		std::cout << tokens[0] << ": command not found" << '\n';
	}
}
