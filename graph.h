#include "heads.h"

#ifndef GRAPH_H
#define GRAPH_H


class Graph
{
    public:
        Graph();
        ~Graph();
        int New_node(char* nm);
        int New_edge(char* source,char* dest,double weight);
        void printall();
        void printNode(char* ns);
        void printEdges(char* from, char* to);
        int Delete_node(char *nm);
        int Delete_edge(char* source,char* dest,double wt=-1);
        int Receiving(char* destination);
        int Modify_Edge(char* source,char* destination,double curwt,double nwt);
        void Writetofile(FILE *fp);
        Edge** FindCycles();
        int getedgenum();
        int getnodenum();
        void CircleFind(char* goal);
        void DFSstart(Node* start,Node* goal,Edge** Visited,int minw=0,int length=-1);
        void DFS(Node* a,Node* goal,Node* strt,Edge* edg,Edge** Visited,int& results,int minw=0,int length=-1,int curl=0);
        double findweight(Node* s,Node* d,int times);
        int getnodenumsq();
        void FindCircles(char* goal,int mwt);
        void TraceFlow(char* s,char* goal,int l);


    private:
        NodeHead* Hd;//head for list of Nodes
};

#endif
