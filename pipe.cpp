#include "splashkit.h"
#include "flappy_pig.h"

pipe_data new_pipe(bool down, int y)
{
    pipe_data result;
    if (down)
    {
    result.name = bitmap_named("pipe");
    result.x = 400;
    result.y = y;
    } else {
    result.name = bitmap_named("pipe2");
    result.x = 400;
    result.y = y;
    }

    return result;
}

void draw_pipe(const pipe_data &pipe_to_draw)
{
    bitmap to_draw;
    to_draw = pipe_to_draw.name;
    draw_bitmap(to_draw,pipe_to_draw.x,pipe_to_draw.y);
    
}

void update_pipe(pipe_data &pipe)
{
    pipe.x = pipe.x - 2;
}
