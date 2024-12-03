/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   Softmax.cpp
 * Author: ltsach
 * 
 * Created on August 25, 2024, 2:46 PM
 */

#include "layer/Softmax.h"
#include "ann/functions.h"
#include "sformat/fmt_lib.h"
#include <filesystem> //require C++17
namespace fs = std::filesystem;

Softmax::Softmax(int axis, string name): m_nAxis(axis) {
    if(trim(name).size() != 0) m_sName = name;
    else m_sName = "Softmax_" + to_string(++m_unLayer_idx);
}

Softmax::Softmax(const Softmax& orig) {
}

Softmax::~Softmax() {
}

xt::xarray<double> Softmax::forward(xt::xarray<double> X) {
    //YOUR CODE IS HERE
    
    m_aCached_Y = softmax(X, m_nAxis);
    return m_aCached_Y;
}
xt::xarray<double> Softmax::backward(xt::xarray<double> DY) {
    //YOUR CODE IS HERE

    const xt::xarray<double>& Y = this->m_aCached_Y;

    // (1) Compute the diagonal matrix of Y, using pre-implemented function diag_stack made by teacher
    xt::xarray<double> diag_Y = diag_stack(Y);
    
    // (2) Compute the outer product Y ⊗ Y^T for each row
    xt::xarray<double> outer_Y = outer_stack(Y, Y);
    
    // (3) Compute DIAG(Y) - Y ⊗ Y^T (the Jacobian matrix)
    xt::xarray<double> jacobian = diag_Y - outer_Y;
    
    // (4) Multiply the Jacobian by DY
    xt::xarray<double> DZ = matmul_on_stack(jacobian, DY);
    
    return DZ;
}

string Softmax::get_desc(){
    string desc = fmt::format("{:<10s}, {:<15s}: {:4d}",
                    "Softmax", this->getname(), m_nAxis);
    return desc;
}
