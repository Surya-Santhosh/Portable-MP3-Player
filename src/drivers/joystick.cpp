//******************************** joystick ************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : joystick.cpp
// Summary : Coordinate Input, Audio and display Uusing semaphore and 
//           message queue.
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
static bool joysticksetEvents(_JOYSTICK_DATA_* pstJoystickData, 
                              EventGroupHandle_t* ppEventHandler);

//****************************.joysticksetEvents.*******************************
// Purpose : Read joystick input, set events. 
// Inputs  : ppEventHandler - poniter to event handler.
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
bool joystickRead(EventGroupHandle_t* ppEventHandler)
{
    bool blReturn = false;
    
    if (NULL != ppEventHandler)
    {
        pinMode(JOYSTICK_SWITCH, INPUT_PULLUP);

        _JOYSTICK_DATA_ stJoystickData = {0};
        stJoystickData.ulXValue = analogRead(JOYSTICK_X);
        stJoystickData.ulYValue = analogRead(JOYSTICK_Y);
        stJoystickData.blSwitchState = digitalRead(JOYSTICK_SWITCH);

        if (true != joysticksetEvents(&stJoystickData, ppEventHandler))
        {
            Serial.println("joysticksetEvents failed");
        }
        
        blReturn = true;
    }

    return blReturn;
}

//****************************.audioManagerTask.********************************
// Purpose : Read joystick input and send to the system manager. 
// Inputs  : None
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
static bool joysticksetEvents(_JOYSTICK_DATA_* pstJoystickData, 
                              EventGroupHandle_t* ppEventHandler)
{
    bool blReturn = false;

    if ((NULL != pstJoystickData) && (NULL != ppEventHandler))
    {
        if ((JOYSTICK_MAX_VALUE < pstJoystickData->ulYValue) && 
            (JOYSTICK_CENTER_VALUE < pstJoystickData->ulXValue))
        {
            Serial.println("Right");
            rtosInitEventSet(ppEventHandler, EVENT_RIGHT);
        }
        else if ((JOYSTICK_MIN_VALUE > pstJoystickData->ulYValue) && 
                (JOYSTICK_CENTER_VALUE < pstJoystickData->ulXValue))
        {
            Serial.println("Left");
            rtosInitEventSet(ppEventHandler, EVENT_LEFT);
        }
        else if ((JOYSTICK_CENTER_VALUE < pstJoystickData->ulYValue) && 
                (JOYSTICK_MAX_VALUE < pstJoystickData->ulXValue))
        {
            Serial.println("Up");
            rtosInitEventSet(ppEventHandler, EVENT_UP);
        }
        else if ((JOYSTICK_CENTER_VALUE < pstJoystickData->ulYValue) && 
                (JOYSTICK_MIN_VALUE > pstJoystickData->ulXValue))
        {
            Serial.println("Down");
            rtosInitEventSet(ppEventHandler, EVENT_DOWN);
        }
        else if (LOW == pstJoystickData->blSwitchState)
        {
            Serial.println("Switch on");
            rtosInitEventSet(ppEventHandler, EVENT_SWITCH_ON);
        }

        blReturn = true;
    }

    return blReturn;
}

// EOF