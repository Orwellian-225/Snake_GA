#include <pop.hpp>
#include <game.hpp>

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

void pop::start_games() {
    //Magic goes here
}

void pop::save_state(std::string filename, int id, int gen_id) {
    FILE* status = std::fopen(filename.c_str(), "a+");
    this->update_ave_game();
    std::fprintf(status, "%s", this->to_csv_string(id, gen_id).c_str());
}
