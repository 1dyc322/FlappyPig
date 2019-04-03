#include "splashkit.h"
#include "flappy_pig.h"
bool ended = 0;
int speed = 2;

player_data new_player()
{
    player_data result; //return data 
    result.name = bitmap_named("player"); // assign player's image name
    result.x = 100; //player’s x coordinate
    result.y = 50; //player’s y coordinate
    result.player_animation = create_animation("players","fly" ); // assign player’s animation 
    return result; //return the data
}



bool player_hit_pipe(const player_data &player, const pipe_data &pipe)
{
    bitmap player_bmp = bitmap_named("player");
    int player_cell = animation_current_cell(player.player_animation);

    bitmap pipe_bmp = bitmap_named("pipe");
    bitmap pipe_bmp2 = bitmap_named("pipe2");
    if (bitmap_collision(player_bmp,player_cell,player.x,player.y,pipe_bmp,0,pipe.x,pipe.y) || 
    bitmap_collision(player_bmp,player_cell,player.x,player.y,pipe_bmp2,0,pipe.x,pipe.y)) return 1;
}

void check_game(bool theend)
{
    if (theend)
    {
        ended = 1;
        speed = 10;
    } else {
        ended = 0;
        speed = 2;
    }
}

void draw_player(const player_data &player)
{
    draw_bitmap("player",player.x,player.y,option_with_animation(player.player_animation));
    
}
void update_player(player_data &player)
{
    update_animation(player.player_animation);
    player.y += speed;
}

void handle_input( player_data &player)
{
    if (ended == 0)
    {
        if ( key_typed(SPACE_KEY)) player.y -= 35 ;
    }
    
}