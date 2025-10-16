#include<iostream>
#include<vector>
#include<queue>
#include<sstream>
#include<map>
#include<unordered_map>
#include<stack>
#include<algorithm>
using namespace std;
vector<vector<int>> Grapher(const std::string& input);
vector<vector<int>> graph();
void print(const vector<vector<int>> &graph);
void bfs_connected(vector<vector<int>> &G, int start);
void dfs_connected_(vector<vector<int>> &G, vector<int> &traversal, vector<bool> &visited, int node);
void dfs_connected(vector<vector<int>> &G, int start);
vector<vector<int>> grapher(const string& input) {
    istringstream iss(input);
    streambuf* cinbuf = cin.rdbuf(); 
    cin.rdbuf(iss.rdbuf());
    auto G = graph();
    cin.rdbuf(cinbuf); 
    return G;
}
vector<vector<int>> graph(){
    int nodes;cin>>nodes;
    vector<vector<int>> graphs;

    for(int i=0;i<nodes;i++){
        int degree;cin>>degree;
        vector<int> current(degree);
        for(int j=0;j<degree;j++)cin>>current[j];
        graphs.push_back(current);
    }return graphs;
}
void print(const vector<vector<int>> &graph){
    cout<<"Graph:"<<endl;
    for(int i=0;i<(int)graph.size();i++){
        cout<<i<<" >> ";
        for (int j=0;j<(int)graph[i].size();j++)cout<<graph[i][j]<<" ";cout<<endl;
    }
}
void bfs_connected(const vector<vector<int>> &G, int start){
    int nodes = G.size();
    vector<bool> visited(nodes,false);
    queue<int> q;
    q.push(start);
    visited[start]=true;
    cout<<"bfs_connected >> ";
    while(!q.empty()){
        int current = q.front();
        q.pop();
        cout<< current<<" ";
        for(int neighbor:G[current]){
            if(!visited[neighbor]){
                visited[neighbor]=true;
                q.push(neighbor);
            }
        }
    }cout<<endl;
}
void dfs_connected_(const vector<vector<int>> &G, vector<int> &traversal, vector<bool> &visited, int node){
    if(!visited[node]){
        visited[node]=true;
        traversal.push_back(node);
        for(auto child : G[node])
        dfs_connected_(G, traversal, visited, child);
    }
}
void dfs_connected(const vector<vector<int>> &G, int start){
    int size = G.size();
    vector<bool> visited(size,false);
    vector<int> traversal;
    cout<<"dfs_connected >> ";
    dfs_connected_(G, traversal, visited, start);
    for(int node: traversal)cout<<node<<" ";cout<<endl;
}
void reg_(const vector<vector<int>> &G, vector<bool> &visited, int node){
    if (!visited[node]){
        visited[node]=true;
        for(auto current:G[node]){
            reg_(G,visited,current);
        }
    }
}
void regions(const vector<vector<int>> &G){
    int size = G.size();
    vector<bool> visited(size,false);
    int count=0;
    for(int node=0;node<size;node++){
        if (!visited[node]){
            count++;
            reg_(G,visited,node);
        }
    }
    cout<<"Regions: "<<count<<endl;
}
void bfs(const vector<vector<int>> &G){
    int size= G.size();
    vector<bool> visited(size, false);
    queue<int> q;
    cout<<"BFS -> "<<endl;
    int count=0;
    for(int i=0;i<size;i++){
        if(!visited[i]){
            q.push(i);
            visited[i]=true;
            count++;
            cout<<"Connected component "<<count<<": ";
            while(!q.empty()){
                int current = q.front();
                q.pop();
                cout<<current<<" ";
                for(int node: G[current]){
                    if(!visited[node]){
                        visited[node]=true;
                        q.push(node);
                    }
                }
            }cout<<endl;
        }
    }
}
void dfs_(const vector<vector<int>> &G, vector<bool> &visited, int node){
    visited[node]=true;
    cout<<node<<" ";
    for(int neighbour: G[node]){
        if(!visited[neighbour]){
            dfs_(G,visited,neighbour);
        }
    }
}
void dfs(const vector<vector<int>> &G){
    int size = G.size();
    int count =0;
    cout<<"DFS ->"<<endl;
    vector<bool> visited(size,false);
    for(int i=0;i<size;i++){
        if(!visited[i]){
            count++;
            cout<<"Connected component "<<count<<": ";
            dfs_(G, visited, i);
            cout<<endl;
            }
    }
}

bool cycle_bfs_(const vector<vector<int>> &G, int start){
    vector<bool> visited(G.size(),false);
    queue<pair<int,int>> q;
    q.push({start,-1});
    
    while(!q.empty()){
        pair<int,int> curr = q.front();
        if(!visited[curr.first]){
            visited[curr.first]=true;
            q.pop();
            for(auto node: G[curr.first]){
                if(node != curr.second){
                    q.push({node,curr.first});
                }
            }
        }else{
            return true;
        }

    }
    return false;
}
bool detect_bfs(const vector<vector<int>> &G,vector<bool> &visited,int start){
    queue<pair<int,int>> q;
    q.push({start,-1});
    cout<<"{";
    bool iscycle = false;
    while(!q.empty()){
        pair<int,int> curr = q.front();q.pop();
        if(!visited[curr.first]){
            cout<<curr.first<<" ";
            visited[curr.first]=true;
            for(auto node:G[curr.first]){
                if(node != curr.second){
                    q.push({node,curr.first});
                }
            }
        }
        else{
            iscycle=true;
        }
    }
    cout<<"} : ";
    return iscycle;
}
void cycle_bfs(const vector<vector<int>> &G){
    vector<bool> visited(G.size(),false);
    for (int i=0;i<visited.size();i++){
        if(!visited[i]){
            cout<<"Cycle in "<<(detect_bfs(G,visited,i)? "true":"false")<<endl;
        }
    }
}
bool detect_dfs(const vector<vector<int>>&G,vector<bool>&visited,vector<int> &trace,int start,int parent){
    bool iscycle = false;
    if(!visited[start]){
        visited[start]=true;
        trace.push_back(start);
        for(auto node : G[start]){
            if(node!=parent){
                iscycle=detect_dfs(G,visited,trace,node,start);
            }
        }
    }
    else{
        iscycle =  true;
    }
    return iscycle;
}
void cycle_dfs(const vector<vector<int>> &G){
    vector<bool> visited(G.size(),false);
    for(int i=0;i<G.size();i++){
        if(!visited[i]){
            vector<int> trace(0);
            bool iscycle = detect_dfs(G,visited,trace,i,-1);
            cout<<(iscycle? "There's a ":"There's no")<<"cycle in { ";
            for(int j=0;j<trace.size();j++){
                cout<<trace[j]<<" ";
            }
            cout<<"}"<<endl;
        }
    }
}
bool dfs_b(const vector<vector<int>>&G,vector<int> &colors,int start,int color){
    bool isBipartite = true;
    colors[start] = color;
    cout<<start<<"->";
    if(G[start].size()>0){
        for(int node : G[start]){
            if(color == colors[node]){
                isBipartite = false;
            }
            if(colors[node]==-1){
                if(!dfs_b(G,colors,node,!color)){
                    isBipartite = false;
                }
            }
        }
    }
    return isBipartite;
}
bool bipartite(const vector<vector<int>> &G){
    bool isBipartite = true;
    vector<int> colors(G.size(),-1);
    int count = 0;
    for(int i=0;i<G.size();i++){
        if(colors[i]==-1){
            count++;
            cout<<"SG "<<count<<": ";
            if(!dfs_b(G,colors,i,1)){
                isBipartite = false;
                cout<<"=> false;";
            }
            else{
                cout<<"=> true";
            }
            cout<<endl;
        }
    }
    return isBipartite;
}

bool bfs_b(const vector<vector<int>>&G, vector<int> &colors, int start,int color){
    queue<int> q;
    bool isBipartite = true;
    q.push(start);
    colors[start]=color;
    while(!q.empty()){
        int curr = q.front();
        q.pop();
        cout<<curr<<"-"<<(colors[curr]?"Red":"Blue")<<" ";
        for(int node : G[curr]){
            if(colors[node]==colors[curr]){
                isBipartite = false;
            }
            if(colors[node]==-1){
                q.push(node);
                colors[node] = !colors[curr];
            }
        }
    }
    return isBipartite;
}
bool bipartite_bfs(const vector<vector<int>> &G){
    vector<int> colors(G.size(),-1);
    bool isBipartite = true;
    int count = 0;
    for(int i=0;i<G.size();i++){
        if(colors[i] == -1){
            count++;
            cout<<"SubGraph "<<count<<"{";
            isBipartite = bfs_b(G,colors,i,1);
            cout<<"}: "<<(isBipartite? "true":"false")<<endl;

        }
    }
    return isBipartite;
}
void dfs_topo(const vector<vector<int>>&G,vector<bool>&visited,stack<int> &s,int node){
    visited[node]=true;
    for(int neighbor: G[node]){
        if(!visited[neighbor]){
            dfs_topo(G,visited,s,neighbor);
        }
    }
    s.push(node);

}
vector<int> topology(const vector<vector<int>> &G){
    int size = G.size();
    vector<bool> visited(size,false);
    vector<int> out;
    stack<int> s;
    for(int i=0;i<size;i++){
        if(!visited[i]){
            dfs_topo(G,visited,s,i);
        }
    }
    for(int j=0;j<size;j++){
        out.push_back(s.top());
        s.pop();
    }
    return out;
}
vector<int> safesates(const vector<vector<int>>&G){
    int size = G.size();
    vector<int> indegree(size,0);
    queue <int>q;
    vector<vector<int>> rev(size);
    vector<int>safenodes;
    for(int i=0;i<size;i++){
        for(auto it: G[i]){
            rev[it].push_back(i);
            indegree[i]++;
        }
    }
    for(int k=0;k<size;k++){
        if(indegree[k]==0){
            q.push(k);
        }
    }
    while(!q.empty()){
        int curr = q.front();
        q.pop();
        safenodes.push_back(curr);
        for(auto it: rev[curr]){
            indegree[it]--;
            if(indegree[it]==0){
                q.push(it);
            }
        }
    }
    sort(safenodes.begin(),safenodes.end());
    return safenodes;
}
int main(){
    string input = "20 2 1 4 3 0 2 3 1 1 1 1 3 0 5 7 2 4 6 2 5 7 2 4 6 1 9 2 8 10 1 9 2 12 13 2 11 14 2 11 14 2 12 13 2 16 17 2 15 17 3 15 16 18 1 17 0";
    string inp = "8 3 4 5 6 2 4 7 1 5 2 6 7 2 0 1 2 0 2 0 1 0 1 2 3";
    string top="6 2 3 4 1 0 1 0 0 0 2 3 4";
    string safe="6 1 3 2 0 4 1 0 0 1 5 2 3 4";
/*
    const vector<vector<int>>G = grapher(input);
    print(G);
    bfs_connected(G,0);
    dfs_connected(G,0);
    bfs(G);
    dfs(G);
    regions(G);
    cout<<"Cycle: "<<cycle_bfs_(G,3)<<endl;
    cycle_bfs(G);
    cycle_dfs(G);
    cout<<(bipartite(G)? "Bipartite":"Not bipartite")<<endl;
    bipartite_bfs(G);
    const vector<vector<int>>Gs = grapher(top);
    print(Gs);
    vector<int> ans = topology(Gs);
    cout<<"Topological Sort: ";
    for(int node: ans)cout<<node<<" ";cout<<endl;
*/
    const vector<vector<int>>Gs = grapher(safe);
    print(Gs);
    const vector<int> ans = safesates(Gs);
    cout<<"safesates : ";
    for(int node: ans)cout<<node<<" ";cout<<endl;
    return 0;

}
//whats up my friend whar are  you doing my frined are u okay brother whats up bro get some sleep my friend why are u doing okay