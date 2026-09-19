#include <stdio.h>
#include "html.h"

void write_html_start(FILE *dest_file)
{
    fprintf(dest_file,"<!DOCTYPE html>\n");
    fprintf(dest_file,"<html>\n");
    fprintf(dest_file,"<head>\n");
    fprintf(dest_file,"<meta charset=\"UTF-8\">\n");
    fprintf(dest_file,"<title>Source Code</title>\n");
    fprintf(dest_file,"<link rel=\"stylesheet\" href=\"style.css\">\n");
    fprintf(dest_file,"</head>\n");
    fprintf(dest_file,"<body>\n");
    fprintf(dest_file,"<pre>\n");
}

void write_html_end(FILE *dest_file)
{
    fprintf(dest_file,"</pre>\n");
    fprintf(dest_file,"</body>\n");
    fprintf(dest_file,"</html>\n");
}

void write_data(FILE *dest_file, char *data)
{
    int i=0;

    while(data[i]!='\0')
    {
        if(data[i]=='<')
        {
            fprintf(dest_file,"&lt;");
        }
        else if(data[i]=='>')
        {
            fprintf(dest_file,"&gt;");
        }
        else if(data[i]=='&')
        {
            fprintf(dest_file,"&amp;");
        }
        else
        {
            fputc(data[i],dest_file);
        }

        i++;
    }
}

void write_event(FILE *dest_file,struct Event event)
{
    switch(event.type)
    {
        case KEYWORD:
            fprintf(dest_file,"<span class=\"keyword\">");
            write_data(dest_file,event.data);
            fprintf(dest_file,"</span>");
            break;

        case IDENTIFIER:
            fprintf(dest_file,"<span class=\"identifier\">");
            write_data(dest_file,event.data);
            fprintf(dest_file,"</span>");
            break;

        case NUMBER:
            fprintf(dest_file,"<span class=\"number\">");
            write_data(dest_file,event.data);
            fprintf(dest_file,"</span>");
            break;

        case STRING_CONSTANT:
            fprintf(dest_file,"<span class=\"string\">");
            write_data(dest_file,event.data);
            fprintf(dest_file,"</span>");
            break;

        case CHARACTER_CONSTANT:
            fprintf(dest_file,"<span class=\"character\">");
            write_data(dest_file,event.data);
            fprintf(dest_file,"</span>");
            break;

        case SINGLE_COMMENT:
            fprintf(dest_file,"<span class=\"single-comment\">");
            write_data(dest_file,event.data);
            fprintf(dest_file,"</span>");
            break;

        case MULTI_COMMENT:
            fprintf(dest_file,"<span class=\"multi-comment\">");
            write_data(dest_file,event.data);
            fprintf(dest_file,"</span>");
            break;

        case PREPROCESSOR:
            fprintf(dest_file,"<span class=\"preprocessor\">");
            write_data(dest_file,event.data);
            fprintf(dest_file,"</span>");
            break;

        case OPERATOR:
            fprintf(dest_file,"<span class=\"operator\">");
            write_data(dest_file,event.data);
            fprintf(dest_file,"</span>");
            break;

        case NORMAL_TEXT:
            write_data(dest_file,event.data);
            break;
    }
}