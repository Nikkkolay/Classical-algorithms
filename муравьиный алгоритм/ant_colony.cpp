#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<cmath>
#include<windows.h>
using namespace std;

double alpha=1,beta=2,evaporation=0.95/*испарение*/,Q=50,gamma=1;
int N=500;

struct ARC
{
    int initialV,terminalV;//начальнна€ и конечна€ вершина
    double lenght,pheromone;//длинна, ферамон
};

int Next_V(int current_vertex, ARC *TG, int numA, int *visitedV, int &idV, int *visitedA, int &idA);

int main()
{
    srand(time(0));
    int numV,numA;//колличество вершин и коллличество ребер
    ifstream graf;//считываем с файла таблицу графа
    graf.open("graf.txt");
    graf>>numV;// олличество вершин
    graf>>numA;// олличество дуг
    int start=0,finish=numV-1;//задаем начальную и конечную вершину

    ARC *TG=new ARC[numA];//cчитываем граф
    for(int i=0; i<numA; i++)
    {
        graf>>TG[i].initialV;
        graf>>TG[i].terminalV;
        graf>>TG[i].lenght;
        TG[i].pheromone=1;
    }
    int *visitedV=new int[numV], *visitedA=new int[numA];//массивы с пройдеными дугами и вершинами
for(int k=0;k<10;k++){
    for(int index=0;index<N;index++)
    {
        start:
        int current_vertex=start,idV=0,idA=0;
        visitedV[idV++]=start;
        bool check=true;
        while(current_vertex!=finish)
        {
            current_vertex=Next_V(current_vertex,TG,numA,visitedV,idV,visitedA,idA);
            if(current_vertex==-1)
            {
                check=false;
                break;
            }
        }
        if(check==false)
            {
                index--;
                break;
            }

        for(int i=0;i<numA;i++)
            TG[i].pheromone*=evaporation;
         double L=0;
         for(int i=0;i<idA;i++)
                L+=TG[visitedA[i]].lenght;
        for(int i=0;i<idA;i++)
            TG[visitedA[i]].pheromone+=pow(Q/L,gamma);
    }

 //   for(int i=0;i<numA;i++)
   //     cout<<i<<':'<<TG[i].pheromone<<endl;
    //cout<<endl;
    cout<<"0";

    int *way=new int[numV];
    int idW=0;
    way[idW++]=start;
    while(way[idW-1]!=finish)
    {
       double max=-1;
       int idMax=-1;
       for(int i=0; i<numA; i++)
        {
            if(way[idW-1]==TG[i].initialV)
            {
                bool check=true;
                for(int j=0; j<idW; j++)
                    if(way[j]==TG[i].terminalV)
                        check=false;
                if(check&&TG[i].pheromone>max)
                    {
                        max=TG[i].pheromone;
                        idMax=i;
                    }

            }
        if(way[idW-1]==TG[i].terminalV)
            {
                bool check=true;
                for(int j=0; j<idW; j++)//////
                    if(way[j]==TG[i].initialV)
                        check=false;
                if(check&&TG[i].pheromone>max)
                    {
                        max=TG[i].pheromone;
                        idMax=i;
                    }
            }
        }
         if(way[idW-1]==TG[idMax].initialV)
            way[idW++]=TG[idMax].terminalV;
         else
            way[idW++]=TG[idMax].initialV;
    }

    for(int i=1;i<idW;i++)
        cout<<'>'<<way[i];
    cout<<endl<<endl;
}
return 0;
}

int Next_V(int current_vertex,ARC *TG,int numA,int *visitedV,int &idV,int *visitedA,int &idA)
{
    double Sigma=0,rand_nam;
    for(int i=0; i<numA; i++)////////ищем сигму
    {
        if(current_vertex==TG[i].initialV)
        {
            bool check=true;
            for(int j=0; j<idV; j++)/////=
                if(visitedV[j]==TG[i].terminalV)
                   check=false;
            if(check)
                Sigma+=pow(TG[i].pheromone,alpha)*pow(1/TG[i].lenght,beta);
        }
        if(current_vertex==TG[i].terminalV)
        {
            bool check=true;
            for(int j=0; j<idV; j++)//////
                if(visitedV[j]==TG[i].initialV)
                    check=false;
            if(check)
                Sigma+=pow(TG[i].pheromone,alpha)*pow(1/TG[i].lenght,beta);
        }
    }
    if(Sigma==0.0) return -1;//если идти некуда возвращаем -1

    double B=0;

    rand_nam=(double)rand()/RAND_MAX;

    for(int i=0; i<numA; i++)//выбираем след вершину
    {
        if(current_vertex==TG[i].initialV)
        {
            bool check=true;
            for(int j=0; j<idV; j++)
                if(visitedV[j]==TG[i].terminalV) check=false;

            if(check)
            {
                B+=pow(TG[i].pheromone,alpha)*pow(1/TG[i].lenght,beta)/Sigma;
                if(rand_nam<=B)
                {
                    visitedV[idV++]=TG[i].terminalV;
                    visitedA[idA++]=i;
                    break;
                }

            }
        }
        else if(current_vertex==TG[i].terminalV)
        {
            bool check=true;
            for(int j=0; j<=idV; j++)
                if(visitedV[j]==TG[i].initialV) check=false;

            if(check)
            {
                B+=pow(TG[i].pheromone,alpha)*pow(1/TG[i].lenght,beta)/Sigma;
                if(rand_nam<=B)
                {
                    visitedV[idV++]=TG[i].initialV;
                    visitedA[idA++]=i;
                    break;
                }
            }
        }
    }
    return visitedV[idV-1];
}
