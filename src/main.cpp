#include "input.hpp"
#include "dispatch.hpp"

int main()
{
	while (true)
	{
	print_symbol(); // Prints "$"
			//
	std::vector<std::string> tokens{ tokenize(get_input()) }; // tokenizer() takes input and will tokenize the entire line into words, the first word being the "command" and the rest being "arguments".

	if (tokens.empty())
	{
		continue;
	}

	command_dispatch(tokens); // Will look at the first word in the vector to determine what command is being utilized.
	}

	return 0;
}
