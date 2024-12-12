/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   TopoSorter.h
 * Author: ltsach
 *
 * Created on July 11, 2021, 10:21 PM
 */

#ifndef TOPOSORTER_H
#define TOPOSORTER_H
#include "graph/DGraphModel.h"
#include "list/DLinkedList.h"
#include "sorting/DLinkedListSE.h"
#include "stacknqueue/Stack.h"
#include "stacknqueue/Queue.h"
#include "hash/xMap.h"

template <class T, class U>
using XHashMap = xMap<T, U>;

template <class T>
class TopoSorter
{
public:
    static int DFS;
    static int BFS;

protected:
    DGraphModel<T> *graph;
    int (*hash_code)(T &, int);

    // Helper functions
    xMap<T, int> vertex2inDegree(int (*hash)(T &, int))
    {
        xMap<T, int> map(this->hash_code);
        typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
        while (vertexIt != this->graph->end())
        {
            T vertex = *vertexIt;
            int inDegree = this->graph->inDegree(vertex);
            map.put(vertex, inDegree);

            vertexIt++;
        }
        return map;
    };
    xMap<T, int> vertex2outDegree(int (*hash)(T &, int))
    {
        xMap<T, int> map(this->hash_code);
        typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
        while (vertexIt != this->graph->end())
        {
            T vertex = *vertexIt;
            int outDegree = this->graph->outDegree(vertex);
            map.put(vertex, outDegree);

            vertexIt++;
        }
        return map;
    };
    DLinkedList<T> listOfZeroInDegrees()
    {
        DLinkedList<T> list;
        typename AbstractGraph<T>::Iterator vertexIt = this->graph->begin();
        while (vertexIt != this->graph->end())
        {
            T vertex = *vertexIt;
            int inDegree = this->graph->inDegree(vertex);
            if (inDegree == 0)
                list.add(vertex);

            vertexIt++;
        }
        return list;
    };

public:
    TopoSorter(DGraphModel<T> *graph, int (*hash_code)(T &, int) = 0)
    {
        this->graph = graph;

        if (hash_code != 0)
        {
            this->hash_code = hash_code;
        }
        else
        {
            // Default hash function
            this->hash_code = [](T &key, int size) -> int
            {
                return std::hash<T>{}(key) % size;
            };
        }
    }

    DLinkedList<T> sort(int mode = 0, bool sorted = true)
    {
        if (mode == DFS)
        {
            return dfsSort(sorted);
        }
        else if (mode == BFS)
        {
            return bfsSort(sorted);
        }
        else
        {
            return DLinkedList<T>();
        }
    }

    DLinkedList<T> dfsSort(bool sorted = true)
    {
        DLinkedList<T> result;
        xMap<T, int> outDegrees = vertex2outDegree(this->hash_code);
        DLinkedListSE<T> zeroOutDegrees = listOfZeroInDegrees();
        Stack<T> stack;
        
        if (sorted)
        {
            zeroOutDegrees.sort();
        }

        for (typename DLinkedListSE<T>::Iterator it = zeroOutDegrees.begin(); it != zeroOutDegrees.end(); ++it)
        {
            T vertex = *it;
            stack.push(vertex);
        }

        while (!stack.empty())
        {
            T vertex = stack.peek();
            int outDegree = outDegrees.get(vertex);
            if (outDegree == 0)
            {
                stack.pop();
                result.add(0, vertex);
            }
            else
            {
                DLinkedListSE<T> neighbors = this->graph->getOutwardEdges(vertex);
                if (sorted && neighbors.size() > 1)
                {
                    neighbors.sort();
                }

                for (typename DLinkedListSE<T>::Iterator it = neighbors.begin(); it != neighbors.end(); ++it)
                {
                    T neighbor = *it;

                    if (stack.contains(neighbor))
                    {
                        stack.remove(neighbor);
                        stack.push(neighbor);
                    }

                    if (!result.contains(neighbor) && !stack.contains(neighbor))
                    {
                        stack.push(neighbor);
                    }

                    outDegrees.put(vertex, outDegree - 1);
                }
            }
        }

        return result;
    }

    DLinkedList<T> bfsSort(bool sorted = true)
    {
        DLinkedList<T> result;
        xMap<T, int> inDegrees = vertex2inDegree(this->hash_code);
        DLinkedListSE<T> zeroInDegrees = listOfZeroInDegrees();
        Queue<T> queue;

        if (sorted)
        {
            zeroInDegrees.sort();
        }

        for (typename DLinkedListSE<T>::Iterator it = zeroInDegrees.begin(); it != zeroInDegrees.end(); ++it)
        {
            T vertex = *it;
            queue.push(vertex);
        }
        
        while (!queue.empty())
        {
            T vertex = queue.pop();
            result.add(vertex);

            DLinkedListSE<T> neighbors = this->graph->getOutwardEdges(vertex);
            if (sorted && neighbors.size() > 1)
            {
                neighbors.sort();
            }
            
            for (typename DLinkedListSE<T>::Iterator it = neighbors.begin(); it != neighbors.end(); ++it)
            {
                T neighbor = *it;
                if (queue.contains(neighbor))
                {
                    continue;
                }

                if (result.contains(neighbor))
                {
                    continue;
                }

                int inDegree = inDegrees.get(neighbor) - 1;
                inDegrees.put(neighbor, inDegree);
                if (inDegree == 0)
                {
                    queue.push(neighbor);
                }
            }
        }
        
        return result;
    }
}; // TopoSorter

template <class T>
int TopoSorter<T>::DFS = 0;

template <class T>
int TopoSorter<T>::BFS = 1;

#endif /* TOPOSORTER_H */
