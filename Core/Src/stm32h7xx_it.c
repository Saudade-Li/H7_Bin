/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32h7xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_it.h"
#include "main.h"
#include <stdlib.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "DPSDrive.h"
#include "common.h"
#include "conveyor.h"
#include "debug.h"
#include "string.h"
#include "trash.h"
#include "usart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern Com_t com;
extern DPS_t dps;
extern Trash_t trash;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern SPI_HandleTypeDef hspi1;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern DMA_HandleTypeDef hdma_uart4_tx;
extern DMA_HandleTypeDef hdma_uart8_rx;
extern DMA_HandleTypeDef hdma_uart8_tx;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart8;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim17;

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32H7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 stream0 global interrupt.
  */
void DMA1_Stream0_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream0_IRQn 0 */

  /* USER CODE END DMA1_Stream0_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_uart4_rx);
  /* USER CODE BEGIN DMA1_Stream0_IRQn 1 */

  /* USER CODE END DMA1_Stream0_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream1 global interrupt.
  */
void DMA1_Stream1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream1_IRQn 0 */

  /* USER CODE END DMA1_Stream1_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_uart4_tx);
  /* USER CODE BEGIN DMA1_Stream1_IRQn 1 */

  /* USER CODE END DMA1_Stream1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream2 global interrupt.
  */
void DMA1_Stream2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream2_IRQn 0 */

  /* USER CODE END DMA1_Stream2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_uart8_rx);
  /* USER CODE BEGIN DMA1_Stream2_IRQn 1 */

  /* USER CODE END DMA1_Stream2_IRQn 1 */
}

/**
  * @brief This function handles DMA1 stream3 global interrupt.
  */
void DMA1_Stream3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Stream3_IRQn 0 */

  /* USER CODE END DMA1_Stream3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_uart8_tx);
  /* USER CODE BEGIN DMA1_Stream3_IRQn 1 */

  /* USER CODE END DMA1_Stream3_IRQn 1 */
}

/**
  * @brief This function handles SPI1 global interrupt.
  */
void SPI1_IRQHandler(void)
{
  /* USER CODE BEGIN SPI1_IRQn 0 */

  /* USER CODE END SPI1_IRQn 0 */
  HAL_SPI_IRQHandler(&hspi1);
  /* USER CODE BEGIN SPI1_IRQn 1 */

  /* USER CODE END SPI1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */

  /* USER CODE END USART3_IRQn 1 */
}

/**
  * @brief This function handles UART4 global interrupt.
  */
void UART4_IRQHandler(void)
{
  /* USER CODE BEGIN UART4_IRQn 0 */

  /* USER CODE END UART4_IRQn 0 */
  HAL_UART_IRQHandler(&huart4);
  /* USER CODE BEGIN UART4_IRQn 1 */

  /* USER CODE END UART4_IRQn 1 */
}

/**
  * @brief This function handles UART5 global interrupt.
  */
void UART5_IRQHandler(void)
{
  /* USER CODE BEGIN UART5_IRQn 0 */

  /* USER CODE END UART5_IRQn 0 */
  HAL_UART_IRQHandler(&huart5);
  /* USER CODE BEGIN UART5_IRQn 1 */

  /* USER CODE END UART5_IRQn 1 */
}

/**
  * @brief This function handles UART8 global interrupt.
  */
void UART8_IRQHandler(void)
{
  /* USER CODE BEGIN UART8_IRQn 0 */
  //��ȡ�����жϱ�־λ
  if (__HAL_UART_GET_FLAG(&huart8, UART_FLAG_IDLE) == SET)
  {
    //��������жϵı�־λ
    __HAL_UART_CLEAR_IDLEFLAG(&huart8);
    //DMA���չر�
    HAL_UART_DMAStop(&huart8);
    //ʵ�ʽ��յ����ֽ����� = �ܵ��ֽ�����-����״̬���ֽ�����
    RxNum = RxBuffSize - __HAL_DMA_GET_COUNTER(&hdma_uart8_rx);
    //DMA��������
    //TODO:��Ϣ���� 1|A|320X|320Y| B|320X|320Y  "1"����,��A�����,"320X|320Y"����
    // "F" ���ʹ�ֹͣ����
    // ������ģʽ
    if (RxBuffer[0] == '1')
    {
      //���ʹ���������
      Conveyor_Set_Vel(Conveyor_High_Vel);
      //TODO:�������ݽ����˲��ľ��ߣ���δ��֤
      //      trash.tar_trash = Trash_Decision(RxBuffer[1]);
      //      //������5�Σ�����Ͱǰ���趨λ��
      //      if (trash.tar_trash != 0)
      //      {
      //        Trash_Set();
      //      }
      //A:�ɻ���
      if (RxBuffer[1] == 'A')
      {
        trash.tar_trash = 1;
        Trash_Set();
      }
      //B���к�
      if (RxBuffer[1] == 'B')
      {
        trash.tar_trash = 2;
        Trash_Set();
      }
      //C������
      if (RxBuffer[1] == 'C')
      {
        trash.tar_trash = 3;
        Trash_Set();
      }
      //D������
      if (RxBuffer[1] == 'D')
      {
        trash.tar_trash = 4;
        Trash_Set();
      }
    }
    //�����
    if ((int) (RxBuffer[0] - '0') >= 2 && (RxBuffer[0] != 'F'))
    {
      trash.a_ = RxBuffer[1]; //��һ�����������
      trash.b_ = RxBuffer[10];//�ڶ������������
      //trash_a��������
      trash.X1 = (int) ((RxBuffer[2] - '0') * 100 + (RxBuffer[3] - '0') * 10 + (RxBuffer[4] - '0'));
      //trash_b��������
      trash.X2 = (int) ((RxBuffer[11] - '0') * 100 + (RxBuffer[12] - '0') * 10 + (RxBuffer[13] - '0'));
      //TODO:���ʹ������������ٶȱ仯���Ի�û����
      //������������Ͱ��Զ
      if (abs(trash.X1) > 300)
        //��������
        Conveyor_Set_Vel(Conveyor_High_Vel);
      else
        //��������Ͱ��Ϊ�����������У�������Ͱ��λ��ʱ��
        Conveyor_Set_Vel(Conveyor_Low_Vel);
      trash.tar_trash = Multi_Trash_Get(trash.a_, trash.b_, trash.X1, trash.X2);
      if (abs(trash.tar_trash) <= 4)
      {
        //����Ͱ��λ
        Trash_Set();
      }
    }
    //���ʹ�ֹͣ
    if (RxBuffer[0] == 'F')
    {
      Conveyor_Set_Vel(Conveyor_Stop);
    }
    //�ж���һ���������
    LastBuffer[0] = RxBuffer[1];
    //�ж��ֽڽ�����ɣ������ֽ�
    RxNum = 0;
    memset(RxBuffer, 0, RxBuffSize);                    //����
    HAL_UART_Receive_DMA(&huart8, RxBuffer, RxBuffSize);//���¿���DMA����
//������ģʽ
#ifdef Single
    //1:�ɻ���
    if (RxBuffer[0] == '1')
    {
      trash.tar_trash = 1;
      Trash_Set();
    }
    //2���к�
    if (RxBuffer[0] == '2')
    {
      trash.tar_trash = 2;
      Trash_Set();
    }
    //3������
    if (RxBuffer[0] == '3')
    {
      trash.tar_trash = 3;
      Trash_Set();
    }
    //4������
    if (RxBuffer[0] == '4')
    {
      trash.tar_trash = 4;
      Trash_Set();
    }
    // ���ʹ�����
    if (RxBuffer[1] == 'T')
    {
      Conveyor_Set_Vel(Conveyor_Vel);
    }
    //���ʹ�ֹͣ
    if (RxBuffer[0] == 'F')
    {
      Conveyor_Set_Vel(Conveyor_Stop);
    }
    //�ж���һ���������
    LastBuffer[0] = RxBuffer[0];
    //�ж��ֽڽ�����ɣ������ֽ�
    RxNum = 0;
    memset(RxBuffer, 0, RxBuffSize);                    //����
    HAL_UART_Receive_DMA(&huart8, RxBuffer, RxBuffSize);//���¿���DMA����
#endif
    //�����ģʽ
    //#ifdef Multi
    //    trash.a_ = RxBuffer[0];
    //    trash.b_ = RxBuffer[10];
    //    //trash_a��Y����
    //    trash.Y1 = (int) ((RxBuffer[6] - '0') * 100 + (RxBuffer[7] - '0') * 10 + (RxBuffer[8] - '0'));
    //    //trash_b��Y����
    //    trash.Y2 = (int) ((RxBuffer[17] - '0') * 100 + (RxBuffer[18] - '0') * 10 + (RxBuffer[19] - '0'));
    //    trash.tar_trash = Trash_Get(trash.a_, trash.b_, trash.Y1, trash.Y2);
    //    //�ж���һ���������
    //    LastBuffer[0] = RxBuffer[0];
    //    //�ж��ֽڽ�����ɣ������ֽ�
    //    RxNum = 0;
    //    memset(RxBuffer, 0, RxBuffSize);                    //����
    //    HAL_UART_Receive_DMA(&huart8, RxBuffer, RxBuffSize);//���¿���DMA����
    //#endif
  }
  /* USER CODE END UART8_IRQn 0 */
  HAL_UART_IRQHandler(&huart8);
  /* USER CODE BEGIN UART8_IRQn 1 */

  /* USER CODE END UART8_IRQn 1 */
}

/**
  * @brief This function handles TIM17 global interrupt.
  */
void TIM17_IRQHandler(void)
{
  /* USER CODE BEGIN TIM17_IRQn 0 */

  /* USER CODE END TIM17_IRQn 0 */
  HAL_TIM_IRQHandler(&htim17);
  /* USER CODE BEGIN TIM17_IRQn 1 */

  /* USER CODE END TIM17_IRQn 1 */
}

/* USER CODE BEGIN 1 */
/* USER CODE END 1 */
