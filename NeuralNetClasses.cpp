#include <iostream>
#include <stdexcept>

class Layer
{
private:
    int numNodesIn, numNodesOut;
    double** weights;
    double* biases;

public:
    Layer(int numNodesIn, int numNodesOut)
    {
        this->numNodesIn = numNodesIn;
        this->numNodesOut = numNodesOut;

        // Allocate memory for weights as a 2D array
        weights = new double*[numNodesIn];
        for (int i = 0; i < numNodesIn; i++)
        {
            weights[i] = new double[numNodesOut];
        }

        // Allocate memory for biases
        biases = new double[numNodesOut];
    }

    double* CalculateOutputs(const double* inputs, double* weightedInputs)
    {
        for (int nodeOut = 0; nodeOut < numNodesOut; nodeOut++)
        {
            double weightedInput = biases[nodeOut];
            for (int nodeIn = 0; nodeIn < numNodesIn; nodeIn++)
            {
                weightedInput += inputs[nodeIn] * weights[nodeIn][nodeOut];
            }
            weightedInputs[nodeOut] = weightedInput;
        }
    return weightedInputs;
    }

    ~Layer()
    {
        // Deallocate memory for weights and biases
        for (int i = 0; i < numNodesIn; i++)
        {
            delete[] weights[i];
        }
        delete[] weights;
        delete[] biases;
    }
};

class NeuralNetwork
{
private:
    Layer* layers;
    int numLayers;

public:
    NeuralNetwork(const int* layerSizes, int numLayers)
    {
        this->numLayers = numLayers;

        // Create an array of layers
        
        // Create an array of layers
        layers = new Layer[numLayers];
        for (int i = 0; i < numLayers; i++)
        {
            layers[i] = Layer(layerSizes[i], layerSizes[i + 1]);
        }
    }

    void CalculateOutputs(const double* inputs, double* outputs)
    {
        double* currentInputs = new double[layerSizes[0]];
        std::memcpy(currentInputs, inputs, layerSizes[0] * sizeof(double));

        for (int i = 0; i < numLayers; i++)
        {
            layers[i].CalculateOutputs(currentInputs, outputs);
            std::memcpy(currentInputs, outputs, layerSizes[i + 1] * sizeof(double));
        }

        delete[] currentInputs;
    }

    int Classify(const double* inputs)
    {
        double* outputs = new double[layerSizes[numLayers]];
        CalculateOutputs(inputs, outputs);

        int maxIndex = IndexOfMaxValue(outputs);

        delete[] outputs;

        return maxIndex;
    }

    int IndexOfMaxValue(const double* array)
    {
        if (array == nullptr)
        {
            throw std::invalid_argument("Array is null.");
        }

        double maxValue = array[0];
        int maxIndex = 0;

        for (int i = 1; i < layerSizes[numLayers]; i++)
        {
            if (array[i] > maxValue)
            {
                maxValue = array[i];
                maxIndex = i;
            }
        }

        return maxIndex;
    }

    ~NeuralNetwork()
    {
        delete[] layers;
    }
};

int main()
{
    // Create a neural network with specified layer sizes
    const int layerSizes[] = {3, 4, 2};
    int numLayers = sizeof(layerSizes) / sizeof(layerSizes[0]);
    //NeuralNetwork network(layerSizes, numLayers);

    // Example input values
    const double inputs[] = {0.5, 0.3, 0.8};

    // Run inputs through the network and classify
    //int classification = NeuralNetwork.Classify(inputs);

    //std::cout << "Classification: " << classification << std::endl;

    return 0;
}
