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
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef unsigned long uint32;
typedef char int8;
typedef signed short int16;

//************************* Global Constants ***********************************

//************************* Global Variables *********************************** 

//************************* Forward Declarations *******************************  
bool displayInit();
bool displayPlayMode(uint8 ucdMode, uint8 ucSelectedIndex, String* psSongList);
bool displaySelectionMode(uint8 sgucSelectedIndex, String* psSongList);

//************************ Inline Method Implementations *********************** 

#endif 

// DISPLAY_H 
// EOF