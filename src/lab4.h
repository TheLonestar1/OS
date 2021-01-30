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
			    printf("Authors: Yuriev Yuriy,Ilya Pahomov,Ilya Karchev \n");
			    printf("Avalible arguments are: \n");
			    printf("-t to transfer file to another directory example:\n  -t ~/home/text.txt ~/home/documents \n");
			    printf("-r to mover file example:\n -r ~/home/text.txt \n");
			    printf("-c to copy file in present directory example:\n -c ~/home/text.txt ~/home/text1.txt \n");
			    printf("-s to watch size of directory or file  example:\n -s ~/home/text.txt \n");
			    printf("-ls to watch all files in directory  example:\n -ls ~/home/documents \n");
			    printf("-pr to watch all processes in /proc directory  example:\n -pr \n");
        }
        else if(strncmp(argv[1],"-t",4)==0)
        {
            message=mover(argn, argv);
        }
        else if(strncmp(argv[1],"-r",4)==0)
        {
            remove(argv[2]);
            message="removed";
        }
        else if(strncmp(argv[1],"-c",4)==0)
        {
            message=copy(argn,argv);
        }
        else if(strncmp(argv[1],"-s",4)==0)
        {
            sprintf(message, "%d", size(argn, argv));;
          //  message=sizehelp();
        }
        else if(strncmp(argv[1],"-ls",4)==0)
        {
            message=ls(argn,argv);
        }
        else if(strncmp(argv[1],"-pr",4)==0)
        {
            argv[1]="/proc";
            message=lspr(argv);
        }
        else if (strncmp(argv[1],"-ch",4)==0)
        {
            message=pchild();
        }
        else if (strncmp(argv[1],"-chbg",4)==0)
        {
            message=pchildbg();
        }
    return message;
}



#endif /* Header_h */
