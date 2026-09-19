#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "parser.h"
#include "html.h"

const char *keywords[] =
{
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while"
};

int keyword_count=sizeof(keywords)/ sizeof(keywords[0]);

int is_keyword(char *word)
{
    int i;

    for(i=0;i<keyword_count;i++)
    {
        if(strcmp(word,keywords[i])==0)
        {
            return 1;
        }
    }
    return 0;
}

void send_token(FILE *dest_file,enum EventType type,char *data)
{
    struct Event event;

    event.type=type;
    strcpy(event.data,data);

    write_event(dest_file, event);
}

void read_word(FILE *src_file,FILE *dest_file,int first_char)
{
    char word[500];
    int i=0;
    int ch;

    word[i++]=first_char;

    while((ch=fgetc(src_file))!=EOF)
    {
        if(isalnum(ch)||ch=='_')
        {
            word[i++]=ch;
        }
        else
        {
            ungetc(ch,src_file);
            break;
        }
    }
    word[i]='\0';

    if(is_keyword(word))
    {
        send_token(dest_file,KEYWORD,word);
    }
    else
    {
        send_token(dest_file,IDENTIFIER,word);
    }
}

void read_number(FILE *src_file,FILE *dest_file,int first_char)
{
    char number[500];
    int i=0;
    int ch;

    number[i++]=first_char;

    while((ch=fgetc(src_file))!=EOF)
    {
        if(isalnum(ch)||ch=='.'||ch=='x'||ch=='X')
        {
            number[i++]=ch;
        }
        else
        {
            ungetc(ch,src_file);
            break;
        }
    }

    number[i]='\0';

    send_token(dest_file,NUMBER,number);
}

void read_string(FILE *src_file,FILE *dest_file)
{
    char string[500];
    int i=0;
    int ch;

    string[i++]='"';

    while((ch=fgetc(src_file))!=EOF)
    {
        string[i++]=ch;

        if(ch=='\\')
        {
            ch=fgetc(src_file);

            if(ch==EOF)
            {
                break;
            }

            string[i++]=ch;
        }
        else if(ch=='"')
        {
            break;
        }
    }

    string[i]='\0';

    send_token(dest_file,STRING_CONSTANT,string);
}

void read_character(FILE *src_file,FILE *dest_file)
{
    char character[100];
    int i=0;
    int ch;

    character[i++]='\''; 

    while((ch=fgetc(src_file))!=EOF)
    {
        character[i++]=ch;

        if(ch=='\\')
        {
            ch=fgetc(src_file);

            if(ch==EOF)
            {
                break;
            }

            character[i++]=ch;
        }
        else if(ch=='\'')
        {
            break;
        }
    }

    character[i]='\0';

    send_token(dest_file,CHARACTER_CONSTANT,character);
}

void read_single_comment(FILE *src_file,FILE *dest_file)
{
    char comment[500];
    int i=0;
    int ch;

    comment[i++]='/';
    comment[i++]='/';

    while((ch=fgetc(src_file))!=EOF)
    {
        if(ch=='\n')
        {
            ungetc(ch,src_file);
            break;
        }

        comment[i++]=ch;
    }

    comment[i]='\0';

    send_token(dest_file,SINGLE_COMMENT,comment);
}

void read_multi_comment(FILE *src_file,FILE *dest_file)
{
    char comment[500];
    int i=0;
    int ch;
    int next_ch;

    comment[i++]='/';
    comment[i++]='*';

    while((ch=fgetc(src_file))!=EOF)
    {
        comment[i++]=ch;

        if(ch=='*')
        {
            next_ch=fgetc(src_file);

            if(next_ch==EOF)
            {
                break;
            }

            comment[i++]=next_ch;

            if(next_ch=='/')
            {
                break;
            }
        }
    }

    comment[i]='\0';

    send_token(dest_file,MULTI_COMMENT,comment);
}

void read_preprocessor(FILE *src_file,FILE *dest_file)
{
    char directive[500];
    int i=0;
    int ch;

    directive[i++]='#';

    while((ch=fgetc(src_file))!=EOF)
    {
        if(ch=='\n')
        {
            ungetc(ch,src_file);
            break;
        }

        directive[i++]=ch;
    }

    directive[i]='\0';

    send_token(dest_file,PREPROCESSOR,directive);
}

void read_operator(FILE *src_file,FILE *dest_file,int first_char)
{
    char operator[10];
    int i=0;
    int ch;

    operator[i++]=first_char;

    ch=fgetc(src_file);

    if((first_char=='=' && ch=='=')||
       (first_char=='!' && ch=='=')||
       (first_char=='<' && ch=='=')||
       (first_char=='>' && ch=='=')||
       (first_char=='+' && ch=='+')||
       (first_char=='-' && ch=='-')||
       (first_char=='&' && ch=='&')||
       (first_char=='|' && ch=='|')||
       (first_char=='+' &&ch=='=')||
       (first_char=='-' && ch=='=')||
       (first_char=='*' && ch=='=')||
       (first_char=='/' &&ch=='='))
    {
        operator[i++]=ch;
    }
    else
    {
        if(ch!=EOF)
        {
            ungetc(ch,src_file);
        }
    }
    operator[i]='\0';

    send_token(dest_file,OPERATOR,operator);
}

void read_normal_character(FILE *src_file,FILE *dest_file,int first_char)
{
    char normal[2];

    normal[0]=first_char;
    normal[1]='\0';

    send_token(dest_file,NORMAL_TEXT,normal);
}

void parse_file(FILE *src_file, FILE *dest_file)
{
    int ch;
    int next_ch;

    while((ch=fgetc(src_file))!=EOF)
    {
        if(isalpha(ch) || ch=='_')
        {
            read_word(src_file,dest_file,ch);
        }
        else if(isdigit(ch))
        {
            read_number(src_file, dest_file,ch);
        }
        else if(ch=='"')
        {
            read_string(src_file,dest_file);
        }
        else if(ch=='\'')
        {
            read_character(src_file,dest_file);
        }
        else if(ch=='/')
        {
            next_ch=fgetc(src_file);

            if(next_ch=='/')
            {
                read_single_comment(src_file,dest_file);
            }
            else if(next_ch== '*')
            {
                read_multi_comment(src_file,dest_file);
            }
            else
            {
                if(next_ch!=EOF)
                {
                    ungetc(next_ch, src_file);
                }

                read_operator(src_file,dest_file,ch);
            }
        }
        else if(ch== '#')
        {
            read_preprocessor(src_file, dest_file);
        }
        else if(ch=='=' || ch=='!'||ch=='<'|| ch=='>' ||
                ch=='+'|| ch=='-'|| ch=='*'|| ch=='&' ||
                ch=='|'|| ch=='%'|| ch=='^')
        {
            read_operator(src_file,dest_file,ch);
        }
        else
        {
            read_normal_character(src_file, dest_file,ch);
        }
    }
}