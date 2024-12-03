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
    XHashMap<T, int> vertex2inDegree(int (*hash)(T &, int));
    XHashMap<T, int> vertex2outDegree(int (*hash)(T &, int));
    DLinkedList<T> listOfZeroInDegrees();

    // Added dfsVisit method
    bool dfsVisit(T &vertex, XHashMap<T, bool> &visited, XHashMap<T, bool> &onStack, DLinkedList<T> &result, bool sorted) {
        visited.put(vertex, true);
        onStack.put(vertex, true);

        DLinkedList<T> neighbors = this->graph->getOutwardEdges(vertex);

        // Sort neighbors if required
        if (sorted) {
            DLinkedListSE<T> sortedNeighbors(neighbors);
            sortedNeighbors.sort();
            neighbors.clear();
            for (T neighbor : sortedNeighbors) {
                neighbors.add(neighbor);
            }
        }

        for (T neighbor : neighbors) {
            if (!visited.get(neighbor)) {
                if (!dfsVisit(neighbor, visited, onStack, result, sorted)) {
                    return false;
                }
            } else if (onStack.get(neighbor)) {
                // Found a cycle
                return false;
            }
        }

        onStack.put(vertex, false);
        result.add(vertex);
        return true;
    }


public:
    TopoSorter(DGraphModel<T> *graph, int (*hash_code)(T &, int) = 0)
    {
        // TODO

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
        // TODO

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
            throw invalid_argument("Invalid mode");
        }
    }
    DLinkedList<T> bfsSort(bool sorted = true)
    {
        // TODO

        DLinkedList<T> result;

        // Get in-degree of all vertices
        XHashMap<T, int> inDegrees = vertex2inDegree(this->hash_code);

        // Get list of vertices with in-degree zero
        DLinkedList<T> zeroInDegreeVertices = listOfZeroInDegrees();

        // Sort zeroInDegreeVertices if required
        if (sorted) {
            DLinkedListSE<T> sortedList(zeroInDegreeVertices);
            sortedList.sort();
            zeroInDegreeVertices.clear();
            for (T vertex : sortedList) {
                zeroInDegreeVertices.add(vertex);
            }
        }

        // Start BFS
        while (!zeroInDegreeVertices.empty()) {
            // Get the first vertex with zero in-degree
            T u = zeroInDegreeVertices.removeAt(0);
            result.add(u);

            // For each neighbor v of u
            DLinkedList<T> neighbors = this->graph->getOutwardEdges(u);

            for (T v : neighbors) {
                // Decrease in-degree of v
                inDegrees[v] -= 1;

                // If in-degree becomes zero, add v to zeroInDegreeVertices
                if (inDegrees[v] == 0) {
                    zeroInDegreeVertices.add(v);
                }
            }

            // Sort zeroInDegreeVertices if required
            if (sorted) {
                DLinkedListSE<T> sortedList(zeroInDegreeVertices);
                sortedList.sort();
                zeroInDegreeVertices.clear();
                for (T vertex : sortedList) {
                    zeroInDegreeVertices.add(vertex);
                }
            }
        }

        // Check if topological sorting is possible (graph has no cycles)
        if (result.size() != this->graph->size()) {
            // Graph has at least one cycle
            return DLinkedList<T>();
        }

        return result;
    }

    DLinkedList<T> dfsSort(bool sorted = true)
    {
        // TODO

        DLinkedList<T> result;
        XHashMap<T, bool> visited(this->graph->size(), this->hash_code);
        XHashMap<T, bool> onStack(this->graph->size(), this->hash_code);

        // Get all vertices
        DLinkedList<T> vertices = this->graph->vertices();

        // Sort vertices if required
        if (sorted) {
            DLinkedListSE<T> sortedVertices(vertices);
            sortedVertices.sort();
            vertices.clear();
            for (T vertex : sortedVertices) {
                vertices.add(vertex);
            }
        }

        // Initialize visited and onStack maps
        for (T vertex : vertices) {
            visited.put(vertex, false);
            onStack.put(vertex, false);
        }

        // Perform DFS
        for (T vertex : vertices) {
            if (!visited.get(vertex)) {
                if (!dfsVisit(vertex, visited, onStack, result, sorted)) {
                    // Graph has at least one cycle
                    return DLinkedList<T>();
                }
            }
        }

        // Reverse the result to get the topological order
        // It doesn't has reverse() method, so we have to create a new list
        DLinkedList<T> reversedResult;
        for (T vertex : result) {
            reversedResult.add(0, vertex);
        }

        return reversedResult;

    }
}; // TopoSorter
template <class T>
int TopoSorter<T>::DFS = 0;
template <class T>
int TopoSorter<T>::BFS = 1;

/////////////////////////////End of TopoSorter//////////////////////////////////

#endif /* TOPOSORTER_H */
