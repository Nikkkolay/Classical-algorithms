#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

class OffsetTable
{
private:
    char *simbols;
    int *shift;
    bool check;
    int idx;
public:
    OffsetTable(string str):idx(1)
    {
        char *tempC=new char[str.size()+1];
        int *tempI=new int[str.size()];
        for(int i=str.length()-2; i>-1; i--)
        {
            check=true;
            for(int j=i+1; j<str.size()-2; j++)
                if(str[i]==str[j]) check=false;
            if(check==true)
            {
                tempC[idx]=str[i];
                tempI[idx]=str.length()-1-i;
                idx++;
            }
        }
        check=true;
        for(int i=1; i<idx; i++)
            if(tempC[i]==str[str.size()-1]) check=false;
        if(check==true)
        {
            tempC[0]=str[str.size()-1];
            tempI[0]=str.size();
        }
        else
        {
            for(int i=1; i<idx; i++)
            {
                tempC[i-1]=tempC[i];
                tempI[i-1]=tempI[i];
            }
            idx--;
        }

        simbols=new char[idx+1];
        simbols[idx]='\0';
        shift=new int[idx];
        for(int i=0; i<idx; i++)
        {
            simbols[i]=tempC[i];
            shift[i]=tempI[i];
        }
        delete [] tempC;
        delete [] tempI;
    }
/////////////////////////////////////////////////////////
    void show()
    {
        for(int i=0; simbols[i]!='\0'; i++)
            cout<<simbols[i]<<' '<<shift[i]<<endl;
    }

    char char_get(int i)
    {return simbols[i];}

    int shift_get(int i)
    {return shift[i];}

    int lght()
    {return idx;}
};

int main()
{
//cat dog elephant canary giraffe cat platypus
    vector<int> coincidence;
    string str,pattern;
    //cout<<"Enter string: ";
    //getline(cin,str);

    ifstream text("text.txt");
    char ch;
    while( text.get(ch))
        str+=ch;
    cout<<str<<endl;

    cout<<"Enter pattern: ";
    getline(cin,pattern);
    OffsetTable T=pattern;
//T.show();
    for(int i=pattern.length()-1; i<str.length();)
    {
      bool  match=true;
        for(int j=pattern.length()-1; j>-1; j--)
            if(pattern[j]!=str[i-(pattern.length()-1)+j])
            {
                match=false;
                bool check=false;
                for(int k=0; k<T.lght(); k++)
                    if(T.char_get(k)==str[i-(pattern.length()-1)+j])
                    {
                        check=true;
                        i+=T.shift_get(k);
                        break;
                    }
                if(check==false)
                    i+=pattern.length();
                break;
            }
        if(match==true)
        {
            coincidence.push_back(i+1-pattern.length());
            i+=pattern.length();
        }
    }
    if(coincidence.size()==0)
    cout<<"No matches found.";
    else
    {
        cout<<endl<<"match found: ";
        for(int i=0;i<coincidence.size();i++)
           cout<<coincidence[i]<<' ';
    }
    char end;
    cin>>end;
    return 0;
}
