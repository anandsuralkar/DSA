
#include<vector>
#include<iostream>
using namespace std;

struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
  };

class Solution {
public:
    pair<int,TreeNode*> trav(TreeNode* curr,int height, int x,TreeNode* parent){
        if(curr->val==x){
            return {height,parent};
        }
        int h1=-1;int h2 =-1;
        if(curr->left!=nullptr){
            auto [h1,par1] = trav(curr->left,height+1,x,curr);
            if(h1!=-1)
                return {h1,par1};
        }
        if(curr->right!=nullptr){
            auto [h2,par2] = trav(curr->right,height+1,x,curr);
            if(h2!=-1)
                return {h2,par2};
        }
        return {-1,nullptr};

    }
    bool isCousins(TreeNode* root, int x, int y) {
        if(root==nullptr)return false;
        auto [hx,parx] = trav(root,0,x,nullptr);
        auto [hy,pary] = trav(root,0,y,nullptr);
        if(hx != -1 && hy != -1){
            if(hx == hy && parx != pary)return true;
        }
        return false;

    }
};