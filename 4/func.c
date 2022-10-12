#include "framework.h"
#include "Windowsx.h"
#include "functions.h"


int clicksCnt = 0;
POINT pt1;
POINT pt2;
void DrawField(HDC hdc) {
    HPEN hBlackPen;
    HBRUSH hBlackBrush, hWhiteBrush;

    hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
    hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
    hBlackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
    if (hdc) {
        SelectObject(hdc, hBlackPen);
        SelectObject(hdc, hBlackBrush);
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((i + j) % 2 == 0) {
                    SelectObject(hdc, hWhiteBrush);
                }
                else {
                    SelectObject(hdc, hBlackBrush);
                }
                Rectangle(hdc, i * 50, j * 50, (i + 1) * 50, (j + 1) * 50);
            }
        }
    }
    DeleteObject(hBlackPen);
    DeleteObject(hBlackBrush);
    DeleteObject(hWhiteBrush);
}
void HandleClick(HWND hWnd, LPARAM lParam) {
    HDC hdc = GetDC(hWnd);
    DrawField(hdc);
    HPEN hBlackPen, hColorPen;
    HBRUSH hBlackBrush, hWhiteBrush;

    hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
    hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
    hBlackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

    if (clicksCnt == 0) {
        clicksCnt = 1;
        pt1.x = GET_X_LPARAM(lParam) / 50;
        pt1.y = GET_Y_LPARAM(lParam) / 50;
    }
    else {
        pt2.x = GET_X_LPARAM(lParam) / 50;
        pt2.y = GET_Y_LPARAM(lParam) / 50;
        DrawField(hdc);
        if (hdc) {
            if (((pt1.x + pt1.y) % 2) == ((pt2.x + pt2.y) % 2)) {
                hColorPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
            }
            else {
                hColorPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
            }
            SelectObject(hdc, hColorPen);
            if ((pt1.x + pt1.y) % 2 == 0) {
                SelectObject(hdc, hWhiteBrush);
            }
            else {
                SelectObject(hdc, hBlackBrush);
            }
            Rectangle(hdc, pt1.x * 50, pt1.y * 50, (pt1.x + 1) * 50, (pt1.y + 1) * 50);
            if ((pt2.x + pt2.y) % 2 == 0) {
                SelectObject(hdc, hWhiteBrush);
            }
            else {
                SelectObject(hdc, hBlackBrush);
            }
            Rectangle(hdc, pt2.x * 50, pt2.y * 50, (pt2.x + 1) * 50, (pt2.y + 1) * 50);
            ReleaseDC(hWnd, hdc);
            DeleteObject(hColorPen);
            DeleteObject(hBlackPen);
            DeleteObject(hBlackBrush);
            DeleteObject(hWhiteBrush);
        }
        clicksCnt = 0;
    }
}
