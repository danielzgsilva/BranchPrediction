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

struct Params
{
    unsigned int B, M1, M2, N, K;
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

        Smith(unsigned int B);
        Smith() {};

        std::string predict();
        void update(std::string outcome, std::string prediction);
        void print_results();
};

class Predictor
{
    public:
        std::string predictor_name;
        Smith smith;

        //Predictor(std::string predictor, Params params);
        Predictor() {};
        
        void initialize(std::string predictor, Params params);
        std::string predict(); 
        void update(std::string outcome, std::string prediction);
        void print_results();
};