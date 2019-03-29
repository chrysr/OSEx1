
#ifndef HEADS1_H
#define HEADS1_H
#include "edge.h"
class EdgeHead
{
    public:
        EdgeHead();
        ~EdgeHead();
        int set_first(Edge* n);
        Edge* get_first();
        int set_last(Edge* n);
        Edge* get_last();
        int get_num();
        void set_num(int n);
        void printedges(char* to=NULL);
        void writedges(FILE* fp);
    private:
        Edge* first=NULL;
        Edge* last=NULL;
        int num;
};
#endif
#ifndef HEADS2_H
#define HEADS2_H
#include "node.h"
class NodeHead
{
    public:
        NodeHead();
        ~NodeHead();
        int set_first(Node* n);
        Node* get_first();
        int set_last(Node* n);
        Node* get_last();
        int get_num();
        void set_num(int n);

    private:
        Node* first=NULL;
        Node* last=NULL;
        int num;
};
#endif
