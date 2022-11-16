#include <array>
#include <cassert>
#include <iostream>
#include <string_view>

class BrainFuck {
public:
    constexpr BrainFuck(const std::string_view code)
        : m_code(std::move(code))
    {
        run();
    }

    constexpr std::uint8_t read_memory(const size_t pos) const
    {
        return m_memory.at(pos);
    }

private:
    constexpr void run()
    {
        assert(!m_code.empty());
        m_pc = 0;
        while (m_pc < m_code.size()) {
            const char current_token = consume();

            switch (current_token) {
            case '>':
                assert(m_ptr + 1 < m_memory.size());
                ++m_ptr;
                break;
            case '<':
                assert(m_ptr != 0);
                --m_ptr;
                break;
            case '+':
                ++m_memory[m_ptr];
                break;
            case '-':
                --m_memory[m_ptr];
                break;
            case '.':
                putchar(m_memory[m_ptr]);
                break;
            case ',':
                m_memory[m_ptr] = getchar();
                break;
            case '[':
                if (m_memory[m_ptr] == 0) {
                    jump_forward();
                }
                break;
            case ']':
                if (m_memory[m_ptr] != 0) {
                    jump_back();
                }
                break;
            default:
                continue;
            }
        }
    }

    constexpr char consume()
    {
        assert(m_pc < m_code.size());
        return m_code[m_pc++];
    }

    constexpr void jump_forward()
    {
        int bracket_count = 0;
        while (true) {
            assert(m_pc + 1 < m_code.size());
            ++m_pc;
            if (m_code[m_pc] == '[') {
                ++bracket_count;
            } else if (m_code[m_pc] == ']' && bracket_count > 0) {
                --bracket_count;
            } else if (m_code[m_pc] == ']') {
                return;
            }
        }
    }

    constexpr void jump_back()
    {
        --m_pc;
        int bracket_count = 0;
        while (true) {
            assert(m_pc != 0);
            --m_pc;
            if (m_code[m_pc] == ']') {
                ++bracket_count;
            } else if (m_code[m_pc] == '[' && bracket_count > 0) {
                --bracket_count;
            } else if (m_code[m_pc] == '[') {
                return;
            }
        }
    }

    std::size_t m_pc { 0 };
    std::size_t m_ptr { 0 };
    std::string_view m_code;
    std::array<std::uint8_t, 32768> m_memory { 0 };
};

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
