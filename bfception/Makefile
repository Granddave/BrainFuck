CFLAGS := -O0 -Wall -Wextra -Werror -std=c11
CXXFLAGS := -O0 -Wall -Wextra -Werror -std=c++11

all: step_9_main.cpp

step_2_main.cpp: step_1_main.cpp generate_brainfuck_code.py
	time ./generate_brainfuck_code.py

step_3_generated.c: step_2_main.cpp
	time g++ $(CXXFLAGS) step_2_main.cpp -o step_3
	time ./step_3 > step_3_generated.c

step_5_main.cpp: step_3_generated.c
	time gcc $(CFLAGS) step_3_generated.c -o step_4
	time ./step_4 > step_5_main.cpp

step_7.c: step_5_main.cpp
	time g++ $(CXXFLAGS) step_5_main.cpp -o step_6
	time ./step_6 > step_7.c

step_9_main.cpp: step_7.c
	time gcc $(CFLAGS) step_7.c -o step_8
	time ./step_8 > step_9_main.cpp
	diff step_1_main.cpp step_9_main.cpp && echo The same!

clean:
	rm -f step_2_main.cpp
	rm -f step_3 step_3_generated.c
	rm -f step_4 step_5_main.cpp
	rm -f step_6 step_7.c
	rm -f step_8 step_9_main.cpp

.PHONY: all clean
