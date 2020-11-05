#include "headers.h"

GShare::GShare(int M, int N)
{
    assert(N <= M && "N must be les than or equal to M!");
    this->M = M;
    this->N = N;
    this->num_entries = pow(2, this->M);
    this->predictions = 0;
    this->mispredictions = 0;

    // create prediction table 
    this->prediction_table.resize(this->num_entries, 4);

    // create history register
    this->history.resize(this->N, 0);
}

std::string GShare::predict(std::string hex_pc)
{
    this->predictions++;

    int decimal_pc;
    std::stringstream ss;
    std::string binary_pc, binary_index;

    // hex to binary
    ss << std::hex << hex_pc;
    ss >> decimal_pc;
    std::bitset<32> pc_bits(decimal_pc);
    binary_pc = pc_bits.to_string();

    // determine the M index bits
    binary_index = binary_pc.substr(32 - 2 - this->M, M);

    // XOR lower N most bits of index with the history contents
    int j = this->N - 1;
    for (int i = this->M - 1; i >= this->M - N; i--)
    {
        if (this->history[j] != binary_index[i] - '0')
        {
            binary_index[i] = '1';
        }
        else
        {
            binary_index[i] = '0';
        }
        j--;
    }
    
    // convert from binary index to int index 
    this->cur_idx = strtol(binary_index.c_str(), NULL, 2);

    // index prediction table and make prediction
    if (this->prediction_table[this->cur_idx] >= 4)
    {
        // predict taken
        return "t";
    }
    else
    {
        // predict not taken
        return "n";
    }
}

void GShare::update(std::string outcome, std::string prediction)
{
    // update history table
    this->update_history(outcome);

    // update counter in prediction table
    if (outcome == "t")
    {
        // increment if taken
        this->prediction_table[this->cur_idx] = std::min(this->prediction_table[this->cur_idx] + 1, this->counter_max);
    }
    else if (outcome == "n")
    {
        // decrement if not taken
        this->prediction_table[this->cur_idx] = std::max(this->prediction_table[this->cur_idx] - 1, this->counter_min);
    }

    // log misprediction
    if (outcome != prediction)
    {
        this->mispredictions++;
    }
}

void GShare::shift_history()
{
    if (this->N <= 1) {return;}

    int prev = this->history[0];
    int temp;

    // shift history register right by 1 bit
    for (int i = 1; i < this->N; i++)
    {
        temp = history[i];
        this->history[i] = prev;
        prev = temp;
    }
}

void GShare::update_history(std::string outcome)
{
    // update history table by first right shifting 
    this->shift_history();

    // then place outcome into most significant bit position
    if (outcome == "t")
    {
        this->history[0] = 1;
    }
    else if (outcome == "n")
    {
        this->history[0] = 0;
    }
}

void GShare::print_table()
{
    for (int i = 0; i < this->num_entries; i++)
    {
        std::cout << i << " " << this->prediction_table[i] << std::endl;
    }
}

void GShare::print_results()
{
    // calculating misprediction rate
    double mispredict_rate = ( (double)this->mispredictions / this->predictions) * 100;

    std::cout << "OUTPUT" << std::endl;
    std::cout << "number of predictions: " << this->predictions << std::endl;
    std::cout << "number of mispredictions: " << this->mispredictions << std::endl;
     std::cout << "misprediction rate: " << std::setprecision(2) << std::fixed << mispredict_rate << "%" << std::endl;

    std::cout << "FINAL GSHARE CONTENTS" << std::endl;
    this->print_table();
}