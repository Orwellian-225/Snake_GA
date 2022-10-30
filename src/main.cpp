#include "generation.hpp"
#include "game.hpp"
#include "chromosome.hpp"

#include <cstdio>
#include <cstdlib>
#include <thread>
#include <chrono>

int main() {
    
    
    generation* gen = new generation(1);
    gen->execute_gen();
    gen->save_generation_status();
    generation* next_gen = generation::next_generation(gen);
    next_gen->execute_gen();
    next_gen->save_generation_status();
    
    
    
    return 0;
}