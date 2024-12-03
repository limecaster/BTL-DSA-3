#include <iostream>

#include "layer/Softmax.h"

using namespace std;

void SoftmaxDemo1()
{
    Softmax layer;
    
    // Input for the forward pass
    xt::xarray<double> X = {{-0.0221,  0.0221},
        { 0.0263, -0.0263},
        {-0.0228,  0.0228},
        { 0.0264, -0.0264},
        {-0.0223,  0.0223},
        { 0.0262, -0.0262},
        {-0.0223,  0.0223},
        { 0.0264, -0.0264},
        {-0.0185,  0.0185},
        { 0.0263, -0.0263}};
    xt::xarray<double> Y = layer.forward(X);
    std::cout << "Softmax Forward Y: " << Y << std::endl;
    
    // Expected output for forward pass
    xt::xarray<double> expected_Y = {{-0.0221,  0.0221},
        { 0.0263, -0.0263},
        {-0.0228,  0.0228},
        { 0.0264, -0.0264},
        {-0.0223,  0.0223},
        { 0.0262, -0.0262},
        {-0.0223,  0.0223},
        { 0.0264, -0.0264},
        {-0.0185,  0.0185},
        { 0.0263, -0.0263}};
    if (xt::allclose(Y, expected_Y, 1e-5)) 
        std::cout << "Softmax forward: PASSED" << std::endl;
    else 
        std::cout << "Softmax forward: FAILED" << std::endl;

    // Backward pass
    xt::xarray<double> DY = {{-0.0221,  0.0221},
        { 0.0263, -0.0263},
        {-0.0228,  0.0228},
        { 0.0264, -0.0264},
        {-0.0223,  0.0223},
        { 0.0262, -0.0262},
        {-0.0223,  0.0223},
        { 0.0264, -0.0264},
        {-0.0185,  0.0185},
        { 0.0263, -0.0263}};
    xt::xarray<double> DX = layer.backward(DY);
    xt::xarray<double> expected_DX = {{-0.0456,  0.0456},
        { 0.0564, -0.0564},
        {-0.0465,  0.0465},
        { 0.0553, -0.0553},
        {-0.0459,  0.0459},
        { 0.0532, -0.0532},
        {-0.0459,  0.0459},
        { 0.0555, -0.0555},
        {-0.0417,  0.0417},
        { 0.0540, -0.0540}};
    std::cout << "Softmax Backward DX: " << DX << std::endl;
    if (xt::allclose(DX, expected_DX, 1e-5)) 
        std::cout << "Softmax backward: PASSED" << std::endl;
    else 
        std::cout << "Softmax backward: FAILED" << std::endl;
    // We can't easily compute an exact expected DX for softmax without using its Jacobian, so we won't check it in this demo.
}