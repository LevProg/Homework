#pragma once
#include "framework.h"

enum keys{
    up = 'w',
    left = 'a',
    down = 's',
    right = 'd'};
void DrawField(HDC hdc);
void Click(WPARAM wParam, HWND hWnd);
void Move(HWND hWnd);