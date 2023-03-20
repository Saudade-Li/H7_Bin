//
// Created by 小李又在摸鱼 on 2022/10/29.
//


#include "DPSDrive.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "debug.h"
#include "key.h"
#include "main.h"
#include "shell_port.h"
#include "string.h"
#include "tle5012b.h"
#include "trash.h"
extern RingQueue Q[Queue_Size];
extern DPS_t dps;
extern DEBUG_t debug;

void trash_task(void *argument)
{
  Trash_Init();
  for (;;)
  {
    key_action();
    //    dps.init_angle = ReadAngle();
    //    UART_printf(&huart5, "%lf\r\n", dps.init_angle);
    osDelay(1);
  }
}