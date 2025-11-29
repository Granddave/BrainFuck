#include <array>
#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <string>
#include <string_view>
using namespace std;
class BF {
public:
    BF(const string_view code) { for(char ch:code) if(strchr("><+-.,[]",ch)) c.push_back(ch); }
    string get_c_code()
    {
        pc=0;
        r<<"#include \"stdio.h\"\n#define P putchar\n#define G getchar\n#define W while\nint main(){\nint m[32768];\n";
        int n;
        while(pc<c.size()){
            char ct=c[pc++];
            switch(ct){
            case'>':++p;break;
            case'<':--p;break;
            case'+':n=1; while(c[pc]=='+') {pc++;++n;}r<<"m["<<p<<"]+="<<n<<";\n";break;
            case'-':n=1; while(c[pc]=='-'){pc++;++n;}r<<"m["<<p<<"]-="<<n<<";\n";break;
            case'.':r<<"P(m["<<p<<"]);\n";break;
            case',':r<<"m["<<p<<"]=G();\n";break;
            case'[':r<<"W(m["<<p<<"]!=0){\n";break;
            case']':r<<"}\n";break;
            default:continue;
            }
        }
        r<<"}";
        return r.str();
    }

private:
    stringstream r;
    size_t pc{0};
    size_t p{0};
    string c;
    array<uint8_t, 32768> m { 0 };
};

int main(int, char**)
{
    string s;
    // BF_HERE
    BF bf(s);
    cout << bf.get_c_code() << endl;
    return 0;
}
