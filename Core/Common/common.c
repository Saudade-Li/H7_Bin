//
// Created by 小李又在摸鱼 on 2022/11/15.
//

#include "common.h"
#include "main.h"
Com_t com;
/**
 * 清除滤波次数
 */
void Clear_All_Count(void)
{
  com.filter_count[0] = 0;
  com.filter_count[1] = 0;
  com.filter_count[2] = 0;
  com.filter_count[3] = 0;
  com.filter_count[4] = 0;
  com.filter_count[5] = 0;
}