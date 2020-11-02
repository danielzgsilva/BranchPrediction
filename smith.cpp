#include "headers.h"

Smith::Smith(unsigned int B)
{
    assert(B >= 1 && B <= 6 && "Counter bits must be 1 <= B <= 6");
    B = B;
    counter = this->initial_vals[B];
    counter_min = 0;
    counter_max = pow(2, B) - 1;
}

std::string Smith::predict()
{
    this->predictions++;
    unsigned int decision_point = (counter_max + 1) / 2;

    if (this->counter >= decision_point)
    {
        // predict taken
        return "t";
    }
    // predict not taken
    return "n";
}

void Smith::update(std::string outcome, std::string prediction)
{
    if (outcome == "t")
    {
        // increment counter 
        this->counter = std::min(this->counter + 1, this->counter_max);
    }
    else if (outcome == "n")
    {
        // decrement counter
        this->counter = std::max(this->counter - 1, this->counter_min);
    }

    if (outcome != prediction)
    {
        this->mispredictions++;
    }
}

void Smith::print_results()
{
    double mispredict_rate = this->mispredictions / this->mispredictions;

    std::cout << "OUTPUT" << std::endl;
    std::cout << "number of predictions: " << this->predictions << std::endl;
    std::cout << "number of mispredictions: " << this->mispredictions << std::endl;
    std::cout << "misprediction rate: " << std::setprecision(2) << mispredict_rate << std::endl;
    std::cout << "FINAL COUNTER CONTENT: " << this->counter << std::endl;
}