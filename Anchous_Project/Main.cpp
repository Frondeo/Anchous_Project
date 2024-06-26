﻿// Anchous_Project.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Main.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


//---------------------------------------THREE----------------------------------------------

const int Gl_scale = 3;
const int Brick_Width = 15;
const int Brick_Hight = 7;

const int Cell_Width = 16;
const int Cell_Height = 8;

const int Level_X_Offset = 8;
const int Level_Y_Offset = 6;




//------------------------------------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ANCHOUSPROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ANCHOUSPROJECT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


//------------------------------------------------------------------------------------------
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ANCHOUSPROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = CreateSolidBrush(RGB(204, 127, 27));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ANCHOUSPROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


//------------------------------------------------------------------------------------------
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable
   
   RECT window_rect;
   window_rect.left = 0;
   window_rect.top = 0;
   window_rect.right = 320 * 3;
   window_rect.bottom = 200 * 3;

   AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW, TRUE); // корректирует структуру окна пользователя
     
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      50, 50, window_rect.right - window_rect.left, window_rect.bottom - window_rect.top, nullptr, nullptr, hInstance, nullptr);

   if (hWnd == 0)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
//----------------------------------------TWO---------------------------------------------

void Draw_Brick(HDC hdc, int x, int y, bool is_green)
{
 //перенеси в область глобальных констант
 /*  const int Gl_scale = 3;
   const int Brick_Width = 15;
   const int Brick_Hight = 7;*/

   HPEN pen;
   HBRUSH brush;

   if (is_green)
   {
      pen = CreatePen(PS_SOLID, 0, RGB(117, 249, 77));
      brush = CreateSolidBrush(RGB(117, 249, 77));

      /*SelectObject(hdc, green_pen);
      SelectObject(hdc, green_brush);*/

      //Rectangle(hdc, x * 3, y * 3, (x + 15) * 3, (y + 7) * 3);
   }
   else
   {
      pen = CreatePen(PS_SOLID, 0, RGB(0, 35, 245));
      brush = CreateSolidBrush(RGB(0, 35, 245));

      /*SelectObject(hdc, blue_pen);
      SelectObject(hdc, blue_brush);*/

      //Rectangle(hdc, x * 3, y * 3, (x + 15) * 3, (y + 7) * 3);
   }

   SelectObject(hdc, pen);
   SelectObject(hdc, brush);

   Rectangle(hdc, x * Gl_scale, y * Gl_scale, (x + Brick_Width) * Gl_scale, (y + Brick_Hight) * Gl_scale);
}

//---------------------------------------ONE----------------------------------------------
void Draw_Frame(HDC hdc) //инициализация функции
{
   //HPEN red_pen = CreatePen(PS_SOLID, 0, RGB(0, 35, 245));
   //HBRUSH red_brush = CreateSolidBrush(RGB(0, 35, 245));

   //SelectObject(hdc, red_pen);
   //SelectObject(hdc, red_brush);
   //Rectangle (hdc, 8*3, 6*3, (8+15)*3, (6+7)*3);

   //HPEN blue_pen = CreatePen(PS_SOLID, 0, RGB(117, 249, 77));
   //HBRUSH blue_brush = CreateSolidBrush(RGB(117, 249, 77));

   //SelectObject(hdc, blue_pen);
   //SelectObject(hdc, blue_brush);
   //Rectangle(hdc, 8 * 3, (6 + 8) * 3, (8 + 15) * 3, (6 + 7 + 8) * 3);

   int i;
   int j;

   //---------------------------------------FOUTH-------------------------------------------
   for(i = 0; i < 14; i++)
   {
      for (j = 0; j < 19; j++)
      {
         Draw_Brick(hdc, Level_X_Offset + j * Cell_Width, Level_Y_Offset + i * Cell_Height, true);
      }
   }

   //for (j = 0; j < 19; j++)
   //{
   //   //Draw_Brick(hdc, 8 + i * (Brick_Width + 1), 6, false);
   //   //Draw_Brick(hdc, 8 + i * (Brick_Width + 1), 6 + 8, true);
   //   Draw_Brick(hdc, 8 + i * Cell_Width, 6, false);
   //   Draw_Brick(hdc, 8 + i * Cell_Width, 6 + Cell_Height, true);
   //}
}


//------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            Draw_Frame(hdc); //вызов функции
            

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


//------------------------------------------------------------------------------------------
// Message handler for about box.
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
