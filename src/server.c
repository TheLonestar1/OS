#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h>    //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread
#include"lab4.h"
#include"lab3.h"
#include"rem.h"

void *connection_handler(void *);


int main(int argc , char *argv[])
{
    int socket_desc , new_socket , c , *new_sock;
    struct sockaddr_in server , client;
    char *message;
    
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Не смог сделать сокет");
    }
    
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons( 8000 );
    
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("Не настроилось");
        return 1;
    }
    puts("Связь есть!");
    
    //Listen
    listen(socket_desc , 3);
    
    //Accept and incoming connection
    puts("Ждем присоединения...");
    c = sizeof(struct sockaddr_in);
    while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Соединение принято");
        
        //Reply to the client
        message = "Здравствуйте , я принял ваше соединение и сейчас передам управление\n";
        write(new_socket , message , strlen(message));
        
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = new_socket;
        
        if( pthread_create( &sniffer_thread , NULL ,  connection_handler , (void*) new_sock) < 0)
        {
            perror("Не создал поток");
            return 1;
        }
    
        puts("управление передано");
    }
    
    if (new_socket<0)
    {
        perror("Соединение не удалось");
        return 1;
    }
    
    return 0;
}

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
    int sock = *(int*)socket_desc;
    long read_size;
    char *message , client_message[2000];
    //char *buffer=NULL;
    
    message = "Здравствуйте!\n -t для переноса файла в другую директорию \n -r для удаления файла\n -c для создания копии файла \n -s для измерения размера директории или файла \n -ls для вывода всего содержимого директории \n -pr для вывода запущенных процессов из директории /proc \nЧто вы хотите сделать?\n";
    write(sock , message , strlen(message));
    while(1){
    read_size=recv(sock , client_message , 2000 , 0);
        //Send the message back to client
        message=NULL;
        removeEndLine(client_message);
        if ((client_message[0])!='\0')
        {
            if (strcmp(client_message,"-h")==0)
            {
                message=helpclient();
            }
            else message=choise(client_message);
            write(sock , message , strlen(message));
        }
        
    
    if(read_size == 0)
    {
        puts("Клиент отсоединился");
        fflush(stdout);
    }
    else if(read_size == -1)
    {
        perror("Не получил");
    }
    }

    
    return 0;
}
