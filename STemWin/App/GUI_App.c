  /**
  ******************************************************************************
  * @file    GUI_App.c
  * @author  MCD Application Team
  * @brief   Simple demo drawing "Hello world"  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright © 2018 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
#include "GUI_App.h"
#include "GUI.h"

#include <stdio.h>
#include <stdlib.h>
#include "stm32746g_discovery_ts.h"
#include "ft5336.h"

#include "DIALOG.h"
extern  WM_HWIN CreateWindow(void);  
extern WM_HWIN CreateBOMB(void);
extern WM_HWIN CreateTEST_E(void);
extern WM_HWIN Createfk(void);

WM_HWIN window,bomb,test_E;
extern int digital_num;
extern int bomb_num;
extern char buff[3];
extern int mode;

extern volatile int queue[120];
extern int square_number[120];
extern int random_array[100];
extern int position_open_or_not[120];
extern int nearby_bomb;
extern int playing_click;
extern int queue_index;
extern int queue_add_index;
extern int queue_length;
extern int WinOrLoss;
extern GUI_TIMER_TIME OS_TimeMS;
char test[6];

GUI_PID_STATE TS_State;
TS_StateTypeDef  ts;

void GRAPHICS_MainTask(void) {

  /* 2- Create a Window using GUIBuilder */
	window = CreateWindow();
/* USER CODE BEGIN GRAPHICS_MainTask */

 /* User can implement his graphic application here */
  /* Hello Word example */
//    GUI_Clear();
//    GUI_SetColor(GUI_WHITE);
//    GUI_SetFont(&GUI_Font32_1);
//    GUI_DispStringAt("Hello world!", (LCD_GetXSize()-150)/2, (LCD_GetYSize()-20)/2);
   
/* USER CODE END GRAPHICS_MainTask */
  while(1)
{

if(mode == 1){
	GUI_Init();
  for(int j = 0 ; j < bomb_num ; j ++){
    GUI_Delay((unsigned)rand()%3+1);
    random_array[j] = (unsigned)rand()%120;
    for(int z = 0 ; z < j ; z ++){
      if(random_array[z] == random_array[j]){
        random_array[j] = (unsigned)rand()%120;
        j--;
      }
    }
  }
  //..............get random array........../
  for(int z = 0 ; z < 120 ; z ++){
    square_number[z] = 0;
    position_open_or_not[z] = 0;
    queue[z] = -1;
  }
  //////////////////////////////////////////////
  //set square_number with graph number of bombs, and set position_open_or_not = 1 when there is a bomb in the position
  for(int k = 0 ; k < bomb_num ; k ++){
    square_number[random_array[k]] = 10; 
    position_open_or_not[random_array[k]] = 2;
  }
  //
  //set square number with graph number with corresponding graph number
  for(int k = 0 ; k < 120 ; k ++){
    if(square_number[k] == 10){
    }
    else{
      switch(k){
        case 0:
          if(square_number[k+1] == 10){nearby_bomb++;}
          if(square_number[k+15] == 10){nearby_bomb++;}
          if(square_number[k+16] == 10){nearby_bomb++;}
        break;
        case 14:
          if(square_number[k-1] == 10){nearby_bomb++;}
          if(square_number[k+14] == 10){nearby_bomb++;}
          if(square_number[k+15] == 10){nearby_bomb++;}
        break;
        case 105:
          if(square_number[k+1] == 10){nearby_bomb++;}
          if(square_number[k-15] == 10){nearby_bomb++;}
          if(square_number[k-14] == 10){nearby_bomb++;}
        break;
        case 119:
          if(square_number[k-1] == 10){nearby_bomb++;}
          if(square_number[k-16] == 10){nearby_bomb++;}
          if(square_number[k-15] == 10){nearby_bomb++;}
        break;
        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: case 12: case 13:
          if(square_number[k-1] == 10){nearby_bomb++;}
          if(square_number[k+1] == 10){nearby_bomb++;}
          if(square_number[k+14] == 10){nearby_bomb++;}
          if(square_number[k+15] == 10){nearby_bomb++;}
          if(square_number[k+16] == 10){nearby_bomb++;}
        break;
        case 106: case 107: case 108: case 109: case 110: case 111: case 112: case 113: case 114: case 115: case 116: case 117: case 118:
          if(square_number[k-16] == 10){nearby_bomb++;}
          if(square_number[k-15] == 10){nearby_bomb++;}
          if(square_number[k-14] == 10){nearby_bomb++;}
          if(square_number[k-1] == 10){nearby_bomb++;}
          if(square_number[k+1] == 10){nearby_bomb++;}
        break;
        case 15: case 30: case 45: case 60: case 75: case 90:
          if(square_number[k-15] == 10){nearby_bomb++;}
          if(square_number[k-14] == 10){nearby_bomb++;}
          if(square_number[k+1] == 10){nearby_bomb++;}
          if(square_number[k+15] == 10){nearby_bomb++;}
          if(square_number[k+16] == 10){nearby_bomb++;}
        break;
        case 29: case 44: case 59: case 74: case 89: case 104:
          if(square_number[k-16] == 10){nearby_bomb++;}
          if(square_number[k-15] == 10){nearby_bomb++;}
          if(square_number[k-1] == 10){nearby_bomb++;}
          if(square_number[k+14] == 10){nearby_bomb++;}
          if(square_number[k+15] == 10){nearby_bomb++;}
        break;
        default:
          if(square_number[k-16] == 10){nearby_bomb++;}
          if(square_number[k-15] == 10){nearby_bomb++;}
          if(square_number[k-14] == 10){nearby_bomb++;}
          if(square_number[k-1] == 10){nearby_bomb++;}
          if(square_number[k+1] == 10){nearby_bomb++;}
          if(square_number[k+14] == 10){nearby_bomb++;}
          if(square_number[k+15] == 10){nearby_bomb++;}
          if(square_number[k+16] == 10){nearby_bomb++;}
        break;
      }
    }
    if(nearby_bomb > 0){
      square_number[k] = nearby_bomb;
    }
    else if (square_number[k] != 10){
      square_number[k] = 9;
    }
    nearby_bomb = 0;
  }
  ///////////////////////////////////////////////////
  //open the bomb_playing window
	bomb = CreateBOMB();
	mode = 0;
}

if(WinOrLoss == 0){
static TS_StateTypeDef prev_state; 
 BSP_TS_GetState(&ts);                
 TS_State.Pressed = ts.touchDetected; 
  if ((prev_state.touchDetected != ts.touchDetected))
 {
  prev_state.touchDetected = ts.touchDetected;
  // Check touch variations 
  if ((ts.touchX[0] != 0) && (ts.touchY[0] != 0)){
    prev_state.touchX[0] = ts.touchX[0];
    prev_state.touchY[0] = ts.touchY[0];
  }
  TS_State.Layer = 0;
  TS_State.x = prev_state.touchX[0];
  TS_State.y = prev_state.touchY[0];
  GUI_TOUCH_StoreStateEx(&TS_State);
	}
    GUI_Delay(100);
	for(int a = 0 ; a < TS_State.x ; a ++){
		for(int b = 0 ; b < TS_State.y ; b ++){
			rand();
		}
	}
}
/*GUI_PID_STATE TS_State;
TS_StateTypeDef  ts;
static TS_StateTypeDef prev_state; 
 BSP_TS_GetState(&ts);                
 TS_State.Pressed = ts.touchDetected; 
  if ((prev_state.touchDetected != ts.touchDetected))
 {
  prev_state.touchDetected = ts.touchDetected;
  // Check touch variations 
  if ((ts.touchX[0] != 0) && (ts.touchY[0] != 0)){
    prev_state.touchX[0] = ts.touchX[0];
    prev_state.touchY[0] = ts.touchY[0];
  }
  TS_State.Layer = 0;
  TS_State.x = prev_state.touchX[0];
  TS_State.y = prev_state.touchY[0];
  GUI_TOUCH_StoreStateEx(&TS_State);
	}
    GUI_Delay(100);*/
}
}

/*************************** End of file ****************************/
