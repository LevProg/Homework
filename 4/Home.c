#include "framework.h"
#include "Home.h"
#include "Windowsx.h"
#include "stdio.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HOME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HOME));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HOME));
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HOME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      0, 0, 416 , 420 +GetSystemMetrics(SM_CYMENUSIZE)+ GetSystemMetrics(SM_CYMENU), NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

int isButtonWasDown = 0;
POINT pt1;
POINT pt2;
void Draw(HDC hdc) {
    HPEN hBlackPen, hColorPen, hOldPen;
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
void ButtonManager(HWND hWnd,LPARAM lParam) {
    HDC hdc = GetDC(hWnd);
    Draw(hdc);
    HPEN hBlackPen, hColorPen, hOldPen;
    HBRUSH hBlackBrush, hWhiteBrush;

    hWhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
    hBlackBrush = CreateSolidBrush(RGB(0, 0, 0));
    hBlackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

    if (isButtonWasDown == 0) {
        isButtonWasDown = 1;
        pt1.x = GET_X_LPARAM(lParam) / 50;
        pt1.y = GET_Y_LPARAM(lParam) / 50;
    }
    else {
        pt2.x = GET_X_LPARAM(lParam) / 50;
        pt2.y = GET_Y_LPARAM(lParam) / 50;
        Draw(hdc);
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

        }
        isButtonWasDown = 0;
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    HPEN hColorPen;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_LBUTTONDOWN:
        {   
            ButtonManager(hWnd, lParam);
        }
        break;
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
            Draw(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
