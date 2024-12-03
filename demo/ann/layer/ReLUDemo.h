#include <iostream>

#include "layer/ReLU.h"

using namespace std;

void ReLUDemo1()
{
    ReLU layer;
    
    // Input for the forward pass
    xt::xarray<double> X = {{-1.0, 0.0, 1.0}, {2.0, -2.0, 3.0}};
    xt::xarray<double> Y = layer.forward(X);
    std::cout << "ReLU Forward Y: " << Y << std::endl;
    
    // Expected output for forward pass
    xt::xarray<double> expected_Y = {{0.0, 0.0, 1.0}, {2.0, 0.0, 3.0}};
    if (xt::allclose(Y, expected_Y)) 
        std::cout << "ReLU forward: PASSED" << std::endl;
    else 
        std::cout << "ReLU forward: FAILED" << std::endl;

    // Backward pass
    xt::xarray<double> DY = {{1.0, 1.0, 1.0}, {1.0, 1.0, 1.0}};
    xt::xarray<double> DX = layer.backward(DY);
    std::cout << "ReLU Backward DX: " << DX << std::endl;
    
    // Expected output for backward pass
    xt::xarray<double> expected_DX = {{0.0, 0.0, 1.0}, {1.0, 0.0, 1.0}};
    if (xt::allclose(DX, expected_DX)) 
        std::cout << "ReLU backward: PASSED" << std::endl;
    else 
        std::cout << "ReLU backward: FAILED" << std::endl;
}