#include <iostream>
#include <cstring>
#include "graph.h"
#include <cstdio>
#include <cstdlib>

using namespace std;

int exec_command(char command[][50],Graph* db);
void usage(char *args[]);

int main(int argc, char *argv[])
{

    char input[40]="\0";    //space for input and output files
    char output[40]="\0";
    if(argc==2||argc==4)
    {
        cout<<"Not enough arguments"<<endl;         //if args are 2 or 4 then a -i or a -o file is not specified
        usage(argv);
        return -1;
    }
    else if(argc>5)         //more than 5 args is too many
    {
        cout<<"Too many arguments"<<endl;
        usage(argv);
        return -2;
    }
    for(int i=0;i<argc;i++)         //search in the arguments list and if -i or -o argument is found, the next is the filename
    {
        if(strcmp(argv[i],"-i")==0)
            if(argv[i+1]!=NULL)
                strcpy(input,argv[i+1]);
        if(strcmp(argv[i],"-o")==0)
            if(argv[i+1]!=NULL)
                strcpy(output,argv[i+1]);
    }
    FILE *fp,*fp2;
    int flag=0;
    if (strcmp(input,"\0")!=0)  //if it is empty, it means it was not given by the user
    {
        fp=fopen(input,"r");
        if(fp==NULL)
        {
            cout<<"Invalid Input file"<<endl;
            usage(argv);
            return -3;
        }
    }
    if(strcmp(output,"\0")!=0)  //same as above
    {
        fp2=fopen(output,"w");
        if(fp2==NULL)
        {
            cout<<"Invalid Output file"<<endl;
            usage(argv);
            return -4;
        }
    }
    Graph* db=new Graph();      //create a graph
    int i=0;

    while(1)
    {
        i++;                //counter. no specific purpose but if you uncomment line 64, you can count how many operations took place
        //cout<<i<<".";
        char arg[200]={0};
        char command[5][50]={0,0};
        int pos=0;
        int let=0;
        if(flag==0) //we defined a flag=0 which becomes 1 when there is no input file or when we have finished reading the input file
        {
            if(strcmp(input,"\0")!=0)   //so if we have not reached the end of file
            {
                if(fgets(arg,200,fp)==NULL)     //read line
                {
                    flag=1;             //if EOF, flag=1
                    fclose(fp);         //close file
                }
            }
            else flag=1;
        }
        if (flag)
        {
            cout<<"\033[31mGraph>\033[36m";//colorful output to easily spot prompt and previous run commands
            cin.getline(arg,200);//read input
            cout<<"\033[39m";
        }
        if(flag==0)
        {
            strcpy(command[0],"n"); //if we are reading the file, we use the n(insert edge) command for each entry due to the format of the file that is given
            pos++;
        }
        for(int i=0;i<200;i++)
        {
            if(arg[i]=='\0'||arg[i]=='\n'||(int)arg[i]==13)//if new line or carriege return or empty string break
                break;
            if(arg[i]!=' '&&arg[i]!='\t')   //we have a **comand which is an array of strings each string contains one argument so
            {                               //if we find a tab, we move the to the next string of the array
                command[pos][let]=arg[i];
                let++;
            }
            else
            {
                command[pos][let]='\0'; //else empty string
                if(pos<4)
                    pos++;
                let=0;
            }
        }
        if(exec_command(command,db)==0) //if it returns 1 continue, if it returns 0, then user has given the exit command
        {
            if(strcmp(output,"\0")!=0)//so if output is defined, write to output file
            {

                db->Writetofile(fp2);
                fclose(fp2);//close file

            }
            cout<<"Exiting..."<<endl;
            //cout<<db->getedgenum()<<endl<<db->getnodenum()<<endl;
            delete db;//delete the graph
            return 0;
        }
    }

    return 0;
}

int exec_command(char command[][50],Graph* db)
{
    if (strcmp(command[0],"n")==0)//insert edge command
    {
        if(strcmp(command[1],"\0")!=0&&strcmp(command[2],"\0")!=0&&strcmp(command[3],"\0")!=0&&strcmp(command[4],"\0")==0)
            if(db->New_edge(command[1],command[2],atof(command[3])))//create new edge in graph
                cout<<"Inserted edge |"<<command[1]<<"| --("<<command[3]<<")-> |"<<command[2]<<"| successfully"<<endl;//returns 1 then successful
            else;
        else cout<<"Correct Format is: <n Ni Nj weight>"<<endl;

    }
    else if(strcmp(command[0],"i")==0)//insert node command
    {
        if(strcmp(command[1],"\0")!=0&&strcmp(command[2],"\0")==0&&strcmp(command[3],"\0")==0&&strcmp(command[4],"\0")==0)
            if(db->New_node(command[1]))
                cout<<"Inserted node |"<<command[1]<<"| successfully"<<endl;//if returns 1 the success
            else cout<<"Node |"<<command[1]<<"| exists"<<endl;//otherwise it exists
        else cout<<"Correct Format is: <i Ni>"<<endl;

    }
    else if(strcmp(command[0],"d")==0)//delete node command
    {
        if(strcmp(command[1],"\0")!=0&&strcmp(command[2],"\0")==0&&strcmp(command[3],"\0")==0&&strcmp(command[4],"\0")==0)
            if(db->Delete_node(command[1]))
                cout<<"Deleted node |"<<command[1]<<"| successfully"<<endl;//if returns 1 then success
            else cout<<"Node |"<<command[1]<<"| does not exist"<<endl;//else does not exist
        else cout<<"Correct Format is: <d Ni>"<<endl;

    }
    else if(strcmp(command[0],"l")==0)//delete edge command
    {
        int a;
        if(strcmp(command[1],"\0")!=0&&strcmp(command[2],"\0")!=0&&strcmp(command[3],"\0")!=0&&strcmp(command[4],"\0")==0)
        {
            a=db->Delete_edge(command[1],command[2],atof(command[3]));//delete edge with weight
            if (a==1)
                cout<<"Deleted edge |"<<command[1]<<"| --("<<command[3]<<")-> |"<<command[2]<<"| successfully"<<endl;
        }
        else if(strcmp(command[1],"\0")!=0&&strcmp(command[2],"\0")!=0&&strcmp(command[3],"\0")==0&&strcmp(command[4],"\0")==0)
        {
            a=db->Delete_edge(command[1],command[2]);//delete all edges from-to
            if (a==1)
                cout<<"Deleted all edges "<<command[1]<<" ---> "<<command[2]<<" successfully"<<endl;
        }
        else cout<<"Correct Format is: <l Ni Nj (weight)>"<<endl;

        if(strcmp(command[3],"\0")==0)
            strcpy(command[3],"-");
        if (a==4)
            cout<<"Node |"<<command[1]<<"| does not exist"<<endl<<"Node |"<<command[2]<<"| does not exist"<<endl;//return values and error codes
        else if (a==2)
            cout<<"Node |"<<command[1]<<"| does not exist"<<endl;
        else if (a==3)
            cout<<"Node |"<<command[2]<<"| does not exist"<<endl;
        else if (a==0)
            cout<<"Edge |"<<command[1]<<"| --("<<command[3]<<")-> |"<<command[2]<<"| does not exist"<<endl;

    }
    else if(strcmp(command[0],"print")==0)//helpful but not required by the exercise
    {
        if(strcmp(command[1],"\0")==0&&strcmp(command[2],"\0")==0&&strcmp(command[3],"\0")==0&&strcmp(command[4],"\0")==0)
        {
            db->printall();//prints everything
        }
        else if(strcmp(command[1],"\0")!=0&&strcmp(command[2],"\0")==0&&strcmp(command[3],"\0")==0&&strcmp(command[4],"\0")==0)
        {
            db->printNode(command[1]);//prints node
        }
        else if (strcmp(command[1],"\0")!=0&&strcmp(command[2],"\0")!=0&&strcmp(command[3],"\0")==0&&strcmp(command[4],"\0")==0)
        {
            db->printEdges(command[1],command[2]);//prints edges from-to
        }
        else cout<<"Correct Format is: <print (Ni) (Nj)>"<<endl;
    }
    else if(strcmp(command[0],"m")==0)//modify edge command
    {
        int a;
        if(strcmp(command[1],"\0")!=0&&strcmp(command[2],"\0")!=0&&strcmp(command[3],"\0")!=0&&strcmp(command[4],"\0")!=0)
        {
            a=db->Modify_Edge(command[1],command[2],atof(command[3]),atof(command[4]));
        }
        else cout<<"Correct Format is: <m Ni Nj weight nweight>"<<endl;//error printing depending on return value
        if(a==1)
            cout<<"Edge |"<<command[1]<<"| --("<<command[4]<<")-> |"<<command[2]<<"| modified Successfully"<<endl;
        else if (a==0)
            cout<<"Edge |"<<command[1]<<"| --("<<command[3]<<")-> |"<<command[2]<<"| does not exist"<<endl;
        else if (a==2)
            cout<<"Node |"<<command[2]<<"| does not exist"<<endl;
        else if (a==3)
            cout<<"Node |"<<command[1]<<"| does not exist"<<endl;
        else if (a==4)
            cout<<"Node |"<<command[1]<<"| does not exist"<<endl<<"Node |"<<command[2]<<"| does not exist"<<endl;
    }
    else if(strcmp(command[0],"r")==0)//receiving command
    {
        if(strcmp(command[1],"\0")!=0&&strcmp(command[2],"\0")==0&&strcmp(command[3],"\0")==0&&strcmp(command[4],"\0")==0)
            if(db->Receiving(command[1])==0)//if return 1 success, else node does not exist;
                cout<<"Node |"<<command[1]<<"| does not exist"<<endl;
            else;
        else cout<<"Correct Format is: <r Ni>"<<endl;


    }
    else if(strcmp(command[0],"e")==0)//exit command
    {
        return 0;
    }
    else if(strcmp(command[0],"c")==0)//circlefind command
    {
        if(strcmp(command[1],"\0")!=0&&strcmp(command[2],"\0")==0&&strcmp(command[3],"\0")==0&&strcmp(command[4],"\0")==0)
            db->CircleFind(command[1]);
        else cout<<"Correct Format is: <c Ni>"<<endl;
    }
    else if(strcmp(command[0],"f")==0)//findcircles command
    {
        if(strcmp(command[1],"\0")!=0&&strcmp(command[2],"\0")!=0&&strcmp(command[3],"\0")==0&&strcmp(command[4],"\0")==0)
            db->FindCircles(command[1],atoi(command[2]));
        else cout<<"Correct Format is: <f Ni k>"<<endl;
    }
    else if(strcmp(command[0],"t")==0)//traceflow command
    {
        if(strcmp(command[1],"\0")!=0&&strcmp(command[2],"\0")!=0&&strcmp(command[3],"\0")!=0&&strcmp(command[4],"\0")==0)
            db->TraceFlow(command[1],command[2],atoi(command[3]));
        else cout<<"Correct Format is: <t Ni Nj l>"<<endl;
    }
    else cout<<"Invalid Command! Availabe commands are:"<<endl<<"-i(nsert) Ni\n-(i)n(sert) Ni Nj weight\n-print (Ni) (Nj)\n-d(elete) Ni\n-(de)l(ete) Ni Nj (weight)\n-m(odify) Ni Nj weight nweight\n-r(eceiving) Ni\n-c(irclefind) Ni\n-f(indcircles) Ni k\n-t(raceflow) Ni Nj l\n-e(xit)"<<endl;
    return 1;//else command is not valid. Print available commands

}
void usage(char *args[])
{
    cout<<"Usage:"<<args[0]<<" [OPTION]. [FILE]."<<endl<<endl<<"-i inputfile.csv"<<endl<<"-o outputfile.csv"<<endl;
    //prints usage of program
}
