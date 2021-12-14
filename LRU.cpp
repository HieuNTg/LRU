#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

struct pageNumber
{
    int sequencePage[100];
    int idx[100];
    string PageFault;
};

int MINidx(pageNumber *pN, int i, int m)
{
    int min= 0;
    for (int j=0; j<m; j++)
    {
        if (pN[i].idx[j] < pN[i].idx[min])
            min = j;
    }
    return min;
}

int main()
{
    pageNumber *pN;
    int sequence[100];
    int n,m;
    cout << "Input number of Sequence Page: ";
    cin >> n;
    cout <<"Referenced sequence: ";
    for (int i=0; i<n; i++)
        cin >> sequence[i];
    cout << "Input page frames: ";
    cin >> m;
    pN = new pageNumber[n];
    for (int i = 0; i<n; i++)
        for (int j=0; j < m; j++)
        {
            pN[i].sequencePage[j] = -1;
            pN[i].idx[j] = -1;
        }
    for (int i = 0; i<n; i++)
    {
        int avaible = 0;
        for (int j=0; j < m; j++)
            if (sequence[i] == pN[i].sequencePage[j])
                avaible = 1;
        if (avaible == 0)
        {
            int a = MINidx(pN,i,m);
            for (int j=0; j < m; j++)
            {
                if (pN[i].sequencePage[j] == -1)
                {
                    pN[i].sequencePage[j] = sequence[i];
                    pN[i].PageFault = "*";
                    break;
                }
            }
            for (int j=0; j < m; j++)
            {
                if (j == a)
                {
                    pN[i].sequencePage[j] = sequence[i];
                    pN[i].idx[j] = i;
                    pN[i].PageFault = "*";
                    break;
                }
            }
        }
        else 
        {
            for (int j=0; j < m; j++)
                if (pN[i].sequencePage[j]==sequence[i])
                    pN[i].idx[j]=i;
        }
        for (int j = 0;j<m;j++)
        {
            pN[i+1].sequencePage[j]=pN[i].sequencePage[j];
            pN[i+1].idx[j]=pN[i].idx[j];
        }
    }
    cout << "--- Page Replacement algorithm --- "<<endl;
    
    for (int i=0;i<n;i++)
        cout<<setw(4)<<sequence[i]<<setw(4);
    cout<<endl;
    for (int j=0;j<m;j++)
    {
        for (int i =0;i<n;i++)
        {
            if (pN[i].sequencePage[j] != -1)
                cout<<pN[i].sequencePage[j]<<setw(4);
            else
                cout<<" "<<setw(4);
        }
        cout<<endl;
    }
    int dem=0;
    for (int i=0;i<n;i++)
    {
        if (pN[i].PageFault == "*")
            dem++;
        cout<<pN[i].PageFault<<setw(4);
    }
    cout << endl;
    cout << "Number of Page Fault: " << dem;
    return 1;
}
