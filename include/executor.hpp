#pragma once

#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

int execute_external(const std::vector<std::string>& tokens);
