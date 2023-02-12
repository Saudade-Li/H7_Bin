#include "DPSDrive.h"
#include "debug.h"
#include "malloc.h"
#include "shell.h"
#include "shell_port.h"
#include "stdio.h"
#include "tle5012b.h"
#define UART_ENABLE_RE(USARTx) USARTx->Instance->CR1 |= (uint32_t) 0x0004
#define UART_DISABLE_RE(USARTx) USARTx->Instance->CR1 &= (~(uint32_t) 0x0004)
RingQueue Q[Queue_Size];
DPS_t dps;
//传送带
DPS_t motor_1 = {
        .huart = &huart2,
};
//旋转垃圾桶
DPS_t motor_2 = {
        .huart = &huart3,
};

void InitQueue(RingQueue *ring_queue, uint8_t init_size, uint8_t *base)
{//循环队列初始化
  ring_queue->base = base;
  ring_queue->front = ring_queue->rear = 0;
  ring_queue->size = init_size;
}

uint8_t InsQueue(RingQueue *ring_queue, uint8_t p)
{//循环队列入队
  if ((ring_queue->rear + 1) % ring_queue->size == ring_queue->front)
  {//队列满
    ring_queue->base[ring_queue->rear] = p;
    ring_queue->rear = (ring_queue->rear + 1) % ring_queue->size;
    ring_queue->front = (ring_queue->front + 1) % ring_queue->size;
  } else
  {
    ring_queue->base[ring_queue->rear] = p;
    ring_queue->rear = (ring_queue->rear + 1) % ring_queue->size;
  }
  return 1;
}
uint8_t QueueGet(RingQueue *ring_queue, uint8_t index)
{
  return ring_queue->base[(ring_queue->front + index) % ring_queue->size];
}


/*
以上对循环队列略作修改,实现了长度可自己定义的滑动窗口,使用QueueGet()函数即可获取窗口内的任意位置数据,注意循环队列判满条件,所以实际数组需要定义多一个
效果如下
base:1,2,3,0,0,0,0,0,0,0
ins: 4
base:1,2,3,4,0,0,0,0,0,0
ins: 5
base:1,2,3,4,5,0,0,0,0,0
ins: 6
base:1,2,3,4,5,6,0,0,0,0
ins: 7
base:1,2,3,4,5,6,7,0,0,0
ins: 8
base:1,2,3,4,5,6,7,8,0,0
ins: 9
base:1,2,3,4,5,6,7,8,9,0
ins: 10
base:2,3,4,5,6,7,8,9,10,1
ins: 11
base:3,4,5,6,7,8,9,10,11,2
ins: 12
base:4,5,6,7,8,9,10,11,12,3
ins: 13
base:5,6,7,8,9,10,11,12,13,4
ins: 14
base:6,7,8,9,10,11,12,13,14,5
ins: 15
base:7,8,9,10,11,12,13,14,15,6
ins: 16
base:8,9,10,11,12,13,14,15,16,7
ins: 17
base:9,10,11,12,13,14,15,16,17,8
以上是解析DPS返回数据的基础
*/


#define crc 0xa001
//                   设备号 功能码  起始地址16 数据数量16 字节数 数据 CRC
uint8_t posFrame[13] = {0x01, 0x10, 0x00, 0x50, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t velFrame[13] = {0x01, 0x10, 0x00, 0x52, 0x00, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t curFrame[8] = {0x01, 0x06, 0x00, 0x54, 0x00, 0x00, 0x00, 0x00};
uint8_t GET_POS[8] = {0x01, 0x04, 0x00, 0x50, 0x00, 0x02, 0x71, 0xDA};
uint8_t GET_ALL[8] = {0x01, 0x04, 0x00, 0x50, 0x00, 0x06, 0x70, 0x19};


void DPS_Transmit(uint8_t DPSnum, uint8_t ch)
{
  switch (DPSnum) {
    case 1: {
      HAL_UART_Transmit(motor_1.huart, &ch, 1, 0xff);
    } break;
    case 2: {
      HAL_UART_Transmit(motor_2.huart, &ch, 1, 0xff);
    } break;
  }
}
void DPS_Receive(uint8_t DPSnum, uint8_t *ch)
{
  switch (DPSnum) {
    case 1: {
      HAL_UART_Receive(motor_1.huart, ch, 1, 0xff);
    } break;
    case 2: {
      HAL_UART_Receive(motor_2.huart, ch, 1, 0xff);
    } break;
  }
}

uint16_t Get_Crc(uint8_t *p, uint16_t len)
{
  uint8_t i = 0;
  uint16_t tmp = 0xffff;
  while (len > 0)
  {
    tmp ^= *p++;
    while (i < 8)
    {
      if (tmp & 0x0001)
      {
        tmp >>= 1;
        tmp ^= crc;
      } else
      {
        tmp >>= 1;
      }
      i++;
    }
    i = 0;
    len--;
  }
  return tmp;
}

void DPS_SetVelocity(uint8_t DPSnum, long int vel)
{
  switch (DPSnum) {
    case 1: {
      UART_DISABLE_RE(motor_1.huart);
    } break;
    case 2: {
      UART_DISABLE_RE(motor_2.huart);
    } break;
  }
  velFrame[7] = vel >> 24;
  velFrame[8] = (vel >> 16) & 0xFF;
  velFrame[9] = (vel >> 8) & 0xFF;
  velFrame[10] = vel & 0xFF;
  uint16_t CRC_C = Get_Crc(velFrame, 11);
  velFrame[11] = CRC_C & 0xFF;//先发低字节,相当于调换顺序后先发高地址
  velFrame[12] = CRC_C >> 8;
  for (uint8_t i = 0; i < 13; i++) DPS_Transmit(DPSnum, velFrame[i]);
}
/**
 * 设置电机旋转位置（绝对位置）
 * @param DPSnum
 * @param pos （0-360）
 */
void DPS_SetPosition(uint8_t DPSnum, long int pos)
{
  switch (DPSnum) {
    case 1: {
      UART_DISABLE_RE(motor_1.huart);
    } break;
    case 2: {
      UART_DISABLE_RE(motor_2.huart);
    } break;
  }
  //归算
  //  pos *= (int) (Max_Pos / 360);
  posFrame[7] = pos >> 24;
  posFrame[8] = (pos >> 16) & 0xFF;
  posFrame[9] = (pos >> 8) & 0xFF;
  posFrame[10] = pos & 0xFF;
  uint16_t CRC_C = Get_Crc(posFrame, 11);
  posFrame[11] = CRC_C & 0xFF;//先发低字节,相当于调换顺序后先发高地址
  posFrame[12] = CRC_C >> 8;
  for (uint8_t i = 0; i < 13; i++) DPS_Transmit(DPSnum, posFrame[i]);
}
void DPS_SetCurrent(uint8_t DPSnum, short int current)
{
  switch (DPSnum) {
    case 1: {
      UART_DISABLE_RE(motor_1.huart);
    } break;
    case 2: {
      UART_DISABLE_RE(motor_2.huart);
    } break;
  }
  curFrame[4] = current >> 8;
  curFrame[5] = current & 0xFF;
  uint16_t CRC_C = Get_Crc(curFrame, 6);
  curFrame[6] = CRC_C & 0xFF;//先发低字节,相当于调换顺序后先发高地址
  curFrame[7] = CRC_C >> 8;
  for (uint8_t i = 0; i < 8; i++) DPS_Transmit(DPSnum, curFrame[i]);
}
/**
 * 获取电机当前的位置
 * @param DPSnum
 * @param ring_queue
 * @param pos
 * @return
 */
int DPS_GetPosition(uint8_t DPSnum, RingQueue *ring_queue, int *pos)
{
  switch (DPSnum) {
    case 1: {
      UART_ENABLE_RE(motor_1.huart);
    } break;
    case 2: {
      UART_ENABLE_RE(motor_2.huart);
    } break;
  }
  uint8_t CrcBase[7] = {0};
  uint8_t i;
  uint16_t C;
  for (uint8_t j = 0; j < 8; j++) DPS_Transmit(DPSnum, GET_POS[j]);
  while (1) {
    //    UART_printf(&huart4, "error\r\n");
    uint8_t ch;
    DPS_Receive(DPSnum, &ch);
    InsQueue(ring_queue, ch);
    if ((ring_queue->rear + 1) % ring_queue->size == ring_queue->front) {
      if (QueueGet(ring_queue, 0) == 0x01 && QueueGet(ring_queue, 1) == 0x04 && QueueGet(ring_queue, 2) == 0x04) {
        C = QueueGet(ring_queue, 7) | QueueGet(ring_queue, 8) << 8;
        for (i = 0; i < 7; i++) CrcBase[i] = QueueGet(ring_queue, i);
        if (Get_Crc(CrcBase, 7) == C) {
          *pos = QueueGet(ring_queue, 3) << 24 | QueueGet(ring_queue, 4) << 16 | QueueGet(ring_queue, 5) << 8 | QueueGet(ring_queue, 6);
          ring_queue->front = 0;
          ring_queue->rear = 0;
          return 1;
        }
      }
    }
  }
  return 1;
}

int DPS_GetAll(uint8_t DPSnum, RingQueue *ring_queue, int *pos, int *vel, int *current)
{
  switch (DPSnum) {
    case 1: {
      UART_ENABLE_RE(motor_1.huart);
    } break;
    case 2: {
      UART_ENABLE_RE(motor_2.huart);
    } break;
  }
  uint8_t CrcBase[15] = {0};
  uint8_t i;
  uint16_t C;
  for (uint8_t j = 0; j < 8; j++) DPS_Transmit(DPSnum, GET_ALL[j]);
  while (1) {
    uint8_t ch;
    DPS_Receive(DPSnum, &ch);
    InsQueue(ring_queue, ch);
    if ((ring_queue->rear + 1) % ring_queue->size == ring_queue->front) {
      if (QueueGet(ring_queue, 0) == 0x01 && QueueGet(ring_queue, 1) == 0x04 && QueueGet(ring_queue, 2) == 0x0C) {
        C = QueueGet(ring_queue, 15) | QueueGet(ring_queue, 16) << 8;
        for (i = 0; i < 15; i++) CrcBase[i] = QueueGet(ring_queue, i);
        if (Get_Crc(CrcBase, 15) == C) {
          *pos = QueueGet(ring_queue, 3) << 24 | QueueGet(ring_queue, 4) << 16 | QueueGet(ring_queue, 5) << 8 | QueueGet(ring_queue, 6);
          *vel = QueueGet(ring_queue, 7) << 24 | QueueGet(ring_queue, 8) << 16 | QueueGet(ring_queue, 9) << 8 | QueueGet(ring_queue, 10);
          *current = QueueGet(ring_queue, 11) << 24 | QueueGet(ring_queue, 12) << 16 | QueueGet(ring_queue, 13) << 8 | QueueGet(ring_queue, 14);
          ring_queue->front = 0;
          ring_queue->rear = 0;
          return 1;
        }
      }
    }
  }
  return 1;
}


//SHELL_EXPORT_CMD(SHELL_CMD_TYPE(SHELL_TYPE_CMD_FUNC), DPS_debug_mode, Trash_Set, 1->Recyclable 2->ther 3->Hazadous 4->Food);