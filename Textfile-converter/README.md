# Address Book Format Converter

A small C++ utility that converts an address book data file from a multi-line format into a compact single-line pipe-delimited format.

## The problem it solves

The original address book stored each contact across 6 separate lines. This is readable, but inconvenient to parse programmatically. This tool converts it into a single line per contact, with fields separated by `|`, which is the format required by the main Address Book application.

## Input format (datafile)

Each contact occupies exactly 6 consecutive lines in this order: ID, First name, Last name, Phone number, E-mail, Address. Fields with no value should be filled with `-` (a dash).

Example input:

    7
    Anna
    Williams
    +44 7911 123456
    anna.w@example.com
    14 Baker Street, London
    8
    James
    Cooper
    -
    james.c@gmail.com
    5 Elm Road, Manchester

## Output format (datafile_new_format)

Each contact is collapsed into one line, fields separated by `|`:

    7|Anna|Williams|+44 7911 123456|anna.w@example.com|14 Baker Street, London|
    8|James|Cooper|-|james.c@gmail.com|5 Elm Road, Manchester|

## Notes

- The program expects a file named `datafile` in the same directory. The output is written to `datafile_new_format`, also in the same directory.
- The input file must contain a multiple of 6 lines — one complete block per contact. Incomplete blocks will produce malformed output.
- This converter was written to prepare data for the Address Book application.
