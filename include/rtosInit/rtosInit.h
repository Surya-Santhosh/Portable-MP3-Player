//***********************8********* rtosInit ***********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//******************************************************************************
//
// Summary : Send and Reeceive data via message queue.
// Note    : None
// 
//******************************************************************************
#ifndef RTOSINIT_H
#define RTOSINIT_H

//**************************** Include Files ***********************************
#include "common.h"

//*************************** Global Types ************************************* 
typedef struct _TASK_
{
    TaskFunction_t pvTaskName;
    const char *pucName;  
    uint32 ulStackSize;
    void* pvParameters;
    UBaseType_t unPriority;
    TaskHandle_t* pvTaskHandle;
}_TASK_;

//************************* Global Constants *********************************** 

//************************* Global Variables *********************************** 

//************************* Forward Declarations ******************************* 
bool rtosInitAll();
bool rtosInitSemRelease(SemaphoreHandle_t* psemHandler);
bool rtosInitSemAcquire(SemaphoreHandle_t* psemHandler);
bool rtosInitMqueueReceive(QueueHandle_t* ppMqAudio, void* pvBuffer);
bool rtosInitMqueueSend(QueueHandle_t* ppMqAudio, void* pvBuffer);
bool rtosInitEvent(EventGroupHandle_t* ppEventHandler);
bool rtosInitEventSet(EventGroupHandle_t* ppEventHandler, 
                      EventBits_t eventBit);
bool rtosInitEventWait(EventGroupHandle_t* ppEventHandler, 
                       EventBits_t* eventBit);
bool freeRtosInitMQueue(QueueHandle_t* ppMqHandle, uint16 unQueueLength, 
                        uint8 ucItemSize);

//********************** Inline Method Implementations ************************* 

#endif 

// RTOSINIT_H 
// EOF