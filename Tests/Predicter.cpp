#include <iostream>
#include <CompiledNN/Model.h>
#include <CompiledNN/CompiledNN.h>
#include <nlohmann/json.hpp>

nlohmann::json predict_model(nlohmann::json input, const std::string &model_path)
{
    ASSERT(input.is_array());
    ASSERT(input.size() > 0);

    const auto is_float = input[0].is_number_float();
    for (auto &value : input)
    {
        ASSERT(value.is_number());
        ASSERT(is_float == value.is_number_float());
    }

    NeuralNetwork::Model model;
    model.load(model_path);

    if (!is_float)
    {
        model.setInputUInt8(0);
    }

    NeuralNetwork::CompiledNN nn;
    nn.compile(model);

    for (unsigned int i = 0; i < input.size(); ++i)
    {
        if (is_float)
        {
            nn.input(0)[i] = input[i].get<float>();
        }
        else
        {
            nn.input(0)[i] = input[i].get<uint8_t>();
        }
    }

    nn.apply();

    nlohmann::json output;
    for (auto &value : nn.output(0))
    {
        output.push_back(value);
    }
    return output;
}

int main(int argc, const char *argv[])
{
    for (std::string line; std::getline(std::cin, line);)
    {
        std::cout << predict_model(nlohmann::json::parse(line), argv[1]).dump() << std::endl;
    }
    return 0;
}
