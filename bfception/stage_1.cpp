#include <cstring>
#include <iostream>
#include <sstream>
using namespace std;int main(int,char**){string s;
// BF_HERE
stringstream r;int pc{0};int p{0};string c;for(char ch:s){if(strchr("><+-.,[]",ch))c.push_back(ch);}pc=0;r<<"#include \"stdio.h\"\n#define P putchar\n#define G getchar\n#define W while\nint main(){\nint m[32768];\n";int n;while(pc<c.size()){char ct=c[pc++];switch(ct){case'>':++p;break;case'<':--p;break;case'+':n=1;while(c[pc]=='+'){pc++;++n;}r<<"m["<<p<<"]+="<<n<<";\n";break;case'-':n=1;while(c[pc]=='-'){pc++;++n;}r<<"m["<<p<<"]-="<<n<<";\n";break;case'.':r<<"P(m["<<p<<"]);\n";break;case',':r<<"m["<<p<<"]=G();\n";break;case'[':r<<"W(m["<<p<<"]!=0){\n";break;case']':r<<"}\n";break;default:continue;}}r<<"}";cout<<r.str()<<endl;}
