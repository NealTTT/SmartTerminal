/**
 * @file task_checktime.c
 * @brief 
 * @author Neal (tangpingyong@gmail.com)
 * @version 1.0
 * @date 2021-06-06
 * 
 * @copyright Copyright (c) 2021  Neal Personal
 * 
 * @par Log:
 * Date         Version     Author  Description
 * 2021-06-06     1.0       Neal    Draft
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/wait.h>

#define TASK_NAME       "Task-CheckTime"
#define PORT            80
#define HOST            "quan.suning.com"
#define IP              "115.238.242.42"

void *Task_CheckTime(void *arg)
{
    int                     fd_socket_CheckTime, ret = 0, len_read = 0;
    unsigned int            i;
    struct sockaddr_in      addr_server;
    char                    buff_send[100], buff_read[4096], cmd_checktime[50];
    char                    *ptr;
    fd_set                  fd_set_read;    
    //struct timeval          read_tv;


    if((fd_socket_CheckTime = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Task-CheckTime:Socket open fail!\r\n");
        pthread_exit("Socket open fail");
    }

    bzero(&addr_server, sizeof(addr_server));
    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(PORT);
    if((inet_pton(AF_INET, IP, &addr_server.sin_addr)) <= 0)
    {
        perror("Task-CheckTime:inet_pton error!\r\n");
        pthread_exit("inet_pton error");
    }

    if((connect(fd_socket_CheckTime, (struct sockaddr *)&addr_server, sizeof(addr_server))) < 0)
    {
        perror("Task-CheckTime:Socket connect error!\r\n");
        close(fd_socket_CheckTime);
        pthread_exit("Socket connect error");
    }

    printf("%s:Check time socket connect OK!\r\n", TASK_NAME);

    memset(buff_send, 0, 100);
    strcat(buff_send, "GET /getSysTime.do HTTP/1.1\r\n");
    strcat(buff_send, "Host: quan.suning.com\r\n");
    strcat(buff_send, "\r\n\r\n");

    FD_ZERO(&fd_set_read);
    FD_SET(fd_socket_CheckTime, &fd_set_read);

    while(1)
    {
        ret = send(fd_socket_CheckTime, buff_send, strlen(buff_send), 0);
        if(ret < 0)
        {
            perror("Task-CheckTime:Socket send data error!\r\n");
            close(fd_socket_CheckTime);
            pthread_exit("Socket send data error");
        }

        ret = 0;
        ret = select(fd_socket_CheckTime + 1, &fd_set_read, NULL, NULL, NULL);

        if(ret < 0)
        {
            perror("Task-CheckTime:Socket select error!\r\n");
            close(fd_socket_CheckTime);
            pthread_exit("Socket select error");
        }

        if(ret > 0)
        {
            memset(buff_read, 0, sizeof(buff_read));
            len_read = read(fd_socket_CheckTime, buff_read, 4096);
            if(len_read == 0)
            {
                perror("Task-CheckTime:Socket read error!\r\n");
                close(fd_socket_CheckTime);
                pthread_exit("Socket read error");
            }

            printf("%s:Socket read data %s!\r\n", TASK_NAME, buff_read);

            if(ptr = strstr(buff_read, "sysTime2"))
            {
                memset(cmd_checktime, 0, sizeof(cmd_checktime));
                strcat(cmd_checktime, "date -s ");
                for(i = 0; i < 21; i++)
                {
                    cmd_checktime[8 + i] = *(ptr + 10 + i);
                }
                printf("Cmd is %s\r\n", cmd_checktime);
                system(cmd_checktime);
            }
        }

        sleep(60);
    }
    close(fd_socket_CheckTime);
    pthread_exit(0);
}





