//******************************* display **************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//****************************************************************************** 
// 
// Summary : Typedefs are included.
// Note    : None
// 
//******************************************************************************
#ifndef DISPLAY_H
#define DISPLAY_H 

//**************************** Include Files ***********************************
#include "common.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//**************************** Global Types ************************************

//************************* Global Constants ***********************************

//************************* Global Variables *********************************** 

//************************* Forward Declarations *******************************  
bool displayInit();
bool displayPlayMode(uint8 ucdMode, uint8 ucSelectedIndex, String* psSongList);
bool displaySelectionMode(uint8 sgucSelectedIndex, String* psSongList);
bool displayHomeScreen();

//************************ Inline Method Implementations *********************** 

#endif 

// DISPLAY_H 
// EOF