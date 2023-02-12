/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "main.h"
#include "task.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "DPSDrive.h"
#include "debug.h"
#include "shell.h"
#include "shell_port.h"
#include "tle5012b.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern DEBUG_t debug;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
Shell shell;
char shell_buffer[512];
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
        .name = "defaultTask",
        .stack_size = 128 * 4,
        .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for shell_log */
osThreadId_t shell_logHandle;
const osThreadAttr_t shell_log_attributes = {
        .name = "shell_log",
        .stack_size = 512 * 4,
        .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for lcd_show */
osThreadId_t lcd_showHandle;
const osThreadAttr_t lcd_show_attributes = {
        .name = "lcd_show",
        .stack_size = 128 * 4,
        .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for classify_trash */
osThreadId_t classify_trashHandle;
const osThreadAttr_t classify_trash_attributes = {
        .name = "classify_trash",
        .stack_size = 1024 * 4,
        .priority = (osPriority_t) osPriorityHigh,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void log_task(void *argument);
void lcd_task(void *argument);
void trash_task(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
__weak void configureTimerForRunTimeStats(void)
{
}

__weak unsigned long getRunTimeCounterValue(void)
{
  return 0;
}
/* USER CODE END 1 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of shell_log */
  shell_logHandle = osThreadNew(log_task, NULL, &shell_log_attributes);

  /* creation of lcd_show */
  lcd_showHandle = osThreadNew(lcd_task, NULL, &lcd_show_attributes);

  /* creation of classify_trash */
  classify_trashHandle = osThreadNew(trash_task, NULL, &classify_trash_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  osThreadExit();//退出默认线程
  /* Infinite loop */
  for (;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_log_task */
/**
* @brief Function implementing the shell_log thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_log_task */
__weak void log_task(void *argument)
{
  /* USER CODE BEGIN log_task */
  shell.write = User_Shell_Write;
  shell.read = User_Shell_Read;
  shellInit(&shell, shell_buffer, 512);
  char data;
  /* Infinite loop */
  for (;;)
  {
    if (shell.read && shell.read(&data, 1) == 1)
    {
      shellHandler(&shell, data);
    }
    osDelay(1);
  }
  /* USER CODE END log_task */
}

/* USER CODE BEGIN Header_lcd_task */
/**
* @brief Function implementing the lcd_show thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_lcd_task */
__weak void lcd_task(void *argument)
{
  /* USER CODE BEGIN lcd_task */

  /* Infinite loop */
  for (;;)
  {
    osDelay(1);
  }
  /* USER CODE END lcd_task */
}

/* USER CODE BEGIN Header_trash_task */
/**
* @brief Function implementing the classify_trash thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_trash_task */
__weak void trash_task(void *argument)
{
  /* USER CODE BEGIN trash_task */
  /* Infinite loop */
  for (;;)
  {
    osDelay(1);
  }
  /* USER CODE END trash_task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
