#include "heads.h"
#include "node.h"
#ifndef EDGE_H
#define EDGE_H


class Edge
{
    public:
        Edge(Node* s,Node* d,double w);
        ~Edge();
        int set_next(Edge* e);
        int set_previous(Edge* e);
        Edge* get_previous();
        Edge* get_next();
        double get_weight();
        int set_source(Node* s);
        int set_destination(Node* d);
        int set_weight(double w);
        Node* get_source();
        Node* get_destination();
    private:
        Edge* previous;
        Edge* next;
        double weight;
        Node* source;
        Node* destination;
};

#endif
