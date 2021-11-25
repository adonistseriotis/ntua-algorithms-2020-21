#include<iostream>
#include<bits/stdc++.h>

using namespace std;

#define INF -44

int main()
{
    std::ios_base::sync_with_stdio (false); //Remove sync with c standards, speeds up cin cout

    int N,Q;
    priority_queue<int, vector<int>, greater<int>> pq;
    unordered_set<int> visited;
    
    cin >> N >> Q;

    int dj[N],q[Q];
    int mindj=INF;

    for(int i=0; i<N; i++)
    {
        cin >> dj[i];
        if(mindj > dj[i] || mindj==INF)
            mindj = dj[i];
    }

    int c[mindj];

    for(int i=0; i<Q; i++)
    {
        cin >> q[i];
        
        if(i<mindj)
            c[i]=INF;
    }

    for(int i=0; i<N; i++)
    {
        int pivot = dj[i]%mindj;
        if(c[pivot] > dj[i] || c[pivot] == INF)
        {
            c[pivot] = dj[i];
            visited.insert(dj[i]);
            pq.push(dj[i]);
        }
    }

    while(!pq.empty())
    {
        int top = pq.top();
        pq.pop();

        if(c[top%mindj] == top)
        {
            visited.insert(top);
        }
        unordered_set<int>::iterator i;
        for(i = visited.begin(); i != visited.end(); i++)
        {
            int sum = (*i + top);
            int pivot = (sum)%mindj;
            if(c[pivot] > (sum) || c[pivot] == INF)
            {
                c[pivot] = sum;
                pq.push(sum);
            }
        }
    }

    for(int i=0; i<Q; i++)
    {
        if(c[q[i]%mindj]<= q[i])
            cout << "YES\n";
        else
            cout << "NO\n";
    }

    return 0;
}