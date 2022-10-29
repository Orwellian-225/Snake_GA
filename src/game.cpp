#include <game.hpp>
#include <chromosome.hpp>
#include <pop.hpp>

#include <cstdio>
#include <stdio.h>
#include <string>
#include <thread>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>
#include <sstream>

#define GAME_LENGTH 130

void game::chromosome_file_write(std::string filename, chromosome* c) {
    //Save to chromosome file
    FILE* file = fopen(filename.c_str(), "w+");

    std::fprintf(file, "mew_heuristic_greater: %lf\n", c->heuristic_greater);
    std::fprintf(file, "mew_heuristic_lesser: %lf\n", c->heuristic_lesser);
    std::fprintf(file, "mew_snake_midpoint: %lf\n", c->snake_midpoint);
    std::fprintf(file, "mew_snake_multiplier: %lf\n", c->snake_multiplier);
    std::fprintf(file, "mew_zombie_midpoint: %lf\n", c->zombie_midpoint);
    std::fprintf(file, "mew_zombie_multiplier: %lf\n", c->zombie_multiplier);
    std::fprintf(file, "mew_barrier_midpoint: %lf\n", c->barrier_midpoint);
    std::fprintf(file, "mew_barrier_multiplier: %lf\n", c->barrier_multiplier);

    std::fclose(file);
}

void game::chromosome_file_read(std::string filename, chromosome* c) {
    FILE* file = fopen(filename.c_str(), "r+");

    char* line = new char[2048];
    std::fscanf(file, "%s%lf\n", line, &c->heuristic_greater);
    std::fscanf(file, "%s%lf\n", line, &c->heuristic_lesser);
    std::fscanf(file, "%s%lf\n", line, &c->snake_midpoint);
    std::fscanf(file, "%s%lf\n", line, &c->snake_multiplier);
    std::fscanf(file, "%s%lf\n", line, &c->zombie_midpoint);
    std::fscanf(file, "%s%lf\n", line, &c->zombie_multiplier);
    std::fscanf(file, "%s%lf\n", line, &c->barrier_midpoint);
    std::fscanf(file, "%s%lf\n", line, &c->barrier_multiplier);
    std::fscanf(file, "%s%lf\n", line, &this->ave_time);
    std::fscanf(file, "%s%lf\n", line, &this->ave_score);
    std::fscanf(file, "%s%lf\n", line, &this->longest);

    std::fclose(file);
}

#define READ 0
#define WRITE 1
//Stolen from Stackoverflow @ https://stackoverflow.com/questions/548063/kill-a-process-started-with-popen
//God bless these wonderful people who are smarter than me
pid_t popen2(const char *command, int *infp, int *outfp) {
    int p_stdin[2], p_stdout[2];
    pid_t pid;

    if (pipe(p_stdin) != 0 || pipe(p_stdout) != 0)
        return -1;

    pid = fork();

    if (pid < 0)
        return pid;
    else if (pid == 0)
    {
        close(p_stdin[WRITE]);
        dup2(p_stdin[READ], READ);
        close(p_stdout[READ]);
        dup2(p_stdout[WRITE], WRITE);

        execl("/bin/sh", "sh", "-c", command, NULL);
        perror("execl");
        exit(1);
    }

    if (infp == NULL)
        close(p_stdin[WRITE]);
    else
        *infp = p_stdin[WRITE];

    if (outfp == NULL)
        close(p_stdout[READ]);
    else
        *outfp = p_stdout[READ];

    return pid;
}

void game::execute(std::string game_id, chromosome* c) {
    /* 
    * Start the game by calling the runnable jar with the chromosome file as a argument
    * Wait for the game to finish
    * Load the data from the game back into the struct
    * Flag as complete
    */

    std::string filedir = "/Users/orwellian/Projects/Snake_GA/gen_game_files/" + game_id + ".txt";

    chromosome_file_write(filedir, c);

    std::string jar = "java -jar /Users/orwellian/Projects/Snake_GA/SnakeGA.jar -develop";
    std::string command = jar + " " + filedir;
    FILE* file;
    pid_t pid;
    int in, out;
    auto cmd_lambda = [](const char* cmd, pid_t* pid, int* in, int* out) { 
        *pid = popen2(cmd, in, out);   
    };
    std::thread game_thr = std::thread(cmd_lambda, command.c_str(), &pid, &in, &out);
    game_thr.detach();

    std::this_thread::sleep_for(std::chrono::seconds(GAME_LENGTH));
    kill(pid, 9); //kill the instance  
    chromosome_file_read(filedir, c);
    this->calc_fitness();
}

void game::calc_fitness() {
    fitness = ave_score*ave_score * longest*longest*longest / ave_time / 10000 ;
}

std::string game::to_csv_string() {
    std::string result = "";

    calc_fitness();

    result += std::to_string(ave_time) + ",";
    result += std::to_string(ave_score) + ",";
    result += std::to_string(longest) + ",";
    result += std::to_string(fitness);

    return result;
}