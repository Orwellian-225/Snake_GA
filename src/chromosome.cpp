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