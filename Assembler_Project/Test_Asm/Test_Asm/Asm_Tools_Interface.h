#pragma once

#include "Common.h"

extern "C" int Make_Sum(int one_value, int another_value);
extern "C" void Draw_Line_Horizontal(CHAR_INFO * screen_buffer, SPos pos, ASymbol symbol);
extern "C" void Draw_Line_Vertical(CHAR_INFO * screen_buffer, SPos pos, ASymbol symbol);
extern "C" void Show_Colors(CHAR_INFO * screen_buffer, SPos pos, CHAR_INFO symbol);
extern "C" void Clear_Area(CHAR_INFO *screen_buffer, SArea_Pos area_pos, ASymbol symbol);
extern "C" int Draw_Text(CHAR_INFO *screen_buffer, SText_Pos pos, const wchar_t *str);
extern "C" void Draw_Limited_Text(CHAR_INFO *screen_buffer, SText_Pos pos, const wchar_t *str, unsigned short limit);

extern "C" bool Try_Lock(int *key);

struct SFloat16;

//extern "C" void Test_Command(char *left_values, char *right_values, short *result);
//extern "C" void Test_Command(short *left_values, short *right_values, short *result);
//extern "C" void Test_Command(int *left_singles, int *right_singles, int *result_singles);
extern "C" void Test_Command(float *left_singles, float *right_singles, SFloat16 *result_singles);
//extern "C" void Test_Command(double *left_singles, double *right_singles, double *result_singles);
//extern "C" void Test_Command(char *left_singles, char *right_singles, char *result_singles);
//extern "C" void Test_Command(int *left_singles, int *right_singles, long long *result_singles);

