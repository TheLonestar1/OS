#ifndef lab4_h
#define lab4_h

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <sys/sysctl.h>
#include <dirent.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include "lab3.h"

//void removeEndLine(char* client_message)
//{
//    int i=0;
//    while((client_message[i])!='\n')
//    {
//        i++;
//    }
//    client_message[i] = '\0';
//}

char *choise(char* client_message){
    
        //char* message=NULL;
        char *message = malloc(100 * sizeof(char));
        char **options = (char**) malloc(6*sizeof(char*));
        int i;
        for(i=0;i<6;i++){
            options[i] = (char*) malloc(100*sizeof(char));
        }

        int argn=1;
            char sep [10]=" ";
           char *buff;
           buff = strtok (client_message,sep);

           while (buff != NULL)
           {
              printf ("%s\n",buff);
               options[argn]=buff;
              buff = strtok (NULL,sep);
               
               argn++;
           }
        char **argv = (char**) malloc(argn*sizeof(char*));

        for(i=0;i<argn;i++){
            argv[i] = (char*) malloc(100*sizeof(char));
        }
        for(i=0;i<argn;i++){
            argv[i] = options[i];
        }
        
         if(strncmp(argv[1],"-h",2)==0)
        {
            printf("Copyright reserved by Nizamova Veronika\n");
            printf("Avalible arguments are: \n");
            printf("-t to transfer file to another directory example:\n  -t /Users/wazovski/Desktop/distant/oss/test.txt /Users/wazovski/Desktop/distant/tes/test.txt \n");
            printf("-r to delete file example:\n -r /Users/wazovski/Desktop/distant/oss/test2.txt \n");
            printf("-c to copy file in present directory example:\n -c /Users/wazovski/Desktop/distant/oss/test1.txt /Users/wazovski/Desktop/distant/oss/test2.txt \n");
            printf("-s to see size of directory or file  example:\n -s /Users/wazovski/Desktop/distant/oss/test1.txt \n");
            printf("-ls to see all files in directory  example:\n -ls /Users/wazovski/Desktop/distant/oss \n");
            printf("-pr to see all processes in /proc directory  example:\n -pr \n");
        }
        else if(strncmp(argv[1],"-t",2)==0)
        {
            message=trans(argn, argv);
        }
        else if(strncmp(argv[1],"-r",2)==0)
        {
            remove(argv[2]);
            message="removed";
        }
        else if(strncmp(argv[1],"-c",3)==0)
        {
            message=cpy(argn,argv);
        }
        else if(strncmp(argv[1],"-s",2)==0)
        {
            sprintf(message, "%d", size(argn, argv));;
          //  message=sizehelp();
        }
        else if(strncmp(argv[1],"-ls",2)==0)
        {
            message=ls(argn,argv);
        }
        else if(strncmp(argv[1],"-pr",2)==0)
        {
            argv[1]="/proc";
            message=lspr(argv);
        }
        else if (strncmp(argv[1],"-ch",2)==0)
        {
            message=ch();
        }
        else if (strncmp(argv[1],"-chbg",4)==0)
        {
            message=chbg();
        }
    return message;
}



#endif /* Header_h */
