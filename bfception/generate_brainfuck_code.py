#!/usr/bin/env python3

from text_to_brainfuck.brainfuck_generator import string_to_bf

SEPARATOR = "[-]>[-]>[-]>[-]>[[[[[-]>]>]>]>]<<<"
BF_LEN = 80


def _main():
    bf_result = ""

    part_1_content = None
    with open("step_1_main_1.cpp", "r") as fd:
        part_1_content = "".join(fd.readlines())
    part_2_content = None
    with open("step_1_main_2.cpp", "r") as fd:
        part_2_content = "".join(fd.readlines())

    # split into parts
    # part_1_splitted = [part_1_content[y-BF_LEN:y] for y in range(BF_LEN, len(part_1_content)+BF_LEN,BF_LEN)]
    # part_1_splitted = [part_1_content]
    # convert to bf
    # for p in part_1_splitted:
    #    # append together with SEPARATOR in between
    #    bf_result += string_to_bf(p, False)
    #    bf_result += SEPARATOR

    part_1_bf = string_to_bf(part_1_content, False)
    part_2_bf = string_to_bf(part_2_content, False)
    mid = part_1_bf + part_2_bf
    mid_bf_lines = [
        mid[y - BF_LEN : y] for y in range(BF_LEN, len(mid) + BF_LEN, BF_LEN)
    ]

    def format_code_string(s):
        return f'    code += "{s}";\n'

    mid_bf = ""
    for bf_line in mid_bf_lines:
        mid_bf += format_code_string(bf_line)
    mid_bf_bf = string_to_bf(mid_bf, False)

    bf_result += part_1_bf
    bf_result += mid_bf_bf
    bf_result += part_2_bf
    bf_results = [
        bf_result[y - BF_LEN : y]
        for y in range(BF_LEN, len(bf_result) + BF_LEN, BF_LEN)
    ]

    with open("step_2_main.cpp", "w") as fd:
        fd.write(part_1_content)
        for bf_line in bf_results:
            fd.write(format_code_string(bf_line))
        fd.write(part_2_content)


if __name__ == "__main__":
    _main()
