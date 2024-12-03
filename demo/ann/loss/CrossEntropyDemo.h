#include <iostream>

#include "loss/CrossEntropy.h"

using namespace std;

void CrossEntropyDemo1()
{
    CrossEntropy layer;
    xt::xarray<double> X = xt::ones<double>({1, 3});
    xt::xarray<double> t = xt::ones<double>({1, 3});
    double loss = layer.forward(X, t);
    cout << loss << endl;

    xt::xarray<double> DX = layer.backward();
    cout << DX << endl;

    auto expected_DX = xt::ones<double>({1, 3});
    if (xt::allclose(DX, expected_DX))
    {
        cout << "CrossEntropyDemo1 backward: PASSED" << endl;
    }
    else
    {
        cout << "CrossEntropyDemo1 backward: FAILED" << endl;
    }

    auto expected_loss = 1.0986122886681098;
    if (abs(loss - expected_loss) < 1e-9)
    {
        cout << "CrossEntropyDemo1 forward: PASSED" << endl;
    }
    else
    {
        cout << "CrossEntropyDemo1 forward: FAILED" << endl;
    }
}
