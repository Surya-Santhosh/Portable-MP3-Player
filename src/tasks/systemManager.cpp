//***************************** systemManager **********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : systemManager.cpp
// Summary : Coordinate Input, Audio and display Uusing semaphore and 
//           message queue.
// Note    : None
// Author  : Surya Santhosh
// Day     : 23/Oct/2025
//******************************************************************************

//**************************** Include Files ***********************************
#include "systemManager.h"
#include "rtosInit.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************
static uint8 sgucSelectedMode = SELECTION_MODE;

//**************************** Local Variables *********************************

//***************************** Local Functions ********************************
static bool systemManagerLoadFiles(String* psSongList);
static bool systemManagerPlayMode(_CURRENT_DATA_ *sstCurrentData, 
                                  EventGroupHandle_t* ppEventHandler);
static bool systemManagerSelectionMode(_CURRENT_DATA_ *sstCurrentData, 
                                       EventGroupHandle_t* ppEventHandler);

//*****************************.systemManagerTask.******************************
// Purpose : Receive the data from the Input manager and send to Audio and 
//           display manager via messsage queue. 
// Inputs  : pstRtosHandler - pointer to the freeRTOS handlers.
// Outputs : None
// Return  : None
// Notes   : None
//******************************************************************************
void systemManagerTask(_RTOS_HANDLER_* pstRtosHandler)
{
    uint8 ucIndex = 0;
    static _CURRENT_DATA_ sstCurrentData = {0};
    static EventBits_t sEventBit = 0;

    freeRtosInitMQueue(&pstRtosHandler->pMqAudio, 1, sizeof(_CURRENT_DATA_));
    freeRtosInitMQueue(&pstRtosHandler->pMqDisplay, 1, sizeof(_CURRENT_DATA_));

    if (NULL != pstRtosHandler)
    {
        while (1)
        {
            // Wait until joystick triggers an event.
            rtosInitEventWait(&pstRtosHandler->pEventHandler, &sEventBit);

            //Store received action.
            sstCurrentData.ucAction = sEventBit;

            // Load MP3 file names from SPIFFS into list.
            systemManagerLoadFiles(sstCurrentData.psSongList);

            if (SELECTION_MODE == sgucSelectedMode)
            {
                systemManagerSelectionMode(&sstCurrentData, 
                                           &pstRtosHandler->pEventHandler);
            }
            else 
            {
                systemManagerPlayMode(&sstCurrentData, 
                                      &pstRtosHandler->pEventHandler);
            }

            // Store current UI mode.
            sstCurrentData.ucMode = sgucSelectedMode;

            // Send updated data to Audio & Display.
            rtosInitMqueueSend(&pstRtosHandler->pMqAudio, &sstCurrentData);
            rtosInitMqueueSend(&pstRtosHandler->pMqDisplay, &sstCurrentData);
            rtosInitSemRelease(&pstRtosHandler->semDisplayManager);
            rtosInitSemRelease(&pstRtosHandler->semAudioManager);
        }
    }
}

//****************************.taskAudioManager.********************************
// Purpose : Load MP3 files from SPIFFS into a string array
// Inputs  : psSongList - pointer to an array of string.
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
static bool systemManagerLoadFiles(String* psSongList)
{
    bool blReturn = false;
    uint8 ucIndex = 0;

    if (NULL != psSongList)
    {
        File cRoot = SPIFFS.open("/");
        File cFile = cRoot.openNextFile();

        while(ucIndex < NUM_AUDIO_FILE)
        {
            psSongList[ucIndex] = cFile.name();
            cFile = cRoot.openNextFile();
            ucIndex++;
        }

        cRoot.close();
        cFile.close();
        blReturn = true;
    }
    else
    {
        Serial.print("systemManagerLoadFiles failed");
    }

    return blReturn;
}

//****************************.taskAudioManager.********************************
// Purpose : Handle joystick input when in Selection mode. 
// Inputs  : pstCurrentData - Ponter to the struct contain selected index and 
//           action.
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
static bool systemManagerSelectionMode(_CURRENT_DATA_* pstCurrentData, 
                                       EventGroupHandle_t* ppEventHandler)
{
    bool blReturn = false;

    if ((NULL != pstCurrentData) && (NULL != ppEventHandler))
    {
        switch(pstCurrentData->ucAction)
        {
            // Move up in list.
            case EVENT_UP : pstCurrentData->ucSelectedIndex--;

                            if (NUM_AUDIO_FILE <= 
                                               pstCurrentData->ucSelectedIndex)
                            {
                                pstCurrentData->ucSelectedIndex = 
                                                             NUM_AUDIO_FILE - 1;
                            }
                            break;

            // Move down in list.
            case EVENT_DOWN : pstCurrentData->ucSelectedIndex++;

                              if (NUM_AUDIO_FILE <= 
                                               pstCurrentData->ucSelectedIndex)
                              {
                                pstCurrentData->ucSelectedIndex = 0;
                              }
                              break;

            // To select play mode.
            case EVENT_SWITCH_ON : sgucSelectedMode = PLAY_MODE;
                                   break;
        }

        blReturn = true;
    }

    return blReturn;
}

//****************************.taskAudioManager.********************************
// Purpose : Handle joystick input when in Play mode. 
// Inputs  : pstCurrentData - Ponter to the struct contain selected index and 
//           action.
// Outputs : None
// Return  : blReturn
// Notes   : None
//******************************************************************************
static bool systemManagerPlayMode(_CURRENT_DATA_* pstCurrentData, 
                                  EventGroupHandle_t* ppEventHandler)
{
    bool blReturn = false;

    if ((NULL != pstCurrentData) && (NULL != ppEventHandler))
    {
        switch(pstCurrentData->ucAction)
        {
            // Go back to file selection.
            case EVENT_UP : sgucSelectedMode = SELECTION_MODE;
                            break;

            case EVENT_DOWN : sgucSelectedMode = SELECTION_MODE;
                              break;

            // Next track.
            case EVENT_RIGHT : pstCurrentData->ucSelectedIndex++;
                               sgucSelectedMode = PLAY_MODE;

                               if (NUM_AUDIO_FILE <= 
                                               pstCurrentData->ucSelectedIndex)
                               {
                                pstCurrentData->ucSelectedIndex = 0;
                               }
                               break;
            
            // Previous track.
            case EVENT_LEFT : pstCurrentData->ucSelectedIndex--;
                              sgucSelectedMode = PLAY_MODE;

                              if (NUM_AUDIO_FILE <= 
                                               pstCurrentData->ucSelectedIndex)
                              {
                                pstCurrentData->ucSelectedIndex = 
                                                             NUM_AUDIO_FILE - 1;
                              }
                              break;

            // Toggle play/pause state.
            case EVENT_SWITCH_ON : if (PLAY_MODE == sgucSelectedMode)
                                   {
                                    sgucSelectedMode = PAUSE_MODE;
                                   }
                                   else
                                   {
                                    sgucSelectedMode = PLAY_MODE;
                                   }
                                   break;
        }

        blReturn = true;
    }

    return blReturn;
}

//EOF