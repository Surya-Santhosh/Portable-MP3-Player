//******************************** main ****************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : main.cpp
// Summary : To play MP3 files from ESP32 internal flash memory through I2S 
//           amplifier MAX98357A.
// Note    : None
// Author  : Surya Santhosh
// Day     : 23/Oct/2025
//******************************************************************************

//**************************** Include Files ***********************************
#include "common.h"
#include "rtosInit.h"
#include "display.h"
#include "audioDriver.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************

//**************************** Local Variables *********************************

//***************************** Local Functions ********************************

//*****************************.mainFunction.***********************************
// Purpose : Initialize serial communication, audio driver and display driver 
//           and FreeRTOS task creation  for system operation.
// Inputs  : none
// Outputs : none
// Return  : 0
// Notes   : None
//******************************************************************************
void setup() 
{
  Serial.begin(UART_BAUD_RATE);
  
  if (true != audioDriverInit())
  {
      Serial.println("audioDriverInit failed");
  }

  if (true != displayInit())
  {
    Serial.print("displayInit failed");
  }

  if (true != rtosInitAll())
  {
    Serial.print("rtosInitAll failed");
  }
}

void loop() 
{

}

// EOF