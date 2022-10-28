#pragma once

#include <chromosome.hpp>

#include <string>

struct game {
    double ave_score;
    double ave_time;
    double longest;
    double fitness;

    void chromosome_file_write(std::string filename, chromosome* c);
    void chromosome_file_read(std::string filename, chromosome* c);
    void execute(std::string game_id, chromosome* c);
    void calc_fitness();
    std::string to_csv_string();
};