#!/usr/bin/env python3

from text_to_brainfuck.brainfuck_generator import string_to_bf

SEPARATOR = "[-]>[-]>[-]>[-]>[[[[[-]>]>]>]>]<<<"
BF_LEN = 80

def _main():
    bf_result = ""

    # read file 1
    part_1_content = None
    with open("step_1_main_1.cpp", "r") as fd:
        part_1_content = "".join(fd.readlines())
    part_2_content = None
    with open("step_1_main_2.cpp", "r") as fd:
        part_2_content = "".join(fd.readlines())

    # split into parts
    #part_1_splitted = [part_1_content[y-BF_LEN:y] for y in range(BF_LEN, len(part_1_content)+BF_LEN,BF_LEN)]
    #part_1_splitted = [part_1_content]
    # convert to bf
    #for p in part_1_splitted:
    #    # append together with SEPARATOR in between
    #    bf_result += string_to_bf(p, False)
    #    bf_result += SEPARATOR

    bf_result += string_to_bf(part_1_content, False)
    bf_result += string_to_bf(string_to_bf(part_1_content, False), False)
    bf_result += string_to_bf(string_to_bf(part_2_content, False), False)
    bf_result += string_to_bf(part_2_content, False)
    bf_results = [bf_result[y-BF_LEN:y] for y in range(BF_LEN, len(bf_result)+BF_LEN,BF_LEN)]

    with open("step_2_main.cpp", "w") as fd:
        fd.write(part_1_content)
        for bf_line in bf_results:
            fd.write(f'    code += "{bf_line}";\n')
        fd.write(part_2_content)


if __name__ == '__main__':
    _main()
