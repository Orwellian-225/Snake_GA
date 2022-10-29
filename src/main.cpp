#include "generation.hpp"
#include "game.hpp"
#include "chromosome.hpp"

#include <cstdio>
#include <cstdlib>
#include <thread>
#include <chrono>

int main() {
    
    generation gen(1);

    gen.execute_gen();
    gen.save_generation_status();
    
    /*
    game g;
    chromosome c;

    g.execute("test_kill", &c);
    */

    return 0;
}