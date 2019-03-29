#include "edge.h"
#include <iostream>

using namespace std;
//************MOSTLY SIMPLE FUNCTIONS THAT HELP WITH THE REST OF THE PROGRAM************
//************COMMENTS MOST LIKELY NOT NEEDED***************
Edge::Edge(Node* s,Node* d,double w)
{
    previous=NULL;
    next=NULL;
    source=s;
    destination=d;
    weight=w;
}
Edge::~Edge()
{
    previous=NULL;
    next=NULL;
    source=NULL;
    destination=NULL;
}
int Edge::set_next(Edge* e)
{
    next=e;
    return 1;
}
int Edge::set_previous(Edge* e)
{
    previous=e;
    return 1;
}
Edge* Edge::get_previous()
{
    return previous;
}
Edge* Edge::get_next()
{
    return next;
}
double Edge::get_weight()
{
    return weight;
}
int Edge::set_source(Node* s)
{
    source=s;
    return 1;
}
int Edge::set_destination(Node* d)
{
    destination=d;
    return 1;
}
int Edge::set_weight(double w)
{
    weight=w;
    return 1;
}
Node* Edge::get_source()
{
    return source;
}
Node* Edge::get_destination()
{
    return destination;
}
