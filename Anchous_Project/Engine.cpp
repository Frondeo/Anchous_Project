#include "Engine.h"


enum EBrick_Type
{
   EBT_None, // None = 7,
   EBT_Red,
   EBT_Blue
};

//int A = EBT_Red;

HPEN Brick_Red_Pen, Brick_Blue_Pen;
HBRUSH  Brick_Red_Brush, Brick_Blue_Brush;

const int Gl_scale = 3;
const int Brick_Width = 15;
const int Brick_Hight = 7;

const int Cell_Width = 16;
const int Cell_Height = 8;

const int Level_X_Offset = 8;
const int Level_Y_Offset = 6;

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
void Init() //Настройка уровня на старте
{
   Brick_Red_Pen = CreatePen(PS_SOLID, 0, RGB(255, 85, 85));
   Brick_Red_Brush = CreateSolidBrush(RGB(255, 85, 85));

   Brick_Blue_Pen = CreatePen(PS_SOLID, 0, RGB(0, 35, 245));
   Brick_Blue_Brush = CreateSolidBrush(RGB(0, 35, 245));
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

   SelectObject(hdc, pen);
   SelectObject(hdc, brush);

   RoundRect(hdc, x * Gl_scale, y * Gl_scale, (x + Brick_Width) * Gl_scale, (y + Brick_Hight) * Gl_scale, 2 * Gl_scale, 2 * Gl_scale);
}
//------------------------------------------------------------------------------------------

void Draw_Level(HDC hdc) //инициализация функции вывода всех кирпичей
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

void Draw_Frame(HDC hdc)
{
   Draw_Level(hdc);
}
//------------------------------------------------------------------------------------------
