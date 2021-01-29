#include "lab3.h"
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

int WtN(char * argv[]);
int main(){
    while(1){
        
        char **options = (char**) malloc(6*sizeof(char*));
        int i;
        for(i=0;i<6;i++){
            options[i] = (char*) malloc(100*sizeof(char));
        }

        int argn=1;

        printf("%s\n", "insert your options. e.g.: -h ok");
        printf("%s\n", "if finished press [ok]");

        scanf("%s",options[argn]);
        while (strcmp(options[argn],"ok")!=0){
            argn++;
            scanf("%s",options[argn]);
        }

        char **argv = (char**) malloc(argn*sizeof(char*));

        for(i=0;i<argn;i++){
            argv[i] = (char*) malloc(100*sizeof(char));
        }
        for(i=0;i<argn;i++){
            argv[i] = options[i];
        }
        int n = WtN(argv);
		switch(n){
			case 0: printf("Wrong argumet");
				break;
			case 1: 
			    printf("Authors: Yuriev Yuriy,Ilya Pahomov,Ilya Karchev \n");
			    printf("Avalible arguments are: \n");
			    printf("-t to transfer file to another directory example:\n  -t ~/home/text.txt ~/home/documents \n");
			    printf("-r to mover file example:\n -r ~/home/text.txt \n");
			    printf("-c to copy file in present directory example:\n -c ~/home/text.txt ~/home/text1.txt \n");
			    printf("-s to watch size of directory or file  example:\n -s ~/home/text.txt \n");
			    printf("-ls to watch all files in directory  example:\n -ls ~/home/documents \n");
			    printf("-pr to watch all processes in /proc directory  example:\n -pr \n");
			        break;
			case 2: mover(argn, argv);
					break;
			case 3: remove(argv[2]);
					break;
			case 4: copy(argn,argv);
					break;
			case 5: size(argn, argv);
					break;
			case 6: ls(argn,argv);
					break;
			case 7:	argv[1]="/proc";
	                lspr(argv);
					break;
			case 8: pchild();
					break;
			case 9:	pchildbg();
					break;		
		}
    }
}
