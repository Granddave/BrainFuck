#include <array>
#include <cassert>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdint.h>
#include <string>
#include <string_view>
using namespace std;
int main(int, char**)
{
stringstream r;
size_t pc{0};
size_t p{0};
string c;
array<uint8_t, 32768> m { 0 };
string s;
// BF_HERE
for(char ch:s){if(strchr("><+-.,[]",ch))c.push_back(ch);}
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
cout<<r.str()<<endl;
return 0;
}
