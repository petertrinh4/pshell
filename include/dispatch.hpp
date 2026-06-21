#pragma once

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <vector>
#include "parser.hpp"
#include "pipe.hpp"
#include "redirection.hpp"
#include "executor.hpp"

void command_dispatch(const ParsedCommand& command);
