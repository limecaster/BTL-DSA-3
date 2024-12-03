/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   UGraphModel.h
 * Author: LTSACH
 *
 * Created on 24 August 2020, 15:16
 */

#ifndef UGRAPHMODEL_H
#define UGRAPHMODEL_H

#include "graph/AbstractGraph.h"
// #include "stacknqueue/PriorityQueue.h"

//////////////////////////////////////////////////////////////////////
///////////// UGraphModel: Undirected Graph Model ////////////////////
//////////////////////////////////////////////////////////////////////

template <class T>
class UGraphModel : public AbstractGraph<T>
{
private:
public:
    using typename AbstractGraph<T>::VertexNode;
    // class UGraphAlgorithm;
    // friend class UGraphAlgorithm;

    UGraphModel(
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

        // If fromNode and toNode are the same, then add a self-loop
        if (fromNode->equals(toNode))
        {
            fromNode->connect(toNode, weight);
        }
        else
        {
            fromNode->connect(toNode, weight);
            toNode->connect(fromNode, weight);
        }
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

        // If fromNode and toNode are the same, then remove the self-loop
        if (fromNode->equals(toNode))
        {
            fromNode->removeTo(toNode);
        }
        else
        {
            fromNode->removeTo(toNode);
            toNode->removeTo(fromNode);
        }
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
    static UGraphModel<T> *create(
        T *vertices, int nvertices, Edge<T> *edges, int nedges,
        bool (*vertexEQ)(T &, T &),
        string (*vertex2str)(T &))
    {
        // TODO

        UGraphModel<T> *graph = new UGraphModel<T>(vertexEQ, vertex2str);

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

#endif /* UGRAPHMODEL_H */
