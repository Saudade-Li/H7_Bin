//
// Created by 小李又在摸鱼 on 2022/9/12.
//


#include "shell_port.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "portable.h"
#include "semphr.h"
#include "shell.h"
#include "stm32h7xx_hal.h"
#include "usart.h"

//static SemaphoreHandle_t shellMutex;
/* 2. 自己实现shell写函数 */

//shell写函数原型：typedef void (*shellWrite)(const char);
short User_Shell_Write(char *data, unsigned short len)
{
  HAL_UART_Transmit(&huart4, (uint8_t *) data, len, 0x1ff);

  return len;
}

/**
 * @brief 用户shell读
 *
 *
 * @param data 数据
 * @param len 数据长度
 *
 * @return short 实际读取到
 */
short User_Shell_Read(char *data, unsigned short len)
{
  if (HAL_UART_Receive(&huart4, (uint8_t *) data, len, 0xFFFF) != HAL_OK)
  {
    return 0;
  } else
  {
    return 1;
  }
}
/**
 * 用户shell上锁
 * @param shell
 * @return
 */
int User_Shell_Lock(Shell *shell)
{
  //  xSemaphoreTake(shellMutex, portMAX_DELAY);
  return 0;
}
/**
 *
 * @param shell
 * @return
 */
int User_Shell_Unlock(Shell *shell)
{
  //  xSemaphoreGive(shellMutex);
  return 0;
}

/* 3. 编写初始化函数 */
