#include <pop.hpp>
#include <game.hpp>

#include <thread>
#include <thread>

pop::pop() {
    c.randomize();
}

void pop::update_ave_game() {
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

std::string pop::to_csv_string(int id, int gen_id) {
    std::string result = "";

    result += std::to_string(gen_id) + ",";
    result += std::to_string(id) + ",";
    result += c.to_csv_string() + ",";
    
    for(game g: games) {
        g.calc_fitness();
        result += g.to_csv_string() + ",";
    }

    result += ave_game.to_csv_string();

    return result;
}

void pop::start_games(int id, int gen_id) {
    //Magic goes here

    //Must be called as its own thread
    //Makes a thread for each game, waits for all to finish, and then updates pop games.
    //Finally it calculates the average game and then exits

    std::thread game_threads[POP_GAME_COUNT];
    for(size_t i = 0; i < POP_GAME_COUNT; ++i) {
        game_threads[i] = std::thread(
            [](game* g, chromosome* c, int pop_id, int gen_id, int game_id) { 
                std::string game_str = std::to_string(gen_id) + "-" + std::to_string(pop_id) + "-" + std::to_string(game_id);
                g->execute(game_str, c); 
            }, 
            &this->games[i], 
            &this->c,
            id,
            gen_id,
            i
        );
    }

    for(std::thread &gt: game_threads) {
        gt.join();
    }

    for(game g: games) {
        g.calc_fitness();
    }

    this->update_ave_game();

}

void pop::save_state(std::string filename, int id, int gen_id) {
    FILE* status = std::fopen(filename.c_str(), "a+");
    this->update_ave_game();
    std::fprintf(status, "%s", this->to_csv_string(id, gen_id).c_str());
}
