//******************************** display *************************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//******************************************************************************
// File    : display.cpp
// Summary : Coordinate Input, Audio and display Uusing semaphore and 
//           message queue.
// Note    : None
// Author  : Surya Santhosh
// Day     : 23/Oct/2025
//******************************************************************************

//**************************** Include Files ***********************************
#include "display.h"

//******************************* Local Types **********************************

//***************************** Local Constants ********************************
Adafruit_SSD1306 gcdisplay(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

//**************************** Local Variables *********************************

//***************************** Local Functions ********************************
static bool displayDrawRectangle(uint8 ucX, uint8 ucY, uint8 ucWidth, 
                                 uint8 ucHeight);
static bool displayDrawTriangle(uint8 ucX0, uint8 ucY0, uint8 ucX1, uint8 ucY1, 
                                uint8 ucX2, uint8 ucY2);
static bool displayDrawLine(uint8 ucX0, uint8 ucY0, uint8 ucX1, uint8 ucY1);

//****************************.audioManagerTask.********************************
// Purpose : Initialize display. 
// Inputs  : None
// Outputs : None
// Return  : true
// Notes   : None
//******************************************************************************
bool displayInit()
{
    Wire.begin(ESP32_SDA, ESP32_SCL);
    Serial.begin(UART_BAUD_RATE);

    gcdisplay.begin(SSD1306_SWITCHCAPVCC, DISPLAY_ADDRESS);

    gcdisplay.clearDisplay();
    gcdisplay.setTextSize(1);
    gcdisplay.setTextColor(WHITE);
    gcdisplay.setCursor(7, 16);

    gcdisplay.println("Portable MP3 Player");
    gcdisplay.display();

    return true;
}

//***************************.displayPlayMode.**********************************
// Purpose : Display the play mode screen.
// Inputs  : ucdMode - Current mode.
//           ucSelectedIndex - Selected index.
//           psSongList - pointer to the songlist.
// Outputs : none
// Return  : blReturn
// Notes   : None
//******************************************************************************
bool displayPlayMode(uint8 ucdMode, uint8 ucSelectedIndex, String* psSongList)
{
  uint8 ucIndex = 0;
  bool blReturn = false;

  if (NULL != psSongList)
  {

    gcdisplay.clearDisplay();
    gcdisplay.setCursor(0, 0);

    // Back Indicator.
    gcdisplay.println(" <- "); 
    gcdisplay.setCursor(0, CHAR_HEIGHT);

    for (ucIndex = 0; ucIndex < NUM_AUDIO_FILE; ucIndex++)
    {
      if (ucSelectedIndex == ucIndex)
      {
        gcdisplay.println(psSongList[ucIndex]);
      }
    }

    if (true != displayDrawLine(0, 20, 128, 20))
    {
      Serial.print("displayDrawLine failed");
    }

    // Previous
    if (true != displayDrawTriangle(50, 24, 50, 32, 40, 28))
    {
      Serial.print("displayDrawTriangle failed");
    }

    // Next
    if (true != displayDrawTriangle(78, 24, 78, 32, 88, 28))
    {
      Serial.print("displayDrawTriangle failed");
    }

    // Draw play or pause icon depending on current state.
    if (PAUSE_MODE == ucdMode)
    {
      if (true != displayDrawTriangle(60, 24, 60, 32, 68, 28))
      {
        Serial.print("displayDrawTriangle failed");
      }
    }
    else
    {
      if (true != displayDrawRectangle(60, 24, 3, 8))
      {
        Serial.print("displayDrawRectangle failed");
      }

      if (true != displayDrawRectangle(68, 24, 3, 8))
      {
        Serial.print("displayDrawRectangle failed");
      }
    }

    gcdisplay.display();
    blReturn = true;
  }

  return blReturn;
}

//**************************.displaySelectionMode.******************************
// Purpose : Display the selection mode screen.
// Inputs  : ucSelectedIndex - Selected index.
//           psSongList - pointer to the songlist.
// Outputs : none
// Return  : blReturn
// Notes   : None
//******************************************************************************
bool displaySelectionMode(uint8 ucSelectedIndex, String* psSongList)
{
  uint8 ucIndex = 0;
  bool blReturn = false;

  if (NULL != psSongList)
  {
    gcdisplay.clearDisplay();
    gcdisplay.setCursor(0, 0);
    gcdisplay.println("Folder Name");

    for (ucIndex = 0; ucIndex < NUM_AUDIO_FILE; ucIndex++)
    {
      gcdisplay.setCursor(0, ((ucIndex + 1) * CHAR_HEIGHT));

      // List available songs and mark the highlighted selection.
      if (ucSelectedIndex == ucIndex)
      {
        gcdisplay.println("->");
      }
      else
      {
        gcdisplay.println("  ");
      }

      gcdisplay.setCursor(13, ((ucIndex + 1) * CHAR_HEIGHT));
      gcdisplay.print(psSongList[ucIndex]);
    }

    gcdisplay.display();
    blReturn = true;
  }

  return blReturn;
}

//**************************.displayDrawTriangle.*******************************
// Purpose : Draw traingle with colour fill.
// Inputs  : ucX0 - Vertex 0 X coordinate. 
//         : ucY0 - Vertex 0 Y coordinate. 
//         : ucX1 - Vertex 1 X coordinate. 
//         : ucY1 - Vertex 1 Y coordinate. 
//         : ucX2 - Vertex 2 X coordinate. 
//         : ucX2 - Vertex 2 Y coordinate. 
// Outputs : none
// Return  : true
// Notes   : None
//******************************************************************************
static bool displayDrawTriangle(uint8 ucX0, uint8 ucY0, uint8 ucX1, uint8 ucY1, 
                                uint8 ucX2, uint8 ucY2)
{
  gcdisplay.fillTriangle(ucX0, ucY0, ucX1, ucY1, ucX2, ucY2, WHITE);
  gcdisplay.display();

  return true;
}

//**************************.displayDrawRectangle.******************************
// Purpose : Draw Rectangle with colour fill.
// Inputs  : ucX - Top left corner X coordinate. 
//         : ucY - Top left corner Y coordinate.  
//         : ucWidth - Width of the rectangle 
//         : ucHeight - Height of the rectangle. 
// Outputs : none
// Return  : true
// Notes   : None
//******************************************************************************
static bool displayDrawRectangle(uint8 ucX, uint8 ucY, uint8 ucWidth, 
                                 uint8 ucHeight)
{
  gcdisplay.fillRect(ucX, ucY, ucWidth, ucHeight, WHITE);
  gcdisplay.display();

  return true;
}

//*****************************.displayDrawLine.********************************
// Purpose : Draw a line.
// Inputs  : ucX0 - Start point x coordinate.
//         : ucY0 - Start point y coordinate.  
//         : ucX1 - End point x coordinate.
//         : ucY1 - End point y coordinate.
// Outputs : none
// Return  : true
// Notes   : None
//******************************************************************************
static bool displayDrawLine(uint8 ucX0, uint8 ucY0, uint8 ucX1, uint8 ucY1)
{
  gcdisplay.drawLine(ucX0, ucY0, ucX1, ucY1, WHITE);
  gcdisplay.display();

  return true;
}

// EOF