#!/usr/bin/env python3

import argparse
from pathlib import Path

from text_to_brainfuck.brainfuck_generator import string_to_bf


def _str_to_bf(s):
    return string_to_bf(s, False)


def _split_to_lines(s, width=120):
    return [s[y - width : y] for y in range(width, len(s) + width, width)]


def _to_c_str_lines(s):
    c_str = ""
    for line in _split_to_lines(s):
        c_str += f's+="{line}";\n'
    return c_str


def _parse_args():
    parser = argparse.ArgumentParser("Generate Brainfuck code that prints C++ code")
    parser.add_argument("input", type=Path, help="Input C++ file to read")
    parser.add_argument(
        "--output", "-o", type=Path, required=True, help="Output C++ file to write"
    )
    return parser.parse_args()


def _main():
    args = _parse_args()
    stage_1 = args.input.read_text()
    part_1, part_2 = stage_1.split("// BF_CODE\n", maxsplit=1)

    stage_1_bf = _str_to_bf(stage_1)
    stage_1_bf_c_str = _to_c_str_lines(stage_1_bf)
    stage_1_bf_c_str_bf = _str_to_bf(stage_1_bf_c_str)

    stage_2 = ""
    stage_2 += part_1
    stage_1_bf_c_str_bf_wrapped = (
        _str_to_bf(part_1) + stage_1_bf_c_str_bf + _str_to_bf(part_2)
    )
    stage_2 += _to_c_str_lines(stage_1_bf_c_str_bf_wrapped)
    stage_2 += part_2
    args.output.write_text(stage_2)


if __name__ == "__main__":
    _main()
