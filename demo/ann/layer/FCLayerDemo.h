#include <iostream>
#include <string>

#include "layer/FCLayer.h"

using namespace std;

void FCLayerDemo1()
{
    FCLayer layer(3, 2, true);

    // Manually set weights and bias for testing
    xt::xarray<double> W = {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}};
    xt::xarray<double> b = {0.5, -0.5};
    layer.set_weights(W);
    layer.set_bias(b);

    xt::xarray<double> X = {{1.0, 1.0, 1.0}};
    xt::xarray<double> Y = layer.forward(X);

    cout << "Forward pass result Y: " << Y << endl;

    // Expected output for forward pass: Y = X * W^T + b
    xt::xarray<double> expected_Y = {{6.5, 14.5}};
    if (xt::allclose(Y, expected_Y))
    {
        cout << "FCLayerDemo1 forward: PASSED" << endl;
    }
    else
    {
        cout << "FCLayerDemo1 forward: FAILED" << endl;
    }

    // Backward pass
    xt::xarray<double> DY = {{1.0, 1.0}};
    xt::xarray<double> DX = layer.backward(DY);
    
    cout << "Backward pass result DX: " << DX << endl;

    // Expected output for backward pass
    xt::xarray<double> expected_DX = {{5.0, 7.0, 9.0}};
    if (xt::allclose(DX, expected_DX))
    {
        cout << "FCLayerDemo1 backward: PASSED" << endl;
    }
    else
    {
        cout << "FCLayerDemo1 backward: FAILED" << endl;
    }
}
