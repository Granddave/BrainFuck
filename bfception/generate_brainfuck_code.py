#!/usr/bin/env python3

import argparse
from pathlib import Path

from text_to_brainfuck.brainfuck_generator import string_to_bf


def _parse_args():
    parser = argparse.ArgumentParser("Generate Brainfuck code that prints C++ code")
    parser.add_argument("input", type=Path, help="Input C++ file to read")
    parser.add_argument(
        "--output", "-o", type=Path, required=True, help="Output C++ file to write"
    )
    return parser.parse_args()


def _split_to_lines(s, width=220):
    return [s[y - width : y] for y in range(width, len(s) + width, width)]


def _format_c_append(s):
    return f's+="{s}";\n'


def _main():
    args = _parse_args()
    split_marker = "// BF_HERE\n"
    part_1, part_2 = args.input.read_text().split(split_marker, maxsplit=1)

    # This is now Brainfuck code that prints the C++ code
    part_1_bf = string_to_bf(part_1, False)
    split_marker_bf = string_to_bf(split_marker, False)
    part_2_bf = string_to_bf(part_2, False)

    # `mid` is what we want BF to print out in the end
    mid = part_1_bf + split_marker_bf + part_2_bf

    # Now add this brainfuck code as many lines of C++ code
    mid_bf = ""
    for line in _split_to_lines(mid):
        mid_bf += _format_c_append(line)

    mid_bf_bf = string_to_bf(mid_bf, False)

    bf_results_bf = part_1
    for line in _split_to_lines(part_1_bf + mid_bf_bf + part_2_bf):
        bf_results_bf += _format_c_append(line)
    bf_results_bf += part_2

    args.output.write_text(bf_results_bf)


if __name__ == "__main__":
    _main()
