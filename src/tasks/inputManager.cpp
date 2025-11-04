//**************************** inputManger *************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : inputManger.cpp
// Summary : Read joystick input and update system manager via event.
// Note    : None
// Author  : Surya Santhosh
// Day     : 23/Oct/2025
//******************************************************************************

//**************************** Include Files ***********************************
#include "joystick.h"
#include "inputManager.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//**************************** Local Variables *********************************

//***************************** Local Functions ********************************

//****************************.taskAudioManager.********************************
// Purpose : Read joystick input, set events and update system manager via event 
// Inputs  : pstRtosHandler - pointer to the freeRTOS handlers.
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void inputManagerTask(_RTOS_HANDLER_* pstRtosHandler)
{
    if (NULL != pstRtosHandler)
    {
        while (1)
        {
            // Read joystick and set event based on action.
            if (true != joystickRead(&pstRtosHandler->pEventHandler))
            {
                Serial.println("joystickRead failed");
            }

            vTaskDelay(500);
        }
    }
}

//EOF