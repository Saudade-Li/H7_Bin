//
// Created by 小李又在摸鱼 on 2022/10/12.
//

#include "debug.h"
#include "shell.h"
#include "shell_port.h"
DEBUG_t debug;
/**
 * 串口重定向
 * @param huart
 * @param fmt
 * @param ...
 * @return
 */
int UART_printf(UART_HandleTypeDef *huart, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  int length;
  char buffer[512];
  length = vsnprintf(buffer, 512, fmt, ap);
  HAL_UART_Transmit(huart, (uint8_t *) buffer, length, HAL_MAX_DELAY);
  va_end(ap);
  return length;
}

void DPS_MODE(uint16_t type)
{
  if (type == 1)
  {
    //    UART_printf(&huart4, "mode || close current");
    debug.DPS_mode = 1;
  } else if (type == 2)
  {
    //    UART_printf(&huart4, "mode || close angle\r\n");
    debug.DPS_mode = 2;
  } else if (type == 3)
  {
    //    UART_printf(&huart4, "mode || close angle\r\n");
    debug.DPS_mode = 3;
  } else if (type == 4)
  {
    //    UART_printf(&huart4, "mode || close angle\r\n");
    debug.DPS_mode = 4;
  }
}
SHELL_EXPORT_CMD(SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), DPS_debug_mode, DPS_MODE, 1 --++2 -- --);
//SHELL_EXPORT_CMD(SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), Trash_set_pos, Trash_Set, 1->R 2->o 3->H 4->F);