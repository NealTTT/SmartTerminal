/**
 * @file main.c
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
#include <errno.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/wait.h>

#include "task/checktime/task_checktime.h"

#define TASK_NAME           "Main"     

int main(int argc, char *argv[])
{
    int                 ret = 0;
    pthread_t           thread_checktime;
    void                *res;

    ret = pthread_create(&thread_checktime, NULL, Task_CheckTime, NULL);
    if(ret != 0)
    {
        perror("Main:Create the check time thread error!\r\n");
        exit(-EAGAIN);
    }

    printf("%s: Create the check time thread success!\r\n", TASK_NAME);

    ret = pthread_join(thread_checktime, &res);
    if(ret != 0)
    {
        perror("Main:Join the check time thread error!\r\n");
        exit(-EAGAIN);
    }

    printf("%s: Check time thread run success - %d!\r\n", TASK_NAME, (long)res);

    exit(0);
}