#include <iostream>
#include <xtensor/xarray.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include <tensor/xtensor_lib.h>

using namespace std;

int main(){
    xt::xarray<double> X = {1, 2, 3};
    xt::xarray<double> Y = {4, 5, 6};

    //cout << outer_stack(X, xt::transpose(Y)) << endl;
    cout << xt::linalg::outer(X, Y) << endl;
    return 0;
}