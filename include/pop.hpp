#pragma once

#include <chromosome.hpp>
#include <game.hpp> 
#include "config.hpp"

#include <string>

struct pop {
    chromosome c;
    game games[POP_GAME_COUNT];
    game ave_game;

    pop();

    void update_ave_game();
    void start_games(int id, int gen_id);
    std::string to_csv_string(int id, int gen_id);
    void save_state(std::string filename, int id, int gen_id);
};