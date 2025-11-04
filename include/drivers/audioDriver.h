//******************************* audioDriver **********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//****************************************************************************** 
// 
// Summary : Typedefs are included.
// Note    : None
// 
//******************************************************************************
#ifndef AUDIODRIVER_H
#define AUDIODRIVER_H

//**************************** Include Files ***********************************
#include "common.h"
#include "systemManager.h"

//**************************** Global Types ************************************
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef unsigned long uint32;
typedef char int8;
typedef signed short int16;

//************************* Global Constants ***********************************

//************************* Global Variables *********************************** 

//************************* Forward Declarations *******************************  
bool audioDriverInit();
bool audioDriverPlayRingtone(_CURRENT_DATA_ *pstReceivedData, 
                             QueueHandle_t *ppMqAudio, 
                             EventGroupHandle_t* pEventHandler);

//************************ Inline Method Implementations *********************** 

#endif 

// AUDIODRIVER_H 
// EOF