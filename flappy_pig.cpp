#include "splashkit.h"
#include "flappy_pig.h"
using namespace std;
double score = 0; // This is the score record varible
double highest = 0; // This is the varible that record the highest score
bool gameover = 0; // Gameover, boolean, store if the game is over or not
bool stop = 0; // Stop, boolean, if it is true, will stop the game's update.


// Function that use to Create a new game. 
flappy_pig_data new_game()
{
    flappy_pig_data result; //Declare result
    result.player = new_player();  // Create a new player
    add_background(result); // Add background to the game
    add_pipe(result); // Add pipes to the game
    return result; // Return the result
}


// Procedure that resonsible to the draw game part.
void draw_game(flappy_pig_data &game)
{
    clear_screen(COLOR_BLACK); // Clear the screen each time run
    
    if (gameover == 0) // Check if the game is over if not, keep drawing game elements.
    {
    for (int i = 0; i < game.backgrounds.size() ; i++)
    {
       draw_background(game.backgrounds[i]);
    }
    for (int i = 0; i < game.pipes.size() ; i++)
    {
       draw_pipe(game.pipes[i]);
    }
    draw_player(game.player);
    draw_text("SCORE: " + to_string((int)score), COLOR_WHITE, "a", 30, 10, 10);
    } else { // if the game is over, stop drawing game element, and draw 
             // text and prompt if player want to play again.
        
        draw_bitmap(bitmap_named("background"),-80,0); // Draw an background image.
        draw_text("Game Over", COLOR_WHITE, "a", 30, 130, 150); //Draw text
        draw_text("Highest: "+to_string((int)highest), COLOR_WHITE, "a", 30, 130, 200); //Draw text
        draw_text("Press Enter to play again", COLOR_WHITE, "a", 30, 50, 250); //Draw text

        // Handle user's input, if user push enter, then will 
        // reset the game data and add the elements back.
        if (key_typed(RETURN_KEY)) 
        {   
            score = 0;
            highest = 0;
            gameover = 0;
            stop = 0;
            check_game(0); //This procedure is in player.cpp, change the fall speed to normal 
            check_background(0); //This procedure is in background.cpp, change the background image's x coordinate to 0.
            game.player = new_player(); // Create new player.
            add_background(game); // Add background to the game.
        }
    }


    refresh_screen(); // Refresh the screen
}

// Add pipe procedure
void add_pipe(flappy_pig_data &game)
{
    int y = rnd(40) * 5; // Generate random y coordinate
    
    game.pipes.push_back( new_pipe(0,0-y) ); // Create upside pipe
    game.pipes.push_back( new_pipe(1,400-y) ); // Create downside pipe
    
}

// Remove pipe procedure
void remove_pipe(vector<pipe_data> &pipes, int idx)
{
    //Get the last data from vector then remove it
    pipes[idx] = pipes[pipes.size() -1];
    pipes.pop_back();
}

// Add a new background
void add_background(flappy_pig_data &game)
{
    game.backgrounds.push_back( new_background() ); // Create a background
}

// Remove background procedure
void remove_background(vector<background_data> &backgrounds, int idx)
{
    //Get the last data from vector then remove it
    backgrounds[idx] = backgrounds[backgrounds.size() -1];
    backgrounds.pop_back();
}

// This procedure is use for update pipes
void update_pipes(vector<pipe_data> &pipes, player_data &player)
{
    vector<int> to_remove; //Create a vector for remove use.

    // If there is any pipes exist, then loop.
    for (int i = 0; i < pipes.size() ; i++)
    {
        update_pipe(pipes[i]); // Call update pipe that is in pipe.cpp

        // Check if player hit the pipe. Function is in player.cpp
        if (player_hit_pipe(player, pipes[i]))
        {
            // not allow player control the pig
            check_game(1);
            // Stop = true.
            stop = 1;
        }
        // remove pipe when it out of the screen boundary
        if (pipes[i].x < 0 )
        {
            // If pipes out of the boundary than add one score
            // Because we will have two pipes each time, so add 0.5 for each pipe
            score = score + 0.5;
            // Check if score is bigger than highest than update highest score.
            if (score > highest) highest = score;
            // Push the pipe's data to the end of vector 
            to_remove.push_back(i);
        }

    }
    // If need to remove then,
    for (int i = to_remove.size() - 1; i >= 0; i--)
    {
        // Call the remove procedure
        remove_pipe(pipes, to_remove[i]);
    }
}

// This procedure is use for update the background
void update_backgrounds(vector<background_data> &backgrounds)
{
    vector<int> to_remove; //Create a vector for remove use.
    for (int i = 0; i < backgrounds.size() ; i++)
    {
        
        update_background(backgrounds[i]); // Call update background that is in background.cpp

        // remove background when it is out of the screen boundary
        if (backgrounds[i].x < -800 )
        {
            // Push the background data to the end of the vector 
            to_remove.push_back(i);
        }
    }
    // If the remove vector is bigger or equal than 0, then
    for (int i = to_remove.size() - 1; i >= 0; i--)
    {
        // Call the remove procedure
        remove_background(backgrounds, to_remove[i]);
    }
}

// This procedure is use for update Entire game.
void update_game(flappy_pig_data &game)
{

    update_player(game.player); // Call update player procedure that is in player.cpp
    if (stop == 0) // If boolean stop is false then keep update the element. 
    {
    update_pipes(game.pipes, game.player); // call update_pipes from flappy_pig.cpp
    update_backgrounds(game.backgrounds); // call update_backgrounds from flappy_pig.cpp
    }

   // Check player's y coordinate is larger then 500
   if (game.player.y > 500)
   {
       gameover = 1; // Gameover is true
       game.backgrounds.clear(); // Release the background vector
       game.pipes.clear(); // Release the pipe vector
   }

   // Check if last background has finished.
    int lastbackground = game.backgrounds.size() - 1;  // Get the last background data from the vector
    if ((game.backgrounds[lastbackground].x < -400)) //If it's x coordinate is greater than -400
    {
        // Add a new background image to join the last background to avoid darkness.
        add_background(game); 
    }

    // Check if last pipe has finished.
    int lastpipe = game.pipes.size() - 1;  // Get the last pipe data from the vector
    //If it's x coordinate is greater than 180
    if ((game.pipes[lastpipe].x < 180))
    {
        //Add a new pipe to the game.
        add_pipe(game);
    }

}

