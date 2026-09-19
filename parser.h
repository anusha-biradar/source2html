#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>

enum EventType
{
    NORMAL_TEXT,
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    STRING_CONSTANT,
    CHARACTER_CONSTANT,
    SINGLE_COMMENT,
    MULTI_COMMENT,
    PREPROCESSOR,
    OPERATOR
};

struct Event
{
    enum EventType type;
    char data[500];
};

void parse_file(FILE *src_file,FILE *dest_file);

#endif