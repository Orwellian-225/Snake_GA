#include <generation.hpp>
#include <pop.hpp>

#include <string>
#include <array>
#include <utility>
#include <algorithm>
#include <cstdio>
#include <thread>

generation::generation() {
    for(size_t i = 0; i < GENERATION_SIZE; ++i) {
        this->pops[i] = new pop();
    }

    this->gen_id = -1;
}

generation::generation(int gen_id) {
    for(size_t i = 0; i < GENERATION_SIZE; ++i) {
        this->pops[i] = new pop();
    }

    this->gen_id = gen_id;
}


void generation::execute_gen() {
    std::thread pop_threads[GENERATION_SIZE];

    for(size_t i = 0; i < GENERATION_SIZE; ++i) {
       pop_threads[i] = std::thread(
        [](pop* p, int gen_id, int pop_id) {
            p->start_games(gen_id, pop_id);
            }, 
            pops[i],
            this->gen_id,
            i
        );
    }

    for(std::thread &pt: pop_threads) {
        pt.join();
    }

}

void generation::save_generation_status() {
    FILE* file = std::fopen(STATUS_FILE, "a+");

    std::fprintf(file, "\n");

    for(size_t i = 0; i < GENERATION_SIZE; ++i) {
        std::string state_i = pops[i]->to_csv_string(i, gen_id);

        std::fprintf(file, "%s\n", state_i.c_str());
    }
 
    std::fclose(file);
}

void generation::save_generation() {
    std::string filename = "gen_" + std::to_string(gen_id) + ".txt";
    FILE* file = std::fopen(filename.c_str(), "w+");

    for(size_t i = 0; i < pops.size(); ++i) {
        std::string state_i = pops[i]->to_csv_string(i, gen_id);

        std::fprintf(file, "%s\n", state_i.c_str());
    }

    std::fclose(file);
}

generation* generation::next_generation(generation* current) {

    generation* next = new generation(current->gen_id + 1);

    std::array<pop*, SELECTION_SIZE> selection = current->select_pops();

    for(size_t i = 0; i < SELECTION_SIZE; ++i) {
        next->pops[i] = selection[i];
    }

    for(size_t i = 0; i < GENERATION_SIZE - SELECTION_SIZE; ++i) {
        size_t idx = i + SELECTION_SIZE;

        std::pair<int, int> parents_idx = std::make_pair(
            std::rand() % SELECTION_SIZE,
            std::rand() % SELECTION_SIZE
            );

        while(parents_idx.first == parents_idx.second) {
            parents_idx = std::make_pair(
                std::rand() % SELECTION_SIZE,
                std::rand() % SELECTION_SIZE
                );
        }

        next->pops[idx] = generation::crossover_pops(selection[parents_idx.first], selection[parents_idx.second]);

        float mutation_chance = (float)(rand()) / ((float)(RAND_MAX));
        if(mutation_chance <= MUTATION_PROBABILITY) {
            mutate_pop(next->pops[idx]);
        }

    } 

    return next; 

}

void generation::mutate_pop(pop* p) {
    int mutating_gene = rand() % 8;
    double mutated_value = (double)(rand()) / ((double)(RAND_MAX/1000));

    switch (mutating_gene) {
        case 0:
            p->c.heuristic_greater = mutated_value / 100;
            break;
        
        case 1:
            p->c.heuristic_lesser = mutated_value / 100;
            break;

        case 2:
            p->c.snake_midpoint = mutated_value / 10;
            break;

        case 3:
            p->c.snake_multiplier = mutated_value;
            break;

        case 4:
            p->c.zombie_midpoint = mutated_value / 10;
            break;

        case 5:
            p->c.zombie_multiplier = mutated_value;
            break;

        case 6:
            p->c.barrier_midpoint = mutated_value / 10;
            break;

        case 7:
            p->c.barrier_multiplier = mutated_value;
            break;

        default:
            break;
    }
}

pop* generation::crossover_pops(pop* p1, pop* p2) {
    pop* child = new pop();

    const double weight = 0.5;

    child->c.heuristic_greater = weight*p1->c.heuristic_greater + (1-weight)*p2->c.heuristic_greater;
    child->c.heuristic_lesser = weight*p1->c.heuristic_lesser + (1-weight)*p2->c.heuristic_lesser;
    child->c.snake_midpoint = weight*p1->c.snake_midpoint + (1-weight)*p2->c.heuristic_greater;
    child->c.snake_multiplier = weight*p1->c.snake_multiplier + (1-weight)*p2->c.snake_multiplier;
    child->c.zombie_midpoint = weight*p1->c.zombie_midpoint + (1-weight)*p2->c.zombie_midpoint;
    child->c.zombie_multiplier = weight*p1->c.zombie_multiplier + (1-weight)*p2->c.zombie_multiplier;
    child->c.barrier_midpoint = weight*p1->c.barrier_midpoint + (1-weight)*p2->c.barrier_midpoint;
    child->c.barrier_multiplier = weight*p1->c.barrier_multiplier + (1-weight)*p2->c.barrier_multiplier;

    return child;
}

bool compare_pops(pop* p1, pop* p2) { return p1->ave_game.fitness < p2->ave_game.fitness; }

std::array<pop*, SELECTION_SIZE> generation::select_pops() {
    std::sort(std::begin(pops), std::end(pops), compare_pops);

    std::array<pop*, SELECTION_SIZE> result;

    for(size_t i = 0; i < SELECTION_SIZE; ++i) {
        result[i] = new pop();
        result[i]->c = pops[i]->c;
        
        for(size_t j = 0; j < POP_GAME_COUNT; ++j) {
            result[i]->games[j].ave_score = pops[i]->games[j].ave_score;
            result[i]->games[j].ave_time = pops[i]->games[j].ave_time;
            result[i]->games[j].longest = pops[i]->games[j].longest;
        }

        result[i]->ave_game.ave_score = pops[i]->ave_game.ave_score;
        result[i]->ave_game.ave_time = pops[i]->ave_game.ave_time;
        result[i]->ave_game.longest = pops[i]->ave_game.longest;
    }

    return result;
}

generation::~generation() {
    for(pop* p: this->pops) {
        delete p;
    }
}