#ifndef TOPOSORTERDEMO_H
#define TOPOSORTERDEMO_H

#include <iostream>
#include <iomanip>
#include "graph/TopoSorter.h"
#include "graph/DGraphModel.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"
using namespace std;

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

    TopoSorter<string> sorter(&model);
    DLinkedList<string> result = sorter.sort(TopoSorter<string>::BFS);
    cout << "Topological sorting (BFS): ";
    // for (string vertex : result)
    // {
    //     cout << vertex << " ";
    // }
    // cout << endl;
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

    TopoSorter<char> sorter(&model);
    DLinkedList<char> result = sorter.sort(TopoSorter<char>::DFS);
    cout << "Topological sorting (DFS): ";
    // for (char vertex : result)
    // {
    //     cout << vertex << " ";
    // }
    // cout << endl;
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

    TopoSorter<char> sorter(&model);
    DLinkedList<char> result = sorter.sort(TopoSorter<char>::BFS, false);
    cout << "Topological sorting (BFS): ";
    // for (char vertex : result)
    // {
    //     cout << vertex << " ";
    // }
    // cout << endl;
    cout << left << setw(15) << result.toString() << endl;
}



#endif /* TOPOSORTERDEMO_H */