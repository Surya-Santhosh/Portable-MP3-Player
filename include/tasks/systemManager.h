//***************************** systemManager **********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//******************************************************************************
//
// Summary : Coordinate Input, Audio and display Uusing semaphore and 
//           message queue.
// Note    : None
// 
//******************************************************************************
#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

//**************************** Include Files ***********************************
#include "common.h"

//*************************** Global Types ************************************* 
typedef struct _CURRENT_DATA_
{
    uint8 ucMode;
    uint8 ucAction;
    uint8 ucSelectedIndex;
    String psSongList[NUM_AUDIO_FILE];
}_CURRENT_DATA_;

//************************* Global Constants *********************************** 

//************************* Global Variables *********************************** 

//************************* Forward Declarations ******************************* 
void systemManagerTask(_RTOS_HANDLER_* pstEventHandler);

//********************** Inline Method Implementations ************************* 

#endif 

// SYSTEM_MANAGER_H 
// EOF