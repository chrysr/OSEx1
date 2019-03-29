#include "node.h"
#include <cstring>

//************MOSTLY SIMPLE FUNCTIONS THAT HELP WITH THE REST OF THE PROGRAM************
//************COMMENTS MOST LIKELY NOT NEEDED***************
Node::Node(char* n)
{
    id_num=new char[60];//node_id. 60 characters (i think) is more than enough
    strcpy(id_num,n);
    previous=NULL;
    next=NULL;
    Edges=new EdgeHead();//make a new head for edge list.
}
Node::~Node()
{
    delete[] id_num;//free nod_id memory
    previous=NULL;
    next=NULL;
    delete Edges;//delete the edge list
}
char* Node::getid()
{
    return id_num;
}
int Node::set_next(Node* n)
{
    next=n;
    return 1;
}
int Node::set_previous(Node* n)
{
    previous=n;
    return 1;
}
Node* Node::get_next()
{
    return next;
}
Node* Node::get_previous()
{
    return previous;
}
EdgeHead* Node::get_head()
{
    return Edges;
}
