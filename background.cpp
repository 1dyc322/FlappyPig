#include "splashkit.h"
#include "flappy_pig.h"
bool firstbackground = 1;
background_data new_background()
{
    background_data result;
    result.name = bitmap_named("background");
    if (firstbackground == 1)
    {
        result.x = 0;
        firstbackground = 0;
    } else {
        result.x = 390;
    }

    result.y = 0;
    return result;
}

void check_background(bool newgame)
{
    if (newgame == 0)
    {
        firstbackground = 1;
    }
}

void draw_background(const background_data &background_to_draw)
{
    bitmap to_draw;
    to_draw = bitmap_named("background");
    draw_bitmap(to_draw,background_to_draw.x,background_to_draw.y);
}


void update_background(background_data &background)
{
    background.x = background.x - 2;
}