#include <iostream>
#include "heads.h"
#ifndef NODE_H
#define NODE_H

class EdgeHead;
class Node
{
    public:
        Node(char* n);
        ~Node();
        char* getid();
        int set_next(Node* n);
        int set_previous(Node* n);
        Node* get_previous();
        Node* get_next();
        EdgeHead* get_head();//returns the header of the edgelist

    private:
        Node* previous;
        Node* next;
        char *id_num;
        EdgeHead* Edges;
};

#endif
