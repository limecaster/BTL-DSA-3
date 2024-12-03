/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   UGraphDemo.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:26
 */

#ifndef UGRAPHDEMO_H
#define UGRAPHDEMO_H

#include <string>
#include <iostream>
#include <iomanip>
#include "graph/UGraphModel.h"
using namespace std;


bool strEQ(string& lhs, string& rhs){
    return lhs.compare(rhs) == 0;
}
string vertex2str(string& item){
    return item;
}

void ugraphDemo1(){
    UGraphModel<string> model(&strEQ, &vertex2str);
    
    model.add("HCM");
    model.add("LongAn");
    model.add("BinhDuong");
    model.add("DongNai");
    model.add("BinhThuan");
    model.connect("HCM", "LongAn");
    model.connect("HCM", "BinhDuong");
    model.connect("HCM", "DongNai");
    model.connect("DongNai", "BinhThuan");
    
    model.println();
}

bool charEQ(char& lhs, char& rhs){
    return lhs == rhs;
}
string char2str(char& item){
    stringstream os;
    os << item;
    return os.str();
}

void ugraphDemo2(){
    UGraphModel<char> model(&charEQ, &char2str);
    model.add('A');
    model.add('B');
    model.add('C');
    model.add('D');
    model.add('E');
    model.add('F');
    model.connect('A', 'B', 6);
    model.connect('A', 'C', 3);

    model.connect('B', 'C', 2);
    model.connect('B', 'D', 5);

    model.connect('C', 'D', 3);
    model.connect('C', 'E', 4);

    model.connect('D', 'E', 2);
    model.connect('D', 'F', 3);

    model.connect('E', 'F', 5);

    model.println();

    model.disconnect('C', 'A');
    model.disconnect('C', 'B');
    model.disconnect('C', 'D');
    model.disconnect('C', 'E');

    model.println();
}


void ugraphDemo3(){
    UGraphModel<char> model(&charEQ, &char2str);
    model.add('A');
    model.add('B');
    model.add('C');
    model.add('D');
    model.add('E');
    model.add('F');
    model.connect('A', 'B', 6);
    model.connect('A', 'C', 3);

    model.connect('B', 'C', 2);
    model.connect('B', 'D', 5);

    model.connect('C', 'D', 3);
    model.connect('C', 'E', 4);

    model.connect('D', 'E', 2);
    model.connect('D', 'F', 3);

    model.connect('E', 'F', 5);

    model.println();
    
    // cout << "Minimum Spanning Tree:" << endl;
    // UGraphAlgorithm<char> mst;
    // UGraphModel<char> tree = mst.minSpanningTree(&model);
    // tree.println();
}

void ugraphTestCallException()
{
    UGraphModel<char> model(&charEQ, &char2str);
    model.add('A');
    model.add('B');
    model.add('C');
    model.add('D');
    model.connect('A', 'B');
    model.connect('B', 'D');
    model.connect('C', 'B');
    model.connect('C', 'D');
    model.println();
    try
    {
        model.connect('X', 'Y');
    }
    catch (VertexNotFoundException &e)
    {
        cout << e.what() << endl;
    }
    try
    {
        model.disconnect('X', 'Y');
    }
    catch (VertexNotFoundException &e)
    {
        cout << e.what() << endl;
    }
    try
    {
        model.remove('X');
    }
    catch (VertexNotFoundException &e)
    {
        cout << e.what() << endl;
    }
    try {
        model.weight('A', 'D');
    } catch(EdgeNotFoundException &e){
        cout << e.what() << endl;
    }
}

bool xtEQ(xt::xarray<float>& lhs, xt::xarray<float>& rhs){
    return xt::allclose(lhs, rhs);
}

string xt2str(xt::xarray<float>& item){
    stringstream os;
    os << item;
    return os.str();
}

void ugraphDemo4() {
    // Test with xt::xarray
    UGraphModel<xt::xarray<float>> model(&xtEQ, &xt2str);
    model.add(xt::xarray<float>{1, 2, 3});
    model.add(xt::xarray<float>{4, 5, 6});
    model.add(xt::xarray<float>{7, 8, 9});
    model.connect(xt::xarray<float>{1, 2, 3}, xt::xarray<float>{4, 5, 6});
    model.connect(xt::xarray<float>{4, 5, 6}, xt::xarray<float>{7, 8, 9});
    model.println();

}

void ugraphDemo()
{
    cout << "==================== UGraphDemo ====================" << endl;
    ugraphDemo1();
    ugraphDemo2();
    ugraphDemo3();
    ugraphDemo4();
    ugraphTestCallException();
    cout << "===================================================" << endl;
}


#endif /* UGRAPHDEMO_H */

