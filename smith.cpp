#include "headers.h"

Smith::Smith(int B)
{
    assert(B >= 1 && B <= 6 && "Counter bits must be 1 <= B <= 6");

    this->B = B;
    this->counter = this->initial_vals[B];
    this->counter_min = 0;
    this->counter_max = pow(2, B) - 1;
    this->decision_point = (counter_max + 1) / 2;
    this->predictions = 0;
    this->mispredictions = 0;

    //std::cout << "initial counter: " << this->counter << std::endl;
    //std::cout << "counter min: " << this->counter_min << std::endl;
    //std::cout << "counter max: " << this->counter_max << std::endl;
    //std::cout << "decision point: " <<  this->decision_point << std::endl;
    //std::cout << "num bits: " <<  this->B << std::endl;
}

std::string Smith::predict()
{
    this->predictions++;
   // std::cout << "counter: " << this->counter;

    if (this->counter >= this->decision_point)
    {
        // predict taken
       // std::cout << " predict taken" << std::endl;
        return "t";
    }
    // predict not taken
  //  std::cout << " predict NOT taken" << std::endl;
    return "n";
}

void Smith::update(std::string outcome, std::string prediction)
{
    if (outcome == "t")
    {
        // increment counter 
        this->counter = std::min(this->counter + 1, this->counter_max);
       // std::cout << "increment to " << this->counter << std::endl;
    }
    else if (outcome == "n")
    {
        // decrement counter
        this->counter = std::max(this->counter - 1, this->counter_min);
       // std::cout << "decrement to " << this->counter << std::endl;
    }

    if (outcome != prediction)
    {
      //  std::cout << "MISPREDICT" << std::endl;
        this->mispredictions++;
    }
}

void Smith::print_results()
{
    double mispredict_rate = ( (double)this->mispredictions / this->predictions) * 100;

    std::cout << "OUTPUT" << std::endl;
    std::cout << "number of predictions: " << this->predictions << std::endl;
    std::cout << "number of mispredictions: " << this->mispredictions << std::endl;
    std::cout << "misprediction rate: " << std::setprecision(2) << std::fixed << mispredict_rate << "%" << std::endl;
    std::cout << "FINAL COUNTER CONTENT: " << this->counter << std::endl;
}