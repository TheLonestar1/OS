#include "rem.h"

void removeEndLine(char* client_message)
{
    int i=0;
    while((client_message[i])!='\n')
    {
        i++;
    }
    client_message[i] = '\0';
}

char* helpclient()
{
    return  "Avalible arguments are: \n-t to transfer file to another directory example:\n  -t ~/home/text.txt ~/home/documents \n-r to delete file example:\n -r ~/home/text.txt \n-c to copy file in present directory example:\n -c ~/home/text.txt ~/home/text.txt1 \n-s to see size of directory or file  example:\n -s ~/home/text.txt \n-ls to see all files in directory  example:\n -ls ~/home/documents \n-pr to see all processes in /proc directory  example:\n -pr \n";
}
