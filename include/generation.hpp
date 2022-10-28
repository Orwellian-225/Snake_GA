#pragma once

#include <pop.hpp>

#include <string>
#include <array>

#define GENERATION_SIZE 100
#define SELECTION_SIZE 20

#define STATUS_FILE "status.csv"

struct generation {
    std::array<pop*, GENERATION_SIZE> pops;
    int gen_id;

    void mutate_pop(pop* p);
    void crossover_pops(pop* p1, pop* p2);
    std::array<pop*, SELECTION_SIZE> select_pops();
    generation next_generation();
    void save_generation_status();
    void save_generation();
};