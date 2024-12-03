#include <iostream>

#include "layer/Tanh.h"

using namespace std;

void TanhDemo1()
{
    Tanh layer;
    
    // Input for the forward pass
    xt::xarray<double> X = {{0.0, 1.0, -1.0}};
    xt::xarray<double> Y = layer.forward(X);
    std::cout << "Tanh Forward Y: " << Y << std::endl;

    // Expected output for forward pass
    xt::xarray<double> expected_Y = {{0.0, 0.76159, -0.76159}};
    if (xt::allclose(Y, expected_Y, 1e-5)) 
        std::cout << "Tanh forward: PASSED" << std::endl;
    else 
        std::cout << "Tanh forward: FAILED" << std::endl;

    // Backward pass
    xt::xarray<double> DY = {{1.0, 1.0, 1.0}};
    xt::xarray<double> DX = layer.backward(DY);
    std::cout << "Tanh Backward DX: " << DX << std::endl;

    // Expected output for backward pass
    xt::xarray<double> expected_DX = {{1.0, 0.41997, 0.41997}};
    if (xt::allclose(DX, expected_DX, 1e-5)) 
        std::cout << "Tanh backward: PASSED" << std::endl;
    else 
        std::cout << "Tanh backward: FAILED" << std::endl;
}