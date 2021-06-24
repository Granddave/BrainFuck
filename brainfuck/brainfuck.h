#pragma once

#include <array>
#include <math.h>
#include <optional>
#include <string>
#include <string_view>

namespace BrainFuck {

std::optional<std::string> parse(std::string filepath);

class Runner {
public:
    Runner(std::string code);
    void run();

private:
    char consume();
    void jump_forward();
    void jump_back();

    std::size_t m_pc { 0 };
    std::size_t m_ptr { 0 };
    std::string m_code;
    std::array<std::uint8_t, 32768> m_memory { 0 };
};

}
