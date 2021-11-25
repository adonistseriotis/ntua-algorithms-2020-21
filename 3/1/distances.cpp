#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> tupla;
typedef pair<tupla,int> edge;
typedef vector<edge> Edge;
typedef vector<tupla> subsets;      //First is parent, second is rank

struct MST{
    int V;
    vector<tupla>* adj;
    unordered_map<int, long long int> result;

    void initMST(int V)
    {
        this->adj = new vector<tupla>[V];
        this->V=V;
    }

    void addEdge(int u, int v, int w)
    {
        this->adj[u].push_back({v,w});
        this->adj[v].push_back({u,w});
    }

    int DFSutil(int v,long long int weight, bool visited[])
    {
        long long int cnt=0;
        visited[v] = true;
        vector<tupla>::iterator i;
        for(i=this->adj[v].begin(); i<this->adj[v].end(); ++i)
            if(!visited[(*i).first])
            {
                cnt += DFSutil((*i).first,(*i).second, visited);
                cnt++;
            }
        if(weight == -1)
        {
            if(cnt == 1)
                result[adj[v][0].second] = V-1;
            return 0;
        }
        result[weight] = ((V-1-cnt)*(cnt+1));
        return cnt;
        //return sum + ((cnt==0)?((this->V - 1)*weight):((this->V-1-cnt)*(cnt+1)*weight));
    }

    void DFS(int v)
    {
        bool * visited = new bool[this->V];
        for(int i = 0; i < V; i++)
            visited[i]=false;

        this->DFSutil(v,-1,visited);
    }

    void printTree () 
    {
        for (int i = 0; i < V; i++) 
        {
            cout << i + 1 << ": ";
            for (unsigned long int j = 0; j < adj[i].size(); j++)
                cout << adj[i][j].first + 1 << " ";
            cout << endl;
        }
    }
};

struct Graph{
    int V;
    int E;

    Edge edges;

    MST mst;

    Graph(int N, int M)
    {
        this->V = N;
        this->E = M;
        this->edges.reserve(M);
        this->mst.initMST(N);
    }

    /* Custom comparator */
   /*  bool SortEdges(const edge &x, edge &y)
    {
        return (x.second < y.second);
    } */

    /* Method to add edges */
    void addEdge(int u, int v, int w)
    {
        this->edges.push_back({{u,v},w});
    }

   /*  void rectify()
    {
        sort(this->edges.begin(), this->edges.end(), SortEdges);
    } */
};

int find(subsets &subset, int i)
{
    if(subset[i].first != i)
        subset[i].first = find(subset, subset[i].first);

    return subset[i].first;
}

void Union(subsets &subset, int x, int y)
{
    int xroot = find(subset,x);
    int yroot = find(subset,y);

    if(subset[xroot].second < subset[yroot].second)
        subset[xroot].first = yroot;
    else if (subset[xroot].second > subset[yroot].second)
        subset[yroot].first = xroot;
    else
    {
        subset[yroot].first = xroot;
        subset[xroot].second++;
    }
}

void boruvkaMST(struct Graph * g)
{
    int V=g->V, E=g->E;
    Edge edges = g->edges;

    subsets subset;
    int cheapest[V];

    for(int i=0; i<V; ++i)
    {
        subset.push_back({i,0});
        cheapest[i] = -1;
    }

    int numTrees = V;
    
    while(numTrees > 1)
    {
        for(int i = 0; i < V; ++i)
        {
            cheapest[i] = -1;
        }

        /* Find next cheapest edges */
        for(int i=0; i<E; i++)
        {
            int set1 = find(subset, edges[i].first.first);
            int set2 = find(subset, edges[i].first.second);

            if(set1 == set2)
                continue;

            else
            {
                if(cheapest[set1] == -1 || edges[cheapest[set1]].second > edges[i].second)
                    cheapest[set1] = i;
                
                if(cheapest[set2] == -1 || edges[cheapest[set2]].second > edges[i].second)
                    cheapest[set2] = i;
            }       
        }

        for(int i=0; i<V; i++)
        {
            int cheap = cheapest[i];
            if(cheap != -1)
            {
                int set1 = find(subset,edges[cheap].first.first);
                int set2 = find(subset,edges[cheap].first.second);

                if(set1==set2)
                    continue;
                
                g->mst.addEdge(edges[cheap].first.first, edges[cheap].first.second, edges[cheap].second);
                
               // printf("Edge %d-%d included in MST\n",edges[cheap].first.first+1, edges[cheap].first.second+1);
                Union(subset,set1,set2);
                numTrees--;
            }
        }
    }
}


string D2B(int n)
{
    string s = bitset<64> (n).to_string();

    const auto loc1 = s.find('1');

    if(loc1 != string::npos)
        return s.substr(loc1);

    return "0";
} 

int main()
{
    std::ios_base::sync_with_stdio(false); //Remove sync with C standards speeds up IO

    /* Define variables */
    int N,M,u,v,w;
    stack<bool> bin;

    /* Get number of nodes and edges */
    cin >> N >> M;

    Graph g(N,M);
    
    /* Get edges */
    for(int i=0; i<M; i++)
    {
        cin >> u >> v >> w;
        g.addEdge(u-1,v-1,w);
    }

    boruvkaMST(&g);

    //g.mst.DFS(0);
    g.mst.printTree();

    /* for(auto const& pair: g.mst.result)
        cout << "(" << pair.second << ", " << pair.first << ")\n"; */

   /*  for (int i = 0; i < M || g.mst.result[i] != 0; i++)
    {
        g.mst.result[i+1] += g.mst.result[i]/2;
        bin.push(g.mst.result[i]&1);
    }
    while(bin.top() == 0)
        bin.pop();
    while(!bin.empty())
    {
        cout << bin.top();
        bin.pop();
    }
    cout << "\n"; */
    return 0;
}