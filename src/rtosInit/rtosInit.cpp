//***************************** freeRtosInit ***********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : freeRtosInit.cpp
// Summary : Initialize all FreeRTOS resources (task, semaphore and 
//           message queue).
// Note    : None
// Author  : Surya Santhosh
// Day     : 23/Oct/2025
//******************************************************************************

//**************************** Include Files ***********************************
#include "rtosInit.h"
#include "audioManager.h"
#include "inputManager.h"
#include "systemManager.h"
#include "displayManger.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************
static _RTOS_HANDLER_ sgstEventHandler = {0};
static _TASK_ sgstTask[] = {{(TaskFunction_t) inputManagerTask, "Input Manager", 
                        STACK_SIZE, &sgstEventHandler,  tskIDLE_PRIORITY, NULL}, 
                        {(TaskFunction_t) audioManagerTask, "Audio Manager", 
                        STACK_SIZE, &sgstEventHandler, tskIDLE_PRIORITY, NULL}, 
                        {(TaskFunction_t) displayManagerTask, "Display Manager", 
                        STACK_SIZE, &sgstEventHandler, tskIDLE_PRIORITY, NULL}, 
                        {(TaskFunction_t) systemManagerTask, "System Manager", 
                        STACK_SIZE, &sgstEventHandler, tskIDLE_PRIORITY, NULL}};

//**************************** Local Variables *********************************

//***************************** Local Functions ********************************
static bool rtosInitTask();

//**************************.rtosInitTask.**********************************
// Purpose : To create FreeRTOS tasks. 
// Inputs  : None
// Outputs : None
// Return  : true
// Notes   : None
//******************************************************************************
static bool rtosInitTask()
{
    uint8 ucIndex = 0;
    uint8 ucTaskCount = sizeof(sgstTask) / sizeof(sgstTask[0]);

    for (ucIndex = 0; ucIndex < ucTaskCount; ucIndex++)
    {
        xTaskCreate(sgstTask[ucIndex].pvTaskName, sgstTask[ucIndex].pucName, 
                    sgstTask[ucIndex].ulStackSize, 
                    sgstTask[ucIndex].pvParameters, 
                    sgstTask[ucIndex].unPriority, 
                    sgstTask[ucIndex].pvTaskHandle);
    }

    return true;
}

//*******************************.rtosInitAll.**********************************
// Purpose : Initialize task and semaphore. 
// Inputs  : None
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
bool rtosInitAll()
{
    bool blReturn = false;

    do 
    {
        if (true != rtosInitEvent(&sgstEventHandler.pEventHandler))
        {
            Serial.print("rtosInitEvent failed");
        }

        rtosInitTask();

        blReturn = true;
    }
    while (true != blReturn);

    return blReturn;
}

//*************************.rtosInitMqueueReceive.**************************
// Purpose : To Receive an item from a queue. 
// Inputs  : ppMqAudio - pointer to Message queue handler.
//         : pvBuffer - Pointer to the buffer into which the received item will
//           be copied.
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
bool rtosInitMqueueReceive(QueueHandle_t* ppMqAudio, void* pvBuffer)
{
    bool blReturn = false;

    if ((NULL != ppMqAudio) && (NULL != pvBuffer))
    {
        if (pdTRUE == xQueueReceive(*ppMqAudio, pvBuffer, portTICK_PERIOD_MS))
        {
            blReturn = true;
        }
    }

    return blReturn;
}

//***************************.rtosInitMqueueSend.*******************************
// Purpose : To Receive an item from a queue. 
// Inputs  : psemHandler - pointer to Message queue handler.
//         : pvBuffer - A pointer to the item that is to be placed on the queue.
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
bool rtosInitMqueueSend(QueueHandle_t* ppMqAudio, void* pvBuffer)
{
    bool blReturn = false;

    if ((NULL != ppMqAudio) && (NULL != pvBuffer))
    {
        if (pdTRUE == xQueueOverwrite(*ppMqAudio, pvBuffer))
        {
            blReturn = true;
        }
    }

    return blReturn;
}

//******************************.rtosInitEvent.*********************************
// Purpose : Create an event . 
// Inputs  : ppEventHandler - pointer to event handler.
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
bool rtosInitEvent(EventGroupHandle_t* ppEventHandler)
{
    bool blReturn = false;

    if (NULL != ppEventHandler)
    {
        *ppEventHandler = xEventGroupCreate();
        blReturn = true;
    }

    return blReturn;
}

//*****************************.rtosInitEventSet.*******************************
// Purpose : Set bits within an event group. 
// Inputs  : ppEventHandler - Pointer to event group in which the bits are to 
//           be set.
//         : EventBit - A bitwise value that indicates the bit or bits to set.
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
bool rtosInitEventSet(EventGroupHandle_t* ppEventHandler, EventBits_t eventBit)
{
    bool blReturn = false;
    BaseType_t priority = pdFALSE;

    if (NULL != ppEventHandler)
    {
        xEventGroupSetBits(*ppEventHandler, eventBit);

        blReturn = true;
    }

    return blReturn;
}

//*****************************.rtosInitEventWait.******************************
// Purpose : Set bits within an event group. 
// Inputs  : ppEventHandler - Pointer to event group in which the bits are to 
//           be set.
//         : pvBuffer - A bitwise value that indicates the bit or bits to set.
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
bool rtosInitEventWait(EventGroupHandle_t* ppEventHandler, 
                       EventBits_t* pEventBit, TickType_t ticksToWait)
{
    bool blReturn = false;

    if ((NULL != ppEventHandler) && (NULL != pEventBit))
    {
        *pEventBit =  xEventGroupWaitBits(*ppEventHandler, EVENT_DOWN | 
                                           EVENT_LEFT | EVENT_RIGHT | EVENT_UP | 
                                           EVENT_SWITCH_ON, pdTRUE, pdFALSE, 
                                           ticksToWait);
        blReturn = true;
    }

    return blReturn;
}


//***************************.freeRtosInitMQueue.*******************************
// Purpose : To create message queue. 
// Inputs  : pMqHandle - pointer to message descriptor.
//           unQueueLength - The number of items that the queue can contain.
//           ucItemSize - The number of bytes each item in the queue.
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
bool freeRtosInitMQueue(QueueHandle_t* ppMqHandle, uint16 unQueueLength, 
                        uint8 ucItemSize)
{
    bool blReturn = false;

    if (NULL != ppMqHandle)
    {
        *ppMqHandle = xQueueCreate(unQueueLength, ucItemSize);
        blReturn = true;
    }

    return blReturn;
}

// EOF