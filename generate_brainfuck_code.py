#!/usr/bin/env python3

from text_to_brainfuck.brainfuck_generator import string_to_bf

SEPARATOR = "[-]>[-]>[-]>[-]>[[[[[-]>]>]>]>]<<<"
BF_LEN = 1600

def _main():
    bf_result = ""

    # read file 1
    part_1_content = None
    with open("bfception/main_1.cpp", "r") as f:
        part_1_content = "".join(f.readlines())

    # split into parts of 1600 bytes
    part_1_splitted = [part_1_content[y-BF_LEN:y] for y in range(BF_LEN, len(part_1_content)+BF_LEN,BF_LEN)]

    # convert to bf
    for p in part_1_splitted:
        # append together with SEPARATOR in between
        bf_result += string_to_bf(p, False)
        bf_result += SEPARATOR

    # read file 2
    part_2_content = None
    with open("bfception/main_2.cpp", "r") as f:
        part_2_content = "".join(f.readlines())
        bf_result += string_to_bf(part_2_content, False)

    with open("bfception/main.cpp", "w") as f:
        f.write(part_1_content)
        f.write(bf_result)
        f.write(part_2_content)


if __name__ == '__main__':
    _main()
