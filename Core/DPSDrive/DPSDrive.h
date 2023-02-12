#ifndef __DPSDRIVE_H
#define __DPSDRIVE_H
#include "usart.h"
#include <stdint.h>
#define Queue_Size 10
#define trash_init_pos (0)
#define tle_init_pos (100.0)
typedef struct {
  uint8_t *base;
  uint8_t front;
  uint8_t rear;
  uint8_t size;
} RingQueue;
typedef struct {
  uint32_t ID;
  TIM_HandleTypeDef *htim;
  GPIO_TypeDef *ENPort;
  uint16_t ENPin;
  UART_HandleTypeDef *huart;
  int init_pos;
  int trash_pos;
  double init_angle;
  double trash_angle;
  double offset_angle;
  int recyclable_pos;
  int other_pos;
  int food_pos;
  int hazardous_pos;
  int offset_pos;
  int initial_flag;
} DPS_t;
void InitQueue(RingQueue *ring_queue, uint8_t init_size, uint8_t *base);
uint8_t InsQueue(RingQueue *ring_queue, uint8_t p);
void DPS_Transmit(uint8_t DPSnum, uint8_t ch);
void DPS_Receive(uint8_t DPSnum, uint8_t *ch);
uint16_t Get_Crc(uint8_t *p, uint16_t len);
void DPS_SetVelocity(uint8_t DPSnum, long int vel);
void DPS_SetPosition(uint8_t DPSnum, long int pos);
void DPS_SetCurrent(uint8_t DPSnum, short int currnet);
int DPS_GetPosition(uint8_t DPSnum, RingQueue *ring_queue, int *pos);
int DPS_GetAll(uint8_t DPSnum, RingQueue *ring_queue, int *pos, int *vel, int *current);

#endif