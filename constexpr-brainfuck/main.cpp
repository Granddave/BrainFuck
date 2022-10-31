#include "constexpr-brainfuck.h"

int main(int, char**)
{
    constexpr std::string_view code(R"(
++       Cell c0 = 2
> +++++  Cell c1 = 5
[        Start your loops with your cell pointer on the loop counter (c1 in our case)
< +      Add 1 to c0
> -      Subtract 1 from c1
]        End your loops with the cell pointer on the loop counter
)");
    constexpr BrainFuck bf(code);

    return bf.read_memory(0);
}
