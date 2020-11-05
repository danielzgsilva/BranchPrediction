#include "headers.h"

Smith::Smith(int B)
{
    assert(B >= 1 && B <= 6 && "Counter bits must be 1 <= B <= 6");

    this->B = B;

    // initialize counter 
    this->counter = this->initial_vals[B];
    this->counter_min = 0;
    this->counter_max = pow(2, B) - 1;

    // find decision point for counter
    this->decision_point = (counter_max + 1) / 2;

    this->predictions = 0;
    this->mispredictions = 0;
}

std::string Smith::predict()
{
    this->predictions++;

    if (this->counter >= this->decision_point)
    {
        // predict taken if counter greater than or equal to decision point
        return "t";
    }
    // predict not taken if counter less than decision point
    return "n";
}

void Smith::update(std::string outcome, std::string prediction)
{
    // update counter based off branch's true outcome
    if (outcome == "t")
    {
        // increment counter and saturate at upper limit
        this->counter = std::min(this->counter + 1, this->counter_max);
    }
    else if (outcome == "n")
    {
        // decrement counter and saturate at lower limit
        this->counter = std::max(this->counter - 1, this->counter_min);
    }


    // log misprediction
    if (outcome != prediction)
    {
        this->mispredictions++;
    }
}

void Smith::print_results()
{
    // calculating misprediction rate 
    double mispredict_rate = ( (double)this->mispredictions / this->predictions) * 100;

    std::cout << "OUTPUT" << std::endl;
    std::cout << "number of predictions: " << this->predictions << std::endl;
    std::cout << "number of mispredictions: " << this->mispredictions << std::endl;
    std::cout << "misprediction rate: " << std::setprecision(2) << std::fixed << mispredict_rate << "%" << std::endl;
    std::cout << "FINAL COUNTER CONTENT: " << this->counter << std::endl;
}