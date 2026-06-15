#include "input.hpp"

void print_symbol()
{
    std::cout << "$ ";
}

std::string get_input()
{
    std::string input{};

    if (!std::getline(std::cin, input)) // Get user input
    {
        std::exit(0);
    }

    return input;
}

std::vector<std::string> tokenize(const std::string& input)
{
    std::stringstream ss(input);
    std::string token{};
    std::vector<std::string> tokens;

    while (ss >> token)
    {
        tokens.push_back(token); // Insert words into vector
    }

    return tokens;
}
