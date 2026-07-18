//Binary Trees 

//A Binary Tress has Following Components
    //Root
    //Children
    //Leaf Node
    //Sub Tree
    //Ancestors
    //Node
    //Siblings(Whose parents are same)

//Binary Trees are of Following Types (see Internet for more)
    //Full BT
    //Complete BT
    //Perfect BT
    //Balanced BT
    //Degenerate BT

//Representation of BT
    //                       [__,3,__]
    //                 [__,4,__]  [__,7,__]
    //The first block in 20th line corresponds to to the first blank in the 19th line
    //The leaf nodes at last points to NULL (or they have null value)

//Traversing In Binary Tree
    //Depth First Search 
        //Pre Order Traversal (Root->Left->Right)
        //Post Order Traversal (Left->Right->Root)
        //In Order Traversal (Left->Root->Right)

    //Breadth First Search
        //Level Wise Search (Left to Right at Same Level)


#include<bits/stdc++.h>
using namespace std;

//Pre Order Traversal

// void preOrder(node){
//     if(node==null) return;
//     print(node->data);
//     preOrder(node->left);
//     preOrder(node->right);
// }

/*
void preOrder(node){
    if(node==null) return ;
    print(node->data);
    preOrder(node->left);
    preOrder(node->right);
}

void inOrder(node){
    if(node==null) return;
    inOrder(node->left);
    print(node->data);
    inOrder(node->right);
}

void postOrder(node){
    if(node==null) return;
    postOrder(node->left);
    postOrder(node->right);
    print(node->data);
}
*/

//In Order Traversal

// void inOrder(node){
//     if(node==null) return;
//     inOrder(node->left);
//     print(node->data);
//     inOrder(node->right);
// }

//Post Order Traversal

//Storing or creation of binary trees
// void postOrder(node){
//     if(node==null) return;
//     postOrder(node->left);
//     postOrder(node->right);
//     print(node->data);
// }

//Note : When using recursion, if the array or map etc is not being changed, then we should pass it by reference,
    //   Reason because it avoid creating copies at each recursion call
class Node{
    public:
        int val;
        Node* left;
        Node* right;
        Node(){
            this->val=0;
            this->left=nullptr;
            this->right=nullptr;
        }
    
        Node(int x){
            this->val=x;
            this->left=nullptr;
            this->right=nullptr;
        }

        Node(int x,Node* left,Node* right){
            this->val=x;
            this->left=left;
            this->right=right;
        }
};


//Level order traversal
vector<vector<int>> leverOrderTrav(Node* root){
    vector<vector<int>> ans;
    if(root==NULL) return ans;
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        int size=q.size();
        vector<int> level;
        for(int i=0;i<size;i++){
            Node* node=q.front();
            q.pop();
            if(node->left !=NULL) q.push(node->left);
            if(node->right !=NULL) q.push(node->right);
            level.push_back(node->val);
        }
        ans.push_back(level);
    }
    return ans;
}


//Iterative Pre Order Traversal
vector<int> preOrderIterative(Node* root){
    Node* node=root;
    stack<Node*> st;
    vector<int> preOrder;
    if(root==NULL) return preOrder;
    st.push(node);
    while(!st.empty()){
        node=st.top();
        st.pop();
        preOrder.push_back(node->val);
        if(node->right!=NULL) st.push(node->right);
        if(node->right!=NULL) st.push(node->left);
    }
    return preOrder;
};


//Iterative In Order Traversal
vector<int> inOrderIterative(Node* root){
    Node* node=root;
    stack<Node*> st;
    vector<int> inOrder;
    if(root==NULL) return inOrder;
    while(true){
        if(node){
            st.push(node);
            node=node->left;
        }
        else{
            if(st.empty()) break;
            node=st.top();
            st.pop();
            inOrder.push_back(node->val);
            node=node->right;
        }
    }
    return inOrder;
}


//Iterative Post Order Traversal using two stack
vector<int> postOrderIterative_twoStack(Node* root){
    Node* node=root;
    stack<Node*> st1;
    stack<Node*> st2;
    vector<int> postOrder;
    if(root==NULL) return postOrder;
    st1.push(node);
    while(!st1.empty()){
        node=st1.top();
        st2.push(st1.top());
        st1.pop();
        if(node->left) st1.push(node->left);
        if(node->right) st1.push(node->right);
    }
    while(!st2.empty()){
        postOrder.push_back(st2.top()->val);
        st2.pop();
    }
    return postOrder;
};


//Iterative Pre Order Traversal using one Stack
//My Method : A clever trick, easier but double time complexity
vector<int> postOrder_iterative_1Stack_myMethod(Node* root){
    vector<int> ans;
    stack<Node*> st;
    if(!root) return ans;
    st.push(root);
    while(!st.empty()){
        Node* node=st.top();
        st.pop();
        ans.push_back(node->val);
        if(node->left) st.push(node->left);
        if(node->right) st.push(node->right);
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
//Time Complexity will be O(2n)

//Striver's Method
vector<int> postOrderIterative_1Stack(Node* root){
    vector<int> ans;
    Node* curr=root;
    stack<Node*> st;
    while(curr && !st.empty()){
        if(curr!=NULL){
            st.push(curr);
            curr=curr->left;
        }
        else{
            Node* temp=st.top()->right;
            if(temp==NULL){
                temp=st.top();
                st.pop();
                ans.push_back(temp->val);
                while(!st.empty() && temp==st.top()->right){
                    temp=st.top();
                    st.pop();
                    ans.push_back(temp->val);
                }
            }
            else curr=temp;
        }
    }
    return ans;
}


//All Traversals in a single code
void allTraversals(vector<int> &preOrder,vector<int> &inOrder,vector<int> &postOrder,Node* root){
    stack<pair<Node*,int>> st;
    st.push({root,1});
    if(!root) return;
    while(!st.empty()){
        auto it=st.top();
        st.pop();
        if(it.second==1){
            preOrder.push_back(it.first->val);
            it.second++;
            st.push(it);
            if(it.first->left!=NULL) st.push({it.first->left,1});
        }
        else if(it.second==2){
            inOrder.push_back(it.first->val);
            it.second++;
            st.push(it);
            if(it.first->right!=NULL) st.push({it.first->right,1});
        }
        else postOrder.push_back(it.first->val);
    }
}
//Time Complexity will be O(3n) (each element/node is visited thrice)
//Space Complexity will be O(4n) (n for stack and 3n for returning the answer)


//Maximum depth/level (total levels) in a binary tree
int heightOfBT(Node* root){
    if(!root) return 0;
    int leftHeight=heightOfBT(root->left);
    int rightHeight=heightOfBT(root->right);
    int height=(1+max(leftHeight,rightHeight));
    return height;
}


//Check for Balanced Binary Tree
//Brute Force
bool balancedBT_brute(Node* node){
    if(!node) return true;
    bool leftCheck=balancedBT_brute(node->left);
    bool rightCheck=balancedBT_brute(node->right);
    bool diff=abs(heightOfBT(node->right)-heightOfBT(node->left))<=1;
    if(left && right && diff) return true;
    else return false;
}

// Optimal Approach : Modifying the heightofBt function to return height of the tree if it is balanced, otherwise -1
// Return height if the tree is balanced, otherwise return -1
int dfsHeight(Node* root){
    if(!root) return 0;
    int lh=dfsHeight(root->left);
    if(lh==-1) return -1;
    int rh=dfsHeight(root->right);
    if(rh==-1) return -1;
    if(abs(lh-rh)>1) return -1;
    return max(lh,rh)+1;

}
bool balancedBT(Node* root){
    return dfsHeight(root)!=-1;
}
//Time Complexity will be O(N)


//Diameter of a Binary Tree
//Diameter is the longest path possible between any two nodes(the path must not cross same node twice)
//When standing on a root, the max path possible is from left node to right node, via root node


int diameterOfBT_brute(Node* root){
    if(!root) return 0;
    int lh=heightOfBT(root->left);
    int rh=heightOfBT(root->right);
    int leftMax=diameterOfBT_brute(root->left);
    int rightMax=diameterOfBT_brute(root->right);
    int maxPath=max(leftMax,rightMax);
    maxPath=max(maxPath,(lh+rh));
    return maxPath;
}

int fx(Node* node,int &diameter){
    if(!node) return 0;
    int lh=fx(node->left,diameter);
    int rh=fx(node->right,diameter);
    diameter=max(diameter,lh+rh);
    return (1+max(lh,rh));
}
int diameterOfBT(Node* node){
    if(!node) return 0;
    int diameter=0;
    fx(node,diameter);
    return diameter;
}
//Time Complexity will be O(N)


//Maximum Path
int maxPathDown(Node* node,int maxi){
    if(!node) return 0;
    int left=max(0,maxPathDown(node->left,maxi));
    int right=max(0,maxPathDown(node->right,maxi));
    maxi=max(maxi,left+right+node->val);
    return max(left,right)+node->val; 
}
int maxPathSum(Node* root){
    int maxi=INT_MIN;
    maxPathDown(root,maxi);
    return maxi;
}
//Time Complexity will be O(N)
//Space Complexity will be O(N) due to recursion stack space 


//Check for identical binary trees
bool checkForIdenticalBT(Node* root1,Node* root2){
    if(!root1 && !root2) return true;
    if(!root1 || !root2) return false;
    if(root1->val!=root2->val) return false;
    bool leftCheck=checkForIdenticalBT(root1->left,root2->left);
    bool rightCheck=checkForIdenticalBT(root1->right,root2->right);
    return (leftCheck && rightCheck);
}
//Time Complexity will be O(N)
//Space Complexity will be O(N) (recursion stack space)


//Zig Zag Traversal Of Binary Tree
vector<vector<int>> zigZag(Node* root){
    vector<vector<int>> ans;
    if(!root) return ans;
    queue<Node*> q;
    q.push(root);
    bool lToR=true;
    while(!q.empty()){
        int size=q.size();
        vector<int> rows(size);
        for(int i=0;i<size;i++){
            Node* node=q.front();
            q.pop();

            //Find position to fill node's value
            int index=(lToR)? i:(size-1-i);

            rows[index]=node->val;
            if(node->left) q.push(node->left);
            if(node->right) q.push(node->right);
        }
        //After this level
        lToR=!lToR;
        ans.push_back(rows);
    }
    return ans;
}
//Time Complexity will be O(N)
//Space Complexity will be O(N)


//Boundary Traversal of a Binary Tree
//Boundary Traversal is done in three steps : 

//A function to check if a node is leaf node
bool isLeaf(Node* node){
    if(!node->right && !node->left) return true;
    return false;
}

//Function for left boundary traversal
void addLeftBoundary(Node* root,vector<int> &ans){
    Node* curr=root->left;
    while(curr){
        if(!isLeaf(curr)) ans.push_back(curr->val);
        if(curr->left) curr=curr->left;
        else curr=curr->right;
    }
}

//Function for right boundary traversal
void addRightBoundary(Node* root,vector<int> &ans){
    Node* curr=root->right;
    vector<int> temp;
    while(curr){
        if(!isLeaf(curr)) temp.push_back(curr->val);
        if(curr->right) curr=curr->right;
        else curr=curr->left;
    }

    for(int i=temp.size()-1;i>=0;i--) ans.push_back(temp[i]);
}

//Function for leaves traversal
void addLeaves(Node* root,vector<int> &ans){
    if(isLeaf(root)){
        ans.push_back(root->val);
        return;
    }
    if(root->left) addLeaves(root->left,ans);
    if(root->right) addLeaves(root->right,ans);
}

vector<int> boundaryTraversal(Node* root){
    vector<int> ans;
    if(!root) return ans;

    //Checking if the root is itself not a leaf node
    if(!isLeaf(root)) ans.push_back(root->val);

    //Step 1 : Left boundary traversal (without leaf nodes)
    addLeftBoundary(root,ans);

    //Step 2 : Leaf Nodes traversal
    addLeaves(root,ans);

    //Step 3 : Right boundary traversal (without leaf nodes)
    addRightBoundary(root,ans);

    return ans;
}



//Vertical Traversal of Binary Tree
vector<vector<int>> verticalTraversal(Node* root){
    map<int,map<int,multiset<int>>> nodes;
    queue<pair<Node*,pair<int,int>>> todo;
    todo.push({root,{0,0}});
    while(!todo.empty()){
        auto p=todo.front();
        todo.pop();
        Node* node=p.first;
        int x=p.second.first;
        int y=p.second.second;
        nodes[x][y].insert(node->val);
        if(node->left) todo.push({node->left,{x-1,y+1}});
        if(node->right) todo.push({node->right,{x+1,y+1}});
    }
    vector<vector<int>> ans;
    for(auto p:nodes){
        vector<int> col;
        for(auto q:p.second){
            for(int it:q.second) col.push_back(it);
        }
        ans.push_back(col);
    }
    return ans;
}
//Time complexity will be O(n*logn)
//Space Complexity will be O(3n) 



//Top View of a Binary Tree
vector<int> topView(Node* root){
    vector<int> ans;
    if(!root) return ans;
    map<int,int> mpp;
    queue<pair<Node*,int>> q;
    q.push({root,0});
    while(!q.empty()){
        auto it=q.front();
        q.pop();
        Node* node=it.first;
        int line=it.second;
        if(mpp.find(line)==mpp.end()) mpp[line]=node->val;
        if(node->left) q.push({node,line-1});
        if(node->right) q.push({node,line+1});
    }
    for(auto it:mpp){
        ans.push_back(it.second);
    }
    return ans;
}
//Time Complexity will be O(N)
//Space Complexity will be O(2N)



//Bottom View
vector<int> bottomView(Node* root){
    vector<int> ans;
    if(!root) return ans;
    queue<pair<Node*,int>> q;
    map<int,int> mp;
    q.push({root,0});
    while(!q.empty()){
        Node* node=q.front().first;
        int line=q.front().second;
        q.pop();
        mp[line]=node->val;
        if(node->left) q.push({node->left,line-1});
        if(node->right) q.push({node->right,line+1});
    }
    for(auto it:mp) ans.push_back(it.second);
    return ans;
}
//Time Complexity will be O(N)
//Space Complexity will be O(N)



//Right View Of Binary Tree
void fxRV(Node* node,int level,vector<int> &ans){
    if(!node) return;
    if(level==ans.size()) ans.push_back(node->val);
    fxRV(node->right,level+1,ans);
    fxRV(node->left,level+1,ans);
}
vector<int> rightViewOfBT(Node* root){
    vector<int> ans;
    int level=0;
    fxRV(root,level,ans);
    return ans;
}
//Time Complexity will be O(N)
//Space Complexity will be O(h) h is the height of the binary tree(space is recursion stack space)


//Left View of the Binary Tree
void fxLV(Node* node,int level,vector<int> &ans){
    if(!node) return;
    if(level==ans.size()) ans.push_back(node->val);
    fxLV(node->left,level+1,ans);
    fxLV(node->right,level+1,ans);
}

vector<int> leftView(Node* root){
    vector<int> ans;
    if(!root) return ans;
    int level=0;
    fxLV(root,level,ans);
    return ans;
}
//Time Complexity will be O(N)
//Space Complexity will be O(h) h is the height of the binary tree(space is recursion stack space)


//Check for Symmetrical trees
bool checkSymmetry(Node* left,Node* right){
    if(!left && !right) return true;
    if(!left || !right) return false;
    if(left->val!=right->val) return false;
    return checkSymmetry(left->left,right->right) && checkSymmetry(left->right,right->left);
}
bool isSymmetric(Node* root){
    if(!root) return true;
    return checkSymmetry(root->left,root->right);
}
//Time Complexity will be O(N)
//Space Complexity will be O(N) (Recursion stack space)


//Root to Node Path
//We will be given a node and we need to find the path from root to that node
bool fxGP(Node* node,Node* target,vector<int> &ans){
    if(!node) return false;
    ans.push_back(node->val);
    if(node==target) return true;
    if(fxGP(node->left,target,ans) || fxGP(node->right,target,ans)) return true;
    ans.pop_back();
    return false;
}
vector<int> getPath(Node* root,Node* target){
    vector<int> ans;
    if(!root) return ans;
    fxGP(root,target,ans);
    return ans;
}


//Lowest Common Ancestor
//Brute Force : Write the root to node path for both nodes, then check the array for the last matching integer
int LCA_brute(Node* root,Node* node1,Node* node2){
    if(!root) return -1;
    vector<int> a=getPath(root,node1);
    vector<int> b=getPath(root,node2);
    int n=a.size();
    int m=b.size();
    int i=0;
    int j=0;
    int ans=-1;
    while(i<n && j<m && a[i]==b[j]){
        ans=a[i];
        i++;
        j++;
    }
    return ans;
}

//Optimal Method : Watch Video
Node* LCA(Node* root, Node* node1, Node* node2){
    if(!root || root==node1 || root==node2) return root;
    Node* left=LCA(root->left,node1,node2);
    Node* right=LCA(root->right,node1,node2);
    if(left && right) return root;
    return left? left:right;
}
//Time Complexity will be O(N)
//Space Complexity will be O(N) (Recursion Stack Space)


//Maximum Width of a Binary Tree x
int maxWidth(Node* root){
    if(!root) return 0;
    int ans=0;
    queue<pair<Node*,int>> q;
    q.push({root,0});
    while(!q.empty()){
        int size=q.size();
        int mmin=q.front().second;
        int first,last;
        for(int i=0;i<size;i++){
            int curr_id=q.front().second-mmin;
            Node* node=q.front().first;
            q.pop();
            if(i==0) first=curr_id;
            if(i==size-1) last=curr_id;
            if(node->left) q.push({node->left,curr_id*2+1});
            if(node->right) q.push({node->right,curr_id*2+2});
        }
        ans=max(ans,last-first+1);
    }
    return ans;
}
//Time Complexity will be O(N)
//Space Complexity will be O(N)


//Children Sum Property
//Only increasing the value of node is allowed
void childSum(Node* root){
    if(!root) return;
    int child=0;
    if(root->left) child+=root->left->val;
    if(root->right) child+=root->right->val;
    if(child>=root->val) root->val=child;
    else{
        if(root->left) root->left->val=root->val;
        if(root->right) root->right->val=root->val;
    }
    childSum(root->left);
    childSum(root->right);
    int tot=0;
    if(root->left) tot+=root->left->val;
    if(root->right) tot+=root->right->val;
    if(root->left || root->right) root->val=tot;
}
//Time Complexity will be O(N) 
//Space Complexity will be O(N) (Recursion Stack Space)


//Nodes at a distance K
void markParents(Node* root,unordered_map<Node*,Node*> &parentTrack){
    if(!root) return;
    queue<Node*> q;
    q.push(root);
    parentTrack[root]=nullptr;
    while(!q.empty()){
        Node* curr=q.front();
        q.pop();
        if(curr->left){
            parentTrack[curr->left]=curr;
            q.push(curr->left);
        }
        if(curr->right){
            parentTrack[curr->right]=curr;
            q.push(curr->right);
        }
    }
}

vector<int> nodesAtDistK(Node* root, Node* target, int k){
    vector<int> ans;
    if(!root || !target || k<0) return ans;
    unordered_map<Node*,Node*> mp;
    markParents(root,mp);
    queue<Node*> q;
    unordered_set<Node*> vis;
    vis.insert(target);
    int level=0;
    q.push(target);
    while(!q.empty()){
        int size=q.size();
        if(level++==k) break;
        for(int i=0;i<size;i++){
            Node* curr=q.front();
            q.pop();
            if(curr->left && vis.find(curr->left)==vis.end()){
                q.push(curr->left);
                vis.insert(curr->left);
            }
            if(curr->right && vis.find(curr->right)==vis.end()){
                q.push(curr->right);
                vis.insert(curr->right);
            }
            if(mp[curr] && vis.find(mp[curr])==vis.end()){
                q.push(mp[curr]);
                vis.insert(mp[curr]);
            }
        }
    }
    while(!q.empty()){
        ans.push_back(q.front()->val);
        q.pop();
    }
    return ans;
}
//Time Complexity will be O(2N) (Not taking into account time complexity for map and set)
//Space Complexity will be O(3N)


//Minimum Time Needed to Burn the tree
int minTimeToBurnTree(Node* root,Node* target){
    if(!root || !target) return 0; 
    unordered_map<Node*,Node*> mp;
    markParents(root,mp);
    
    //Now we do BFS Traversal
    queue<Node*> q;
    unordered_set<Node*> vis;
    vis.insert(target);
    q.push(target);
    int count=0;
    while(!q.empty()){
        int size=q.size();
        for(int i=0;i<size;i++){
            Node* curr=q.front();
            q.pop();
            if(curr->left && !vis.count(curr->left)){
                vis.insert(curr->left);
                q.push(curr->left);
            }
            if(curr->right && !vis.count(curr->right)){
                vis.insert(curr->right);
                q.push(curr->right);
            }
            if(mp[curr] && !vis.count(mp[curr])){
                vis.insert(mp[curr]);
                q.push(mp[curr]);
            }
        }
        count++;
    }
    return count-1;
}
//Time Complexity will be O(2N)
//Space Complexity will be O(N)


//Count Total Nodes in a complete Binary Tree
//A Complete Binary Tree is one in which all the nodes are present except at the last level(at the last level, any number of nodes 
//can be present) and at the last level every node is as left as possible
//Brute Force : Traverse through the tree and count the number of nodes
//Any traversal can be used although morris traversal is preferred since it is most optimal
//We are using basic recursion based traversal
int tnHelper(Node* root){
    if(!root) return 0;
    int left=tnHelper(root->left);
    int right=tnHelper(root->right);
    return 1+left+right;

}
int totalNodesInCompBT_brute(Node* root){
    if(!root) return 0;
    return tnHelper(root);
}

//Optimal Code
int findLeftHeight(Node* node){
    int height=0;
    while(node){
        height++;
        node=node->left;
    }
    return height;
}

int findRightHeight(Node* node){
    int height=0;
    while(node){
        height++;
        node=node->right;
    }
    return height;
}
int totalNodesInCompBT(Node* root){
    if(!root) return 0;
    int lh=findLeftHeight(root->left);
    int rh=findRightHeight(root->right);

    if(lh==rh) return ((1<<(lh+1))-1) ;
    return 1+totalNodesInCompBT(root->left)+totalNodesInCompBT(root->right);
}
//Time Complexity will be O((logn)2)


//Constructing a unique binary treee
//To construct a unique binary tree, we must have Inorder traversal, along with either post order traversal or pre order traversal
//Even if we have both post and pre order traversals, but not inorder traversal, we still can't form a unique binary tree

//Constructing a binary tree from inorder and preorder traversal
Node* fxBuildTree(vector<int> &preOrder,int preStart,int preEnd,vector<int> &inOrder,int inStart,int inEnd,unordered_map<int,int> &mpp){
    if(preStart>preEnd || inStart>inEnd) return NULL;
    Node* root=new Node(preOrder[preStart]);
    int inRoot=mpp[root->val];
    int numsLeft=inRoot-inStart;
    root->left=fxBuildTree(preOrder,preStart+1,preStart+numsLeft,inOrder,inStart,inRoot-1,mpp);
    root->right=fxBuildTree(preOrder,preStart+numsLeft+1,preEnd,inOrder,inRoot+1,inEnd,mpp);
    return root;
}
Node* buildTreeFromPreOrderAndInorder(vector<int> &preOrder,vector<int> &inOrder){
    unordered_map<int,int> mpp;
    int n=inOrder.size();
    for(int i=0;i<n;i++) mpp[inOrder[i]]=i;
    Node* root=fxBuildTree(preOrder,0,preOrder.size()-1,inOrder,0,inOrder.size()-1,mpp);
    return root;
}
//Time Complexity will be O(N) 
//Space Complexity will be O(n(for map) + n(for recursion stack space))


//Constructing a binary tree using postOrder and inOrder traversals
Node* f2BuildTree(vector<int> &postOrder,int postStart,int postEnd,vector<int> &inOrder,int inStart,int inEnd,unordered_map<int,int> &mpp){
    if(postStart>postEnd || inStart>inEnd) return NULL;
    Node* root=new Node(postOrder[postEnd]);
    int inRoot=mpp[root->val];
    int numsLeft=inRoot-inStart;
    root->left=f2BuildTree(postOrder,postStart,postStart+numsLeft-1,inOrder,inStart,inRoot-1,mpp);
    root->right=f2BuildTree(postOrder,postStart+numsLeft,postEnd-1,inOrder,inRoot+1,inEnd,mpp);
    return root;
}
Node* buildTreeFromPostOrderAndInOrder(vector<int> &postOrder,vector<int> &inOrder){
    if(inOrder.size()!=postOrder.size()) return NULL;
    unordered_map<int,int> mpp;
    for(int i=0;i<inOrder.size();i++) mpp[inOrder[i]]=i;
    Node* root=f2BuildTree(postOrder,0,postOrder.size()-1,inOrder,0,inOrder.size()-1,mpp);
    return root;
}


//Time Complexity will be O(N)
//Space Complexity will be O(n(for hashmap)+n(for recursion stack space))



//Serialize and Deserialize a Binary Tree
//We will write two functions, one to serialize and one to de-serialize

//Serialize Functions
string serialize(Node* root){
    if(!root) return "";
    string s="";
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* node=q.front();
        q.pop();
        if(!node) s.append("#,");
        else{
            s.append(to_string(node->val)+',');
            q.push(node->left);
            q.push(node->right);
        }
    }
    return s;
}
//Time Complexity will be O(N)
//Space Complexity will be O(N)

//Now we write the De-Serialize function
Node* deSerialize(string data){
    if(data.size()==0) return NULL;
    stringstream s(data);
    string str;
    getline(s,str,',');
    Node* root=new Node(stoi(str));
    queue<Node*> q;
    q.push(root);
    while(!q.empty()){
        Node* node=q.front();
        q.pop();
        getline(s,str,',');
        if(str=="#") node->left=NULL;
        else{
            Node* leftNode=new Node(stoi(str));
            node->left=leftNode;
            q.push(leftNode);
        }
        getline(s,str,',');
        if(str=="#") node->right=NULL;
        else{
            Node* rightNode=new Node(stoi(str));
            node->right=rightNode;
            q.push(rightNode);
        }
    }
    return root;
}
//Time Complexity will be O(N)
//Space Complexity will be O(N)




//Morris Traversal
vector<int> morrisTraversal_inOrder(Node* root){
    vector<int> ans;
    if(!root) return ans;
    Node* curr=root;
    while(curr){
        if(!curr->left){
            ans.push_back(curr->val);
            curr=curr->right;
        }
        else{
            Node* prev=curr->left;
            while(prev->right && prev->right!=curr) prev=prev->right;
            if(!prev->right){
                prev->right=curr;
                curr=curr->left;
            }
            else{
                prev->right=nullptr;
                ans.push_back(curr->val);
                curr=curr->right;
            }
        }
    }
    return ans; 
}
//Time Complexity will be O(2n)


vector<int> morrisTraversal_preOrder(Node* root){
    vector<int> ans;
    if(!root) return ans;
    Node* curr;
    while(curr){
        if(!curr->left){
            ans.push_back(curr->val);
            curr=curr->right;
        }
        else{
            Node* prev=curr->left;
            while(prev->right && prev->right!=curr) prev=prev->right;
            if(!prev->right){
                prev->right=curr;
                ans.push_back(curr->val);
                curr=curr->left;
            }
            else{
                prev->right=nullptr;
                curr=curr->right;
            }
        }
    }
    return ans;
}
//Time Complexity will be O(N)

//Flatten a Binary Tree to a LL
//The root of the BT becomes the head of the LL
//Stack Method
void flattenBT_stack(Node* root){
    stack<Node*> st;
    st.push(root);
    Node* curr;
    while(!st.empty()){
        curr=st.top();
        st.pop();
        if(curr->right) st.push(curr->right);
        if(curr->left) st.push(curr->left);
        if(!st.empty()) curr->right=st.top();
        curr->left=nullptr;
    }
}
//Time Complexity will be O(N)
//Space Complexity will be O(N)

//Using Recursion
//First we create a flattenHelper function
void flattenHelper(Node* node,Node* &prev){
    if(!node) return;
    flattenHelper(node->right,prev);
    flattenHelper(node->left,prev);
    node->right=prev;
    node->left=nullptr;
    prev=node;
}

void flatten_recursion(Node* root){
    Node* prev=nullptr;
    flattenHelper(root,prev);
}
//Time Complexity will be O(N)
//Space Complexity will be O(N) (Recursion Stack Space)

//We can use the concept of threaded binary trees, the one used in morris traversal
void flatten(Node* root){
    if(!root) return;
    Node* curr=root;
    Node* temp;
    while(curr){
        if(curr->left){
            temp=curr->left;
            while(temp->right) temp=temp->right;
            temp->right=curr->right;
            curr->right=curr->left;
            curr->left=nullptr;
        }
        curr=curr->right;
    }
}
//Time Complexity will be O(N)




int main(){
    //Your function here
    return 0;
}
