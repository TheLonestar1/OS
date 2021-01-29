#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h>    //inet_addr
#include<pthread.h>

#define Buffer_size 200

volatile sig_atomic_t flag = 0;
int sockfd = 0;

void str_overwrite_stdout() {
  printf("%s", "> ");
  fflush(stdout);
}

void str_trim_lf (char* arr, int length) {
  int i;
  for (i = 0; i < length; i++) { // trim \n
    if (arr[i] == '\n') {
      arr[i] = '\0';
      break;
    }
  }
}

void catch_ctrl_c_and_exit(int sig) {
    flag = 1;
}

void SendMsg()
{
    char message[Buffer_size] = {};
    char buffer[Buffer_size] = {};

    while(1)
    {
        str_overwrite_stdout();
        fgets(message, Buffer_size, stdin);
        str_trim_lf(message, Buffer_size);

        if (strcmp(message, "exit") == 0)
                break;
        else
        {
            sprintf(buffer, "%s\n", message);
            send(sockfd, buffer, strlen(buffer), 0);
        }

        bzero(message, Buffer_size);
        bzero(buffer, Buffer_size);
    }
    catch_ctrl_c_and_exit(2);
}

void RecvMsg()
{
    char message[Buffer_size] = {0};
    while (1)
    {
        int receive = (int)recv(sockfd, message, Buffer_size, 0);
            if (receive > 0)
            {
                printf("%s", message);
                str_overwrite_stdout();
            }
            else if (receive == 0)
                    break;
            
            memset(message, 0, sizeof(message));
    }
}

int main(int argc , char *argv[])
{
    
    int socket_desc;
    struct sockaddr_in server;
    
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Не могу создать сокет");
    }
    sockfd=socket_desc;
        
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons( 8000 );

    //Connect to remote server
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("Ошибка подключения");
        return 1;
    }
    
    puts("Подключено\n");
    pthread_t recv_msg_thread;
    pthread_create(&recv_msg_thread, NULL, (void *) RecvMsg, NULL);
    pthread_t send_msg_thread;
    pthread_create(&send_msg_thread, NULL, (void *) SendMsg, NULL);

    
    while (1)
        if(flag)
        {
            printf("\nBye\n");
            break;
        }
    

    shutdown(socket_desc, SHUT_RD);
    return 0;
}
