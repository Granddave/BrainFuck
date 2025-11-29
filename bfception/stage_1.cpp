#include <array>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <stdint.h>

class BF {
public:
    BF(const std::string_view code)
    {
        for (char ch : code) {
            switch (ch) {
            case '>':
            case '<':
            case '+':
            case '-':
            case '.':
            case ',':
            case '[':
            case ']':
                c.push_back(ch);
                break;
            default:
                continue;
            }
        }
    }

    std::string get_c_code()
    {
        assert(!c.empty());
        pc = 0;

        r << "#include \"stdio.h\"\n"
          << "int main()\n{\n";
        r << "int m[32768];\n";
        r << "#define P putchar\n";
        r << "#define G getchar\n";
        r << "#define W while\n";

        int count = 1;
        while (pc < c.size()) {
            const char current_token = consume();

            switch (current_token) {
            case '>':
                assert(ptr + 1 < m.size());
                ++ptr;
                break;
            case '<':
                assert(ptr != 0);
                --ptr;
                break;
            case '+':
                count = 1;
                while (peek() == '+') {
                    consume();
                    ++count;
                }
                r << "m[" << ptr << "] += " << count << ";\n";
                break;
            case '-':
                count = 1;
                while (peek() == '-') {
                    consume();
                    ++count;
                }
                r << "m[" << ptr << "] -= " << count << ";\n";
                break;
            case '.':
                r << "P(m[" << ptr << "]);\n";
                break;
            case ',':
                r << "m[" << ptr << "] = G();\n";
                break;
            case '[':
                r << "W (m[" << ptr << "] != 0) {\n";
                break;
            case ']':
                r << "}\n";
                break;
            default:
                continue;
            }
        }
        r << "}";
        return r.str();
    }

private:
    char consume()
    {
        assert(pc < c.size());
        return c[pc++];
    }

    char peek()
    {
        assert(pc < c.size());
        return c[pc];
    }
    std::stringstream r;
    std::size_t pc { 0 };
    std::size_t ptr { 0 };
    std::string c;
    std::array<uint8_t, 32768> m { 0 };
};

int main(int, char**)
{
    std::string code;
    // BF_HERE
    BF bf(code);
    std::cout << bf.get_c_code() << std::endl;
    return 0;
}
