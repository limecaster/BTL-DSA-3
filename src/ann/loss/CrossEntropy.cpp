/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.cc to edit this template
 */

/* 
 * File:   CrossEntropy.cpp
 * Author: ltsach
 * 
 * Created on August 25, 2024, 2:47 PM
 */

#include "loss/CrossEntropy.h"
#include "ann/functions.h"

CrossEntropy::CrossEntropy(LossReduction reduction): ILossLayer(reduction){
    
}

CrossEntropy::CrossEntropy(const CrossEntropy& orig):
ILossLayer(orig){
}

CrossEntropy::~CrossEntropy() {
}

double CrossEntropy::forward(xt::xarray<double> X, xt::xarray<double> t){
    //YOUR CODE IS HERE

    // Compute the softmax of X
    // cout << "X: " << X << endl;
    // m_aCached_Ypred = softmax(X, 1);
    // cout << "m_aCached_Ypred: " << m_aCached_Ypred << endl;
    m_aYtarget = t;
    //cout << "m_aYtarget: " << m_aYtarget << endl;

    // If last layer is softmax, then we don't need to compute softmax again
    m_aCached_Ypred = X;
    // Otherwise, we need to compute softmax, or using BCELoss

    double loss = cross_entropy(m_aCached_Ypred, m_aYtarget, m_eReduction == REDUCE_MEAN);

    return loss;
}
xt::xarray<double> CrossEntropy::backward() {
    //YOUR CODE IS HERE

     // dY = -1/Nnormalize *  t/(y + EPSILON)
    double EPSILON = 1e-7;

    double_tensor dY = -m_aYtarget / (m_aCached_Ypred + EPSILON);
    if (m_eReduction == REDUCE_MEAN)
        dY /= m_aYtarget.shape()[0];

    return dY;
}
