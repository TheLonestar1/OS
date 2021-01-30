#ifndef lab3_h
#define lab3_h

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
#include <ftw.h>
static unsigned int total = 0;
char* pchilde (char *argv[]);

int WtN(char * argv[]) {
    if(strncmp(argv[1],"-h",2)==0) return 1;
    else if(strncmp(argv[1],"-t",6)==0) return 2;
    else if(strncmp(argv[1],"-r",6)==0)return 3;
    else if(strncmp(argv[1],"-c",6)==0)return 4;
    else if(strncmp(argv[1],"-s",6)==0)return 5;
    else if(strncmp(argv[1],"-ls",6)==0)return 6;
    else if(strncmp(argv[1],"-pr",6)==0)return 7;
    else if(strncmp(argv[1],"-pchild",6)==0)return 8;
    else if(strncmp(argv[1],"-pchildbg",6)==0)return 9;	
    return 0;
}


void signalHandler(int signal)
{
    printf("Cought signal %d!\n",signal);
    if (signal==SIGCHLD) {
        printf("Child ended\n");
        wait(NULL);
    }
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
    return total;
}
char *ls(int argn, char * argv[])
{
    DIR *d;
    struct dirent *dir;
    char *buffer;
    //char lsOutput[300];
    char *lsOutput = malloc(300 * sizeof(char));
//    lsOutput[0]=" ";
    d = opendir(argv[2]);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
            buffer=dir->d_name;
            strcat(lsOutput, buffer);
            strcat(lsOutput, " ");
        }
        closedir(d);
    }
    return lsOutput;
}

char *mover(int argn, char * argv[])
{
    int src_fd, dst_fd, err;
    unsigned char buffer[4096];
    //char output[300];
    char *transOutput = malloc(300 * sizeof(char));
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
    strcat(transOutput, "transfered");
    return transOutput;
}

char *copy(int argn, char * argv[])
{
    int src_fd, dst_fd, err;
    unsigned char buffer[4096];
    //char output[300];
    char *copyOutput = malloc(300 * sizeof(char));
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
    strcat(copyOutput, "copied");
    return copyOutput;
}
char *pchild()
{
    //char output[300];
    char *chOutput = malloc(300 * sizeof(char));
    char *message;
    message=pchilde('-h');
    strcat(chOutput, message);
    return chOutput;
}
char* pchilde (char *argv[])
{
    pid_t pid;
    int rv=0,status;
    char  *buffer;
    //char output[300];
    char *cheOutput = malloc(300 * sizeof(char));
    switch(pid=fork()){
        case -1:
            perror("fork"); /* произошла ошибка */
            buffer="err";
            strcat(cheOutput, buffer);
            exit(1); /*выход из родительского процесса*/
        case 0:
            printf(" CHILD: Мой PID — %d\n", getpid());
            buffer="CHILD: Мой PID";
            strcat(cheOutput, buffer);
            sprintf(cheOutput, "%d", getpid());
            //strcat(cheOutput, itoa(getpid()));
            buffer="CHILD: Выход";
            strcat(cheOutput, buffer);
            printf(" CHILD: Выход!\n");
            exit(rv);
        default:
            printf("PARENT: Это процесс-родитель!\n");
            buffer="PARENT: Это процесс-родитель!";
            strcat(cheOutput, buffer);
            signal(SIGCHLD,signalHandler);
            wait(&status);
            WEXITSTATUS(rv);
            printf("PARENT: Выход!\n");
    }
    return cheOutput;
}
char* pchildbg()
{
    char  *buffer;
    //char output[300];
    char *chbgOutput = malloc(300 * sizeof(char));
//    FILE *fp= NULL;
        pid_t process_id = 0;
        pid_t sid = 0;
        process_id = fork();
        if (process_id < 0)
        {
            buffer="fork failed";
            strcat(chbgOutput, buffer);
            printf("fork failed!\n");
            exit(1);
        }
        if (process_id > 0)
        {
            buffer="pid of child proc";
            strcat(chbgOutput, buffer);
            //strcat(chbgOutput, (char)process_id);
            sprintf(chbgOutput, "%d", process_id);
            printf("pid of child proc %d \n", process_id);
            
            exit(0);
        }
        umask(0);
        sid = setsid();
        if(sid < 0)
        {
            exit(1);
        }
        chdir("/");
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
    return chbgOutput;
}

char *lspr(char * argv[])
{
    DIR *d;
    struct dirent *dir;
    char  *buffer;
    //char output[300];
    char *lsprOutput = malloc(300 * sizeof(char));
    d = opendir(argv[1]);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(atoi(dir->d_name)!=0){
                int pid;
                sscanf(dir->d_name, "%d", &pid);
                printf("pid = %d\n", pid);
                buffer="pid=";
                strcat(lsprOutput, buffer);
                //strcat(lsprOutput, (char)pid);
                sprintf(lsprOutput, "%d", pid);
                char filename[1000];
                sprintf(filename, "/proc/%d/stat", pid);
                FILE *f = fopen(filename, "r");
                int unused;
                char comm[1000];
                fscanf(f, "%d %s", &unused, comm);
                printf("comm = %s\n", comm);
                buffer="comm=";
                strcat(lsprOutput, buffer);
                strcat(lsprOutput, comm);
                fclose(f);
            }
        }
    closedir(d);
    }
    else {
        buffer="err";
        strcat(lsprOutput, buffer);}
    return lsprOutput;
}



#endif 
