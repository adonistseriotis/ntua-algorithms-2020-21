#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>
#include <unordered_map> 
using namespace std;

typedef pair<pair<int,int>,long long int> portal; // For ((ai,bi),wi)
typedef unordered_map<int,int> dict;    //For lost Mortys

/* Custom comparator for Sort */
bool SortWeight(const portal &x, const portal &y)
{
    return (x.second > y.second);
}

/* Find node's parent and compress path when is needed */
int find(int *parent, int i)
{

    if(parent[i] != i)
    {
        parent[i] = find(parent,parent[i]);
    }
    
    return parent[i];
}

/* Make union between 2 nodes */
void Union(int *parent, int x, int y)
{
    int xset = find(parent,x-1);
    int yset = find(parent,y-1);
    parent[yset] = xset;

}

/* For Debug */
void printA(int * parent,int N)
{
    cout << "[";
    for(int i = 0; i<N; i++)
    {
        cout << parent[i]+1;
        if(i < N -1) 
            cout << ", ";
    }
    cout << "]\n";
}

int result(int * parent, portal *port,int *c, const int &N, const int &M)
{
    int n = 0;
    int m = 0;
    /* For all Mortys not in position */
    while(n < N)
    {
        if(c[n] != n+1)
        {
            /* See how many portals he needs to go home */
            while(m < M)
            {
                if(find(parent,c[n]-1) == find(parent,n))
                    break;
                else
                {
                    Union(parent,port[m].first.first,port[m].first.second);
                    if(find(parent,c[n]-1) == find(parent,n))
                        break;
                    else
                        m++;
                }
            }
        }
        n++;
    }
    return m;
}

int main()
{
    std::ios_base::sync_with_stdio (false); //Remove sync with c standards, speeds up cin

    /* Define variables */
    int N,M;

    cin >> N >> M;

    int c[N];
    portal port[M];
    int parent[N];

    /* Get Mortys position */
    for(int i = 0; i < N; i++)
    {
        cin >> c[i];
        parent[i] = i;
    }

    for(int i = 0; i < M; i++)
    {
        cin >> port[i].first.first >> port[i].first.second >> port[i].second;
    }

    sort(port,port+M,SortWeight);

   
    printf("%lld\n", port[result(parent,port,c,N,M)].second);
    return 0; 
}

