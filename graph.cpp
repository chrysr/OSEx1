#include "graph.h"
#include <cstring>
#include <iostream>
#include <cstdio>

using namespace std;

Graph::Graph()
{
    Hd=new NodeHead();//initializes a list of nodes
}
Graph::~Graph()
{
    delete Hd;//deletes the list of nodes
}
int Graph::New_node(char* nm)
{
    Node* t=Hd->get_first();//get the first from the node list
    if(t==NULL)//if there are 0 nodes
    {
        t=new Node(nm);//create node
        Hd->set_first(t);//set it as first and last in the list
        Hd->set_last(t);
        Hd->set_num(Hd->get_num()+1);//increase number by 1
    }
    else
    {
        int flag=1;
        while(t!=NULL)//else
        {
            if(strcmp(t->getid(),nm)==0)//search for node
            {
                flag=0;
                break;
            }
            t=t->get_next();
        }
        if(flag)//if it does not exist
        {
            Node* n=new Node(nm);//create it
            t=Hd->get_last();//append it at the end of list
            t->set_next(n);//set the new node as the next of the previously last node
            n->set_previous(t);//set new node previous as the previously last
            Hd->set_last(n);//set new node as last
            Hd->set_num(Hd->get_num()+1);//increase num
        }
        else return 0;//if flag=0 node exists
    }
    //cout<<Hd->get_num()<<" nodes in"<<endl;
    return 1;//everything went ok
}
int Graph::New_edge(char* source,char* dest,double weight)
{
    Node* sc;
    Node* ds;
    New_node(source);
    New_node(dest);//this will create nodes if they do not exist already
    Node* t=Hd->get_first();
    while(t!=NULL)
    {
        if(strcmp(t->getid(),dest)==0)
            ds=t;
        if(strcmp(t->getid(),source)==0)
            sc=t;
        t=t->get_next();

    }//assign pointers to source and destination nodes
    Edge* edg=sc->get_head()->get_last();//create new edge at the end of the source edgelist
    Edge* te=new Edge(sc,ds,weight);
    if (sc->get_head()->get_first()==NULL)//make necessary updates to pointers so that the new Edge is part of the list
    {
        sc->get_head()->set_first(te);
        sc->get_head()->set_last(te);
        sc->get_head()->set_num(sc->get_head()->get_num()+1);
    }
    else
    {
        edg->set_next(te);
        te->set_previous(edg);
        sc->get_head()->set_last(te);
        sc->get_head()->set_num(sc->get_head()->get_num()+1);
    }
    return 1;



}
void Graph::printall()
{
    Node* t=Hd->get_first();
    while(t!=NULL)
    {
        cout<<"Node: "<<t->getid()<<endl;//for every node it prints the node and its edges
        t->get_head()->printedges();
        t=t->get_next();

    }
}
void Graph::printNode(char* ns)
{
    Node* t=Hd->get_first();
    int flag=0;
    while(t!=NULL)
    {
        if(strcmp(t->getid(),ns)==0)//print edges when you find the specific node(if it exists)
        {
            flag=1;
            cout<<"Node: "<<t->getid()<<endl;
            t->get_head()->printedges();
            break;
        }
        t=t->get_next();
    }
    if(flag==0)
        cout<<"Node |"<<ns<<"| does not exist"<<endl;
}
void Graph::printEdges(char* from, char* to)
{
    Node* t=Hd->get_first();
    int flag=0;
    int flag2=0;
    while(t!=NULL)
    {
        if(strcmp(t->getid(),from)==0)//check if the two nodes exist and if they do print the edges from the from to the to
        {
            flag=1;
            cout<<"Node: "<<t->getid()<<endl;
            t->get_head()->printedges(to);
        }
        if(strcmp(t->getid(),to)==0)
            flag2=1;
        t=t->get_next();
    }
    if(flag==0&&flag2==0)
        cout<<"Node |"<<from<<"| does not exist"<<endl<<"Node |"<<to<<"| does not exist"<<endl;
    else if(flag==0)
        cout<<"Node |"<<from<<"| does not exist"<<endl;
    else if(flag2==0)
        cout<<"Node |"<<to<<"| does not exist"<<endl;

}
int Graph::Delete_node(char *nm)
{
    int flag=0;
    Node* t=Hd->get_first();
    Node* del=NULL;
    if(t==NULL)
        return 0;
    while(t!=NULL)
    {
        if(strcmp(t->getid(),nm)==0)//if found, keep the object in a pointer and raise a flag
        {
            flag=1;
            del=t;
        }
        else
        {
            Edge* te=t->get_head()->get_first();//else search in the edgelist of the node
            Edge * m;
            while(te!=NULL)
            {
                m=te->get_next();
                if(strcmp(te->get_destination()->getid(),nm)==0)//if the node we want to delete appears as the destination node, delete the edge
                {
                    Delete_edge(te->get_source()->getid(),te->get_destination()->getid(),te->get_weight());
                }
                te=m;
            }
        }
        t=t->get_next();//get next edge

    }
    if (flag)//if the node we are looking for was found make necessary updates to connect previous with next nodes
    {
        if(del->get_next()!=NULL&&del->get_previous()!=NULL)
        {
            del->get_previous()->set_next(del->get_next());
            del->get_next()->set_previous(del->get_previous());
        }
        else if (del->get_next()!=NULL&&del->get_previous()==NULL)
        {
            Hd->set_first(del->get_next());
            del->get_next()->set_previous(NULL);
        }
        else if (del->get_next()==NULL&&del->get_previous()!=NULL)
        {
            Hd->set_last(del->get_previous());
            del->get_previous()->set_next(NULL);
        }
        else if (del->get_next()==NULL&&del->get_previous()==NULL)
        {
            Hd->set_first(NULL);
            Hd->set_last(NULL);
        }
        delete del;//delete and update number
        Hd->set_num(Hd->get_num()-1);
        return 1;
    }
    return 0;

}
int Graph::Delete_edge(char* source,char* dest,double wt)
{
    int flag=0;
    int flag2=0;
    int flag3=0;
    int flag1=0;
    Node* t=Hd->get_first();
    Node* nd;
    Edge* te;
    Edge* e;
    if(t==NULL)
        return 0;
    while(t!=NULL)
    {
        if(strcmp(t->getid(),source)==0)//check if source exists and save it if found
        {
            flag2=1;
            nd=t;
        }

        if(strcmp(t->getid(),dest)==0)//check if destination exists
        {
            flag3=1;
        }
        if(flag3==1&&flag2==1)//if both are found, we don't need to search for more
            break;
        t=t->get_next();
    }
    if(flag2==1&&flag3==1)
    {
        te=nd->get_head()->get_first();//get first edge
    }
    else return 0;
    while(te!=NULL)//for every edge in the source, check and see if one matches the one we are looking for
    {
        flag=0;
        if(wt==-1)
        {
            if(strcmp(te->get_destination()->getid(),dest)==0&&strcmp(te->get_source()->getid(),source)==0)//if weight not defiend
                flag=1;
        }
        else
        {
            if(strcmp(te->get_destination()->getid(),dest)==0&&strcmp(te->get_source()->getid(),source)==0&&te->get_weight()==wt)//if weight is defined
                flag=2;
        }
        if(flag)
        {
            flag1=1;//if comparison comes out true make necessary changes before deleting the edge
            e=te->get_next();
            if(te->get_next()!=NULL&&te->get_previous()!=NULL)
            {
                te->get_previous()->set_next(te->get_next());
                te->get_next()->set_previous(te->get_previous());
            }
            else if (te->get_next()==NULL&&te->get_previous()!=NULL)
            {
                nd->get_head()->set_last(te->get_previous());
                te->get_previous()->set_next(NULL);
            }
            else if (te->get_next()!=NULL&&te->get_previous()==NULL)
            {
                nd->get_head()->set_first(te->get_next());
                te->get_next()->set_previous(NULL);
            }
            else if (te->get_next()==NULL&&te->get_previous()==NULL)
            {
                nd->get_head()->set_first(NULL);
                nd->get_head()->set_last(NULL);
            }
            delete te;//delete edge
            te=e;
            nd->get_head()->set_num(nd->get_head()->get_num()-1);
            if (flag==2)
                return 1;
        }
        else te=te->get_next();

    }
    if(flag2==0&&flag3==0)//return non 1 if there was a problem
        return 4;
    if(flag2==0)
        return 2;
    if(flag3==0)
        return 3;
    if(flag1==0)
        return 0;
    return 1;
}

int Graph::Receiving(char* destination)
{
    Node* t=Hd->get_first();
    int flag=0;
    if(t==NULL)
        return 0;
    while(t!=NULL)
    {
        Edge* te=t->get_head()->get_first();
        if(strcmp(t->getid(),destination)==0)
            flag=1;
        while(te!=NULL)
        {
            if(strcmp(te->get_destination()->getid(),destination)==0)
            {
                cout<<te->get_source()->getid()<<" --("<<te->get_weight()<<")-> "<<te->get_destination()->getid()<<endl;
            }
            te=te->get_next();
        }
        t=t->get_next();
    }
    if(flag)
        return 1;
    return 0;
}

int Graph::Modify_Edge(char* source,char* destination,double curwt,double nwt)
{
    Node* t=Hd->get_first();
    int flags=0;
    int flagd=0;
    int flage=0;
    if(t==NULL)
        return 0;
    while(t!=NULL)
    {
        Edge* te=t->get_head()->get_first();
        if(strcmp(t->getid(),source)==0)
            flags=1;
        if(strcmp(t->getid(),destination)==0)
            flagd=1;
        if(te!=NULL)
        {
            while(te!=NULL)//search on edge lists of all nodes for matching edges
            {
                if(strcmp(te->get_destination()->getid(),destination)==0&&strcmp(te->get_source()->getid(),source)==0&&te->get_weight()==curwt)
                {
                    te->set_weight(nwt);
                    flage=1;
                }
                te=te->get_next();
            }


        }
        t=t->get_next();
    }
    if(flags==0&&flagd==0)//trouble reporting return values
        return 4;
    if(flags==0)
        return 3;
    if(flagd==0)
        return 2;
    if (flage==0)
        return 0;
    return 1;
}

void Graph::Writetofile(FILE *fp)
{
    Node* t=Hd->get_first();
    while(t!=NULL)//for every node, print node and write the edges it contains
    {
        fprintf(fp,"|%s|\n",t->getid());
        t->get_head()->writedges(fp);
        t=t->get_next();
    }
}
int Graph::getedgenum()
{
    int cnt=0;
    Node* t=Hd->get_first();//go through the nodelist and get the count of the edges which is found on the edgehead
    while(t!=NULL)
    {
        cnt+=t->get_head()->get_num();
        t=t->get_next();
    }
    return cnt;
}
int Graph::getnodenum()
{
    return Hd->get_num();//return the number of nodes in the the nodlist
}
void Graph::CircleFind(char* goal)
{
    Edge** edges=new Edge*[getedgenum()];//make an array of the edges that exist
    Node* inp=NULL;
    Node* t=Hd->get_first();
    while(t!=NULL)
    {
        if(strcmp(t->getid(),goal)==0)//create a pointer that points to the goal node
            inp=t;
        t=t->get_next();
    }
    if(inp==NULL)
        cout<<"Node |"<<goal<<"| does not exist"<<endl;//if we can't find the goal node in the graph
    for(int i=0;i<getedgenum();i++)
    {
        edges[i]=NULL;
    }
    delete [] edges;
    DFSstart(inp,inp,edges);//start DFS search starting from goal and wanting to reach goal again
}
void Graph::DFSstart(Node* start,Node* goal,Edge** Visited,int minw,int length)
{
    if(goal==NULL)//if the goal node was not defined correctly, return
        return;

    Edge* e= start->get_head()->get_first();
    if(e==NULL)//if starting node has no children, then it is not in a circle
    {
        cout<<"Node |"<<goal->getid()<<"| is not in a circle"<<endl;
        return;
    }
    int results=0;//result counter
    while(e!=NULL)
    {
        if(e->get_weight()>=minw)//if minw is defined, check that each edge weight >= than the min weight
            DFS(e->get_destination(),goal,start,e,Visited,results,minw,length,1);//call dfs
        e=e->get_next();
    }
    if(results==0&&length==-1&&minw==0)
        cout<<"Node |"<<start->getid()<<"| is not in a circle"<<endl;//if results does not change, no circle was found
    else if(results==0&&length!=-1)
        cout<<"No path from Node |"<<start->getid()<<"| ---> |"<<goal->getid()<<"| with length "<<length<<endl;
    else if(results==0&&minw>0)
        cout<<"Node |"<<start->getid()<<"| is not in a circle where all weights are >= "<<minw<<endl;

}
int c=0;
void Graph::DFS(Node* a,Node* goal,Node* strt,Edge* edg,Edge** Visited,int &results,int minw,int length,int curl)
{
    if(curl-1==length)
        return;//if current length of solution is equal to the length (if defined) then return
    if(a==NULL)
        return;//if current node is NULL for some reason
    if(edg==NULL)
        return;
    Edge** tmp=new Edge*[getedgenum()];//create new edge array and copy the contents of the old one
    int flag=1;
    for(int i=0;i<getedgenum();i++)
    {
        tmp[i]=NULL;
        if(Visited[i]!=NULL)
        {
            tmp[i]=Visited[i];

        }
        else if(Visited[i]==NULL&&flag==1)//when we find the first NULL element, set it to the edge that sent us to this DFS instance
        {
            flag=0;
            tmp[i]=edg;
        }

    }
    if(a==goal)//if goal node found
    {
        results++;//+1 result
        for(int i=0;i<getnodenum();i++)//print the path that brought us to the goal node
        {
            if(tmp[i]!=NULL)
            {
                if(strcmp(tmp[i]->get_source()->getid(),strt->getid())==0)
                {
                    cout<<endl<<"|"<<tmp[i]->get_source()->getid()<<"|"<<endl<<" --("<<tmp[i]->get_weight()<<")-> |"<<tmp[i]->get_destination()->getid()<<"| "<<endl;
                }
                else
                {
                    cout<<" --("<<tmp[i]->get_weight()<<")-> |"<<tmp[i]->get_destination()->getid()<<"| "<<endl;
                }
            }
            else break;

        }
        cout<<endl<<endl;
        delete[] tmp;
        return;
    }
    Edge* e=a->get_head()->get_first();
    if(e==NULL)
    {
        delete[] tmp;
        return;
    }
    while(e!=NULL)//search on all the edges of the node we are currently searching
    {
        flag=1;
        for(int i=0;i<getedgenum();i++)
        {
            if(tmp[i]==NULL)
                break;
            if(tmp[i]->get_destination()==e->get_destination())//if we have already seen this node again, skip it
                flag=0;
        }
        if(flag)//seen this node only once
        {
            if(e->get_weight()>=minw)
                DFS(e->get_destination(),goal,strt,e,tmp,results,minw,length,curl+1);
        }
        e=e->get_next();
    }
    delete[] tmp;
}
void Graph::FindCircles(char* goal,int mwt)
{
    Edge** edges=new Edge*[getedgenum()];//again create an edge array to put all the edge element in graph
    Node* inp=NULL;
    Node* t=Hd->get_first();
    while(t!=NULL)
    {
        if(strcmp(t->getid(),goal)==0)
            inp=t;
        t=t->get_next();
    }
    if(inp==NULL)
        cout<<"Node |"<<goal<<"| does not exist"<<endl;
    for(int i=0;i<getedgenum();i++)
    {
        edges[i]=NULL;
    }
    DFSstart(inp,inp,edges,mwt);//all are the same as Circlefind, but here we also have a min weight that each edge must have
    delete[] edges;
}


void Graph::TraceFlow(char* s,char* goal,int l)
{
    Edge** edges=new Edge*[getedgenum()];
    Node* strt=NULL;
    Node* g=NULL;
    Node* t=Hd->get_first();
    while(t!=NULL)//look and save start and goal nodes
    {
        if(strcmp(t->getid(),goal)==0)
            g=t;
        if(strcmp(t->getid(),s)==0)
            strt=t;
        t=t->get_next();
    }
    if(g==NULL&&strt==NULL)//error reporting if start or goal node was not found
        cout<<"Node |"<<goal<<"| and "<<"Node |"<<s<<"| does not exist"<<endl;
    else if(g==NULL)
        cout<<"Node |"<<goal<<"| does not exist"<<endl;
    else if(strt==NULL)
        cout<<"Node |"<<s<<"| does not exist"<<endl;
    if(g==NULL||strt==NULL)
    {
        delete[] edges;
        return;
    }
    for(int i=0;i<getedgenum();i++)
    {
        edges[i]=NULL;
    }
    DFSstart(strt,g,edges,0,l);//call dfs with min weight 0 and max length l
    delete[] edges;
}
