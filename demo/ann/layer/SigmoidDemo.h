#include <iostream>
#include <string>

#include "layer/Sigmoid.h"

using namespace std;

void SigmoidDemo1()
{
    Sigmoid layer;
    
    // Input for the forward pass
    xt::xarray<double> X = {{0.0, 1.0, -1.0}};
    xt::xarray<double> Y = layer.forward(X);
    std::cout << "Sigmoid Forward Y: " << Y << std::endl;

    // Expected output for forward pass
    xt::xarray<double> expected_Y = {{0.5, 0.73106, 0.26894}};
    if (xt::allclose(Y, expected_Y, 1e-5)) 
        std::cout << "Sigmoid forward: PASSED" << std::endl;
    else 
        std::cout << "Sigmoid forward: FAILED" << std::endl;

    // Backward pass
    xt::xarray<double> DY = {{1.0, 1.0, 1.0}};
    xt::xarray<double> DX = layer.backward(DY);
    std::cout << "Sigmoid Backward DX: " << DX << std::endl;
    
    // Expected output for backward pass
    xt::xarray<double> expected_DX = {{0.25, 0.19661, 0.19661}};
    if (xt::allclose(DX, expected_DX, 1e-5)) 
        std::cout << "Sigmoid backward: PASSED" << std::endl;
    else 
        std::cout << "Sigmoid backward: FAILED" << std::endl;
}