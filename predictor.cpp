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
         this->gshare = GShare((int)params.M1, (int)params.N);
    }
    else if (predictor == "hybrid")
    {
        this->hybrid = Hybrid((int)params.K, (int)params.M1, (int)params.N, (int)params.M2);
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
        return this->gshare.predict(branch_pc);
    }
    else if (this->predictor_name == "hybrid")
    {
        return this->hybrid.predict(branch_pc);
    }
    else
    {
        assert(false &&  "predictor not supported!");
    }
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
        this->gshare.update(outcome, prediction);
    }
    else if (this->predictor_name == "hybrid")
    {
        this->hybrid.update(outcome, prediction);
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
        this->gshare.print_results();
    }
    else if (this->predictor_name == "hybrid")
    {
        this->hybrid.print_results();
    }
}