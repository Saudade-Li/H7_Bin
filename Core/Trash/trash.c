//
// Created by 小李又在摸鱼 on 2022/11/5.
//

#include "trash.h"
#include "DPSDrive.h"
#include "debug.h"
#include "stdio.h"
#include "tle5012b.h"
#include "usart.h"
#include <stdlib.h>
extern DPS_t dps;
extern RingQueue Q[Queue_Size];
Trash_t trash;
void Trash_Init(void)
{
  //获取电机编码器位置
  InitQueue(Q, Queue_Size, 0);
  DPS_GetPosition(2, Q, &dps.init_pos);
  HAL_Delay(100);//延时等待获取电机位置
                 //  UART_printf(&huart4, "%d\r\n", dps.init_pos);
  for (int i = 0; i < 50; i++)
  {
    dps.init_angle += (float) ReadAngle();
  }
  dps.init_angle /= 50;
  dps.offset_angle = dps.init_angle - tle_init_pos;
  //  UART_printf(&huart4, "%lf,%lf\r\n", dps.init_angle, dps.offset_angle);
  if (dps.offset_angle < 0.0f)
  {
    dps.init_pos += (int) (fabs(dps.offset_angle) / 90.0f * Bin_Offset * 1.0f);
  } else
  {
    dps.init_pos -= (int) (fabs(dps.offset_angle) / 90.0f * Bin_Offset * 1.0f);
  }
  DPS_SetPosition(2, dps.init_pos);
  // 当前垃圾桶设置为可回收(编号1)
  trash.curr_trash = 1;
  //更新垃圾桶的初始位置
  trash.curr_pos = dps.init_pos;
}
/**设定垃圾桶
 *  1:可回收，2：有害，3：厨余，4：其他
 * @param trash_num
 */
void Trash_Set(void)
{
  trash.res = trash.tar_trash - trash.curr_trash;
  //相差大于两个垃圾桶
  if (abs(trash.res) == 3)
  {
    trash.res = trash.res < 0 ? trash.res + 4 : trash.res - 4;
  }
  //90度
  trash.tar_pos = trash.curr_pos + trash.res * Quarter;
  DPS_SetPosition(2, trash.tar_pos);
  //更新垃圾桶位置和编号
  trash.curr_trash = trash.tar_trash;
  trash.curr_pos = trash.tar_pos;
}
/**
 * 多分类
 * 获取传送带前面的垃圾（第一个进入垃圾桶的垃圾）
 * TODO:接收的数据需要现场调试，还未调试 date：2023/2/4
 * @param trash_a
 * @param trash_b
 * @param Y1
 * @param Y2
 * @return
 */
int Trash_Get(uint8_t trash_a, uint8_t trash_b, int X1, int X2)
{
  if (X1 > X2)
  {
    return (int) (trash_a - 'A' + 1);
  } else
    return (int) (trash_b - 'A' + 1);
}