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
    return  "Avalible arguments are: \n-t to transfer file to another directory example:\n  -t /Users/wazovski/Desktop/distant/oss/test.txt /Users/wazovski/Desktop/distant/tes/test.txt \n-r to delete file example:\n -r /Users/wazovski/Desktop/distant/oss/test2.txt \n-c to copy file in present directory example:\n -c /Users/wazovski/Desktop/distant/oss/test1.txt /Users/wazovski/Desktop/distant/oss/test2.txt \n-s to see size of directory or file  example:\n -s /Users/wazovski/Desktop/distant/oss/test1.txt \n-ls to see all files in directory  example:\n -ls /Users/wazovski/Desktop/distant/oss \n-pr to see all processes in /proc directory  example:\n -pr \n";
}
