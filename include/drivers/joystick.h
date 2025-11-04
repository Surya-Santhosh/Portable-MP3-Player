//******************************* joystick *************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved 
//****************************************************************************** 
// 
// Summary : Typedefs are included.
// Note    : None
// 
//******************************************************************************
#ifndef JOYSTICK_H
#define JOYSTICK_H 

//**************************** Include Files ***********************************
#include "common.h"
#include "rtosInit.h"

//**************************** Global Types ************************************
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef unsigned long uint32;
typedef char int8;
typedef signed short int16;

//************************* Global Constants ***********************************

//************************* Global Variables *********************************** 

//************************* Forward Declarations *******************************  
bool joystickRead(EventGroupHandle_t* ppEventHandler);

//************************ Inline Method Implementations *********************** 

#endif 

// JOYSTICK_H 
// EOF