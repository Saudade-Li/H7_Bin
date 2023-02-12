//
// Created by 小李又在摸鱼 on 2022/11/9.
//

#ifndef H7_BIN_V1_0_KEY_H
#define H7_BIN_V1_0_KEY_H
#define key1_set HAL_GPIO_WritePin(KEY_1_GPIO_Port, KEY_1_Pin, GPIO_PIN_SET)
#define key1_get HAL_GPIO_ReadPin(KEY_1_GPIO_Port, KEY_1_Pin)
#define key2_set HAL_GPIO_WritePin(KEY_2_GPIO_Port, KEY_2_Pin, GPIO_PIN_SET)
#define key2_get HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin)
#define key3_set HAL_GPIO_WritePin(KEY_3_GPIO_Port, KEY_3_Pin, GPIO_PIN_SET)
#define key3_get HAL_GPIO_ReadPin(KEY_3_GPIO_Port, KEY_3_Pin)
#define key4_set HAL_GPIO_WritePin(KEY_4_GPIO_Port, KEY_4_Pin, GPIO_PIN_SET)
#define key4_get HAL_GPIO_ReadPin(KEY_4_GPIO_Port, KEY_4_Pin)
#include "stdio.h"
typedef struct
{
  uint8_t key1_state_last;
  uint8_t key1_state;
  uint8_t key2_state_last;
  uint8_t key2_state;
  uint8_t key3_state_last;
  uint8_t key3_state;
  uint8_t key4_state_last;
  uint8_t key4_state;
  uint8_t key1_flag, key2_flag, key3_flag, key4_flag;
} Key_t;
void key_action(void);
#endif//H7_BIN_V1_0_KEY_H
