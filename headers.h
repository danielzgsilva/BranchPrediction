#include <iostream>
#include <iomanip>  
#include <string>
#include <fstream>
#include <sstream>
#include <bitset>
#include <vector>
#include <map>
#include <cmath>
#include <cassert>
#include <cstdio>
#include <valarray>

struct Params
{
    int B, M1, M2, N, K;
};

class Smith
{
    public:
        unsigned long predictions, mispredictions;
        int counter, B, counter_min, counter_max, decision_point; 

        // initial counter values based off counter size
        std::map<unsigned int, unsigned int> initial_vals = {
            {1, 1},
            {2, 2},
            {3, 4},
            {4, 8},
            {5, 16},
            {6, 32},
        };

        Smith(int B);
        Smith() {};

        std::string predict();
        void update(std::string outcome, std::string prediction);
        void print_results();
};

class Bimodal
{   
    public: 
        unsigned long predictions, mispredictions;
        int M, num_entries;
        int counter_min = 0;
        int counter_max = 7;
        int cur_idx = 0;

        std::vector<int> prediction_table;

        Bimodal(int M);
        Bimodal() {};

        std::string predict(std::string hex_pc);
        void update(std::string outcome, std::string prediction);
        void print_table();
        void print_results();
};

class GShare
{
    public:
        unsigned long predictions, mispredictions;
        int M, N, num_entries, cur_idx;
        int counter_min = 0;
        int counter_max = 7;

        std::vector<int> prediction_table;
        std::vector<int> history;

        GShare(int M, int N);
        GShare() {};

        std::string predict(std::string hex_pc);
        void update(std::string outcome, std::string prediction);
        void shift_history();
        void update_history(std::string outcome);
        void print_table();
        void print_results();
};

class Hybrid
{
    public:
        unsigned long predictions, mispredictions;
        int K, M1, N, M2, cur_idx;
        int chooser_min = 0;
        int chooser_max = 3;
        std::string last_chosen, gshare_prediction, bimodal_prediction;

        std::vector<int> chooser;

        Bimodal bimodal;
        GShare gshare;

        Hybrid(int K, int M1, int N, int M2);
        Hybrid() {};

        std::string predict(std::string hex_pc);
        void update(std::string outcome, std::string prediction);
        void print_results();
        void print_chooser();
};

class Predictor
{
    public:
        std::string predictor_name;
        Smith smith;
        Bimodal bimodal;
        GShare gshare;
        Hybrid hybrid;

        Predictor() {};
        
        void initialize(std::string predictor, Params params);
        std::string predict(std::string branch_pc); 
        void update(std::string outcome, std::string prediction);
        void print_results();
};