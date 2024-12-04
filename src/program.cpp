#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

#include <filesystem> //require C++17
namespace fs = std::filesystem;

#include "list/listheader.h"
#include "sformat/fmt_lib.h"
#include "tensor/xtensor_lib.h"
#include "ann/annheader.h"
#include "loader/dataset.h"
#include "loader/dataloader.h"
#include "config/Config.h"
#include "dataset/DSFactory.h"
#include "optim/Adagrad.h"
#include "optim/Adam.h"
#include "modelzoo/twoclasses.h"
#include "modelzoo/threeclasses.h"

#include "hash/xMapDemo.h"
#include "heap/HeapDemo.h"
#include "ann/model/MLPDemo.h"
#include "graph/DGraphDemo.h"
#include "graph/UGraphDemo.h"
#include "graph/TopoSorterDemo.h"

int main(int argc, char** argv) {

    //dataloader:
    // case_data_wo_label_1();
    // case_data_wi_label_1();
    // case_batch_larger_nsamples();

    //hashmap:
    // simpleMap();
    // hashDemo1();
    // hashDemo2();
    // hashDemo3();
    // hashDemo4();
    // hashDemo5();
    // hashDemo6();
    // hashDemo7();
    // countryDemo();
    // hashDemo8();
    // hashDemo9();
    // hashDemo10();
    //hashDemo11();

    //heap:
    // anotherHeap();
    // simpleMinHeap();
    // testInitialization();
    // testPush();
    // testPop();
    // testPeek();
    // testRemove();
    // testContains();
    // testHeapify();
    // testClear();
    // heapDemo1();
    // heapDemo2();
    // heapDemo3();
    // heapDemo4();

    //Classification:
    //twoclasses_classification();
    //threeclasses_classification();


    //MLP:
    // mlpDemo1();
    // mlpDemo2();
    // mlpDemo3();

    // Submission test:
    // hashDemo6();
    // mlpDemo1();
    // mlpDemo2();
    // mlpDemo3();
    //twoclasses_classification();
    //hashDemo11();
    //hashDemo3();

    //UGraph:
    // ugraphDemo();

    //DGraph:
    // DGraphDemo();

    //TopoSorter:
    topoSorterDemo1();
    // topoSorterDemo2();
    // topoSorterDemo3();

    return 0;
}
