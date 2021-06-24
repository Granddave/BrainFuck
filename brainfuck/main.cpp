#include <iostream>

#include "brainfuck.h"

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Run with " << argv[0] << " <source file>\n";
        return -1;
    }

    auto code_or_error = BrainFuck::parse(argv[1]);
    if (!code_or_error.has_value()) {
        std::cerr << "Failed to parse\n";
        return EXIT_FAILURE;
    }

    BrainFuck::Runner runner(code_or_error.value());
    runner.run();

    return EXIT_SUCCESS;
}
