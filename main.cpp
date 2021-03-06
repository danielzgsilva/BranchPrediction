#include "headers.h"


int main(int argc, char** argv)
{
    // Sim arguments
    std::string predictor_name, trace_file;
    Params params = Params{0, 0, 0, 0, 0};
    
    // Get predictor type from command
    predictor_name = argv[1];

    std::cout << "COMMAND" << std::endl;
    std::cout << std::string(argv[0]) << " ";

    // create predictor object
    Predictor predictor;

    // extract predictor parameters from command
    if (predictor_name == "smith")
    {
        params.B = atoi(argv[2]);
        trace_file = argv[3];
        std::cout << predictor_name << " " << params.B;
    }
    else if (predictor_name == "bimodal")
    {
        params.M2 = atoi(argv[2]);
        trace_file = argv[3];
        std::cout << predictor_name << " " << params.M2;
    }
    else if (predictor_name == "gshare")
    {
        params.M1 = atoi(argv[2]);
        params.N = atoi(argv[3]);
        trace_file = argv[4];
        std::cout << predictor_name << " " << params.M1 << " " << params.N;
    }
    else if (predictor_name == "hybrid")
    {
        params.K = atoi(argv[2]);
        params.M1 = atoi(argv[3]);
        params.N = atoi(argv[4]);
        params.M2 = atoi(argv[5]);
        trace_file = argv[6];
        std::cout << predictor_name << " " << params.K << " " << params.M1
        << " " << params.N << " " << params.M2;
    }
    else
    {
        std::cout << "predictor " + predictor_name + " is not supported!" << std::endl;
        return -1;
    }

    // Initializes predictor counter values, history, etc.
    predictor.initialize(predictor_name, params);

    // find name of trace file from provided trace file path
    std::string trace_name;
    std::size_t pos = trace_file.find_last_of("/\\");
    if (pos == std::string::npos)
    {
        trace_name = trace_file;
    }
    else
    {
        trace_name =  trace_file.substr(pos + 1);
    }
    std::cout << " " << trace_name << std::endl;
    

    // Create trace file stream
    std::ifstream input(trace_file);
    
    unsigned long PC = 0;
    std::string line, hex_address, outcome, prediction;

    // Process input file
    if (input.is_open())
    {
        while (getline(input, line))
        {
            // ignore empty line
            if (line.empty()) 
            {
                continue;
            }

            // read in address and outcome
            std::istringstream ss_line(line);
            if (!(ss_line >> hex_address >> outcome)) { break; }

            // Make prediction
            prediction = predictor.predict(hex_address);

            // Update predictor (update counter, history, etc.)
            predictor.update(outcome, prediction);

            PC++;
        }
    }

    input.close();

    // Print results of branch prediction simulation
    predictor.print_results();

    return 0;
}