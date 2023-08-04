#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <algorithm>
#include "Game.h"
#include <iostream>
#include "nums.h"

#define RECTSIZE 40
#define RADIUS 50
#define WHITE 0xffffff
#define BLACK 0x000000


//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

int direction;
bool rectCatch;
bool rectPlay;
int trend;
int score;



// initialize game data in this function
void initialize()
{
    direction = 1;
    rectCatch = 0;
    rectPlay = 0;
    score = 0;


}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    if (is_key_pressed(VK_ESCAPE))
        schedule_quit_game();

    if (is_key_pressed(VK_SPACE))
        direction *= -1;

}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
    // clear backbuffer
    FillWin();
    FillCircle(383, 513, 200, 0x8A9DB4);
    Craze(383, 513, 200, direction);

    //memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
}

// free game data in this function
void finalize()
{
}

void FillCircle(uint32_t x, uint32_t y, uint32_t r, uint32_t color)
{
    for (int rad = r; rad >= 0; rad--) {

        // stroke a circle
        for (double i = 0; i <= 3.1415926535 * 2; i += 0.001) {

            int pX = x + rad * cos(i);
            int pY = y + rad * sin(i);

            buffer[pX][pY] = color;

        }
    }
}

void FillWin()
{
    for (size_t i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (size_t j = 0; j < SCREEN_WIDTH; j++)
        {
            buffer[i][j] = 0x94A9C1;
        }
    }
}

void Craze(uint32_t x, uint32_t y, uint32_t r, int32_t direction)
{

    static double angle1 = 0;

    angle1 += 0.1 * direction;  // or some other value.  Higher numbers = circles faster

    double x1 = cos(angle1) * r;
    double y1 = sin(angle1) * r;

    x1 += x;
    y1 += y;

    FillCircle((int)x1, (int)y1, RADIUS, WHITE);

    static double angle2 = 600;

    angle2 += 0.1 * direction;  // or some other value.  Higher numbers = circles faster

    double x2 = cos(angle2) * r;
    double y2 = sin(angle2) * r;

    x2 += x;
    y2 += y;

    FillCircle((int)x2, (int)y2, RADIUS, WHITE);


    static int cx;
    static int cy;
    static int color2;

    if (!rectPlay)
    {
        cx = 1 + rand() % SCREEN_WIDTH - 1;
        cy = SCREEN_HEIGHT;

        if (cx < SCREEN_HEIGHT / 3)
            trend = 1;
        else if (cx < (SCREEN_HEIGHT / 3) * 2 && cx > SCREEN_HEIGHT / 3)
            trend = 2;
        else if (cx < SCREEN_HEIGHT && cx >(SCREEN_HEIGHT / 3) * 2)
            trend = 3;

        if (!((0 + rand() % 10) % 2))
            color2 = BLACK;
        else
            color2 = WHITE;

        rectPlay = true;

    }
    else
    {
        if (trend == 1)
            cx += 10;
        if (trend == 3)
            cx -= 10;

        cy -= 10;
    }




    FillRect(cx, cy, RECTSIZE, RECTSIZE, color2);

    int dx = (cy - 25) - x1;
    int dy = (cx + 25) - y1;
    int multi = dx * dx + dy * dy;


    if (multi <= RADIUS * RADIUS)
    {
        rectPlay = false;
        if (color2 == BLACK)
            schedule_quit_game();
        score++;
    }


    dx = (cy - 25) - x2;
    dy = (cx + 25) - y2;
    multi = dx * dx + dy * dy;

    if (multi <= RADIUS * RADIUS)
    {
        rectPlay = false;
        if (color2 == BLACK)
            schedule_quit_game();
        score++;
    }

    int first = score / 10;
    int second = score - first * 10;


    switch (first)
    {
    case 1: DrawNums(40, num1);
        break;
    case 2:DrawNums(45, num2);
        break;
    case 3:DrawNums(45, num3);
        break;
    case 4:DrawNums(45, num4);
        break;
    case 5:DrawNums(45, num5);
        break;
    case 6:DrawNums(45, num6);
        break;
    case 7:DrawNums(45, num7);
        break;
    case 8:DrawNums(45, num8);
        break;
    case 9:DrawNums(45, num9);
        break;
    case 0: DrawNums(45, num0);
        break;
    default:
        break;
    }

    switch (second)
    {
    case 1: DrawNums(20, num1);
        break;
    case 2:DrawNums(20, num2);
        break;
    case 3:DrawNums(20, num3);
        break;
    case 4:DrawNums(20, num4);
        break;
    case 5:DrawNums(20, num5);
        break;
    case 6:DrawNums(20, num6);
        break;
    case 7:DrawNums(20, num7);
        break;
    case 8:DrawNums(20, num8);
        break;
    case 9:DrawNums(20, num9);
        break;
    case 0:DrawNums(20, num0);
        break;
    default:
        break;
    }




}

void FillRect(int32_t x, int32_t y, int32_t h, int32_t w, int32_t color)
{
    if (x >= SCREEN_WIDTH - 50 || y <= 0 || x <= 0)
    {
        rectPlay = false;
        return;
    }

    for (size_t i = y - h; i <= y; i++)
    {
        for (size_t k = x; k <= x + w; k++)
        {
            buffer[i][k] = color;
        }
    }
}

void DrawNums(int32_t pos, uint32_t num[][20])
{

    for (size_t i = 20, j = 0; i < 40; i++, j++)
    {
        for (size_t k = SCREEN_WIDTH - pos, c = 0; k < SCREEN_WIDTH; k++, c++)
        {
            if (c < 20)
                buffer[i][k] = num[j][c];
        }
    }

}