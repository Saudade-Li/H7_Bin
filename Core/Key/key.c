//
// Created by 小李又在摸鱼 on 2022/11/9.
//

#include "key.h"
#include "DPSDrive.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "debug.h"
#include "main.h"
#include "tle5012b.h"
#include "trash.h"
Key_t key;
extern DPS_t dps;
/**
 * 按键轮询
 */
void key_action(void)
{
  key.key1_state_last = key.key1_state;
  key.key2_state_last = key.key2_state;
  key.key3_state_last = key.key3_state;
  key.key4_state_last = key.key4_state;
  key.key1_state = key1_get;
  key.key2_state = key2_get;
  key.key3_state = key3_get;
  key.key4_state = key4_get;
  if (!key.key1_state && key.key1_state_last)
    key.key1_flag = 1;
  if (!key.key2_state && key.key2_state_last)
    key.key2_flag = 1;
  if (!key.key3_state && key.key3_state_last)
    key.key3_flag = 1;
  if (!key.key4_state && key.key4_state_last)
    key.key4_flag = 1;
  if (key.key1_flag == 1)
  {
    key.key1_flag = 0;
    dps.offset_pos += (Key_Offset + 10000);
    DPS_SetPosition(2, dps.offset_pos);
  } else if (key.key2_flag == 1)
  {
    key.key2_flag = 0;
    dps.offset_pos -= Key_Offset;
    DPS_SetPosition(2, dps.offset_pos);
  } else if (key.key3_flag == 1)
  {
    key.key3_flag = 0;
    dps.initial_flag = 1;
  } else if (key.key4_flag == 1)
  {
    key.key4_flag = 0;
    dps.initial_flag = 0;
  }
}