#ifndef TOPOSORTERDEMO_H
#define TOPOSORTERDEMO_H

#include <iostream>
#include <iomanip>
#include "graph/TopoSorter.h"
#include "graph/DGraphModel.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"

using namespace std;

static int simpleHash(int &key, int capacity)
{
    return key % capacity;
}
static int stringKeyHash(string &key, int capacity)
{
    long long int sum = 0;
    for (int idx = 0; idx < key.length(); idx++)
        sum += key[idx];
    return sum % capacity;
}

static int charHash(char &key, int capacity)
{
    return key % capacity;
}

void topoSorterDemo1()
{
    DGraphModel<string> model(&strEQ, &vertex2str);

    model.add("HCM");
    model.add("LongAn");
    model.add("BinhDuong");
    model.add("DongNai");
    model.add("BinhThuan");
    model.connect("HCM", "LongAn");
    model.connect("HCM", "BinhDuong");
    model.connect("HCM", "DongNai");
    model.connect("DongNai", "BinhThuan");

    TopoSorter<string> sorter(&model, &stringKeyHash);

    DLinkedList<string> result = sorter.sort(TopoSorter<string>::BFS);
    cout << "Topological sorting (BFS): ";
    cout << left << setw(15) << result.toString() << endl;
    result.clear();
    result = sorter.sort(TopoSorter<string>::DFS);
    cout << "Topological sorting (DFS): ";
    for (string vertex : result)
    {
        cout << vertex << " ";
    }
    cout << endl;
    cout << left << setw(15) << result.toString() << endl;
}

void topoSorterDemo2()
{
    DGraphModel<char> model(&charEQ, &char2str);
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

    TopoSorter<char> sorter(&model, &charHash);
    DLinkedList<char> result = sorter.sort(TopoSorter<char>::DFS);
    cout << "Topological sorting (DFS): ";
    for (char vertex : result)
    {
        cout << vertex << " ";
    }
    cout << endl;
    cout << left << setw(15) << result.toString() << endl;
}

void topoSorterDemo3()
{
    DGraphModel<char> model(&charEQ, &char2str);
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

    TopoSorter<char> sorter(&model, &charHash);
    DLinkedList<char> result = sorter.sort(TopoSorter<char>::BFS, false);
    cout << "Topological sorting (BFS): ";
    for (char vertex : result)
    {
        cout << vertex << " ";
    }
    cout << endl;
    cout << left << setw(15) << result.toString() << endl;
}

bool intEQ(int &a, int &b)
{
    return a == b;
}

void topoSorterDemo4()
{
    // Complex graph
    DGraphModel<int> model(&intEQ, &int2str);
    model.add(1);
    model.add(2);
    model.add(3);
    model.add(4);
    model.add(5);
    model.add(6);
    model.add(7);
    model.add(8);
    model.add(9);
    model.add(10);
    model.add(11);
    model.add(12);
    model.add(13);
    model.add(14);

    model.connect(1, 2);
    model.connect(1, 3);
    model.connect(1, 4);
    model.connect(2, 5);
    model.connect(2, 6);
    model.connect(3, 7);
    model.connect(4, 8);
    model.connect(5, 9);
    model.connect(6, 10);
    model.connect(7, 11);
    model.connect(8, 12);
    model.connect(9, 13);
    model.connect(10, 14);

    TopoSorter<int> sorter(&model, &simpleHash);
    DLinkedList<int> result = sorter.sort(TopoSorter<int>::DFS);
    cout << "Topological sorting (DFS): ";
    for (int vertex : result)
    {
        cout << vertex << " ";
    }
    cout << endl;
    //result.clear();
    result = sorter.sort(TopoSorter<int>::BFS);
    cout << "Topological sorting (BFS): ";
    for (int vertex : result)
    {
        cout << vertex << " ";
    }
    cout << endl;
}

void topoSorterDemo5()
{
    DGraphModel<int> model(&intEQ, &int2str);
    model.add(1);
    model.add(2);
    model.add(3);
    model.add(4);
    model.add(5);
    model.add(6);

    model.connect(1, 2);
    model.connect(1, 3);
    model.connect(2, 4);
    model.connect(3, 4);
    model.connect(4, 5);
    model.connect(5, 6);

    TopoSorter<int> sorter(&model, &simpleHash);
    DLinkedList<int> result = sorter.sort(TopoSorter<int>::DFS);
    cout << "Topological sorting (DFS): ";
    for (int vertex : result)
    {
        cout << vertex << " ";
    }
    cout << endl;
    //result.clear();
    result = sorter.sort(TopoSorter<int>::BFS);
    cout << "Topological sorting (BFS): ";
    cout << endl;
    cout << "RESULT: " << result.toString() << endl;
}


void topoSorterDemo6()
{
    // Complex graph
    DGraphModel<int> model(&intEQ, &int2str);
    model.add(1);
    model.add(2);
    model.add(3);
    model.add(4);
    model.add(5);
    model.add(6);
    model.add(7);
    model.add(8);
    model.add(9);
    model.add(10);
    model.add(11);
    model.add(12);
    model.add(13);
    model.add(14);

    model.connect(1, 2);
    model.connect(1, 3);
    model.connect(1, 4);
    model.connect(2, 5);
    model.connect(2, 6);
    model.connect(3, 7);
    model.connect(4, 8);
    model.connect(5, 9);
    model.connect(6, 10);
    model.connect(7, 11);
    model.connect(8, 12);
    model.connect(9, 13);
    model.connect(10, 14);

    TopoSorter<int> sorter(&model, &simpleHash);
    DLinkedList<int> result = sorter.sort(TopoSorter<int>::DFS, false);
    cout << "Topological sorting (DFS): ";
    for (int vertex : result)
    {
        cout << vertex << " ";
    }
    cout << endl;
    //result.clear();
    result = sorter.sort(TopoSorter<int>::BFS, false);
    cout << "Topological sorting (BFS): ";
    for (int vertex : result)
    {
        cout << vertex << " ";
    }
    cout << endl;
}

void topoSorterDemo()
{
    topoSorterDemo1();
    topoSorterDemo2();
    topoSorterDemo3();
    topoSorterDemo4();
    topoSorterDemo5();
    topoSorterDemo6();
}

#endif /* TOPOSORTERDEMO_H */