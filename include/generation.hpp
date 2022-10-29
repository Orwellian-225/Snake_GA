#pragma once

#include <pop.hpp>

#include <string>
#include <array>

#define GENERATION_SIZE 20
#define SELECTION_SIZE 5
#define MUTATION_PROBABILITY 0.05

#define STATUS_FILE "../status.csv"

struct generation {
    std::array<pop*, GENERATION_SIZE> pops;
    int gen_id;

    generation();
    generation(int gen_id);

    static void mutate_pop(pop* p);
    static pop* crossover_pops(pop* p1, pop* p2);
    std::array<pop*, SELECTION_SIZE> select_pops();

    static generation* next_generation(generation* current);

    void save_generation_status();
    void save_generation();

    void execute_gen();

    ~generation();
};