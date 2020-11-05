#include "headers.h"

Bimodal::Bimodal(int M)
{
    this->M = M;
    this->num_entries = pow(2, this->M);
    this->predictions = 0;
    this->mispredictions = 0;
    
    // create prediction table 
    this->prediction_table.resize(this->num_entries, 4);
}

std::string Bimodal::predict(std::string hex_pc)
{
    this->predictions++;

    std::stringstream ss;
    int decimal_pc;
    std::string binary_pc, binary_index;

    // hex to binary
    ss << std::hex << hex_pc;
    ss >> decimal_pc;
    std::bitset<32> bits(decimal_pc);
    binary_pc = bits.to_string();

    // determine length M index into prediction table
    binary_index = binary_pc.substr(32 - 2 - this->M, M);
    this->cur_idx = strtol(binary_index.c_str(), NULL, 2);

    // index prediction table (counter >= 4 prediction taken, counter < 4 predict not taken)
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

void Bimodal::update(std::string outcome, std::string prediction)
{
    // update counter in prediction table according to branch's true outcome
    if (outcome == "t")
    {
        this->prediction_table[this->cur_idx] = std::min(this->prediction_table[this->cur_idx] + 1, this->counter_max);
    }
    else if (outcome == "n")
    {
        this->prediction_table[this->cur_idx] = std::max(this->prediction_table[this->cur_idx] - 1, this->counter_min);
    }

    // track misprediction
    if (outcome != prediction)
    {
        this->mispredictions++;
    }
}

void Bimodal::print_table()
{
    for (int i = 0; i < this->num_entries; i++)
    {
        std::cout << i << " " << this->prediction_table[i] << std::endl;
    }
}

void Bimodal::print_results()
{
    // calculating misprediction rate
    double mispredict_rate = ( (double)this->mispredictions / this->predictions) * 100;

    std::cout << "OUTPUT" << std::endl;
    std::cout << "number of predictions: " << this->predictions << std::endl;
    std::cout << "number of mispredictions: " << this->mispredictions << std::endl;
     std::cout << "misprediction rate: " << std::setprecision(2) << std::fixed << mispredict_rate << "%" << std::endl;

    std::cout << "FINAL BIMODAL CONTENTS" << std::endl;
    this->print_table();
}