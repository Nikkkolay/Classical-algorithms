#include<iostream>
#include<fstream>
using namespace std;
int main()
{
    int N,**TG,*least_weight,*visited_vertex,*previous_vertex;//кол-во вершин,таблица графа,min вес пути,массив поесещённых вершин,массив адресов предыдущих вершин

    ifstream graf;//считываем с файла таблицу графа
    graf.open("graf.txt");
    graf>>N;
    TG=new int*[N];
    for(int i=0; i<N; i++)
        TG[i]=new int[N];
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            graf>>TG[i][j];
    graf.close();

    least_weight=new int[N];//заполняем массивы веса кротчайшего пути,номера предыдущей вершины и посещения
    previous_vertex=new int[N];
    visited_vertex=new int[N];
    for(int i=0; i<N; i++)
    {
        least_weight[i]=INT_MAX;
        visited_vertex[i]=0;
        previous_vertex[i]=-1;
    }
    int start;
    cout<<"Enter the number of the first vertex ";
    cin>>start;
    cout<<endl;
    least_weight[start]=0;
    previous_vertex[start]=0;

    for(int i=0; i<N; i++)
    {
        int min=INT_MAX,minidx;
        for(int j=0; j<N; j++)
            if(least_weight[j]<min&&visited_vertex[j]==0)
            {
                min=least_weight[j];
                minidx=j;
            }
        visited_vertex[minidx]=1;

        for(int j=0; j<N; j++)
            if(TG[minidx][j]!=0&&visited_vertex[j]==0&&min+TG[minidx][j]<least_weight[j])
            {
                least_weight[j]=min+TG[minidx][j];
                previous_vertex[j]=minidx;
            }
    }

    for(int i=0; i<N; i++)
        if(previous_vertex[i]!=-1)
        {
            cout<<i<<": weight "<<least_weight[i]<<", way ";
            int j=i;
            cout<<j;
            while(j!=start)
            {
                j=previous_vertex[j];
                cout<<'<'<<j;
            }
            cout<<endl;
        } else cout<<i<<": Vertex isn't connected to the beginning of the way."<<endl;
int pause;
cin>>pause;
    return 0;
}
