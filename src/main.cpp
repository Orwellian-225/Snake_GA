#include <generation.hpp>
#include <pop.hpp>

#include <cstdio>

int main() {

    
    generation* gen = new generation(1);

    for(size_t i = 0; i < 5; ++i) {
        for(pop* p: gen->pops) {
            p->c.randomize();
        }

        gen->save_generation_status();

        generation* next_gen = generation::next_generation(gen);
        delete gen;
        gen = next_gen;
    }

    return 0;
}