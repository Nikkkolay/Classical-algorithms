#include<iostream>
#include<fstream>
#include<conio.h>
using namespace std;

struct Arc
{
    int initialV,terminalV;//начальнная и конечная вершина
    unsigned int troughput,flow;//пропускная способность
};

void show(Arc *A,int N)
{
    for(int i=0; i<N; i++)
        cout<<i<<": "<<A[i].initialV<<"->"<<A[i].terminalV<<' '<<A[i].troughput<<'/'<<A[i].flow<<endl;
}

void first_step(Arc *TG,int N,int M)//N-дуги М-вершины
{

    int *visited_vertex=new int[M], *way=new int[N];

    for(int i=0; i<M; i++)
        visited_vertex[i]=0;
    int idx_V=0,idx_W=0;

    while(true)
    {
        bool check_find=false;
        for(int i=0; i<N; i++)
            if(TG[i].initialV==idx_V&&visited_vertex[TG[i].terminalV]==0&&TG[i].troughput-TG[i].flow>0)
            {
                idx_V=TG[i].terminalV;
                way[idx_W]=i;
                idx_W++;
                visited_vertex[idx_V]=1;
                check_find=true;
                break;
            }

        if(check_find==true&&idx_V!=M-1) continue;

        if(check_find==true&&idx_V==M-1)
        {
            int min=TG[way[0]].troughput-TG[way[0]].flow;
            for(int i=1;i<idx_W;i++)
                if(TG[way[i]].troughput-TG[way[i]].flow<min)
                    min=TG[way[i]].troughput-TG[way[i]].flow;
            for(int i=0;i<idx_W;i++)
                TG[way[i]].flow+=min;

           for(int i=0; i<M; i++)
               visited_vertex[i]=0;
           idx_V=0,idx_W=0;
           continue;
        }

        if(check_find==false&&idx_V!=0)
        {
            idx_W--;
            idx_V=TG[way[idx_W]].initialV;
            continue;
        }

         if(check_find==false&&idx_V==0) break;

    }
}

void second_step(Arc *TG,int N,int M)//N-дуги М-вершины
{
    int *visited_vertex=new int[M], *way[2];
    way[0]=new int[N];
    way[1]=new int[N];

    for(int i=0; i<M; i++)
        visited_vertex[i]=0;
    visited_vertex[0]=1;
    int idx_V=0,idx_W=0;

        while(true)
    {

        bool check_find=false;
        for(int i=0; i<N; i++)
         {
            if(TG[i].initialV==idx_V&&visited_vertex[TG[i].terminalV]==0&&TG[i].troughput-TG[i].flow>0)
             {
                idx_V=TG[i].terminalV;
                way[0][idx_W]=i;
                way[1][idx_W]=1;
                idx_W++;
                visited_vertex[idx_V]=1;
                check_find=true;
                break;
             }
            if(TG[i].terminalV==idx_V&&visited_vertex[TG[i].initialV]==0&&TG[i].flow>0)
             {
                idx_V=TG[i].initialV;
                way[0][idx_W]=i;
                way[1][idx_W]=-1;
                idx_W++;
                visited_vertex[idx_V]=1;
                check_find=true;
                break;
             }
         }

        if(check_find==true&&idx_V!=M-1) continue;

        if(check_find==true&&idx_V==M-1)
        {
            int min=TG[way[0][0]].troughput-TG[way[0][0]].flow;
            for(int i=1;i<idx_W;i++)
            {
                if(way[1][i]==1&&TG[way[0][i]].troughput-TG[way[0][i]].flow<min)
                    min=TG[way[0][i]].troughput-TG[way[0][i]].flow;
                if(way[1][i]==-1&&TG[way[0][i]].flow<min)
                    min=TG[way[0][i]].flow;/////////////////////////////////////////
            }
            for(int i=0;i<idx_W;i++)
                TG[way[0][i]].flow+=way[1][i]*min;

           for(int i=0; i<M; i++)
               visited_vertex[i]=0;
           idx_V=0,idx_W=0;
           continue;
        }

        if(check_find==false&&idx_V!=0)
        {
            idx_W--;
            if(way[1][idx_W]==1)
                idx_V=TG[way[0][idx_W]].initialV;
                else
                    idx_V=TG[way[0][idx_W]].terminalV;

            continue;
        }
         if(check_find==false&&idx_V==0) break;
    }
}

int main()
{
    int N,M;//N-дуги М-вершины
    Arc *TG;

    ifstream graf;//считываем с файла таблицу графа
    graf.open("graf2.txt");
    graf>>N;
    graf>>M;
    TG=new Arc[N];
    for(int i=0; i<N; i++)
    {
        graf>>TG[i].initialV;
        graf>>TG[i].terminalV;
        graf>>TG[i].troughput;
        TG[i].flow=0;
    }

    show(TG,N);
    cout<<endl;
    first_step(TG,N,M);
    show(TG,N);
    second_step(TG,N,M);
    cout<<endl;
    show(TG,N);
    _getch();
    return 0;
}

