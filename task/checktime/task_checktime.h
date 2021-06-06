/**
 * @file task_checktime.h
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
#ifndef _TASK_TERMINAL_
#define _TASK_TERMINAL_

/**
 * @brief Create the task to calibrate the systime by http
 * @return int Result
 */
extern void *Task_CheckTime(void *arg);

#endif //_TASK_TERMINAL_