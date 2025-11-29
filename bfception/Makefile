CFLAGS := -std=c11
CXXFLAGS := -std=c++20

all: stage_6.cpp

stage_2.cpp: stage_1.cpp generate_brainfuck_code.py
	time ./generate_brainfuck_code.py stage_1.cpp -o stage_2.cpp

stage_3.c: stage_2.cpp
	time g++ $(CXXFLAGS) stage_2.cpp -o stage_2
	time ./stage_2 > stage_3.c

stage_4.cpp: stage_3.c
	time gcc $(CFLAGS) stage_3.c -o stage_3
	time ./stage_3 > stage_4.cpp

stage_5.c: stage_4.cpp
	time g++ $(CXXFLAGS) stage_4.cpp -o stage_4
	time ./stage_4 > stage_5.c

stage_6.cpp: stage_5.c
	time gcc $(CFLAGS) stage_5.c -o stage_5
	time ./stage_5 > stage_6.cpp
	diff stage_1.cpp stage_6.cpp && echo The same!

clean:
	rm -f stage_2.cpp stage_2
	rm -f stage_3.c stage_3
	rm -f stage_4.cpp stage_4
	rm -f stage_5.c stage_5
	rm -f stage_6.cpp

.PHONY: all clean
