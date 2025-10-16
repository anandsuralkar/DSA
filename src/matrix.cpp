#include<iostream>
#include<vector>
#include<queue>
#include<set>
using namespace std;
void print(vector<vector<int>> &M,int color){
    for(int k=0;k<20;k++)cout<<"_";cout<<endl;
    for(int i=0;i<M.size();i++){
        cout<<"|";
        for(int j=0;j<M[0].size();j++){
            if(M[i][j] == color||color == -1)
            cout<<M[i][j]<<" ";
            else cout<<"  ";
        }cout<<"|"<<endl;
    }
}
void flood(vector<vector<int>> &M,int x,int y,int color,int prev){
    if(x<0||x>=M.size()||y<0||y>=M[0].size()){
        return;
    }
    if(M[x][y]==color)return;
    if(M[x][y]==prev){
        M[x][y]=color;
    flood(M,x-1,y,color,prev);
    flood(M,x+1,y,color,prev);
    flood(M,x,y-1,color,prev);
    flood(M,x,y+1,color,prev);}
    else return;
}
vector<vector<int>> nearest1(vector<vector<int>> &G) {
    int n = G.size(), m = G[0].size();
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int,int>> q;

    // Push all 1's as sources
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(G[i][j]==1){
                dist[i][j] = 0;
                q.push({i,j});
            }
        }
    }

    int dx[] = {-1,1,0,0};
    int dy[] = {0,0,-1,1};

    while(!q.empty()){
        auto [x,y] = q.front();
        q.pop();

        for(int dir=0; dir<4; dir++){
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            if(nx>=0 && nx<n && ny>=0 && ny<m && dist[nx][ny]==-1){
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx,ny});
            }
        }
    }

    return dist;
}
void bfs(vector<vector<int>> &G,vector<vector<bool>> & visited,int x,int y){
    queue<pair<int,int>> q;
    vector<pair<int,int>> group;
    int sizex = G.size();
    int sizey = G[0].size();
    bool isSurrounded=true;
    q.push({x,y});
    int dx[] = {-1,1,0,0};
    int dy[] = {0,0,-1,1};
    while(!q.empty()){
        auto [a,b] = q.front();
        q.pop();
        if(!visited[a][b]){
            visited[a][b] =true;
            if(G[a][b]==0){
                group.push_back({a,b});
                if(a == 0 || a == sizex-1 || b == 0 || b == sizey-1){
                    isSurrounded = false;
                }
                for(int dir=0;dir<4;dir++){
                    int xx =a+dx[dir];
                    int yy =b+dy[dir];
                    if(xx>=0 && xx<sizex && yy>=0 && yy<sizey){
                        if(G[xx][yy]==0){
                            q.push({xx,yy});
                        }
                    }
                }
            }
        }
    }
    if (isSurrounded){
        for( auto[x,y] : group){
            G[x][y] = 1;
        }
    }
}
vector<vector<int>> surround(vector<vector<int>> &G){
    //O is 0
    //X is 1
    int sizex = G.size();
    int sizey = G[0].size();
    vector<vector<int>> M(sizex,vector<int>(sizey,0));
    vector<vector<bool>> visited (sizex,vector<bool>(sizey,false));
    for(int i = 0;i<sizex;i++){
        for(int j=0;j<sizey;j++){
            M[i][j]=G[i][j];
        }
    }
    for(int i=0;i<sizex;i++){
        for(int j=0;j<sizey;j++){
            if(!visited[i][j] && M[i][j]==0){
                bfs(M,visited,i,j);
            }
        }
    }
    return M;
}
vector<pair<int,int>> bfs_distinct(vector<vector<int>>&G,vector<vector<bool>>&visited,pair<int,int> start){
    vector<int> group;
    queue<pair<int,int>> q;
    vector<pair<int,int>> trace;
    int dx[] = {-1,1,0,0};
    int dy[] = {0,0,-1,1};
    int sizex = G.size();
    int sizey = G[0].size();
    q.push(start);
    while(!q.empty()){
        auto [x,y] = q.front();
        q.pop();
        if(!visited[x][y]){
            visited[x][y]=true;
            trace.push_back({x - start.first ,y - start.second});
            for(int dir=0;dir<4;dir++){
                int xx = x+dx[dir];
                int yy = y+dy[dir];
                if(xx>=0 && xx<sizex && yy>=0 && yy<sizey && !visited[xx][yy] && G[xx][yy]==1){
                    q.push({xx,yy});    
                }
            }
        }
    }
    return trace;

}
int islands(vector<vector<int>> &G){
    const int sizex = G.size();
    const int sizey = G[0].size();
    set<vector<pair<int,int>>> islands;
    vector<vector<bool>> visited(G.size(),vector<bool>(G[0].size(),false));
    for(int i=0;i<sizex;i++){
        for(int j=0;j<sizey;j++){
            if(!visited[i][j] && G[i][j]==1){
                islands.insert(bfs_distinct(G,visited,{i,j}));
            }
        }
    }
    for(auto island :islands){
        cout<<"[";
        for(auto[one,two]:island){
            cout<<"("<<one<<","<<two<<")"<<", ";
        }
        cout<<"]"<<endl;
    }
    return islands.size();
}
int main(){
    vector<vector<int>> M = {
        {2,2,2,2,2,2,2,0,2,2},
        {2,1,1,1,1,1,1,0,1,2},
        {2,1,0,0,0,0,0,0,1,2},
        {2,1,0,0,1,1,1,0,1,2},
        {2,1,2,1,2,2,1,0,1,2},
        {2,1,0,0,2,2,1,0,1,2},
        {2,1,0,0,0,0,0,0,1,2},
        {2,1,2,0,0,0,0,0,1,2},
        {2,0,0,1,1,1,1,1,1,2},
        {2,0,0,2,2,2,2,2,2,2}
    };
    vector<vector<int>> N = {
        {0,0,0,0,0,1,0,1,0,0},
        {0,0,0,1,0,1,1,0,1,0},
        {0,1,0,0,1,0,0,0,1,0},
        {0,1,1,0,1,1,1,0,1,0},
        {0,1,0,1,0,0,1,0,1,0},
        {0,1,0,0,1,0,1,0,0,1},
        {1,1,0,1,0,0,1,0,1,0},
        {0,1,1,0,0,0,1,0,1,0},
        {0,0,0,0,1,0,0,1,1,0},
        {1,0,0,1,0,0,0,0,0,0}
    };
    vector<vector<int>> C={
        {0,1,0,1,1},
        {1,1,0,0,0},
        {0,0,0,0,0},
        {0,0,0,1,1},
        {1,1,0,1,0},
    };

    // cout<<"__________________Original_Canvas__________________"<<endl;
    // print(M,-1);
    // cout<<"____________0_pixelx_in_Original_Canvas____________"<<endl;
    // print(M,0);
    // flood(M,3,3,3,0);
    // cout<<"______________After_floodfill_3_on_0_______________"<<endl;
    // print(M,3);
    // cout<<"_____________0_pixels_after_floodfill______________"<<endl;
    // print(M,0);
    // cout<<"_________________After_floodfill___________________"<<endl;
    // print(M,-1);



    //print(N,-1);
    //vector<vector<int>> O = nearest1(N);
    //print(O,-1);
    print(N,-1);
    vector<vector<int>> S = surround(N);
    print(S,-1);
    print(C,-1);
    cout<<islands(C)<<endl;
}