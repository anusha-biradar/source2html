#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "html.h"

int main(int argc,char *argv[])
{
    FILE *src_file;
    FILE *dest_file;
    char dest_name[500];

    if(argc!=2)
    {
        printf("Usage: ./s2html <src_file.c>\n");
        return 1;
    }

    src_file=fopen(argv[1],"r");

    if(src_file==NULL)
    {
        printf("Unable to open source file\n");
        return 1;
    }

    strcpy(dest_name,argv[1]);
    strcat(dest_name,".html");

    dest_file=fopen(dest_name,"w");

    if(dest_file==NULL)
    {
        printf("Unable to create HTML file\n");
        fclose(src_file);
        return 1;
    }

    write_html_start(dest_file);
    parse_file(src_file,dest_file);
    write_html_end(dest_file);

    fclose(src_file);
    fclose(dest_file);

    printf("HTML file created successfully: %s\n",dest_name);

    return 0;
}