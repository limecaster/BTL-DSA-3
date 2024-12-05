
#ifndef DLINKEDLISTSE_DEMO_H
#define DLINKEDLISTSE_DEMO_H
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"

#include <iostream>
#include <iomanip>
using namespace std;

void dllSortDemo1()
{
    DLinkedList<int> list;
    list.add(45);
    list.add(97);
    list.add(12);
    list.add(2);
    list.add(39);
    list.add(3);
    list.add(37);
    list.add(87);

    cout << left << setw(22) << "Before:";
    cout << list.toString() << endl;

    DLinkedListSE<int> list2(list);

    list2.sort();
    cout << left << setw(22) << "After, Ascending:";
    cout << list2.toString() << endl;

    list2.sort(&SortSimpleOrder<int>::compare4Desending);
    cout << left << setw(22) << "After, Descending:";
    cout << list2.toString() << endl;
}

void dllSortDemo2()
{
    DLinkedList<string> list;
    list.add("HCM");
    list.add("LongAn");
    list.add("BinhDuong");
    list.add("DongNai");
    list.add("BinhThuan");

    cout << left << setw(22) << "Before:";
    cout << list.toString() << endl;

    DLinkedListSE<string> list2(list);
    
    list2.sort();
    cout << left << setw(22) << "After, Ascending:";
    cout << list2.toString() << endl;

    list2.sort(&SortSimpleOrder<string>::compare4Desending);
    cout << left << setw(22) << "After, Descending:";
    cout << list2.toString() << endl;
}

void dllSortDemo3()
{
    // Empty list
    DLinkedList<int> list;
    cout << left << setw(22) << "Before:";
    cout << list.toString() << endl;

    DLinkedListSE<int> list2(list);
    list2.sort();

    cout << left << setw(22) << "After, Ascending:";
    cout << list2.toString() << endl;

    list2.sort(&SortSimpleOrder<int>::compare4Desending);
    cout << left << setw(22) << "After, Descending:";
    cout << list2.toString() << endl;
    
}

void dllSortDemo()
{
    dllSortDemo1();
    dllSortDemo2();
    dllSortDemo3();
}


#endif // DLINKEDLISTSE_DEMO_H

