#include<iostream>
#include<vector>
#include<queue>
using namespace std;

vector<vector<int>> graph(){
    int nodes;
    cin>>nodes;
    vector<vector<int>> graphs;

    for(int i=0;i<nodes;i++){
        int degree;
        cin>>degree;
        vector<int> current(degree);
        for(int j=0;j<degree;j++){
            cin>>current[j];
        }
        graphs.push_back(current);
    }
    return graphs;
}
void print(const vector<vector<int>> &graph){
    cout<<"Graph:"<<endl;
    for(int i=0;i<(int)graph.size();i++){
        cout<<i<<" >> ";
        for (int j=0;j<(int)graph[i].size();j++){
            cout<<graph[i][j]<<" ";
        }cout<<endl;
    }
}
void bfs(vector<vector<int>> &G, int start){
    print(G);
    int nodes = G.size();
    vector<bool> visited(nodes,false);
    queue<int> q;
    q.push(start);
    visited[start]=true;
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
void dfs_(vector<vector<int>> &G, vector<int> &traversal, vector<bool> &visited, int node){
    if(!visited[node]){
        visited[node]=true;
        traversal.push_back(node);
        for(auto child : G[node])
        dfs_(G, traversal, visited, child);
    }
}
void dfs(vector<vector<int>> &G, int start){
    int size = G.size();
    vector<bool> visited(size,false);
    vector<int> traversal;
    cout<<"DFS >> ";
    dfs_(G, traversal, visited, start);
    for(int node: traversal)cout<<node<<" ";cout<<endl;
}
int main(){
    vector<vector<int>>G = graph();
    print(G);
    dfs(G,0);
    return 0;
}


/*

INPUT:

8
2
1 4
3
0 2 3
1
1
1
1
3
0 5 7
2    
4 6
2
5 7
2
4 6


./graph
8
2
1 4
3
0 2 3
1
1
1
1
3
0 5 7
2    
4 6
2
5 7
2
4 6
Graph:
0 >> 1 4 
1 >> 0 2 3 
2 >> 1 
3 >> 1 
4 >> 0 5 7 
5 >> 4 6 
6 >> 5 7 
7 >> 4 6 
DFS >> 1 0 4 5 6 7 2 3 

*/