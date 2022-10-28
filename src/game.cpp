#include <game.hpp>
#include <chromosome.hpp>
#include <pop.hpp>

#include <cstdio>
#include <string>
#include <thread>

#define GAME_LENGTH 30

void game::chromosome_file_write(std::string filename, chromosome* c) {
    //Save to chromosome file
    FILE* file = fopen(filename.c_str(), "w+");

    std::fprintf(file, "mew_heuristic_greater: %lf\n", c->heuristic_greater);
    std::fprintf(file, "mew_heuristic_lesser: %lf\n", c->heuristic_lesser);
    std::fprintf(file, "mew_snake_midpoint: %lf\n", c->snake_midpoint);
    std::fprintf(file, "mew_snake_multiplier: %lf\n", c->snake_multiplier);
    std::fprintf(file, "mew_zombie_midpoint: %lf\n", c->zombie_midpoint);
    std::fprintf(file, "mew_zombie_multiplier: %lf\n", c->zombie_multiplier);
    std::fprintf(file, "mew_barrier_midpoint: %lf\n", c->barrier_midpoint);
    std::fprintf(file, "mew_barrier_multiplier: %lf\n", c->barrier_multiplier);

    std::fclose(file);
}

void game::chromosome_file_read(std::string filename, chromosome* c) {
    FILE* file = fopen(filename.c_str(), "r+");

    std::fscanf(file, "%lf", &c->heuristic_greater);
    std::fscanf(file, "%lf", &c->heuristic_lesser);
    std::fscanf(file, "%lf", &c->snake_midpoint);
    std::fscanf(file, "%lf", &c->snake_multiplier);
    std::fscanf(file, "%lf", &c->zombie_midpoint);
    std::fscanf(file, "%lf", &c->zombie_multiplier);
    std::fscanf(file, "%lf", &c->barrier_midpoint);
    std::fscanf(file, "%lf", &c->barrier_multiplier);
    std::fscanf(file, "%lf", &this->ave_time);
    std::fscanf(file, "%lf", &this->ave_score);
    std::fscanf(file, "%lf", &this->longest);

    std::fclose(file);
}

void game::execute(std::string game_id, chromosome* c) {
    /* 
    * Start the game by calling the runnable jar with the chromosome file as a argument
    * Wait for the game to finish
    * Load the data from the game back into the struct
    * Flag as complete
    */

    chromosome_file_write(game_id + ".txt", c);

    //TODO: Start runnable

    std::this_thread::sleep_for(std::chrono::milliseconds(GAME_LENGTH));
    chromosome_file_read(game_id + ".txt", c);
    this->calc_fitness();
}

void game::calc_fitness() {
    fitness = ave_score*ave_score * longest*longest*longest / ave_time ;
}

std::string game::to_csv_string() {
    std::string result = "";

    calc_fitness();

    result += std::to_string(ave_time) + ",";
    result += std::to_string(ave_score) + ",";
    result += std::to_string(longest) + ",";
    result += std::to_string(fitness);

    return result;
}