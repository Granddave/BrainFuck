#!/usr/bin/env python3

import argparse

from text_to_brainfuck.brainfuck_generator import string_to_bf

BF_CODE_WIDTH = 120


def _parse_args():
    parser = argparse.ArgumentParser("Generate Brainfuck code that prints C++ code")
    parser.add_argument("input", type=str, help="Input C++ file to read")
    parser.add_argument(
        "--output", "-o", type=str, required=True, help="Output C++ file to write"
    )
    return parser.parse_args()


def _main():
    args = _parse_args()
    main_cpp = None
    with open(args.input, "r") as fd:
        main_cpp = fd.read()
    split_marker = "// BF_HERE\n"
    part_1, part_2 = main_cpp.split(split_marker, maxsplit=1)

    # This is now Brainfuck code that prints the C++ code
    part_1_bf = string_to_bf(part_1, False)
    split_marker_bf = string_to_bf(split_marker, False)
    part_2_bf = string_to_bf(part_2, False)

    # `mid` is what we want BF to print out in the end
    mid = part_1_bf + split_marker_bf + part_2_bf
    mid_bf_lines = [
        mid[y - BF_CODE_WIDTH : y]
        for y in range(BF_CODE_WIDTH, len(mid) + BF_CODE_WIDTH, BF_CODE_WIDTH)
    ]

    def format_code_string(s):
        return f's+="{s}";\n'

    # Now add this brainfuck code as many lines of C++ code
    mid_bf = ""
    for bf_line in mid_bf_lines:
        mid_bf += format_code_string(bf_line)
    mid_bf_bf = string_to_bf(mid_bf, False)

    main_stage_2 = part_1_bf + mid_bf_bf + part_2_bf
    bf_results = [
        main_stage_2[y - BF_CODE_WIDTH : y]
        for y in range(BF_CODE_WIDTH, len(main_stage_2) + BF_CODE_WIDTH, BF_CODE_WIDTH)
    ]

    with open(args.output, "w") as fd:
        fd.write(part_1)
        for bf_line in bf_results:
            fd.write(format_code_string(bf_line))
        fd.write(part_2)


if __name__ == "__main__":
    _main()
