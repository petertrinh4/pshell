#include "parser.hpp"
#include <iostream>

ParsedCommand parse(const std::vector<std::string>& tokens) // Takes in tokenized vector
{
    ParsedCommand parsed{};
    bool parsing_piped_command{false}; // Tokens after "|" belong to piped_command

    for (std::size_t i{}; i < tokens.size(); ++i)
    {
        const auto& token{tokens[i]};

        if (token == "|")
        {
            parsed.has_pipe = true;
            parsing_piped_command = true;
        }
        else if (token == ">")
        {
            parsed.has_output_redirect = true;

            if (i + 1 >= tokens.size())
            {
                std::cerr << "Parse error: expected filename after '>'\n";
                return parsed;
            }

            ++i;
            parsed.output_file = tokens[i];
        }
        else if (token == "<")
        {
            parsed.has_input_redirect = true;

            if (i + 1 >= tokens.size())
            {
                std::cerr << "Parse error: expected filename after '<'\n";
                return parsed;
            }

            ++i;
            parsed.input_file = tokens[i];
        }
        else if (token == "&")
        {
            parsed.background = true;
        }
        else
        {
            if (parsing_piped_command)
            {
                parsed.piped_command.push_back(token); // Placing tokens in piped_command
            }
            else
            {
                parsed.command.push_back(token); // Placing tokens in command
            }
        }
    }

    return parsed;
}
