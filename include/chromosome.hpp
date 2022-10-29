#pragma once

#include <string>

struct chromosome {
    double heuristic_lesser;
    double heuristic_greater;
    double snake_midpoint;
    double snake_multiplier;
    double zombie_midpoint;
    double zombie_multiplier;
    double barrier_midpoint;
    double barrier_multiplier;

    std::string to_csv_string();
    void randomize();
};