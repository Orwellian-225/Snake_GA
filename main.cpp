#include <cstdio>
#include <string>
#include <array>

#define GEN_SIZE 1000
#define POP_GAME_COUNT 3

int main() {
    printf("Hello World");
    return 0;
}

struct chromosome {
    double heuristic_lesser = 0.;
    double heuristic_greater = 0.;
    double snake_midpoint = 0.;
    double snake_multiplier = 0.;
    double zombie_midpoint = 0.;
    double zombie_multiplier = 0.;
    double barrier_midpoint = 0.;
    double barrier_multiplier = 0.;

    std::string to_csv_string() {
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
};

struct game {
    double ave_score = 0.0;
    double ave_time = 0.0;
    double longest = 0.0;
    double fitness = 0.0;

    void calc_fitness() {
        fitness = ave_score*ave_score * longest*longest*longest / ave_time ;
    }

    std::string to_csv_string() {
        std::string result = "";

        calc_fitness();

        result += std::to_string(ave_time) + ",";
        result += std::to_string(ave_score) + ",";
        result += std::to_string(longest) + ",";
        result += std::to_string(fitness);

        return result;
    }

};

struct pop {
    chromosome c;
    int generation;
    int id;
    game games[POP_GAME_COUNT];
    game ave_game;

    void update_ave_game() {
        double a_t = 0., a_s = 0., a_l = 0.;

        for(game g: games) {
            a_t += g.ave_time;
            a_s += g.ave_score;
            a_l += g.longest;
        }

        a_t /= 3.;
        a_s /= 3.;
        a_l /= 3.;

        ave_game.ave_time = a_t;
        ave_game.ave_score = a_s;
        ave_game.longest = a_l;
        ave_game.calc_fitness();
    }

    std::string to_csv_string() {
        std::string result = "";

        result += std::to_string(generation) + ",";
        result += std::to_string(id) + ",";
        result += c.to_csv_string() + ",";
        
        for(game g: games) {
            g.calc_fitness();
            result += g.to_csv_string() + ",";
        }

        result += ave_game.to_csv_string();

        return result;
    }

    void start_games() {
        //Magic goes here
    }
};

void save_pop_state(pop *p) {
    FILE* status = std::fopen("status.csv", "a+");
    p->update_ave_game();
    std::fprintf(status, p->to_csv_string().c_str());
}

void pop_crossover(pop *p1, pop *p2) {

}

std::array<pop*, GEN_SIZE> pop_selection(std::array<pop*, GEN_SIZE> generation) {

}

std::array<pop*, GEN_SIZE> next_generation(std::array<pop*, GEN_SIZE> current_generation) {

}

void save_generation(std::array<pop*, GEN_SIZE> generation) {
    for(pop *p: generation) {
        save_pop_state(p);
    }
}