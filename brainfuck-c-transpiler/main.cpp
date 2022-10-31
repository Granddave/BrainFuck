#include <iostream>
#include <string_view>

#include "brainfuck-c-transpiler.h"

int main(int, char**)
{
    constexpr std::string_view code(R"(
++++++++++[>+++++++>++++++++++>+++>+<<<<-]
>++.>+.+++++++..+++.>++.<<+++++++++++++++.
>.+++.------.--------.>+.>.
)");
    BrainFuck bf(code);
    std::cout << bf.get_c_code() << std::endl;
    return 0;
}
