//This file contains the basic question of Doubly Linked List

#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
        int data;
        Node* next;
        Node* prev;

        Node(int data1){
            this->data=data1;
            this->next=nullptr;
            this->prev=nullptr;
        }

        Node(int data1,Node* next1,Node* back1){
            this->data=data1;
            this->next=next1;
            this->prev=back1;
        }

        Node(int data1,Node* back1){
            this->data=data1;
            this->next=nullptr;
            this->prev=back1;
        }
};

Node* convertArr2DLL(vector<int> arr){
    Node* head=new Node(arr[0]);
    Node* temp=head;
    int n=arr.size();
    for(int i=1;i<n;i++){
        Node* newNode=new Node(arr[i],temp);
        temp->next=newNode;
        temp=newNode;
    }
    return head;
}

void printDLL(Node* head){
    Node* temp=head;
    while(temp){
        cout<<temp->data<<",";
        temp=temp->next;
    }
}

Node* removeHead(Node* &head){
    if(!head || !head->next) return NULL;
    Node* prev=head;
    head=head->next;
    head->prev=nullptr;
    prev->next=nullptr;
    delete prev;
    return head;
}

Node* removeTail(Node* &head){
    if(!head || !head->next) return NULL;
    Node* tail=head;
    while(tail->next){
        tail=tail->next;
    }
    Node* newTail=tail->prev;
    newTail->next=nullptr;
    tail->prev=nullptr;
    delete tail;
    return head;
}

Node* removeKthElement(Node* &head,int k){
    if(head==NULL) return NULL;
    int cnt=0;
    Node* kNode=head;
    while(kNode){
        cnt++;
        if(cnt==k) break;
        kNode=kNode->next;
    }
    Node* prev=kNode->prev;
    Node* front=kNode->next;
    if(!prev && !front) return NULL;
    else if(!prev) return removeHead(head);
    else if(!front) return removeTail(head);
    prev->next=front;
    front->prev=prev;
    kNode->next=nullptr;
    kNode->prev=nullptr;
    delete kNode;
    return head;
}

Node* removeX(Node* &head,int X){
    Node* currNode=head;
    while(currNode){
        if(currNode->data==X) break;
        currNode=currNode->next;
    }
    if(!currNode) return head;
    Node* prev=currNode->prev;
    Node* front=currNode->next;
    if(!prev && !front) return NULL;
    else if(!prev) return removeHead(head);
    else if(!front) return removeTail(head);
    prev->next=front;
    front->prev=prev;
    currNode->prev=nullptr;
    currNode->next=nullptr;
    delete currNode;
    return head;
}

Node* insertAfterHead(Node* &head,int d){
    Node* newNode=new Node(d);
    Node* prev=head;
    Node* front=head->next;
    newNode->prev=prev;
    newNode->next=front;
    head->next->prev=newNode;
    head->next=newNode;
    return head;
}

Node* insertBeforeHead(Node* &head,int d){
    Node* newNode=new Node(d,head,nullptr);
    head->prev=newNode;
    head=newNode;
    return head;

}

Node* insertAfterTail(Node* &head,int d){
    Node* temp=head;
    while(temp->next){
        temp=temp->next;
    }
    Node* newNode=new Node(d,nullptr,temp);
    temp->next=newNode;
    return head;
}

Node* insertBeforeTail(Node* &head,int d){
    Node* temp=head;
    while(temp->next){
        temp=temp->next;
    }
    Node* newNode=new Node(d,temp,temp->prev);
    temp->prev->next=newNode;
    temp->prev=newNode;
    return head;
}

Node* insertAfterKthElement(Node* &head,int d,int k){
    if(k==1) return insertAfterHead(head,d);
    Node* kNode=head;
    int cnt=1;
    while(kNode->next){
        cnt++;
        kNode=kNode->next;
        if(cnt==k) break;
    }
    if(!kNode->next && cnt==k) return insertAfterTail(head,d);
    if(cnt<k) return head;
    Node* newNode=new Node(d,kNode->next,kNode);
    kNode->next->prev=newNode;
    kNode->next=newNode;
    return head;
}

Node* insertBeforeKthElement(Node* &head,int d,int k){
    if(k==1) return insertBeforeHead(head,d);
    Node* kNode=head;
    int cnt=1;
    while(kNode->next){
        cnt++;
        kNode=kNode->next;
        if(cnt==k) break;
    }
    if(!kNode->next && cnt==k) return insertBeforeTail(head,d);
    if(cnt<k) return head;
    Node* newNode=new Node(d,kNode,kNode->prev);
    kNode->prev->next=newNode;
    kNode->prev=newNode;

    return head;
}

Node* insertAfterX(Node* &head,int d,int x){
    if(head->data==x) return insertAfterHead(head,d);
    Node* kNode=head;
    while(kNode->next){
        if(kNode->data==x) break;
        kNode=kNode->next;
    }
    if(!kNode->next && kNode->data!=x) return head;
    if(!kNode->next) return insertAfterTail(head,d);
    Node* newNode=new Node(d,kNode->next,kNode);
    cout<<"Hi";
    kNode->next->prev=newNode;
    cout<<"he";
    kNode->next=newNode;
    cout<<"hello";
    return head;
}

Node* insertBeforeX(Node* &head,int d,int x){
    if(head->data==x) return insertBeforeHead(head,d);
    Node* kNode=head;
    while(kNode->next){
        if(kNode->data==x) break;
        kNode=kNode->next;
    }
    if(!kNode->next && kNode->data!=x) return head;
    if(!kNode->next) return insertBeforeTail(head,d);
    Node* newNode=new Node(d,kNode,kNode->prev);
    kNode->prev->next=newNode;
    kNode->prev=newNode;
    return head;
}

Node* reverseDLL_brute(Node* &head){
    Node* temp=head;
    stack<int> st;
    while(temp->next){
        st.push(temp->data);
        temp=temp->next;
    }
    st.push(temp->data);
    temp=head;
    while(temp->next){
        temp->data=st.top();
        st.pop();
        temp=temp->next;
    }
    temp->data=st.top();
    st.pop();
    return head;
}
Node* reverseDLL(Node* &head){
    if(head==NULL || head->next==NULL) return head;
    Node* prev=NULL;
    Node* curr=head;
    while(curr){
        prev=curr->prev;
        curr->prev=curr->next;
        curr->next=prev;
        curr=curr->prev;
    }
    return prev->prev;
}


//Delete all occurences of a key in doubly LL
//Brute Force : Just store all the elements in hash map
Node* delAllOccurences(Node* head,int k){
    if(!head) return head;
    Node* temp=head;
    while(temp){
        if(temp->data==k){
            if(temp==head) head=head->next;
            Node* nextNode=temp->next;
            Node* prevNode=temp->prev;
            if(nextNode) nextNode->prev=prevNode;
            if(prevNode) prevNode->next=nextNode;
            delete temp;
            temp=nextNode;
        }
        else temp=temp->next;
    }
    return head;
}
//Time Complexity will be O(n)


//Find all pairs with the given sum
//Brute Force : Double Traversal
vector<pair<int,int>> pairsWithSumK_brute(Node* head,int k){
    if(!head) return {{-1,-1}};
    Node* temp=head;
    vector<int> vec;
    while(temp){
        vec.push_back(temp->data);
        temp=temp->next;
    }
    int n=vec.size();
    vector<pair<int,int>> ans;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(vec[i]+vec[j]==k) ans.push_back({vec[i],vec[j]});
        }
    }
    return ans;
};
//Time Complexity will be O(n+(n*n))
//Space Complexity will be O(n)

//Better Solution : Double traversal without using extra space
vector<pair<int,int>> pairsWithSumK_better(Node* head,int k){
    if(!head) return {{-1,-1}};
    Node* temp=head;
    vector<pair<int,int>> ans;
    while(temp){
        Node* temp2=temp->next;
        while(temp2){
            int n=temp->data;
            int m=temp2->data;
            if(n+m==k) ans.push_back({n,m});
            else if(n+m>k) break;
            temp2=temp2->next;
        }
        temp=temp->next;
    }
    return ans;
}
//Time Complexity will be O(n*n)

//Optimal Solution : Using Sliding Window/Two pointer Approach
vector<pair<int,int>> pairsWithSumK(Node* head,int k){
    if(!head) return {{-1,-1}};
    Node* temp=head;
    while(temp->next) temp=temp->next;
    Node* right=temp;
    Node* left=head;
    vector<pair<int,int>> ans;
    while(((left->data)<=(right->data)) && (right!=left) && (right && left)){
        int n=left->data;
        int m=right->data;
        if((n+m)==k){
            ans.push_back({n,m});
            left=left->next;
            right=right->prev;
        }
        else if((n+m)>k) right=right->prev;
        else left=left->next;
    }
    return ans;
}
//Time Complexity will be O(2n)


//Remove duplicates from a sorted DLL
Node* removeDuplicatesFromSorted(Node* head){
    if(!head) return head;
    Node* temp=head;
    while(temp){
        if(!temp->next) break;
        while(temp->next && (temp->next->data==temp->data)){
            Node* toDel=temp->next;
            temp->next=toDel->next;
            if(!toDel->next) break;
            toDel->next->prev=temp;
            delete toDel;
        }
        temp=temp->next;
    }
    return head;
}
//Time Complexity will be O(n)


//Design Browser History
//For this we would first create a node which can store string
class NodeB{
    public:
        string data;
        NodeB* next;
        NodeB* prev;
        NodeB(string str){
            this->data=str;
            this->next=nullptr;
            this->prev=nullptr;
        }
};

class Browser{
    public:
        NodeB* currentPage;
        Browser(string &homepage){
            currentPage=new NodeB(homepage);
        }
        
        void visit(string url){
            NodeB* newNode=new NodeB(url);
            currentPage->next=newNode;
            newNode->prev=currentPage;
            currentPage=newNode;
        }

        string back(int steps){
            while(steps){
                if(currentPage->prev) currentPage=currentPage->prev;
                else break;
                steps--;
            }
            return currentPage->data;
        }
        //TC : O(n) n is the number of steps

        string forward(int steps){
            while(steps){
                if(currentPage->next) currentPage=currentPage->next;
                else break;
                steps--;
            }
            return currentPage->data;
        }
        //TC : O(n) n is the number of steps
};

int main(){
    vector<int> arr={1,1,2,2,3,3,3};
    Node* head=convertArr2DLL(arr);
    head=removeDuplicatesFromSorted(head);
    printDLL(head);
    return 0;
}
