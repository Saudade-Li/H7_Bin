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
  //获取当前磁编码角度
  dps.init_angle /= 50;
  //获取角度偏差 = 当前（初始）角度-目标角度
  dps.offset_angle = dps.init_angle - tar_init_angle;
  //  UART_printf(&huart4, "%lf,%lf\r\n", dps.init_angle, dps.offset_angle);
  //判断是正转还是反转
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
 * TODO:多分类
 * 获取传送带前面的垃圾（第一个进入垃圾桶的垃圾）
 * @param trash_a
 * @param trash_b
 * @param Y1
 * @param Y2
 * @return
 */
int Multi_Trash_Get(uint8_t trash_a, uint8_t trash_b, int X1, int X2)
{
  if (X1 > X2)
  {
    return (int) (trash_a - 'A' + 1);
  } else
    return (int) (trash_b - 'A' + 1);
}
/**
 * 数据接收滤波
 * @param rx_buff
 * @return
 */
int Trash_Decision(uint8_t rx_buff)
{
  trash.count++;
  if (rx_buff == 'A')
    trash.count_a++;
  if (rx_buff == 'B')
    trash.count_b++;
  if (rx_buff == 'C')
    trash.count_c++;
  if (rx_buff == 'D')
    trash.count_d++;
  //检测5次接收到的数据
  if (trash.count == 5)
  {
    if (trash.count_a >= trash.count_b)
      trash.count_max = trash.count_a;
    else if (trash.count_c >= trash.count_max)
      trash.count_max = trash.count_c;
    else if (trash.count_d >= trash.count_max)
      trash.count_max = trash.count_d;
    //可回收
    if (trash.count_max == trash.count_a)
      return 1;
    //有害
    else if (trash.count_max == trash.count_b)
      return 2;
    //厨余
    else if (trash.count_max == trash.count_c)
      return 3;
    //其他
    else if (trash.count_max == trash.count_d)
      return 4;
    //重新准备计数
    trash.count = 0;
  } else
    return 0;
}
