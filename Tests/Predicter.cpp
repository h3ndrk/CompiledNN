#include <CompiledNN/Model.h>
#include <CompiledNN/CompiledNN.h>

using namespace NeuralNetwork;

void testModelLoad(const std::string &file)
{
    Model model;
    model.load(file);
    // Optionally, indicate which input tensors should be converted from unsigned chars to floats in the beginning.
    // model.setInputUInt8(0);
    CompiledNN nn;
    nn.compile(model);
    // ... fill nn.input(i) with data
    nn.apply();
}

int main()
{
    testModelLoad("doqyqu5580426-195_model_pos_guess");
    testModelLoad("qogwyfu161554-2250_model_classifier");
    return 0;
}
