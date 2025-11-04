//******************************* audioDriver **********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : audioDriver.cpp
// Summary : Coordinate Input, Audio and display Uusing semaphore and 
//           message queue.
// Note    : None
// Author  : Surya Santhosh
// Day     : 23/Oct/2025
//******************************************************************************

//**************************** Include Files ***********************************
#include "audioDriver.h"
#include "rtosInit.h"
#include "systemManager.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//**************************** Local Variables *********************************
static Audio sgcAudio;

//***************************** Local Functions ********************************
static bool audioToSetup(String* psSongList, uint8 ucIndex);

//****************************.audioManagerTask.********************************
// Purpose : Read joystick input and send to the system manager. 
// Inputs  : None
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
bool audioDriverInit()
{
    bool blReturn = false;

    if (true == SPIFFS.begin())
    {
        blReturn = true;
    }

    sgcAudio.setPinout(MAX98357A_BCLK, MAX98357A_LRC, MAX98357A_DIN);
    sgcAudio.setVolume(VOLUME_LEVEL);

    return blReturn;
}

//****************************.audioManagerTask.********************************
// Purpose : Read joystick input and send to the system manager. 
// Inputs  : None
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
bool audioDriverPlayRingtone(_CURRENT_DATA_ *pstReceivedData, 
                             QueueHandle_t *pMqAudio, 
                             EventGroupHandle_t* ppEventHandler)
{
    bool blReturn = false;
    _CURRENT_DATA_ sstNewReceivedData = {0};

    if ((NULL != pstReceivedData) && (NULL != pMqAudio))
    {
        audioToSetup(pstReceivedData->psSongList, 
                                 pstReceivedData->ucSelectedIndex);
        
        // Playback loop until mode changes or song finishes.
        while ((true == sgcAudio.isRunning()) && 
                (PLAY_MODE == pstReceivedData->ucMode))
        {
            sgcAudio.loop();

            if (true == rtosInitMqueueReceive(pMqAudio,
                                              &sstNewReceivedData))
            {
                // Pause button pressed, stop playback loop.
                if (EVENT_SWITCH_ON == sstNewReceivedData.ucAction)
                {
                    sgcAudio.stopSong();
                    pstReceivedData->ucMode = PAUSE_MODE;
                    break;
                }
                // next / previous track selection.
                else if ((EVENT_LEFT == sstNewReceivedData.ucAction) || 
                        (EVENT_RIGHT == sstNewReceivedData.ucAction))
                {
                    sgcAudio.stopSong();
                    pstReceivedData->ucMode = PAUSE_MODE;
                    break;
                }
            }
        }

        if (PLAY_MODE == pstReceivedData->ucMode)
        {
            Serial.println("Song Finished.");
            rtosInitEventSet(ppEventHandler, EVENT_RIGHT);
        }

        pstReceivedData->ucMode = sstNewReceivedData.ucMode;
        pstReceivedData->ucSelectedIndex = sstNewReceivedData.ucSelectedIndex;
        blReturn = true;
    }
    else
    {
        Serial.println("audioDriverplayRingtone failed");
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
static bool audioToSetup(String* psSongList, uint8 ucIndex)
{
    bool blReturn = false;

    if (NULL != psSongList)
    {
        String fileName = "/" + psSongList[ucIndex];

        if (true != SPIFFS.exists(fileName.c_str())) 
        {
            Serial.println("MP3 file not found!");
        }

        if (true != sgcAudio.connecttoFS(SPIFFS, psSongList[ucIndex].c_str())) 
        {
            Serial.println("Failed to open");
        }

        Serial.println(psSongList[ucIndex]);
        blReturn = true;
    }

    return blReturn;
}

// EOF