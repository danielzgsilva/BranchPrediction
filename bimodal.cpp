#include "headers.h"

Bimodal::Bimodal(int M)
{
    this->M = M;
    this->num_entries = pow(2, this->M);
    this->predictions = 0;
    this->mispredictions = 0;

    this->prediction_table.resize(this->num_entries, 4);

    // std::cout << "M: " << M << std::endl;
    // std::cout << "table len: " << num_entries << std::endl;
}

std::string Bimodal::predict(std::string hex_pc)
{
    this->predictions++;

    std::stringstream ss;
    int decimal_pc, index;
    std::string binary_pc, binary_index;

    //std::cout << hex_pc << std::endl;

    // hex to binary
    ss << std::hex << hex_pc;
    ss >> decimal_pc;

    std::bitset<32> bits(decimal_pc);
    binary_pc = bits.to_string();

    //std::cout << binary_pc << std::endl;

    // determine index into prediction table
    binary_index = binary_pc.substr(32 - 2 - this->M, M);

    //std::cout << binary_index << std::endl;

    index = strtol(binary_index.c_str(), NULL, 2);
    this->cur_idx = index;

    //std::cout << index << std::endl;

    if (this->prediction_table[index] >= 4)
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

void Bimodal::update(std::string outcome, std::string prediction)
{
    // the bimodal predictor updates counter in the update() function
    // so all that's left is to update misprediction count

    if (outcome == "t")
    {
        // update prediction table
        this->prediction_table[this->cur_idx] = std::min(this->prediction_table[this->cur_idx] + 1, this->counter_max);
    }
    else if (outcome == "n")
    {
        // update prediction table
        this->prediction_table[this->cur_idx] = std::max(this->prediction_table[this->cur_idx] - 1, this->counter_min);
    }

    if (outcome != prediction)
    {
        this->mispredictions++;
    }
}

void Bimodal::print_results()
{
    double mispredict_rate = ( (double)this->mispredictions / this->predictions) * 100;

    std::cout << "OUTPUT" << std::endl;
    std::cout << "number of predictions: " << this->predictions << std::endl;
    std::cout << "number of mispredictions: " << this->mispredictions << std::endl;
     std::cout << "misprediction rate: " << std::setprecision(2) << std::fixed << mispredict_rate << "%" << std::endl;

    std::cout << "FINAL BIMODAL CONTENTS" << std::endl;
    for (int i = 0; i < this->num_entries; i++)
    {
        std::cout << i << " " << this->prediction_table[i] << std::endl;
    }
}