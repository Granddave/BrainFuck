#include "brainfuck.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

#define ASSERT_NOT_REACHED() assert(false)
#define ASSERT(expr) assert(expr)

//#define DEBUG

namespace BrainFuck {

constexpr char s_valid_tokens[] = {
    '<',
    '>',
    '+',
    '-',
    '.',
    ',',
    '[',
    ']',
};

constexpr bool is_valid_token(const char token)
{
    return std::any_of(std::begin(s_valid_tokens), std::end(s_valid_tokens), [&](int valid_token) {
        return valid_token == token;
    });
}

std::optional<std::string> parse(std::string filepath)
{
    std::ifstream source_stream(filepath.data());

    if (!source_stream.is_open()) {
        std::cerr << "Failed to open source file" << std::endl;
        return {};
    }

    std::stringstream code_stream;
    char current_char;
    while (source_stream.get(current_char)) {
        if (!is_valid_token(current_char))
            continue;
        code_stream << current_char;
    }

    const std::string code = code_stream.str();
    if (code.empty()) {
        std::cerr << "Failed to find code in source file" << std::endl;
        return {};
    }

    return code;
}

Runner::Runner(std::string code)
    : m_code(std::move(code))
{
}

void Runner::run()
{
    ASSERT(!m_code.empty());
#ifdef DEBUG
    std::cout << "Len: " << m_code.size() << '\n'
              << m_code << std::endl;
    int ins_count = 0;
#endif
    m_pc = 0;
    while (m_pc < m_code.size()) {
        const char current_token = consume();

#ifdef DEBUG
        ++ins_count;
        std::cout << ins_count << ": " << current_token << std::endl;
#endif

        switch (current_token) {
        case '>':
            ASSERT(m_ptr + 1 < m_memory.size());
            ++m_ptr;
            break;
        case '<':
            ASSERT(m_ptr != 0);
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
            std::cerr << "Unexpected token: '" << current_token << "' (" << (int)current_token << ")\n";
            ASSERT_NOT_REACHED();
        }
    }
}

char Runner::consume()
{
    ASSERT(m_pc < m_code.size());
    return m_code[m_pc++];
}

void Runner::jump_forward()
{
    int bracket_count = 0;
    while (true) {
        ASSERT(m_pc + 1 < m_code.size());
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

void Runner::jump_back()
{
    --m_pc;
    int bracket_count = 0;
    while (true) {
        ASSERT(m_pc != 0);
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

}
