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

//************************* Global Constants ***********************************

//************************* Global Variables *********************************** 

//************************* Forward Declarations *******************************  
bool audioDriverInit();
bool audioDriverPlayRingtone(_CURRENT_DATA_* pstReceivedData, 
                             QueueHandle_t* ppMqAudio, 
                             EventGroupHandle_t* ppEventHandler);

//************************ Inline Method Implementations *********************** 

#endif 

// AUDIODRIVER_H 
// EOF