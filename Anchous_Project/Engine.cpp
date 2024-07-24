#include "Engine.h"


enum EBrick_Type
{
   EBT_None, // None = 7,
   EBT_Red,
   EBT_Blue
};

//int A = EBT_Red;

HPEN Highlight_Pen, Brick_Red_Pen, Brick_Blue_Pen, Platform_Circle_Pen, Platform_Inner_Pen;
HBRUSH  Brick_Red_Brush, Brick_Blue_Brush, Platform_Circle_Brush, Platform_Inner_Brush;

const int Gl_scale = 3;
const int Brick_Width = 15;
const int Brick_Hight = 7;

const int Cell_Width = 16;
const int Cell_Height = 8;

const int Level_X_Offset = 8;
const int Level_Y_Offset = 6;


int Circle_Size = 7;
int Inner_Width = 21;

int Level_01[14][12] =
{
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
   2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
//------------------------------------------------------------------------------------------

void Create_Pen_Brush(unsigned char r, unsigned char g, unsigned char b, HPEN &pen, HBRUSH &brush)
{
   // так как нужно вернуть более одного параметра то используем & 
   pen = CreatePen(PS_SOLID, 0, RGB(r, g, b)); // передача значения по параметру &
   brush = CreateSolidBrush(RGB(r, g, b)); // передача значения по параметру &
}

//------------------------------------------------------------------------------------------
void Init() //Настройка карандашей и кистей
{
   Highlight_Pen = CreatePen(PS_SOLID, 0, RGB(255, 255, 255));
   //Brick_Red_Pen = CreatePen(PS_SOLID, 0, RGB(255, 85, 85));
   //Brick_Red_Brush = CreateSolidBrush(RGB(255, 85, 85));
   Create_Pen_Brush(255, 85, 85, Brick_Red_Pen, Brick_Red_Brush);

   //Brick_Blue_Pen = CreatePen(PS_SOLID, 0, RGB(0, 35, 245));
   //Brick_Blue_Brush = CreateSolidBrush(RGB(0, 35, 245));
   Create_Pen_Brush(0, 35, 245, Brick_Blue_Pen, Brick_Blue_Brush);

   //Platform_Circle_Pen = CreatePen(PS_SOLID, 0, RGB(151, 0, 0));
   //Platform_Circle_Brush = CreateSolidBrush(RGB(151, 0, 0));
   Create_Pen_Brush(151, 0, 0, Platform_Circle_Pen, Platform_Circle_Brush);

   //Platform_Inner_Pen = CreatePen(PS_SOLID, 0, RGB(0, 128, 192));
   //Platform_Inner_Brush = CreateSolidBrush(RGB(0, 128, 192));
   Create_Pen_Brush(0, 128, 192, Platform_Inner_Pen, Platform_Inner_Brush);
}
//------------------------------------------------------------------------------------------

void Draw_Brick(HDC hdc, int x, int y, EBrick_Type brick_type)
{
   //создание карандаша и кисти внутри функции ограничено ОС !!!
   //Для этого выносим их в область глобальных определений
   //Все компоненты цвета делаем кратным 16

   HPEN pen;
   HBRUSH brush;

   switch (brick_type)
   {
   case EBT_None:
      return;

   case EBT_Red:
      pen = Brick_Red_Pen;
      brush = Brick_Red_Brush;
      break;

   case EBT_Blue:
      pen = Brick_Blue_Pen;
      brush = Brick_Blue_Brush;
      break;

   default:
      return;
   }
   //рисуем кирпичи
   SelectObject(hdc, pen);
   SelectObject(hdc, brush);

   RoundRect(hdc, x * Gl_scale, y * Gl_scale, (x + Brick_Width) * Gl_scale, (y + Brick_Hight) * Gl_scale, 2 * Gl_scale, 2 * Gl_scale);
}
//------------------------------------------------------------------------------------------

void Draw_Level(HDC hdc) //рисуем вывод всех кирпичей
{
   int i;
   int j;


   for (i = 0; i < 14; i++)
   {
      for (j = 0; j < 12; j++)
      {
         Draw_Brick(hdc, Level_X_Offset + j * Cell_Width, Level_Y_Offset + i * Cell_Height, (EBrick_Type)Level_01[i][j]);
      }
   }
}
//------------------------------------------------------------------------------------------

void Draw_Platform(HDC hdc, int x, int y)
{
  //рисуем шарики
   SelectObject(hdc, Platform_Circle_Pen);
   SelectObject(hdc, Platform_Circle_Brush);

   Ellipse(hdc, x * Gl_scale, y * Gl_scale, (x + Circle_Size) * Gl_scale, (y + Circle_Size) * Gl_scale);
   Ellipse(hdc, (x + Inner_Width) * Gl_scale, y * Gl_scale, (x + Circle_Size + Inner_Width) * Gl_scale, (y + Circle_Size) * Gl_scale);
   //рисуем блик
   SelectObject(hdc, Highlight_Pen);

   Arc(hdc, (x + 1)* Gl_scale,(y + 1) * Gl_scale, (x + Circle_Size - 1) * Gl_scale, (y + Circle_Size - 1) * Gl_scale,
      (x + 1 + 1) * Gl_scale, (y + 1) * Gl_scale, (x + 1) * Gl_scale, (y + 1 + 2) * Gl_scale);
   //рисуем среднюю часть
   SelectObject(hdc, Platform_Inner_Pen);
   SelectObject(hdc, Platform_Inner_Brush);

   RoundRect(hdc, (x + 4) * Gl_scale, (y + 1) * Gl_scale, (x + 4 + Inner_Width - 1) * Gl_scale, (y + 1 + 5) * Gl_scale, 3 * Gl_scale, 3 * Gl_scale);
}
//------------------------------------------------------------------------------------------

void Draw_Frame(HDC hdc)
{
   //рисуем уровень
   Draw_Level(hdc);
   Draw_Platform(hdc, 50, 100);
}
//------------------------------------------------------------------------------------------
