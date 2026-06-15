#pragma once

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <vector>
#include <string>

int execute_external(const std::vector<std::string>& tokens);
