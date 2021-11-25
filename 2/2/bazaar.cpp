#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>
using namespace std;

#define INF -42

typedef vector<pair<int,int>> inventory;

inventory A1,B1,C1,A2,B2,C2,A3,B3,C3;
vector<int> A,B,C,v1,v2,v3;
int N,M;

int add(const int &x, const int &y)
{
    if(x == INF || y == INF)
        return INF;
    return x+y;
}

int min(const int &a, const int &b)
{
    if(a == INF && b == INF)
        return INF;
    else if(a == INF || b == INF)
        return (a==INF) ? b : a;
    return (a < b) ? a : b;
    
}

void input(int vendor, char object, int cardin, int price)
{
    pair<int,int> p;
    p.first = cardin;
    p.second = price;
    switch (vendor)
    {
    case 1:
        switch (object)
        {
            case 'A':
                A1.push_back(p);
                break;
            case 'B':
                B1.push_back(p);
                break;
            case 'C':
                C1.push_back(p);
                break;
        }
        break;
    case 2:
        switch (object)
        {
            case 'A':
                A2.push_back(p);
                break;
            case 'B':
                B2.push_back(p);
                break;
            case 'C':
                C2.push_back(p);
                break;
        }
        break;
    case 3:
        switch (object)
        {
            case 'A':
                A3.push_back(p);
                break;
            case 'B':
                B3.push_back(p);
                break;
            case 'C':
                C3.push_back(p);
                break;
        }
        break;
    }
}
/* max_val is how many we can take from each vendor 
 * choices is how many objects of same type each vendor offers */

vector<int> knapsack(const inventory &inv, const int &max_val)
{
    /* Vectors for the recursion (only 2 leves required) */
    vector<int> b (max_val+1, INF),n (max_val+1, 0);
    vector<vector<int>> K;
    K.push_back(b);
    K.push_back(n);
    K[0][0] = 0;
    for(int i=1; i<max_val+1; i++)
    {
        if(i <= inv[0].first)
            K[0][i] = inv[0].second;
    }
    int choices = inv.size();
    //cout << "OK so far...K1\n" << K[1][0];
    //cout << choices << "\n";
    for(int i=1; i<choices; i++)
    {
        for(int j=0; j<= max_val; j++)
        {
            //cout << "OK so far.. K2 " << i << ", " << j  << "value: " << inv[i-1].second << endl;
            if(inv[i].first <= j)
                K[1][j] = min(add(inv[i].second, K[0][j-inv[i].first]), K[0][j]);       
            else 
                K[1][j] = min(inv[i].second, K[0][j]);
        }
        //cout << "OK here also...\n";
        K[0].swap(K[1]);
        //K[1][0] = 0;
        //cout << "OK\n";
    }

    return K[0];

}

vector<int> doStuff(int n)
{
    vector<int> vendor(n+1);
    for(int i=0; i<n+1; i++)
    {
        vendor[i] = add(add(A[i],B[i]),C[i]);
    }
    return vendor;
}

int main()
{
    std::ios_base::sync_with_stdio (false); //Remove sync with c standards, speeds up cin

    int vendor,cardin,price;
    char object;
    cin >> N >> M;
    
/* Fill arrays */
    for(int i=0; i<M; i++)
    {    
        cin >> vendor >> object >> cardin >> price;
        //cout << vendor << " " << object << " " << cardin << " " << price << endl;
        input(vendor,object,cardin,price);
    }

    if(A1.size() != 0 && B1.size() != 0 && C1.size() != 0)
    {
        A=knapsack(A1,N);
        B=knapsack(B1,N);
        C=knapsack(C1,N);
        v1 = doStuff(N);
        A.clear();
        B.clear();
        C.clear();
    }
    else
    {
        for(int i=0; i<N; i++)
            v1.push_back(INF);
    }
    
    if(A2.size() != 0 && B2.size() != 0 && C2.size() != 0)
    {
        A=knapsack(A2,N);
        B=knapsack(B2,N);
        C=knapsack(C2,N);
        v2 = doStuff(N);
        A.clear();
        B.clear();
        C.clear();
    }
    else
    {
        for(int i=0; i<N; i++)
            v2.push_back(INF);
    }

    if(A3.size() != 0 && B3.size() != 0 && C3.size() != 0)
    {
        A=knapsack(A3,N);
        B=knapsack(B3,N);
        C=knapsack(C3,N);
        v3 = doStuff(N);
    }
    else
    {
        for(int i=0; i<N; i++)
            v3.push_back(INF);
    }
    //cout << "OK so far....4"<<endl;
    int result=INF;
    for (int i=0; i<=N; i++)
    {   
        if(v1[i]==INF)
            continue;
        for(int j=0; j<=N; j++)
        {
            if(v2[j]==INF)
                continue;
            if(i+j>=N)
                result = min(result, add(v1[i],v2[j]));
            else
            {
                if(v3[N-i-j]==INF)
                    continue;
                result = min(result, add(v1[i],add(v2[j],v3[N-i-j])));
            }
        }
    }
    if(result == INF)
        result = -1;

    printf("%d\n", result);
    return 0;
}