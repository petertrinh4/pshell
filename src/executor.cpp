#include "executor.hpp"

int execute_external(const std::vector<std::string>& tokens) // Executes commands like "ls", "echo", and "cat"
{
	if (tokens.empty())
	{
		return 0;
	}

	std::vector<char*> argv; // Convert std::string into const char*
	argv.reserve(tokens.size() + 1);

	for (const auto& str: tokens) // Populate new vector for execvp()
	{
		argv.push_back(const_cast<char*>(str.c_str()));
	}

	argv.push_back(nullptr); // Add null pointer at the end of the array

	pid_t pid{ fork() }; // pid is returned on success from fork()
	
	if (pid < 0)
	{
		std::perror("Fork failed");
		return 1;
	}
	else if (pid == 0)
	{
		execvp(argv[0], argv.data());

		std::perror("execvp execution failed");
		std::exit(1);
	}
	else
	{
		int status{};
		if (waitpid(pid, &status, 0) == -1)
		{
			std::perror("waitpid failed");
			return 1;
		}
	}

	return 0;
}
