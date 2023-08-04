#pragma once
#include <stdint.h>

//рисует круг 
void FillCircle(uint32_t x, uint32_t y, uint32_t r, uint32_t color);
void FillWin();
void Craze(uint32_t x, uint32_t y, uint32_t r,int32_t direction);
void FillRect(int32_t x, int32_t y, int32_t h, int32_t w, int32_t color);
void DrawNums( int32_t pos, uint32_t num[][20]);