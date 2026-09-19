#ifndef HTML_H
#define HTML_H

#include <stdio.h>
#include "parser.h"

void write_html_start(FILE *dest_file);
void write_html_end(FILE *dest_file);
void write_escaped(FILE *dest_file,char *data);
void write_event(FILE *dest_file,struct Event event);

#endif