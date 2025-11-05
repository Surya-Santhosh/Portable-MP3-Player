//****************************** audioManger ***********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : audioManger.cpp
// Summary : Handle audio playback control by receiving data from the 
//           system manger via message queue.
// Note    : None
// Author  : Surya Santhosh
// Day     : 23/Oct/2025
//******************************************************************************

//**************************** Include Files ***********************************
#include "audioManager.h"
#include "audioDriver.h"
#include "rtosInit.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//**************************** Local Variables *********************************

//***************************** Local Functions ********************************

//*****************************.audioManagerTask.*******************************
// Purpose : Receives data from system manger via message queue and 
//           control audio playback.
// Inputs  : pstRtosHandler - pointer to the freeRTOS handlers.
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
void audioManagerTask(_RTOS_HANDLER_* pstRtosHandler)
{
    uint8 ucIndex = 0;
    static _CURRENT_DATA_ sstReceivedData = {0};

    if (NULL != pstRtosHandler)
    {
        while (1)
        {
            rtosInitSemAcquire(&pstRtosHandler->semAudioManager);
            rtosInitMqueueReceive(&pstRtosHandler->pMqAudio, &sstReceivedData);

            if ((PLAY_MODE == sstReceivedData.ucMode) || 
                (PAUSE_MODE == sstReceivedData.ucMode))
            {
                audioDriverPlayRingtone(&sstReceivedData,
                                        &pstRtosHandler->pMqAudio, 
                                        &pstRtosHandler->pEventHandler);
            }
        }
    }
}

//EOF