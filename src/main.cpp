#include "dispatch.hpp"
#include "input.hpp"
#include "parser.hpp"

int main()
{
    while (true)
    {
        print_symbol();                     // Prints "$"
                                            //
        auto tokens{tokenize(get_input())}; // tokenizer() takes input and will tokenize
                                            // the entire line into words, the first word
                                            // being the "command" and the rest being "arguments".

        if (tokens.empty())
        {
            continue;
        }

        ParsedCommand parsed{ parse(tokens) };
        command_dispatch(parsed); // Will look at the first word in the vector to determine what
                                  // command is being utilized.
    }

    return 0;
}
