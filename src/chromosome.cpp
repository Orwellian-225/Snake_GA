#include <chromosome.hpp>

#include <string>

std::string chromosome::to_csv_string() {
        std::string result = "";

        result += std::to_string(heuristic_lesser) + ",";
        result += std::to_string(heuristic_greater) + ",";
        result += std::to_string(snake_midpoint) + ",";
        result += std::to_string(snake_multiplier) + ",";
        result += std::to_string(zombie_midpoint) + ",";
        result += std::to_string(zombie_multiplier) + ",";
        result += std::to_string(barrier_midpoint) + ",";
        result += std::to_string(barrier_multiplier);

        return result;
    }

void chromosome::randomize() {

    heuristic_greater = (double)(rand()) / ((double)(RAND_MAX/1000));
    heuristic_lesser = (double)(rand()) / ((double)(RAND_MAX/1000));
    snake_midpoint = (double)(rand()) / ((double)(RAND_MAX/1000));
    snake_multiplier = (double)(rand()) / ((double)(RAND_MAX/1000));
    zombie_midpoint = (double)(rand()) / ((double)(RAND_MAX/1000));
    zombie_multiplier = (double)(rand()) / ((double)(RAND_MAX/1000));
    barrier_midpoint = (double)(rand()) / ((double)(RAND_MAX/1000));
    barrier_multiplier = (double)(rand()) / ((double)(RAND_MAX/1000));
}