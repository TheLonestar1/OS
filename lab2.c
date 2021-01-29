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
static unsigned int total = 0;


int WtN(char * argv[]) {
	if(strncmp(argv[1],"-h",2)==0) return 1;
    else if(strncmp(argv[1],"-t",2)==0) return 2;
    else if(strncmp(argv[1],"-r",2)==0)return 3;
    else if(strncmp(argv[1],"-c",2)==0)return 4;
    else if(strncmp(argv[1],"-s",2)==0)return 5;
    else if(strncmp(argv[1],"-ls",2)==0)return 6;
    else if(strncmp(argv[1],"-pr",2)==0)return 7;
    return 0;
}


int sum(const char *fpath, const struct stat *sb, int typeflag) {
    total += sb->st_size;
    return 0;
}

int size(int argc, char **argv) {
    if (!argv[2] || access(argv[2], R_OK)) {
        return 1;
    }
    if (ftw(argv[2], &sum, 1)) {
        perror("ftw");
        return 2;
    }
    printf("%s: %u\n", argv[2], total);
    return 0;
}

int ls(int argn, char * argv[])
{
    DIR *d;
    struct dirent *dir;
    d = opendir(argv[2]);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }
    return(0);
}

void mover(int argn, char * argv[])
{
    int src_fd, dst_fd, err;
    unsigned char buffer[4096];
    char * src_path, * dst_path;

    if (argn != 4) {
        printf("Wrong argument count.\n");
        exit(1);
    }

    src_path = argv[2];
    dst_path = argv[3];

    src_fd = open(src_path, O_RDONLY);
    dst_fd = open(dst_path, O_WRONLY | O_CREAT | O_EXCL, 0666);

        err = (int)read(src_fd, buffer, 4096);
        if (err == -1) {
            printf("Error reading file.\n");
            exit(1);
        }

        err = (int)write(dst_fd, buffer, err);
        if (err == -1) {
            printf("Error writing to file.\n");
            exit(1);
        }
    remove(src_path);
}

void copy(int argn, char * argv[])
{
    int src_fd, dst_fd, err;
    unsigned char buffer[4096];
    char * src_path, * dst_path;

    if (argn != 4) {
        printf("Wrong argument count.\n");
        exit(1);
    }

    src_path = argv[2];
    dst_path = argv[3];

    src_fd = open(src_path, O_RDONLY);
    dst_fd = open(dst_path, O_WRONLY |O_CREAT, 0666);

        err = (int)read(src_fd, buffer, 4096);
        if (err == -1) {
            printf("Error reading file.\n");
            exit(1);
        }


        err = (int)write(dst_fd, buffer, err);
        if (err == -1) {
            printf("Error writing to file.\n");
            exit(1);
        }
}


int lspr(char * argv[])
{
    DIR *d;
    struct dirent *dir;
    d = opendir(argv[1]);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(atoi(dir->d_name)!=NULL){
                int pid;
                sscanf(dir->d_name, "%d", &pid);
                printf("pid = %d\n", pid);
                char filename[1000];
                sprintf(filename, "/proc/%d/stat", pid);
                FILE *f = fopen(filename, "r");
                int unused;
                char comm[1000];
                char state;
                int ppid;
                fscanf(f, "%d %s %d", &unused, comm);
                printf("comm = %s\n", comm);
                fclose(f);
            }
        }
    closedir(d);
}
return(0);
}
int main(int argn, char * argv[]) {
	int n = WtN(argv);
	switch(n){
		case 1: 
			    printf("Authors: Yuriev Yuriy,Ilya Pahomov,Ilya Karchev \n");
			    printf("Avalible arguments are: \n");
			    printf("-t to move file to another directory example:\n  -t ~/home/text.txt ~/home/documents \n");
			    printf("-r to delete file example:\n -r ~/home/text.txt \n");
			    printf("-c to copy file in present directory example:\n -c ~/home/text.txt ~/home/text1.txt \n");
			    printf("-s to watch size of directory or file  example:\n -s ~/home/text.txt \n");
			    printf("-ls to watch all files in directory  example:\n -ls ~/home/documents \n");
			    printf("-pr to watch all processes in /proc directory  example:\n -pr \n");
		        break;
		case 2: trans(argn, argv);
				break;
		case 3: remove(argv[2]);
				break;
		case 4: cpy(argn,argv);
				break;
		case 5: size(argn, argv);
				break;
		case 6: ls(argn,argv);
				break;
		case 7:	argv[1]="/proc";
                lspr(argv);
				break;			
	}
    return 0;
}
