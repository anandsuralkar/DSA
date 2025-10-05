#include<iostream>
#include<vector>
#include<queue>
#include<sstream>
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
void bfs_connected(vector<vector<int>> &G, int start){
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
void dfs_connected_(vector<vector<int>> &G, vector<int> &traversal, vector<bool> &visited, int node){
    if(!visited[node]){
        visited[node]=true;
        traversal.push_back(node);
        for(auto child : G[node])
        dfs_connected_(G, traversal, visited, child);
    }
}
void dfs_connected(vector<vector<int>> &G, int start){
    int size = G.size();
    vector<bool> visited(size,false);
    vector<int> traversal;
    cout<<"dfs_connected >> ";
    dfs_connected_(G, traversal, visited, start);
    for(int node: traversal)cout<<node<<" ";cout<<endl;
}
void reg_(vector<vector<int>> &G, vector<bool> &visited, int node){
    if (!visited[node]){
        visited[node]=true;
        for(auto current:G[node]){
            reg_(G,visited,current);
        }
    }
}
void regions(vector<vector<int>> &G){
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
void bfs(vector<vector<int>> &G){
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
            cout<<"Connected compunent: "<<count<<endl;
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
void dfs_(vector<vector<int>> &G, vector<bool> &visited, int i){
    for(int node: G[i]){
        if(!visited[node]){
            visited[node]=true;
            cout<<node<<" ";
            dfs_(G,visited,node);
        }
    }
}
void dfs(vector<vector<int>> &G){
    int size = G.size();
    int count =0;
    cout<<"DFS ->"<<endl;
    vector<bool> visited(size,false);
    for(int i=0;i<size;i++){
        if(!visited[i]){
            visited[i]=true;

            count++;
            cout<<"Connected component: "<<count<<endl;
            cout<<i<<" ";
            for(int node: G[i]){
                if(!visited[node]){
                    dfs_(G,visited,node);
                }
            }cout<<endl;
        }
    }
}
int main(){
    string input = "20 2 1 4 3 0 2 3 1 1 1 1 3 0 5 7 2 4 6 2 5 7 2 4 6 1 9 2 8 10 1 9 2 12 13 2 11 14 2 11 14 2 12 13 2 16 17 2 15 17 3 15 16 18 1 17 0";

    vector<vector<int>>G = grapher(input);
    print(G);
    dfs_connected(G,0);
    bfs_connected(G,0);
    bfs(G);
    dfs(G);
    regions(G);
    cout<<" and that is all."<<endl;
    return 0;
}