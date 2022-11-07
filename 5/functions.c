#include "framework.h"
#include "Windowsx.h"
#include "functions.h"
#define TRACKLEN 30
#define INTENSITY 0.3
#define STARTPT { 200,200 }

POINT pt = STARTPT;
int direction = 0;
float speed = 3;
POINT pastPt[TRACKLEN] = { STARTPT };
wchar_t msg[5];

void Move(HWND hWnd) {
    if ((pt.y > 0 && pt.y < 400) && (pt.x > 0 && pt.x < 400)) {
        if (msg[0] == up && pt.y > 5) pt.y -= speed;
        if (msg[0] == left && pt.x > 5) pt.x -= speed;
        if (msg[0] == down && pt.y < 395) pt.y += speed;
        if (msg[0] == right && pt.x < 395) pt.x += speed;
    }
    pastPt[0] = pt;
    for (int i = TRACKLEN-1; i > 0; i--) {
        pastPt[i] = pastPt[i - 1];
    }
    Sleep(10);
    InvalidateRect(hWnd, NULL, FALSE);
}
void Click(WPARAM wParam, HWND hWnd) {
    HDC hdc = GetDC(hWnd);
    msg[0] = (wchar_t)wParam;
}

void DrawField(HDC hdc) {
    HBITMAP hbmMem;
    HANDLE hOld;
    HDC hdcMem;
    HPEN hBluePen, hWhitePen;
    HBRUSH hBlueBrush;
    hdcMem = CreateCompatibleDC(hdc);
    hbmMem = CreateCompatibleBitmap(hdc, 400, 400);
    hOld = SelectObject(hdcMem, hbmMem);

    hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
    hBluePen = CreatePen(PS_SOLID, 5, RGB(0, 0, 255));

    if (hdcMem) {
        SelectObject(hdcMem,hBlueBrush);
        SelectObject(hdcMem, hBluePen);
        Rectangle(hdcMem, 0, 0, 400, 400);
        for (int i = 4; i < TRACKLEN; i++) {
            hWhitePen = CreatePen(PS_DASH, 5, RGB(255/(i* INTENSITY), 255 / (i * INTENSITY), 255));
            SelectObject(hdcMem, hWhitePen);
            Rectangle(hdcMem, pastPt[i].x, pastPt[i].y, pastPt[i].x + 5, pastPt[i].y + 5);
            DeleteObject(hWhitePen);
        }
        hWhitePen = CreatePen(PS_DASH, 5, RGB(255, 255, 255));
        SelectObject(hdcMem, hWhitePen);
        Rectangle(hdcMem, pt.x, pt.y, pt.x + 5, pt.y + 5);
        BitBlt(hdc, 0, 0, 400, 400, hdcMem, 0, 0, SRCCOPY);
        SelectObject(hdcMem, hOld);
        DeleteObject(hbmMem);
        DeleteDC(hdcMem);
        DeleteObject(hBluePen);
        DeleteObject(hBlueBrush);
        DeleteObject(hWhitePen);
    }
}