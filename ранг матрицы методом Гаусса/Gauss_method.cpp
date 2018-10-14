#include<iostream>
#include<conio.h>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;

class Matrix
{
private:
    double **Mat;
    unsigned int numStrings,numColumns;
public:
    Matrix(unsigned int S,unsigned int C):numStrings(S),numColumns(C)//конструктор и деструктор
     {
       Mat=new double*[numStrings];
       for(int i=0;i<numStrings;i++)
         Mat[i]=new double[numColumns];
     }
    ~Matrix()
     {
         for(int i=0;i<numStrings;i++)
            delete[] Mat[i];
         delete[] Mat;
     }
     /////////////////////////////////////////////////////////////////методы
     void show()
     {
         for(int i=0;i<numStrings;i++)
                for(int k=0;k<numColumns;k++)
                 {
                     cout<<Mat[i][k];
                      if(k==numColumns-1) cout<<endl;
                        else cout<<' ';
                 }
     }

     double& at(unsigned int i,unsigned int j)
     {
         if(i<numStrings&&j<numColumns)
            return Mat[i][j];
         else
         {
          cout<<"Yor are traying tp access an element that doesn't exist"<<endl;
          return Mat[0][0];
         }
     }

     void deleteString(unsigned int numSt)
     {
         if(numSt<numStrings&&numSt>=0)
         {
          for(int i=numSt;i<numStrings-1;i++)
            Mat[i]=Mat[i+1];
          delete[] Mat[--numStrings];

            double **tmp=new double*[numStrings];
            for(int i=0;i<numStrings;i++)
                tmp[i]=Mat[i];
            delete[] Mat;
            Mat=new double*[numStrings];
            for(int i=0;i<numStrings;i++)
                Mat[i]=tmp[i];
            delete[] tmp;
         } else cout<<"Error in deleteString"<<endl;
     }

     void deleteColumns(unsigned int numCo)
     {
         if(numCo<numColumns)
         {
             double* temp=new double[numColumns-1];
             for(int i=0;i<numStrings;i++)
             {
              int index=0;
              for(int j=0;j<numColumns;j++)
                  if(j!=numCo) temp[index++]=Mat[i][j];
              delete[] Mat[i];
              Mat[i]=new double[numColumns-1];
              for(int k=0;k<numColumns;k++)
                Mat[i][k]=temp[k];
             }
             delete[] temp;
             numColumns--;
         }
     }

    void PerSrings(int a,int b)//PermutationSrings
     {
         if(a<numStrings&&b<numStrings)
         {
           double *c=Mat[a];
           Mat[a]=Mat[b];
           Mat[b]=c;
           //cout<<"DA";
         }else cout<<"Error in PermutationSrings"<<endl;


     }
     unsigned int getStrings()
     {return numStrings;}
     unsigned int getColumns()
     {return numColumns;}
};

int main()
{
double eps=0.000001;
int N,M;
cout<<"Enter number of strings: ";
cin>>N;
cout<<"Enter number of columns: ";
cin>>M;

Matrix A(N,M);//вызов конструктора

for(int i=0;i<A.getStrings();i++)
    for(int j=0;j<A.getColumns();j++)
     cin>>A.at(i,j);/////////////////////////////доделать рандом
//A.show();
cout<<endl;


int idx=0;
for(int i=0;i<A.getStrings()&&idx<A.getColumns();i++)//приводим к трапецевидному виду//
{
    if(fabs(A.at(i,idx))<=eps)//проверка главной диагонали на ноль
    {
        bool check=false;
        for(int j=i;j<A.getStrings();j++)
            if(fabs(A.at(j,idx))>=eps)
             {
               A.PerSrings(i,j);
               check=true;
               break;
             }
        if(check==false)
         {
          idx++;
          i--;
          continue;;
         }
    }

   for(int j=i;j<A.getStrings();j++)////приводим коллонку к 1ному элементу на главной диагонале
    if(fabs(A.at(j,idx))>eps)
    {
     double tmp=A.at(j,idx);
       for(int k=idx;k<A.getColumns();k++)
        A.at(j,k)=A.at(j,k)/tmp;
    }

   for(int j=i+1;j<A.getStrings();j++)////вычитание
       if(fabs(A.at(j,idx))>eps)
         for(int k=idx;k<A.getColumns();k++)
        A.at(j,k)=A.at(j,k)-A.at(i,k);

idx++;
}

for(int i=0;i<A.getStrings();i++)//удаляем пустые строки
{
    bool check=false;
    for(int j=0;j<A.getColumns();j++)
        if(fabs(A.at(i,j)>=eps)) check=true;
    if(check==false) {A.deleteString(i);i--;}
}

if(A.getStrings()>0)
 {A.show();cout<<endl<<"Rank matrix="<<A.getStrings()<<endl;}
   else cout<<endl<<"Is the zero matrix, the rank is 0\n";

   getch();
   return 0;
}
