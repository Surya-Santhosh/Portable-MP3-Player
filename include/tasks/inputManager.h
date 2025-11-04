//**************************** inputManger *************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//******************************************************************************
//
// Summary : Read joystick input and update system manager via event.
// Note    : None
// 
//******************************************************************************
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

//**************************** Include Files ***********************************
#include "common.h"

//*************************** Global Types ************************************* 
typedef struct _JOYSTICK_DATA_
{
    uint16 ulXValue;
    uint16 ulYValue;
    bool blSwitchState;
}_JOYSTICK_DATA_;

//************************* Global Constants *********************************** 

//************************* Global Variables *********************************** 

//************************* Forward Declarations ******************************* 
void inputManagerTask(_RTOS_HANDLER_* pstEventHandler);

//********************** Inline Method Implementations ************************* 

#endif 

// INPUT_MANAGER_H 
// EOF