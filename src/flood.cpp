#include<iostream>
#include<vector>
#include<unordered_set>
#include<set>
#include<cmath>
#include<tuple>
#include<algorithm>
#include<map>
#include "bmp.h"
using namespace std;
vector<vector<int>> approx(const vector<vector<int>>& img, int levels = 64) {
    vector<vector<int>> out = img;
    int step = 256 / levels;
    for (auto &row : out)
        for (auto &pixel : row) {
            int R = (pixel >> 16) & 0xFF;
            int G = (pixel >> 8) & 0xFF;
            int B = pixel & 0xFF;
            R = (R / step) * step + step / 2;G = (G / step) * step + step / 2;B = (B / step) * step + step / 2;
            pixel = (R << 16) | (G << 8) | B;
        }
    return out;
}
int getR(int c) { return (c >> 16) & 0xFF; }
int getG(int c) { return (c >> 8) & 0xFF; }
int getB(int c) { return c & 0xFF; }
int colorDist(int a, int b) {
    int dr = getR(a) - getR(b);
    int dg = getG(a) - getG(b);
    int db = getB(a) - getB(b);
    return dr*dr + dg*dg + db*db;
}
vector<vector<int>> quantize(const vector<vector<int>>& img, int k = 10) {
    vector<vector<int>> out = img;
    map<int,int> freq;// Count frequency of each color
    for (auto &row : img)
        for (auto &c : row)
            freq[c]++;
    vector<int> colors;// Pick top-k frequent colors
    vector<pair<int,int>> freq_vec(freq.begin(), freq.end());
    sort(freq_vec.begin(), freq_vec.end(), [](auto &a, auto &b){ return a.second > b.second; });
    for (int i = 0; i < min(k, (int)freq_vec.size()); i++)
        colors.push_back(freq_vec[i].first);

    for (auto &row : out)// Map each pixel to nearest top color
        for (auto &c : row) {
            int best = colors[0];
            int best_dist = colorDist(c, best);
            for (int col : colors) {
                int d = colorDist(c, col);
                if (d < best_dist) {
                    best = col;
                    best_dist = d;}
            }c = best;}
    return out;
}
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
vector<int> getColors(const vector<vector<int>>& img) {
    unordered_set<int> colors;
    for (const auto& row : img)
        for (int pixel : row)
            colors.insert(pixel);
    return vector<int>(colors.begin(), colors.end());
}




void flood(vector<vector<int>> &M,int x,int y,int color,int prev){
    if(x<0||x>=M.size()||y<0||y>=M[0].size()){
        return;
    }
    if(M[y][x]==color)return;
    if(M[y][x]==prev){
        M[y][x]=color;
    flood(M,x-1,y,color,prev);
    flood(M,x+1,y,color,prev);
    flood(M,x,y-1,color,prev);
    flood(M,x,y+1,color,prev);}
    else return;
}


int main(){
    int x,y;x=909, y=695;
    auto M = bmp::readBMP("img/img.bmp");

    vector<int> colors = getColors(M);
    flood(M,x,y,0x00FF00,0xffac99);
    
    bmp::writeBMP("img/o_img.bmp",M);
}
