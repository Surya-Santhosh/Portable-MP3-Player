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
static bool joystickSetEvents(_JOYSTICK_DATA_* pstJoystickData, 
                              EventGroupHandle_t* ppEventHandler);

//*******************************.joystickRead.*********************************
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

        if (true != joystickSetEvents(&stJoystickData, ppEventHandler))
        {
            Serial.println("joystickSetEvents failed");
        }
        
        blReturn = true;
    }

    return blReturn;
}

//***************************.joystickSetEvents.********************************
// Purpose : Read joystick input and send to the system manager. 
// Inputs  : pstJoystickData - poniter to struct contain joystick data.
//           ppEventHandler - poniter to event handler.
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
static bool joystickSetEvents(_JOYSTICK_DATA_* pstJoystickData, 
                              EventGroupHandle_t* ppEventHandler)
{
    bool blReturn = false;

    if ((NULL != pstJoystickData) && (NULL != ppEventHandler))
    {
        if ((JOYSTICK_MAX_VALUE < pstJoystickData->ulYValue) && 
            (JOYSTICK_CENTER_VALUE < pstJoystickData->ulXValue))
        {
            rtosInitEventSet(ppEventHandler, EVENT_RIGHT);
        }
        else if ((JOYSTICK_MIN_VALUE > pstJoystickData->ulYValue) && 
                (JOYSTICK_CENTER_VALUE < pstJoystickData->ulXValue))
        {
            rtosInitEventSet(ppEventHandler, EVENT_LEFT);
        }
        else if ((JOYSTICK_CENTER_VALUE < pstJoystickData->ulYValue) && 
                (JOYSTICK_MAX_VALUE < pstJoystickData->ulXValue))
        {
            rtosInitEventSet(ppEventHandler, EVENT_UP);
        }
        else if ((JOYSTICK_CENTER_VALUE < pstJoystickData->ulYValue) && 
                (JOYSTICK_MIN_VALUE > pstJoystickData->ulXValue))
        {
            rtosInitEventSet(ppEventHandler, EVENT_DOWN);
        }
        else if (LOW == pstJoystickData->blSwitchState)
        {
            rtosInitEventSet(ppEventHandler, EVENT_SWITCH_ON);
        }

        blReturn = true;
    }

    return blReturn;
}

// EOF