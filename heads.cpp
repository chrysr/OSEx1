#include "heads.h"
#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

EdgeHead::EdgeHead()
{
    first=NULL;
    last=NULL;
    num=0;
}
EdgeHead::~EdgeHead()
{
    Edge* t=first;//we go through the list and delete each edge
    Edge* t2;
    while(t!=NULL)
    {
        t2=t->get_next();
        delete t;
        t=t2;
    }
}
int EdgeHead::set_first(Edge* e)
{
    first=e;
    return 1;
}
Edge* EdgeHead::get_first()
{
    return first;
}
int EdgeHead::set_last(Edge* e)
{
    last=e;
    return 1;
}
Edge* EdgeHead::get_last()
{
    return last;
}
int EdgeHead::get_num()
{
    return num;
}
void EdgeHead::set_num(int n)
{
    num=n;
}
void EdgeHead::printedges(char* to)
{
    Edge* t=first;
    int flag=0;
    if(t==NULL)//if the list has nodes
        cout<<"\tNo Edges for this node"<<endl;
    while(t!=NULL)//we go through the list and print the edges
    {
        if(to==NULL)
            cout<<"\t|"<<t->get_source()->getid()<<"| --("<<t->get_weight()<<")-> |"<<t->get_destination()->getid()<<"|"<<endl;
        if(to!=NULL)
            if(strcmp(t->get_destination()->getid(),to)==0)
            {
                cout<<"\t|"<<t->get_source()->getid()<<"| --("<<t->get_weight()<<")-> |"<<t->get_destination()->getid()<<"|"<<endl;
                flag=1;
            }
        t=t->get_next();
    }
    if(to!=NULL&&flag==0)
        cout<<"\tNo edge to |"<<to<<"|"<<endl;
}
void EdgeHead::writedges(FILE* fp)
{
    Edge* t=first;
    while(t!=NULL)//same as above we go though the list and write to the file pointer that was given to us
    {
        fprintf(fp,"\t-%.2f->|%s|\n",t->get_weight(),t->get_destination()->getid());
        t=t->get_next();
    }
}
void NodeHead::set_num(int n)
{
    num=n;
}
int NodeHead::get_num()
{
    return num;
}
NodeHead::NodeHead()
{
    first=NULL;
    last=NULL;
    num=0;
}
NodeHead::~NodeHead()
{
    Node* t=first;//again go though the list and delete each node(which in its constructor deletes all edges)
    Node* t2;
    while(t!=NULL)
    {
        t2=t->get_next();
        delete t;
        t=t2;
    }
}
int NodeHead::set_first(Node* n)
{
    first=n;
    return 1;
}
Node* NodeHead::get_first()
{
    return first;
}
int NodeHead::set_last(Node* n)
{
    last=n;
    return 1;
}
Node* NodeHead::get_last()
{
    return last;
}
