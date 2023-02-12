//
// Created by 小李又在摸鱼 on 2022/10/12.
//

#ifndef H7_BIN_V1_0_DEBUG_H
#define H7_BIN_V1_0_DEBUG_H
#include "stdarg.h"
#include "stdio.h"
#include "usart.h"
typedef struct
{
  uint16_t DPS_mode;
  uint16_t AS5048_flag;
  uint16_t current_flag;
} DEBUG_t;
int UART_printf(UART_HandleTypeDef *huart, const char *fmt, ...);
#endif// H7_BIN_V1_0_DEBUG_H
