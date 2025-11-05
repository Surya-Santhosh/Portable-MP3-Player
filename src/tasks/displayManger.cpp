//**************************** displayManager **********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : displayManager.cpp
// Summary : Update display received data from the system manger via 
//           message queue.
// Note    : None
// Author  : Surya Santhosh
// Day     : 23/Oct/2025
//******************************************************************************

//**************************** Include Files ***********************************
#include "display.h"
#include "displayManger.h"
#include "rtosInit.h"
#include "systemManager.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//**************************** Local Variables *********************************

//***************************** Local Functions ********************************

//*****************************.displayManagerTask.*****************************
// Purpose : Receives data from system manger via message queue and update 
//           OLED display.
// Inputs  : pstRtosHandler - pointer to the freeRTOS handlers.
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
void displayManagerTask(_RTOS_HANDLER_* pstRtosHandler)
{
    static _CURRENT_DATA_ sstReceivedData = {0};

    if (NULL != pstRtosHandler)
    {
        while (1)
        {
            rtosInitSemAcquire(&pstRtosHandler->semDisplayManager);
            rtosInitMqueueReceive(&pstRtosHandler->pMqDisplay, 
                                  &sstReceivedData);

            if (SELECTION_MODE == sstReceivedData.ucMode)
            {
                // Display folder and song selection UI.
                displaySelectionMode(sstReceivedData.ucSelectedIndex, 
                                     sstReceivedData.psSongList);
            }
            else if (HOME_SCREEN == sstReceivedData.ucMode)
            {
                displayHomeScreen();
            }
            else 
            {
                // Display playback UI (Play/Pause, next, previous).
                displayPlayMode(sstReceivedData.ucMode, 
                                sstReceivedData.ucSelectedIndex, 
                                sstReceivedData.psSongList);
            }
        }
    }
}

//EOF