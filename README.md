# MineSweeper
 This project is made by STM32f746g_DISCOVERY
## Main file
>"main.c" is still needed, but most code is not write there, we will write in "STenWin/APP/*DLG.c".
<br>The main reason is that we have some page want to change each other.
<br>This project should use two page, so we have two file named "*DLG.c".

## Page discription
- BOMBDLG.c : This file is used to display the Minesweeper gaming graph, and reponse by click
- WindowDLG.c : This file shows the number keyboard and let user input how many mines that user wants.

## Using function
- LCD
- Touch Screen
- STemWin

## reference
http://news.eeworld.com.cn/mcu/ic500782.html (STemWin)