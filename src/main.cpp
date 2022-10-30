#include "generation.hpp"
#include "game.hpp"
#include "chromosome.hpp"
#include "config.hpp"

#include <cstdio>
#include <cstdlib>
#include <thread>
#include <chrono>


int main() {

    generation* current_gen = new generation(1);
    for(size_t i = 0; i < GEN_COUNT; ++i) {
        current_gen->execute_gen();
        current_gen->save_generation_status();
        generation* next_gen = generation::next_generation(current_gen);
        delete current_gen;
        current_gen = next_gen;
    }
    
    return 0;
}