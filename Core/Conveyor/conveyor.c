//
// Created by С���������� on 2022/11/15.
//

#include "conveyor.h"
#include "DPSDrive.h"
#include "main.h"

void Conveyor_Set_Vel(long vel)
{
  DPS_SetVelocity(1, vel);
}
