#include "Example.hpp"

Example::Example(std::vector<double> inputs, std::vector<bool> outputs)
{
    _inputs = inputs;
    _expectedOutputs = outputs;
}

std::vector< double > Example::GetInputs()
{
    return _inputs;
}

std::vector< bool > Example::GetOutputs()
{
    return _expectedOutputs;
}

int Example::GetInputSize()
{
    return _inputs.size();
}

int Example::GetOutputSize()
{
    return _expectedOutputs.size();
}

