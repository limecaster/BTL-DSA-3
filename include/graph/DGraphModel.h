/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DGraphModel.h
 * Author: LTSACH
 *
 * Created on 23 August 2020, 19:36
 */

#ifndef DGRAPHMODEL_H
#define DGRAPHMODEL_H
#include "graph/AbstractGraph.h"
// #include "stacknqueue/Queue.h"
// #include "stacknqueue/Stack.h"
#include "hash/xMap.h"
// #include "stacknqueue/PriorityQueue.h"
// #include "sorting/DLinkedListSE.h"

//////////////////////////////////////////////////////////////////////
///////////// GraphModel: Directed Graph Model    ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class DGraphModel : public AbstractGraph<T>
{
private:
public:
    using typename AbstractGraph<T>::VertexNode;

    DGraphModel(
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &)) : AbstractGraph<T>(vertexEQ, vertex2str)
    {
    }

    void connect(T from, T to, float weight = 0)
    {
        // TODO

        VertexNode *fromNode = this->getVertexNode(from);
        if (!fromNode)
            throw VertexNotFoundException(this->vertex2str(from));

        VertexNode *toNode = this->getVertexNode(to);
        if (!toNode)
            throw VertexNotFoundException(this->vertex2str(to));

        fromNode->connect(toNode, weight);
    }
    void disconnect(T from, T to)
    {
        // TODO

        VertexNode *fromNode = this->getVertexNode(from);
        if (!fromNode)
            throw VertexNotFoundException(this->vertex2str(from));

        VertexNode *toNode = this->getVertexNode(to);
        if (!toNode)
            throw VertexNotFoundException(this->vertex2str(to));

        fromNode->removeTo(toNode);
    }
    void remove(T vertex)
    {
        // TODO

        VertexNode *node = this->getVertexNode(vertex);
        if (!node)
            throw VertexNotFoundException(this->vertex2str(vertex));

        // Remove all edges from this node to other nodes, and remove all edges from other nodes to this node
        for (auto it = this->nodeList.begin(); it != this->nodeList.end(); it++)
        {
            VertexNode *other = *it;
            other->removeTo(node);
            node->removeTo(other);
        }

        // Remove the node
        this->nodeList.removeItem(node);
    }

    static DGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
        // TODO

        DGraphModel<T> *graph = new DGraphModel<T>(vertexEQ, vertex2str);

        // Add vertices
        for (int i = 0; i < nvertices; i++)
        {
            graph->add(vertices[i]);
        }

        // Add edges
        for (int i = 0; i < nedges; i++)
        {
            graph->connect(edges[i].from, edges[i].to, edges[i].weight);
        }

        return graph;
    }
};

#endif /* DGRAPHMODEL_H */
