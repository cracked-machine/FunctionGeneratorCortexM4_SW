/**
  ******************************************************************************
  * @file    basic_gui.c
  * @author  MCD Application Team
  * @brief   This file includes the basic functionalities to drive LCD
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

#include "STMBasicGui.h"
#include "ILI9341_STM32_Driver.h"
#include "ILI9341_GFX.h"

/** @defgroup BASIC_GUI_Private_Types BASIC GUI Private Types
  * @{
  */
typedef struct
{
  uint32_t x1;
  uint32_t y1;
  uint32_t x2;
  uint32_t y2;
  uint32_t x3;
  uint32_t y3;
}Triangle_Positions_t;

/**
  * @brief  Draws an uni-line (between two points) in currently active layer.
  * @param  Xpos1 Point 1 X position
  * @param  Ypos1 Point 1 Y position
  * @param  Xpos2 Point 2 X position
  * @param  Ypos2 Point 2 Y position
  * @param  Color Draw color
  */
void GUI_DrawLine(uint32_t Xpos1, uint32_t Ypos1, uint32_t Xpos2, uint32_t Ypos2, uint32_t Color)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
  curpixel = 0;
  int32_t x_diff, y_diff;

  x_diff = Xpos2 - Xpos1;
  y_diff = Ypos2 - Ypos1;

  deltax = ABS(x_diff);         /* The absolute difference between the x's */
  deltay = ABS(y_diff);         /* The absolute difference between the y's */
  x = Xpos1;                       /* Start x off at the first pixel */
  y = Ypos1;                       /* Start y off at the first pixel */

  if (Xpos2 >= Xpos1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }

  if (Ypos2 >= Ypos1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }

  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }

  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    ILI9341_Draw_Pixel(x, y, Color);   /* Draw the current pixel */
    num += numadd;                            /* Increase the numerator by the top of the fraction */
    if (num >= den)                           /* Check if numerator >= denominator */
    {
      num -= den;                             /* Calculate the new numerator value */
      x += xinc1;                             /* Change the x as appropriate */
      y += yinc1;                             /* Change the y as appropriate */
    }
    x += xinc2;                               /* Change the x as appropriate */
    y += yinc2;                               /* Change the y as appropriate */
  }
}


/**
  * @brief  Draws an poly-line (between many points) in currently active layer.
  * @param  Points      Pointer to the points array
  * @param  PointCount  Number of points
  * @param  Color       Draw color
  */
void GUI_DrawPolygon(pPoint Points, uint32_t PointCount, uint32_t colour)
{
  int16_t x_pos = 0, y_pos = 0;

  if(PointCount < 2)
  {
    return;
  }

  GUI_DrawLine(Points->X, Points->Y, (Points+PointCount-1)->X, (Points+PointCount-1)->Y, colour);

  while(--PointCount)
  {
    x_pos = Points->X;
    y_pos = Points->Y;
    Points++;
    GUI_DrawLine(x_pos, y_pos, Points->X, Points->Y, colour);
  }
}

/**
  * @brief  Draws an ellipse on LCD in currently active layer.
  * @param  Xpos    X position
  * @param  Ypos    Y position
  * @param  XRadius Ellipse X radius
  * @param  YRadius Ellipse Y radius
  * @param  Color   Draw color
  */
void GUI_DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius, uint32_t Color)
{
  int x_pos = 0, y_pos = -YRadius, err = 2-2*XRadius, e2;
  float k = 0, rad1 = 0, rad2 = 0;

  rad1 = XRadius;
  rad2 = YRadius;

  k = (float)(rad2/rad1);

  do
  {
    ILI9341_Draw_Pixel((Xpos-(uint32_t)(x_pos/k)), (Ypos + y_pos), Color);
    ILI9341_Draw_Pixel((Xpos+(uint32_t)(x_pos/k)), (Ypos + y_pos), Color);
    ILI9341_Draw_Pixel((Xpos+(uint32_t)(x_pos/k)), (Ypos - y_pos), Color);
    ILI9341_Draw_Pixel((Xpos-(uint32_t)(x_pos/k)), (Ypos - y_pos), Color);

    e2 = err;
    if (e2 <= x_pos)
    {
      err += ++x_pos*2+1;
      if (-y_pos == x_pos && e2 <= y_pos) e2 = 0;
    }
    if (e2 > y_pos)
    {
      err += ++y_pos*2+1;
    }
  }while (y_pos <= 0);
}




/**
  * @brief  Draws a full circle in currently active layer.
  * @param  Xpos   X position
  * @param  Ypos   Y position
  * @param  Radius Circle radius
  * @param  Color  Draw color
  */
void GUI_FillCircle(uint32_t Xpos, uint32_t Ypos, uint32_t Radius, uint32_t Color)
{
  int32_t   decision;  /* Decision Variable */
  uint32_t  current_x; /* Current X Value */
  uint32_t  current_y; /* Current Y Value */

  decision = 3 - (Radius << 1);

  current_x = 0;
  current_y = Radius;

  while (current_x <= current_y)
  {
    if(current_y > 0)
    {
      if(current_y >= Xpos)
      {
        ILI9341_Draw_Horizontal_Line(0, Ypos + current_x, 2*current_y - (current_y - Xpos), Color);
        ILI9341_Draw_Horizontal_Line(0, Ypos - current_x, 2*current_y - (current_y - Xpos), Color);
      }
      else
      {
        ILI9341_Draw_Horizontal_Line(Xpos - current_y, Ypos + current_x, 2*current_y, Color);
        ILI9341_Draw_Horizontal_Line(Xpos - current_y, Ypos - current_x, 2*current_y, Color);
      }
    }

    if(current_x > 0)
    {
      if(current_x >= Xpos)
      {
        ILI9341_Draw_Horizontal_Line(0, Ypos - current_y, 2*current_x - (current_x - Xpos), Color);
        ILI9341_Draw_Horizontal_Line(0, Ypos + current_y, 2*current_x - (current_x - Xpos), Color);
      }
      else
      {
        ILI9341_Draw_Horizontal_Line(Xpos - current_x, Ypos - current_y, 2*current_x, Color);
        ILI9341_Draw_Horizontal_Line(Xpos - current_x, Ypos + current_y, 2*current_x, Color);
      }
    }
    if (decision < 0)
    {
      decision += (current_x << 2) + 6;
    }
    else
    {
      decision += ((current_x - current_y) << 2) + 10;
      current_y--;
    }
    current_x++;
  }

  ILI9341_Draw_Hollow_Circle(Xpos, Ypos, Radius, Color);
}

/**
  * @brief  Fills a triangle (between 3 points).
  * @param  Positions  pointer to riangle coordinates
  * @param  Color      Draw color
  */
static void FillTriangle(Triangle_Positions_t *Positions, uint32_t Color)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0,
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0,
  curpixel = 0;
  int32_t x_diff, y_diff;

  x_diff = Positions->x2 - Positions->x1;
  y_diff = Positions->y2 - Positions->y1;

  deltax = ABS(x_diff);         /* The absolute difference between the x's */
  deltay = ABS(y_diff);         /* The absolute difference between the y's */
  x = Positions->x1;                       /* Start x off at the first pixel */
  y = Positions->y1;                       /* Start y off at the first pixel */

  if (Positions->x2 >= Positions->x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }

  if (Positions->y2 >= Positions->y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }

  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }

  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    GUI_DrawLine(x, y, Positions->x3, Positions->y3, Color);

    num += numadd;              /* Increase the numerator by the top of the fraction */
    if (num >= den)             /* Check if numerator >= denominator */
    {
      num -= den;               /* Calculate the new numerator value */
      x += xinc1;               /* Change the x as appropriate */
      y += yinc1;               /* Change the y as appropriate */
    }
    x += xinc2;                 /* Change the x as appropriate */
    y += yinc2;                 /* Change the y as appropriate */
  }
}


/**
  * @brief  Draws a full poly-line (between many points) in currently active layer.
  * @param  Points     Pointer to the points array
  * @param  PointCount Number of points
  * @param  Color      Draw color
  */
void GUI_FillPolygon(pPoint Points, uint32_t PointCount, uint32_t Color)
{
  int16_t X = 0, Y = 0, X2 = 0, Y2 = 0, x_center = 0, y_center = 0, x_first = 0, y_first = 0, pixel_x = 0, pixel_y = 0, counter = 0;
  uint32_t  image_left = 0, image_right = 0, image_top = 0, image_bottom = 0;
  Triangle_Positions_t positions;

  image_left = image_right = Points->X;
  image_top= image_bottom = Points->Y;

  for(counter = 1; counter < PointCount; counter++)
  {
    pixel_x = POLY_X(counter);
    if(pixel_x < image_left)
    {
      image_left = pixel_x;
    }
    if(pixel_x > image_right)
    {
      image_right = pixel_x;
    }

    pixel_y = POLY_Y(counter);
    if(pixel_y < image_top)
    {
      image_top = pixel_y;
    }
    if(pixel_y > image_bottom)
    {
      image_bottom = pixel_y;
    }
  }

  if(PointCount < 2)
  {
    return;
  }

  x_center = (image_left + image_right)/2;
  y_center = (image_bottom + image_top)/2;

  x_first = Points->X;
  y_first = Points->Y;

  while(--PointCount)
  {
    X = Points->X;
    Y = Points->Y;
    Points++;
    X2 = Points->X;
    Y2 = Points->Y;
    positions.x1 = X;
    positions.y1 = Y;
    positions.x2 = X2;
    positions.y2 = Y2;
    positions.x3 = x_center;
    positions.y3 = y_center;
    FillTriangle(&positions, Color);

    positions.x2 = x_center;
    positions.y2 = y_center;
    positions.x3 = X2;
    positions.y3 = Y2;
    FillTriangle(&positions, Color);

    positions.x1 = x_center;
    positions.y1 = y_center;
    positions.x2 = X2;
    positions.y2 = Y2;
    positions.x3 = X;
    positions.y3 = Y;
    FillTriangle(&positions, Color);
  }

    positions.x1 = x_first;
    positions.y1 = y_first;
    positions.x2 = X2;
    positions.y2 = Y2;
    positions.x3 = x_center;
    positions.y3 = y_center;
    FillTriangle(&positions, Color);

    positions.x2 = x_center;
    positions.y2 = y_center;
    positions.x3 = X2;
    positions.y3 = Y2;
    FillTriangle(&positions, Color);

    positions.x1 = x_center;
    positions.y1 = y_center;
    positions.x2 = X2;
    positions.y2 = Y2;
    positions.x3 = x_first;
    positions.y3 = y_first;
    FillTriangle(&positions, Color);
}

/**
  * @brief  Draws a full ellipse in currently active layer.
  * @param  Xpos    X position
  * @param  Ypos    Y position
  * @param  XRadius Ellipse X radius
  * @param  YRadius Ellipse Y radius
  * @param  Color   Draw color
  */
void GUI_FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius, uint32_t Color)
{
  int x_pos = 0, y_pos = -YRadius, err = 2-2*XRadius, e2;
  float k = 0, rad1 = 0, rad2 = 0;

  rad1 = XRadius;
  rad2 = YRadius;

  k = (float)(rad2/rad1);

  do
  {
    ILI9341_Draw_Horizontal_Line((Xpos-(uint32_t)(x_pos/k)), (Ypos + y_pos), (2*(uint32_t)(x_pos/k) + 1), Color);
    ILI9341_Draw_Horizontal_Line((Xpos-(uint32_t)(x_pos/k)), (Ypos - y_pos), (2*(uint32_t)(x_pos/k) + 1), Color);

    e2 = err;
    if (e2 <= x_pos)
    {
      err += ++x_pos*2+1;
      if (-y_pos == x_pos && e2 <= y_pos) e2 = 0;
    }
    if (e2 > y_pos) err += ++y_pos*2+1;
  }
  while (y_pos <= 0);
}



