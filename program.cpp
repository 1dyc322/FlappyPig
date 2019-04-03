#include "splashkit.h"
#include "flappy_pig.h"



void load_resources()
{
    load_resource_bundle("game_bundle", "flappy_pig.txt");

}


int main()
{
    open_window("Flappy Pig", 400, 500);
    load_resources();

    flappy_pig_data game;
    game = new_game();

    while ( not quit_requested() ) 
    {
        process_events();
        handle_input(game.player);
        update_game(game);
        draw_game(game);
    }
    return 0;
}