#include "headers.h"

Predictor::Predictor(std::string predictor, Params params)
{
    this->predictor_name = predictor;

    if (predictor == "smith")
    {
        this->smith = Smith(params.B);
    }
    else if (predictor == "bimodal")
    {
        
    }
    else if (predictor == "gshare")
    {
        
    }
    else if (predictor == "hybrid")
    {
        
    }
}

std::string Predictor::predict()
{
    if (this->predictor_name == "smith")
    {
        return this->smith.predict();
    }
    else if (this->predictor_name == "bimodal")
    {
        
    }
    else if (this->predictor_name == "gshare")
    {
        
    }
    else if (this->predictor_name == "hybrid")
    {
        
    }

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
        
    }
    else if (this->predictor_name == "gshare")
    {
        
    }
    else if (this->predictor_name == "hybrid")
    {
        
    }
}