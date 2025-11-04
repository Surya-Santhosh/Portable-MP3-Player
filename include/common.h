//******************************* common ***************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//****************************************************************************** 
// 
// Summary : Typedefs are included.
// Note    : None
// 
//******************************************************************************
#ifndef COMMON_H
#define COMMON_H 

//**************************** Include Files ***********************************
#include <Arduino.h>
#include <SPIFFS.h>
#include <stdio.h>
#include <Audio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <Wire.h>

//**************************** Global Types ************************************
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef unsigned long uint32;
typedef char int8;
typedef signed short int16;

typedef struct _RTOS_HANDLER_
{
    SemaphoreHandle_t semDisplayManager;
    SemaphoreHandle_t semAudioManager;
    SemaphoreHandle_t semSystemManager;
    EventGroupHandle_t pEventHandler;
    QueueHandle_t pMqAudio;
    QueueHandle_t pMqDisplay;
}_RTOS_HANDLER_;

//************************* Global Constants ***********************************
#define UART_BAUD_RATE                   (115200)
#define TASK_COUNT                       (4)
#define STACK_SIZE                       (4000)
#define EVENT_UP                         (1 << 0)
#define EVENT_DOWN                       (1 << 1)
#define EVENT_RIGHT                      (1 << 2)
#define EVENT_LEFT                       (1 << 3)
#define EVENT_SWITCH_ON                  (1 << 4)
#define SELECTION_MODE                   (0x01)
#define PLAY_MODE                        (0x02)
#define PAUSE_MODE                       (0x03)
#define JOYSTICK_SWITCH                  (5)
#define JOYSTICK_X                       (34)
#define JOYSTICK_Y                       (35)
#define MAX98357A_BCLK                   (27)
#define MAX98357A_LRC                    (14)
#define MAX98357A_DIN                    (26)
#define NUM_AUDIO_FILE                   (3)
#define DISPLAY_ADDRESS                  (0x3C)
#define ESP32_SDA                        (21)
#define ESP32_SCL                        (22)
#define OLED_WIDTH                       (128)
#define OLED_HEIGHT                      (32)
#define CHAR_HEIGHT                      (8)
#define CHAR_WIDTH                       (6)
#define JOYSTICK_MIN_VALUE               (100)
#define JOYSTICK_MAX_VALUE               (3900)
#define JOYSTICK_CENTER_VALUE            (1500)
#define VOLUME_LEVEL                     (5)
#define DELAY_TASK                       (500)

//************************* Global Variables *********************************** 

//************************* Forward Declarations *******************************  

//************************ Inline Method Implementations *********************** 

#endif 

// COMMON_H 
// EOF