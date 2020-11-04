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
        void print_results();
};

class GShare
{
    public:
        unsigned long predictions, mispredictions;
        int M, N;

        GShare(int M, int N);
        GShare() {};

};

class Predictor
{
    public:
        std::string predictor_name;
        Smith smith;
        Bimodal bimodal;
        GShare gshare;

        Predictor() {};
        
        void initialize(std::string predictor, Params params);
        std::string predict(std::string branch_pc); 
        void update(std::string outcome, std::string prediction);
        void print_results();
};