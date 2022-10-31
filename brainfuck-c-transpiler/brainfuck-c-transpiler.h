#pragma once

#include <array>
#include <cassert>
#include <sstream>
#include <string>

const static int INDENTATION_STEP = 4;

class BrainFuck {
public:
    BrainFuck(const std::string_view code)
        : m_code(std::move(code))
    {
    }

    std::string get_c_code()
    {
        assert(!m_code.empty());
        m_pc = 0;

        m_result << "#include \"stdio.h\"\n"
                 << "int main()\n{\n";
        indent();
        indentation();
        m_result << "int memory[32768];\n";

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
                indentation();
                m_result << "memory[" << m_ptr << "] += 1;\n";
                break;
            case '-':
                indentation();
                m_result << "memory[" << m_ptr << "] -= 1;\n";
                break;
            case '.':
                indentation();
                m_result << "putchar(memory[" << m_ptr << "]);\n";
                break;
            case ',':
                indentation();
                m_result << "memory[" << m_ptr << "] = getchar();\n";
                break;
            case '[':
                indentation();
                m_result << "while (memory[" << m_ptr << "] != 0) {\n";
                indent();
                break;
            case ']':
                unindent();
                indentation();
                m_result << "}\n";
                break;
            default:
                continue;
            }
        }
        unindent();
        m_result << "}";
        return m_result.str();
    }

private:
    char consume()
    {
        assert(m_pc < m_code.size());
        return m_code[m_pc++];
    }

    void indentation()
    {
        m_result << std::string(m_indentation * INDENTATION_STEP, ' ');
    }

    void indent()
    {
        ++m_indentation;
    }

    void unindent()
    {
        --m_indentation;
    }

    std::stringstream m_result;
    int m_indentation { 0 };
    std::size_t m_pc { 0 };
    std::size_t m_ptr { 0 };
    std::string_view m_code;
    std::array<std::uint8_t, 32768> m_memory { 0 };
};
