/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DGraphDemo.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 20:26
 */

#ifndef DGRAPHDEMO_H
#define DGRAPHDEMO_H
#include "graph/DGraphModel.h"

bool charComparator(char& lhs, char& rhs){
    return lhs==rhs;
}
string vertex2str(char& v){
    stringstream os;
    os << v;
    return os.str();
}
void DGraphDemo1(){
    DGraphModel<char> model(&charComparator, &vertex2str);
    char vertices[] = {'A', 'B', 'C', 'D'};
    for(int idx=0; idx < 4; idx++){
        model.add(vertices[idx]);
    }
    model.connect('A', 'B');
    model.connect('B', 'D');
    model.connect('C', 'B');
    model.connect('C', 'D');
    model.println();
}

void DGraphDemo2(){
    DGraphModel<char> model(&charComparator, &vertex2str);
    char vertices[] = {'A', 'B', 'C', 'D'};
    for(int idx=0; idx < 4; idx++){
        model.add(vertices[idx]);
    }
    model.connect('A', 'B');
    model.connect('B', 'D');
    model.connect('C', 'B');
    model.connect('C', 'D');
    model.println();
    
    // TopoSorter<char> sorter(&model);
    // DLinkedList<char> topo = sorter.sort(TopoSorter<char>::BFS);
    // cout << left << setw(15) << "Topo-order: " << topo.toString() << endl;
}


void DGraphDemo3(){
    DGraphModel<char> model(&charComparator, &vertex2str);
    for(int idx=0; idx<10; idx++){
        model.add((char)('0' + idx));
    }

    model.connect('0', '1');
    model.connect('0', '5');
    model.connect('1', '7');
    model.connect('3', '2');
    model.connect('3', '4');
    model.connect('3', '7');
    model.connect('3', '8');
    model.connect('4', '8');
    model.connect('6', '0');
    model.connect('6', '1');
    model.connect('6', '2');
    model.connect('8', '2');
    model.connect('8', '7');
    model.connect('9', '4');
    model.println();
    
    // TopoSorter<char> sorter(&model);
    // DLinkedList<char> bfs = sorter.sort(TopoSorter<char>::BFS);
    // cout << left << setw(15) << "Topo-order (BFS): " << bfs.toString() << endl;
    
    // DLinkedList<char> dfs = sorter.sort(TopoSorter<char>::DFS);
    // cout << left << setw(15) << "Topo-order (DFS): " << dfs.toString() << endl;
}

void dijkstraDemo(){
    DGraphModel<char> model(&charComparator, &vertex2str);
    model.add('0');
    model.add('1');
    model.add('2');
    model.add('3');
    model.add('4');
    model.connect('0', '1', 5);
    model.connect('0', '2', 3);
    model.connect('0', '4', 2);

    model.connect('1', '2', 2);
    model.connect('1', '3', 6);

    model.connect('2', '1', 1);
    model.connect('2', '3', 2);

    model.connect('4', '1', 6);
    model.connect('4', '2', 10);
    model.connect('4', '3', 4);
    model.println();
 

    // DGraphAlgorithm<char> finder;
    // DLinkedList<Path<char>*> list = finder.dijkstra(&model, '0');
    // cout << "Dijkstra output:" << endl;
    // for(DLinkedList<Path<char>*>::Iterator it= list.begin(); it != list.end(); it++){
    //     Path<char>* path = *it;
        
    //     cout << left << setw(8) << "path: ";
    //     cout << path->toString() << endl;
    // }
    // cout << endl;
}

void DGraphTestCallException()
{
    DGraphModel<char> model(&charComparator, &vertex2str);
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
    }
    catch (EdgeNotFoundException &e)
    {
        cout << e.what() << endl;
    }
}

bool xtDEQ(xt::xarray<float>& lhs, xt::xarray<float>& rhs){
    return xt::allclose(lhs, rhs);
}

string xt2Dstr(xt::xarray<float>& item){
    stringstream os;
    os << item;
    return os.str();
}

void DGraphDemo4() {
    // Test with xt::xarray
    DGraphModel<xt::xarray<float>> model(&xtDEQ, &xt2Dstr);
    model.add(xt::xarray<float>{1, 2, 3});
    model.add(xt::xarray<float>{4, 5, 6});
    model.add(xt::xarray<float>{7, 8, 9});
    model.connect(xt::xarray<float>{1, 2, 3}, xt::xarray<float>{4, 5, 6});
    model.connect(xt::xarray<float>{4, 5, 6}, xt::xarray<float>{7, 8, 9});
    model.println();

}


void DGraphMLPLayerDemo(){
    DGraphModel<ILayer*> model([](ILayer*& lhs, ILayer*& rhs){return lhs == rhs;}, [](ILayer*& item){return item->get_desc();});
    ILayer* layers[] = {
        new FCLayer(2, 50, true),
        new ReLU(),
        new FCLayer(50, 20, true),
        new ReLU(),
        new FCLayer(20, 2, true),
        new Softmax()
    };
    for(int idx=0; idx < 6; idx++){
        model.add(layers[idx]);
    }
    model.connect(layers[0], layers[1]);
    model.connect(layers[1], layers[2]);
    model.connect(layers[2], layers[3]);
    model.connect(layers[3], layers[4]);
    model.connect(layers[4], layers[5]);
    model.println();

    for (int idx = 0; idx < 6; idx++)
    {
        delete layers[idx];
    }
}

void DGraphDemo(){
    DGraphDemo1();
    DGraphDemo2();
    DGraphDemo3();
    DGraphDemo4();
    dijkstraDemo();
    DGraphTestCallException();
    DGraphMLPLayerDemo();
}

#endif /* DGRAPHDEMO_H */

