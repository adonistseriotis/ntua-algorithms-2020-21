#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>

using namespace std;
using namespace std::chrono;

typedef vector<vector<int>> matrix;

void solve(int i, int prevj, int upjlim, int l, int start, int end, matrix &cost, matrix &C)
{
    if(end<start)
        return;
    int newupjlim=min(upjlim,i);
    int min=cost[0][i];
    int temp;
    int mincut = 0;
    for(int j=newupjlim-1; j>=prevj+1; j--)
    {
        temp = C[j][l-1]+cost[j+1][i];
        if(temp< min)
        {
            min = temp;
            mincut=j;
        }
        if(temp==0)
            break;
    }
    C[i][l]=min;
    int newi=(i + (end+1-i)/2);
    solve((start + (i-start)/2),prevj,mincut+1,l,start,i-1,cost,C);    //Recurse left half
    solve(newi,mincut-1,upjlim,l,i+1,end,cost,C);     //Recurse right half
}

int main()
{
    std::ios_base::sync_with_stdio (false); //Remove sync with c standards, speeds up cin

    /* Define variables */
    int N,K;

    /* Get number of substances and bottles */
    cin >> N >> K;

    /* Array to read reactions */
    //int A[N][N];
    matrix A;
    
    /* Array to hold calculated reactions */
    //int cost[N][N];
    matrix cost(N, vector<int> (N,0)); 

    /* Array for recursion */
    //int C[N][K];
    matrix C(N, vector<int> (K,0));

    /* Read input */
    for(int i=0; i< N; i++)
    {
        cost[i][i]=0;           //Make diagonal equal to 0
        vector<int> temp;       //Vector to hold temporarily the lines of the matrix
        int readValue;          //Value to hold temporarily A[i][j]
        for(int j=i+1; j<N; j++)
        {
            cin >> readValue;
            temp.push_back(readValue);
            cost[i][j] = readValue + cost[i][j-1];
        }
        A.push_back(temp);
        temp.clear();
    }

    /* Calculate all costs */
    for(int i=N-2; i >= 0; i--)
    {
        for(int j=N-1; j>=i+2; j--)
        {
            cost[i][j]+=cost[i+1][j];
        }
    }
    if(K==1)
    {
        printf("%d\n", cost[0][N-1]);
        return 0;
    }
    for(int i=0; i<N; i++)
    {
        C[i][0] = cost[0][i];   //Initialize recursive array
    }
    for(int l=1; l<K; l++)
    {
        solve(N/2,-1,N,l,0,N-1,cost,C);
    }
    printf("%d\n", C[N-1][K-1]);
    return 0;
}

