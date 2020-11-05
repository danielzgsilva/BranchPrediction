#include "headers.h"

Hybrid::Hybrid(int K, int M1, int N, int M2)
{   
    this->predictions = 0;
    this->mispredictions = 0;

    // PC bits for chooser table
    this->K = K;
    this->chooser.resize(pow(2, this->K), 1);

    // PC bits for gshare table indexing
    this->M1 = M1;
    // History register bits for gshare
    this->N = N;

    this->gshare = GShare(M1, N);

    // PC bits for bimodal table indexing
    this->M2 = M2;

    this->bimodal = Bimodal(M2);
}

std::string Hybrid::predict(std::string hex_pc)
{  
    this->predictions++;

    int decimal_pc;
    std::string prediction, binary_pc, binary_index;
    std::stringstream ss;

    // get predictions from gshare and bimodal predictors
    this->gshare_prediction = this->gshare.predict(hex_pc);
    this->bimodal_prediction = this->bimodal.predict(hex_pc);

    // determine index into chooser table
    ss << std::hex << hex_pc;
    ss >> decimal_pc;
    std::bitset<32> pc_bits(decimal_pc);
    binary_pc = pc_bits.to_string();

    // determine the K index bits for chooser table
    binary_index = binary_pc.substr(32 - 2 - this->K, this->K);
    this->cur_idx = strtol(binary_index.c_str(), NULL, 2);

    // choose gshare or bimodal prediction based off chooser table
    if (this->chooser[this->cur_idx] >= 2)
    {
        prediction = this->gshare_prediction;
        this->last_chosen = "gshare";
    }
    else
    {
        prediction = this->bimodal_prediction;
        this->last_chosen = "bimodal";
    }

    return prediction;
}

void Hybrid::update(std::string outcome, std::string prediction)
{
    if (this->last_chosen == "gshare")
    {
        // updates gshare counter and history table
        this->gshare.update(outcome, prediction);
    }
    else
    {   
        // updates bimodal counter
        this->bimodal.update(outcome, prediction);

        // always need to update history table of gshare
        this->gshare.update_history(outcome);
    }
    
    // update chooser table counter
    if (this->gshare_prediction == outcome && this->bimodal_prediction != outcome)
    {
        // increment if gshare correct and bimodal incorrect
        this->chooser[this->cur_idx] = std::min(this->chooser[this->cur_idx] + 1, this->chooser_max);
    }   
    else if (this->bimodal_prediction == outcome && this->gshare_prediction != outcome)
    {
        // decrement if bimodal correct and gshare incorrect
        this->chooser[this->cur_idx] = std::max(this->chooser[this->cur_idx] - 1, this->chooser_min);
    }

    // log misprediction
    if (outcome != prediction)
    {
        this->mispredictions++;
    }
}

void Hybrid::print_chooser()
{
    int size_chooser = pow(2, this->K);
    for (int i = 0; i < size_chooser; i++)
    {
        std::cout << i << " " << this->chooser[i] << std::endl;
    }
}

void Hybrid::print_results()
{   
    // calculating misprediction rate
    double mispredict_rate = ( (double)this->mispredictions / this->predictions) * 100;

    std::cout << "OUTPUT" << std::endl;
    std::cout << "number of predictions: " << this->predictions << std::endl;
    std::cout << "number of mispredictions: " << this->mispredictions << std::endl;
     std::cout << "misprediction rate: " << std::setprecision(2) << std::fixed << mispredict_rate << "%" << std::endl;

    std::cout << "FINAL CHOOSER CONTENTS" << std::endl;
    this->print_chooser();

    std::cout << "FINAL GSHARE CONTENTS" << std::endl;
    this->gshare.print_table();

    std::cout << "FINAL BIMODAL CONTENTS" << std::endl;
    this->bimodal.print_table();
}