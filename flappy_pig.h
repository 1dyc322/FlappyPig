#include "splashkit.h"
#include <vector>
using namespace std;

struct player_data
{
    bitmap name;
    double x;
    double y;
    animation player_animation;
};

struct pipe_data
{
    bitmap name;
    double x;
    double y;
};

struct background_data
{
    bitmap name;
    double x;
    double y;
};


struct flappy_pig_data
{
    player_data player;
    vector<pipe_data> pipes;
    vector<background_data> backgrounds;
};

//game
flappy_pig_data new_game();
void draw_game(flappy_pig_data &game);
void update_game(flappy_pig_data &game);

//pipe
pipe_data new_pipe(bool down, int y);
void draw_pipe(const pipe_data &pipe_to_draw);
void update_pipe(pipe_data &pipe);
void add_pipe(flappy_pig_data &game);

//player
player_data new_player();
void handle_input( player_data &player);
void update_player(player_data &player);
void draw_player(const player_data &player);
bool player_hit_pipe(const player_data &player, const pipe_data &pipe);
void check_game(bool theend);


//background
background_data new_background();
void draw_background(const background_data &background_to_draw);
void update_background(background_data &background);
void add_background(flappy_pig_data &game);
void check_background(bool newgame);