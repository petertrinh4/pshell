cmake_minimum_required(VERSION 3.15)
project(pshell VERSION 1.0 LANGUAGES CXX)

# Generates compile_commands.json in build folder for Neovim's LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Force modern C++ standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Compiler options
if(MSVC)
	add_compile_options(/W4 /WX)
else()
	add_compile_options(-Wall -Wextra -Werror -pedantic)
endif()

# Source files
set(SOURCES
	src/main.cpp
)

# Builds an executable named "pshell"
add_executable(${PROJECT_NAME} ${SOURCES})
