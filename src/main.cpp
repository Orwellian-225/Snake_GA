#include <generation.hpp>
#include <pop.hpp>

#include <cstdio>

int main() {

    
    generation gen;
    gen.build_generation();

    for(pop* p: gen.pops) {
        p->c.randomize();
    }

    gen.save_generation_status();

    return 0;
}