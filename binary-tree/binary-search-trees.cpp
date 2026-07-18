/*
Binary Search Trees
A Binary search tree is a special type of binary tree which follows L<N<R (strict inequality) that is value of left node is smaller than the 
value of root node which is smaller than the value of the right node. Thus All values of the left side are smaller than the values on the right. 
Also any part of Binary search tree for eg, the right subtree is a binary search tree in itself.
The rule follows more strictly than we think, think it as everything on the left is smaller (exactly smaller) than the right values
In such strict inequality, it is obvious that duplicates values can't exist in a binary search trees, therefore if we want duplicate values we modify
conditions on our basis, for eg the L<N<R may become L<=N<R, that would be a modified version of binary search tree, but in actual bst, duplicate 
values are not allowed

Also the binary search tree are almost never degenerate, therefore their heights are (log2 n) unlike binary trees, whose heights in the worst case
can be n (n is the number of nodes), this happens when a binary tree is degenerate

Since everything on the left is smaller, this means we can apply binary search and hence reduce the time complexity to O(log2 n)
This is the main advantage of binary search tree
*/


//Space Complexity, if not mentioned, is constant
#include<bits/stdc++.h>
using namespace std;

//Creating Blueprint for tree
class Node{
    public:
        int val;
        Node* left;
        Node* right;

        Node(int val){
            this->val=val;
            this->left=nullptr;
            this->right=nullptr;
        }

        Node(int val,Node* left,Node* right){
            this->val=val;
            this->left=left;
            this->right=right;
        }
};

//Searching For a value in BST
//Type I : Check if the value exists or not
bool checkForElement_brute(Node* root,int x){
    if(!root) return false;
    int rootVal=root->val;
    if(rootVal>x) return checkForElement_brute(root->left,x);
    else if(rootVal<x) return checkForElement_brute(root->right,x);
    else return true;
}
//Time Complexity will be same as height of tree O(log n)(base 2)
//Space Complexity will be O(log n) (recursion stack space)

//We can eliminate recursion stack space by using loop
bool checkForElement(Node* root,int x){
    while(root && root->val!=x) root=root->val>x?root->left:root->right;
    return root!=nullptr;
}
//Time Complexity will be O(log n)


//Type II : Tell at which level the element was found, it is given that the element is always present
//Level begins at 0
int fxCFEII(Node* root,int x,int level){
    if(!root) return -1;
    int rootVal=root->val;
    if(rootVal>x) return fxCFEII(root->left,x,level+1);
    else if(rootVal<x) return fxCFEII(root->right,x,level+1);
    else return level;
}
int checkForElementII_brute(Node* root,int x){
    return fxCFEII(root,x,0);
}
//Time Complexity will be O(log n)
//Space Complexity will be O(log n) (recursion stack space)

//Space Complexity will be constant if we use loops
int checkForElementII(Node* root,int x){
    int level=0;
    while(root && root->val!=x){
        level++;
        root=(root->val>x?root->left:root->right);
    }
    if(!root) return -1;
    return level;
}
//Time Complexity will be O(log n)


//Find Ceil in a BST
int findCeil(Node* root,int key){
    int ans=-1;
    while(root){
        if(root->val>key){
            ans=root->val;
            root=root->left;
        }
        else if(root->val==key){
            ans=root->val;
            return ans;
        }
        else root=root->right;
    }
    return ans;
}
//Time Complexity will be O(log n)


//Find Floor in a BST
int findFloor(Node* root,int key){
    int ans=-1;
    while(root){
        if(root->val==key) return root->val;
        else if(root->val>key) root=root->left;
        else {
            ans=root->val;
            root=root->right;
        }
    }
    return ans;
}
//Time Complexity will be O(log n)


//Insert a node in a BST
//You will be only given a node value, that doesn't exists in the binary search tree currently
Node* insertInBST(Node* root,int key){
    if(!root) return new Node(key);
    Node* curr=root;
    while(true){
        if(curr->val<=key){
            if(curr->right!=nullptr) curr=curr->right;
            else{
                curr->right=new Node(key);
                break;
            }
        }
        else{
            if(curr->left!=nullptr) curr=curr->left;
            else{
                curr->left=new Node(key);
                break;
            }
        }
    }
    return root;
}


//Delete a node in BST

//First we create a function to find the rightmost node
Node* findLastRight(Node* root){
    if(!root->right) return root;
    return findLastRight(root->right);
}

//Then is the helper function for deleting a node, if root is the node to be deleted
Node* fxDN(Node* root){
    if(!root->right){
        Node* temp=root->left;
        delete root;
        return temp;
    }
    else if(!root->left){
        Node* temp=root->right;
        delete root;
        return temp;
    }
    Node* rightChild=root->right;
    Node* lastRight=findLastRight(root->left);
    lastRight->right=rightChild;
    Node* temp=root;
    delete root;
    return temp->left;
}

//Function to delete node
Node* deleteNode(Node* &root,int key){
    if(!root) return root;
    if(root->val==key) return fxDN(root);
    Node* dummy=root;
    while(root){
        int x=root->val;
        if(x>key){
            if(root->left && root->left->val==key){
                root->left=fxDN(root->left);
                break;
            }
            else root=root->left;
        }
        else{
            if(root->right && root->right->val==key){
                root->right=fxDN(root->right);
                break;
            }
            else root=root->right;
        }
    }
    return root;
}


//Kth Smallest Element
//Brute Force : Take the traversal in an array, sort the array then return the element at (K-1)th index
//For traversal we can use Morris traversal
//We Define Morris Traversal here
vector<int> morrisTraversal(Node* root){
    vector<int> inOrder;
    if(!root) return inOrder;
    Node* curr=root;
    while(curr){
        if(!curr->left){
            inOrder.push_back(curr->val);
            curr=curr->right;
        }
        else{
            Node* temp=curr->left;
            while(temp->right && temp->right!=curr) temp=temp->right;
            if(temp->right==curr){
                temp->right=nullptr;
                inOrder.push_back(curr->val);
                curr=curr->right;

            }
            else{
                temp->right=curr;
                curr=curr->left;
            }
        }
    }
    return inOrder;
}

int kthSmallest_brute(Node* root,int k){
    vector<int> nodes=morrisTraversal(root);
    sort(nodes.begin(),nodes.end());
    return nodes[k-1];
}
//Time Complexity will be O(n+nlogn) (n for Morris Traversal)
//Space Complexity will be O(n)

//Better Method : If you observer, inorder traversal of a BST is always sorted, try it
//Therefore there's is no need to sort the vector
int kthSmallest_better(Node* root,int k){
    vector<int> nodes=morrisTraversal(root);
    return nodes[k-1];
}
//Time Complexity will be O(n);
//Space Complexity will be O(n)

//This still uses extra O(n) space, but we don't need to store the elements one by one
//We can maintain a counter while doing inOrder traversal, and as soon as the counter reaches k, we can stop
//We just write the morris traversal in better way
int kthSmallest(Node* root,int k){
    if(!root) return -1;
    int cnt=0;
    Node* curr=root;
    while(curr){
        if(!curr->left){
            cnt++;
            if(cnt==k) return curr->val;
            curr=curr->right;
        }
        else{
            Node* temp=curr->left;
            while(temp->right && temp->right!=curr) temp=temp->right;
            if(!temp->right){
                temp->right=curr;
                curr=curr->left;
            }
            else{
                temp->right=nullptr;
                cnt++;
                if(cnt==k) return curr->val;
                curr=curr->right;
            }
        }
    }
    return -1;
}
//Time Complexity will be O(n)


//Kth Largest Element
//Count the total number of nodes
//Kth largest element is the (n-k+1)th smallest element
int countNodes(Node* root){
    int cnt=0;
    if(!root) return cnt;
    Node* curr=root;
    while(curr){
        if(!curr->left){
            cnt++;
            curr=curr->right;
        }
        else{
            Node* temp=curr->left;
            while(temp->right && temp->right!=curr) temp=temp->right;
            if(!temp->right){
                temp->right=curr;
                curr=curr->left;
            }
            else{
                temp->right=nullptr;
                cnt++;
                curr=curr->right;
            }
        }
    }
    return cnt;
}
int kthLargest(Node* root,int k){

    //First we count the total number of nodes
    int n=countNodes(root);

    //Now just run the kthSmallest function for k=n-k+1
    return kthSmallest(root,n-k+1);
}
//Time Complexity will be O(2n) which is as good as O(n)


//Check if a BT is BST or not
//Idea is to maintain a range 
bool fxCFBST(Node* root,int leftRange,int rightRange){
    if(!root) return true;
    int x=root->val;
    if(!(x>leftRange && x<rightRange)) return false;
    bool leftCheck=fxCFBST(root->left,leftRange,root->val);
    bool rightCheck=fxCFBST(root->right,root->val,rightRange);
    return (leftCheck && rightCheck);
}
bool checkForBST(Node* root){
    return fxCFBST(root,INT_MIN,INT_MAX);
}
//Time Complexity will be O(n) 
//Space Complexity will be O(n) (Recursion Stack Space)



//LCA in BST 
int lca(Node* root,Node* node1, Node* node2){
    if(!root) return -1;
    Node* node=root;
    int x=node1->val;
    int y=node2->val;

    while(node){
        int s=node->val;
        if(x>s && y>s) node=node->right;
        else if(x<s && y<s) node=node->left;
        else return node->val;
    }
    return -1;
}
//Time Complexity will be O(H) 


//Construct a BST from preorder traversal
void constructHelper(int element,Node* &root){
    Node* node=root;
    Node* prevNode=node;
    while(node){
        prevNode=node;
        if(element>node->val) node=node->right;
        else node=node->left;
    }
    Node* newNode=new Node(element);
    if(element>prevNode->val) prevNode->right=newNode;
    else prevNode->left=newNode;
}
Node* constructBST_preorder_brute(vector<int> preOrder){
    int n=preOrder.size();
    Node* root=new Node(preOrder[0]);
    for(int i=1;i<n;i++) constructHelper(preOrder[i],root);
    return root;
}
//Time Complexity will be O(N2)

//Better Method 
//Concept : Inorder traversal of a BST is always sorted, therefore sorting the preorder traversal will give us the inorder traversal array
//          therefore we now have inorder and preorder traversals, we did learn in BT that using a pre and inorder traversals, a unique 
//          BT can be constructed, in this case the unique BT will be BST
Node* constructBTHelper(vector<int> &preOrder,int preStart,int preEnd,vector<int> &inOrder,int inStart,int inEnd,unordered_map<int,int> &mpp){
    if(preStart>preEnd || inStart>inEnd) return NULL;
    Node* root=new Node(preOrder[preStart]);
    int inRoot=mpp[root->val];
    int numsLeft=inRoot-inStart;
    root->left=constructBTHelper(preOrder,preStart+1,preStart+numsLeft,inOrder,inStart,inRoot-1,mpp);
    root->right=constructBTHelper(preOrder,preStart+numsLeft+1,preEnd,inOrder,inRoot+1,inEnd,mpp);
    return root;
}
Node* constructBTFromPreorderAndInorder(vector<int> preOrder,vector<int> inOrder){
    unordered_map<int,int> mpp;
    int n=inOrder.size();
    for(int i=0;i<n;i++) mpp[inOrder[i]]=i;
    Node* root=constructBTHelper(preOrder,0,preOrder.size()-1,inOrder,0,inOrder.size()-1,mpp);
    return root;
}
Node* constructBST_preOrder_better(vector<int> preOrder){
    int n=preOrder.size();
    vector<int> inOrder=preOrder;
    sort(inOrder.begin(),inOrder.end());
    return constructBTFromPreorderAndInorder(preOrder,inOrder);
}
//Time Complexity will be O(nlogn + n)
//Space Complexity will be O(n) (for map data structure)

//Optimal Method : Maintaining an upper bound at each level
Node* constructBSTHelper(vector<int> &preOrder,int &idx,int upperBound){
    if(idx>=preOrder.size() || preOrder[idx]>upperBound) return nullptr;
    Node* root=new Node(preOrder[idx]);
    idx++;
    root->left=constructBSTHelper(preOrder,idx,root->val);
    root->right=constructBSTHelper(preOrder,idx,upperBound);
    return root;
}
Node* constructBST_preOrder(vector<int> &preOrder){
    int idx=0;
    return constructBSTHelper(preOrder,idx,INT_MAX);
}
//Time Complexity will be O(n)
//Space Complexity will be O(n) (Recursion Stack Space)



//Inorder Successor of an element in BST
//Find the next element that would appear in the inorder traversal, after the given element
//Brute Force : Write down the inorder traversal and find the next element, in case the given element is last, print -1
//Use Morris Traversal for traversing
int inorderSuccessor_brute(Node* root, int x){
    if(!root) return -1;
    vector<int> inOrder=morrisTraversal(root);
    int n=inOrder.size();
    for(int i=0;i<n-1;i++){
        if(inOrder[i]==x) return inOrder[i+1];
    }
    return -1;
}
//Time Complexity will be O(2N) 
//Space Complexity will be O(N)

//Better Method : Don't try to store inOrder Traversal, instead when you encounter x, the next element should be given
int inorderSuccessor_better(Node* root,int x){
    if(!root) return -1;
    Node* curr=root;
    bool flag=false;
    while(curr){
        if(!curr->left){
            if(flag==true) return curr->val;
            if(curr->val==x) flag=true;
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
                if(flag==true) return curr->val;
                if(curr->val==x) flag=true;
                curr=curr->right;
            }
        }
    }
    return -1;
}
//Time Complexity will be O(N)

int inorderSuccessor(Node* root,int x){
    int ans=-1;
    if(!root) return ans;
    Node* node=root;
    while(node){
        if(x>=node->val) node=node->right;
        else{
            ans=node->val;
            node=node->left;
        }
    }
    return ans;
}
//Time Complexity will be O(H)



//Inorder Predecessor
//Brute And Better Approach are similar to inOrderSuccessor

//Optimal Approach
int nextInorderPredecessor(Node* root, int x){
    int ans=-1;
    if(!root) return ans;
    Node* node=root;
    while(node){
        if(x>node->val){
            ans=node->val;
            node=node->right;
        }
        else node=node->left;
    }
    return ans;
}
//Time Complexity will be O(H)



//BST Iterator
class BSTIterator{
    public:
        stack<Node*> st;
        void pushAll(Node* node){
            while(node){
                st.push(node);
                node=node->left;
            }
        }

        bool hasNext(){
            return !st.empty();
        }

        int next(){
            Node* node=st.top();
            st.pop();
            pushAll(node->right);
            return node->val;
        }
        BSTIterator(Node* root){
            pushAll(root);
        }
};
//Time Complexity will be O(1)
//Space Complexity will be O(h) h is the height of the tree



//Pair with sum K
//Brute Force : Write inorder traversal(always in sorted order) then apply two pointer's method
//First we create a function to find sum with pair in an array
pair<int,int> twoSum(vector<int> arr,int k){
    int n=arr.size();

    //We are assuming that the array is sorted
    int i=0;//Left Pointer
    int j=n-1;//Right Pointer
    while(i<j){
        int sum=arr[i]+arr[j];
        if(sum<k) i++;
        else if(sum>k) j--;
        else return {arr[i],arr[j]};
    }
    return {-1,-1};
}

pair<int,int> pairWithSumK_brute(Node* root,int k){
    pair<int,int> ans;
    if(!root) return ans;

    //We will do Morris traversal
    vector<int> arr=morrisTraversal(root);
    ans=twoSum(arr,k);
    return ans;
};
//Time Complexity will be O(n+n) for morris and two pointer
//Space Complexity will be O(n) for storing the inorder traversal


//Optimal Solution : Using BST Iterator
//We will need to create a different BST Iterator, one that can also iterate backwards
class BSTIteratorWithRev{
    private:
        stack<Node*> st;
        bool reverse=true;
        void pushAll(Node* node){
            while(node){
                st.push(node);
                if(reverse==true) node=node->right;
                else node=node->left;
            }
        }
    
    public:
        BSTIteratorWithRev(Node* root,bool isRev){
            reverse=isRev;
            pushAll(root);
        }

        bool hasNext(){
            return !st.empty();
        }

        int next(){
            Node* tempNode=st.top();
            st.pop();
            if(reverse) pushAll(tempNode->right);
            else pushAll(tempNode->left);
            return tempNode->val;
        }
};
//Time Complexity will be O(1)
//Space Complexity will be O(h) h is the height of the tree


//Recover Binary Search Tree
//We will be given a BST whose two nodes are swapped, swap the nodes back and return the corrected BST
//A very brute method can be to write down the inorder traversal, which in this case will not be sorted, since the nodes have been swapped
//Now sort the inorder traversal and traverse the binary tree again, comparing each node with the inOrder traversal(sorted one)
//Assign the two nodes that appear different to that of the sorted inorder
//Then swap these two nodes
void recoverBST_brute(Node* root){
    if(!root) return;
    vector<int> inOrder=morrisTraversal(root);
    sort(inOrder.begin(),inOrder.end());
    Node* curr=root;
    int i=0;
    while(curr){
        if(!curr->left){
            if(curr->val!=inOrder[i]) curr->val=inOrder[i];
            i++;
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
                if(curr->val!=inOrder[i]) curr->val=inOrder[i];
                i++;
                curr=curr->right;
            }
        }
    }
}
//Time Complexity will be O(N+NlogN+N)
//Space Complexity will be O(N)

//Optimal Method
void recoverBST(Node* root){
    if(!root) return;
    Node* prevNode=nullptr;
    Node* first=nullptr;
    Node* second=nullptr;
    Node* curr=root;
    while(curr){
        if(!curr->left){
            if(prevNode && prevNode->val>curr->val){
                if(!first){
                    first=prevNode;
                    second=curr;
                }
                else second=curr;
            }
            prevNode=curr;
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
                if(prevNode && prevNode->val>curr->val){
                    if(!first){
                        first=prevNode;
                        second=curr;
                    }
                    else second=curr;
                }
                prevNode=curr;
                curr=curr->right;
            }
        }
    }
    swap(first->val,second->val);
}
//Time Complexity will be O(N)



//Find the largest BST in a BT
//Brute Force 
//Validate each subtree for a bst, if it is a bst then count its nodes and keep updating the maxnodes variable
void lBSTBrute_helper(int &maxNodes,Node* root){
    if(!root) return;
    if(checkForBST(root)) maxNodes=max(maxNodes,countNodes(root));
    lBSTBrute_helper(maxNodes,root->left);
    lBSTBrute_helper(maxNodes,root->right);
}
int largestBST_brute(Node* root){
    int maxNodes=0;
    lBSTBrute_helper(maxNodes,root);
    return maxNodes;
}
//Time Complexity will be O(N2)
//Space Complexity will be O(N)

//Optimal Approach 
class NodeValue{
    public:
        int maxNode;
        int minNode;
        int maxSize;

        NodeValue(int minNode,int maxNode,int maxSize){
            this->minNode=minNode;
            this->maxNode=maxNode;
            this->maxSize=maxSize;
        }
};

NodeValue lBSTHelper(Node* root){
    //An empty tree is a BST of size 0
    if(!root) return NodeValue(INT_MAX,INT_MIN,0);

    //Get Values from left and right subtree of current tree
    auto left=lBSTHelper(root->left);
    auto right=lBSTHelper(root->right);

    //Current node is greater than max in left AND smaller than min on right
    if(left.maxNode<root->val && root->val<right.minNode)return NodeValue(min(root->val,left.minNode),max(root->val,right.maxNode),left.maxSize+right.maxSize+1);
    
    //Otherwise, return [-inf,inf] so that parent can't be valid BST
    return NodeValue(INT_MIN,INT_MAX,max(left.maxSize,right.maxSize));
}

int largestBST(Node* root){
    return lBSTHelper(root).maxSize;
}
//Time Complexity will be O(N)
//Space Complexity will be O(N) (Recursion stack space in the worst case of skewed tree)



int main(){
    //Your function here
    return 0;
}
