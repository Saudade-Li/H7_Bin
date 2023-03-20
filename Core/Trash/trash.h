//
// Created by 小李又在摸鱼 on 2022/11/5.
//

#ifndef H7_BIN_V1_0_TRASH_H
#define H7_BIN_V1_0_TRASH_H
#define Quarter (400000)   //1/4圈
#define Round (3072000)    //一整圈
#define Key_Offset (80000) //按键调整累计偏差
#define Bin_Offset (400000)//垃圾桶的偏置
//#define Single             //单分类模式
#define Multi//多分类模式
#include "stdio.h"
typedef struct {
  int tar_trash;
  int curr_trash;
  int res;
  int tar_pos;
  int curr_pos;
  //垃圾置信度决策
  int count;
  int count_a;
  int count_b;
  int count_c;
  int count_d;
  int count_max;
  int count_stop;
  int final_bin;
#ifdef Multi
  int a_;
  int b_;
  int X1;
  int X2;
#endif
} Trash_t;
void Trash_Init();
void Trash_Set(void);
int Multi_Trash_Get(uint8_t trash_a, uint8_t trash_b, int Y1, int Y2);
int Trash_Decision(uint8_t rx_buff);
void Count_Clear(void);
#endif//H7_BIN_V1_0_TRASH_H
