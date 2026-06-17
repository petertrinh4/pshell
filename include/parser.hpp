#pragma once

#include <string>
#include <vector>

struct ParsedCommand
{
    std::vector<std::string> command; // Original vector w/ tokens

    bool has_pipe{ false };
    std::vector<std::string> piped_command;

    bool has_output_redirect{ false };
    std::string output_file{};

    bool has_input_redirect{ false };
    std::string input_file{};

    bool background{ false };
};

ParsedCommand parse(const std::vector<std::string>& tokens);
