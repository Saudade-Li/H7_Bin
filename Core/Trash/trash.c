//
// Created by С���������� on 2022/11/5.
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
  //��ȡ���������λ��
  InitQueue(Q, Queue_Size, 0);
  DPS_GetPosition(2, Q, &dps.init_pos);
  HAL_Delay(100);//��ʱ�ȴ���ȡ���λ��
                 //  UART_printf(&huart4, "%d\r\n", dps.init_pos);
  for (int i = 0; i < 50; i++)
  {
    dps.init_angle += (float) ReadAngle();
  }
  //��ȡ��ǰ�ű���Ƕ�
  dps.init_angle /= 50;
  //��ȡ�Ƕ�ƫ�� = ��ǰ����ʼ���Ƕ�-Ŀ��Ƕ�
  dps.offset_angle = dps.init_angle - tar_init_angle;
  //  UART_printf(&huart4, "%lf,%lf\r\n", dps.init_angle, dps.offset_angle);
  //�ж�����ת���Ƿ�ת
  if (dps.offset_angle < 0.0f)
  {
    dps.init_pos += (int) (fabs(dps.offset_angle) / 90.0f * Bin_Offset * 1.0f);
  } else
  {
    dps.init_pos -= (int) (fabs(dps.offset_angle) / 90.0f * Bin_Offset * 1.0f);
  }
  DPS_SetPosition(2, dps.init_pos);
  // ��ǰ����Ͱ����Ϊ�ɻ���(���1)
  trash.curr_trash = 1;
  //��������Ͱ�ĳ�ʼλ��
  trash.curr_pos = dps.init_pos;
}
/**�趨����Ͱ
 *  1:�ɻ��գ�2���к���3�����࣬4������
 * @param trash_num
 */
void Trash_Set(void)
{
  trash.res = trash.tar_trash - trash.curr_trash;
  //��������������Ͱ
  if (abs(trash.res) == 3)
  {
    trash.res = trash.res < 0 ? trash.res + 4 : trash.res - 4;
  }
  //90��
  trash.tar_pos = trash.curr_pos + trash.res * Quarter;
  DPS_SetPosition(2, trash.tar_pos);
  //��������Ͱλ�úͱ��
  trash.curr_trash = trash.tar_trash;
  trash.curr_pos = trash.tar_pos;
}
/**
 * �����
 * ��ȡ���ʹ�ǰ�����������һ����������Ͱ��������
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