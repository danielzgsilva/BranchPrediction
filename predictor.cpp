#include "headers.h"

void Predictor::initialize(std::string predictor, Params params)
{
    this->predictor_name = predictor;

    if (predictor == "smith")
    {
        this->smith = Smith(params.B);
    }
    else if (predictor == "bimodal")
    {
        this->bimodal = Bimodal((int)params.M2);
    }
    else if (predictor == "gshare")
    {
        
    }
    else if (predictor == "hybrid")
    {
        
    }
}

std::string Predictor::predict(std::string branch_pc)
{
    if (this->predictor_name == "smith")
    {
        return this->smith.predict();
    }
    else if (this->predictor_name == "bimodal")
    {
        return this->bimodal.predict(branch_pc);
    }
    else if (this->predictor_name == "gshare")
    {
        
    }
    else if (this->predictor_name == "hybrid")
    {
        
    }

    std::cout << "SHOULD NOT BE HERE" << std::endl;
    return "b";
}

void Predictor::update(std::string outcome, std::string prediction)
{
    if (this->predictor_name == "smith")
    {
        this->smith.update(outcome, prediction);
    }
    else if (this->predictor_name == "bimodal")
    {
        this->bimodal.update(outcome, prediction);
    }
    else if (this->predictor_name == "gshare")
    {
        
    }
    else if (this->predictor_name == "hybrid")
    {
        
    }
}

void Predictor::print_results()
{
    if (this->predictor_name == "smith")
    {
        this->smith.print_results();
    }
    else if (this->predictor_name == "bimodal")
    {
        this->bimodal.print_results();
    }
    else if (this->predictor_name == "gshare")
    {
        
    }
    else if (this->predictor_name == "hybrid")
    {
        
    }
}