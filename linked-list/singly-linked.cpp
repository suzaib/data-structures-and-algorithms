/*
Linked List : A data structure that allows to increase as well as decrease its size
-> Elements of a LL are not stored in contiguous locations like arrays, if one element is at x position in memory , the next element can be anywhere
-> Since in array we can't store extra element since we don't know if the next immediate memory is free or not, but in LL since it stores anywhere in the memory , it can always find a place to store the next input
-> Each time we store an element , we also store next, that is , the next memory location along with it, in case we are storing the last element, the next is null*(null pointer)
-> LL are used in stacks/queues extensively and also for browser
-> 1D linked list store only the forward pointer ,that is next. But recall that in browsers, if you click the < button , it takes you the previous page, that is where a 2D LL is used that stores both, the next and the previous memory location


Pointers :
    int x=10 
    int* y=&x;
    the first line creates a variable and assigns a value 10 to it
    the second line:
        & before a variable means we are not accessing the value of variable but are trying to know , where in the memory of computer , does the variable resides
        Also we can't store memory locations like int mem=&x, this is not correct. We can , however, have a pointer pointing to that memory location like int* y
        So when we try to cout<<y  it returns the place in memory where the x is stored

Now , since the LL stores two things, the data and the pointer to the next memory location , and both the things are not of single types, therefore they can't be stored in any datatype known,
for this we will create our own datatype

*/
#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
        int data;
        Node* next;
        Node(int data1){
            this->data=data1;
            this->next=NULL;
        }
};
Node* convertArr2LL(vector<int> &arr){
    Node* head=new Node(arr[0]);
    Node* mover=head;
    for(int i=1;i<arr.size();i++){
        Node* temp=new Node(arr[i]);
        mover->next=temp;
        mover=temp;
    }
    return head;

}

void printLL(Node* head){
    Node* temp=head;
    while(temp){
        cout<<temp->data<<",";
        temp=temp->next;
    }
}

int lenOfLL(Node* &head){
    if(!head) return 0;
    Node* temp=head;
    int cnt=0;
    while(temp){
        temp=temp->next;
        cnt++;
    }
    return cnt;
}

//Does an element exists in Linked List
bool doesExist(Node* head,int x){
    Node* temp=head;
    while(temp){
        if(temp->data==x) return true;
        temp=temp->next;
    }
    return false;
}

Node* removeHead(Node* &head){
    if(head==NULL) return head;
    Node* temp=head;
    head=head->next;
    delete temp;
    return head;
}

void removeTail(Node* head){
    if(head==NULL) return;
    if(head->next==NULL) return;
    Node* temp=head;
    while(temp->next->next){
        temp=temp->next;
    }
    delete temp->next;
    temp->next=nullptr;
}

void removeKthElement(Node* &head,int k){
    if(k==1){
        Node* temp=head;
        head=head->next;
        delete temp;
        return;
    }
    int cnt=2;
    Node* temp=head;
    while(temp){
        if(cnt==k){
            Node* toRemove=temp->next;
            temp->next=temp->next->next;
            delete toRemove;
            return;
        }
        cnt++;
        temp=temp->next;
    }
}

void removeX(Node* &head,int X){
    Node* temp=head;
    if(head->data==X){
        Node* tmp=head;
        head=head->next;
        delete tmp;
        return;

    }
    while(temp->next){
        if(temp->next->data==X){
            Node* toRemove=temp->next;
            temp->next=temp->next->next;
            delete toRemove;
            return;
        }
        temp=temp->next;
    }
}

Node* insertAtHead(Node* &head,int k){
    Node* newNode=new Node(k);
    newNode->next=head;
    head=newNode;
    return head;
}

void insertAtTail(Node* &head,int k){
    Node* temp=head;
    while(temp->next){
        temp=temp->next;
    }
    Node* newNode=new Node(k);
    temp->next=newNode;
    newNode->next=nullptr;
}

Node* insertAtKthPos(Node* &head,int k,int pos){
    if(pos==1) return insertAtHead(head,k);
    int cnt=1;
    Node* temp=head;
    while(temp){
        cnt++;
        if(cnt==pos){
            Node* newNode=new Node(k);
            newNode->next=temp->next;
            temp->next=newNode;
            return head;
        }
        temp=temp->next;
    }
    return head;
}

Node* insertBeforeX(Node* &head,int k,int x){
    if(head->data==x) return insertAtHead(head,k);
    Node* temp=head;
    while(temp->next){
        if(temp->next->data==x){
            Node* newNode=new Node(k);
            newNode->next=temp->next;
            temp->next=newNode;
            return head;
        }
        temp=temp->next;
    }
    return head;
}

//Add Two Numbers represented as LL
Node* addTwoNumLL(Node* head1,Node* head2){
    string s1="";
    string s2="";
    Node* temp1=head1;
    Node* temp2=head2;
    while(temp1){
        s1+=to_string(temp1->data);
        temp1=temp1->next;
    }

    while(temp2){
        s2+=to_string(temp2->data);
        temp2=temp2->next;
    }
    int a=stoi(s1);
    int b=stoi(s2);
    int res=a+b;
    string s=to_string(res);
    Node* head=new Node(s[0]-'0');
    int n=s.size();
    Node* temp=head;
    for(int i=1;i<n;i++){
        Node* newNode=new Node(s[i]-'0');
        temp->next=newNode;
        temp=temp->next;
    }
    return head;

}

//Consider 12 and 44
//When adding in reverse means add 443 and 21 which will be adding 344 and 12 and answer is also to be given in reverse 
Node* addTwoLL_reversed(Node* head1,Node* head2){
    Node* t1=head1;
    Node* t2=head2;
    Node* dummy=new Node(-1);
    Node* curr=dummy;
    int sum=0;
    int carry=0;
    while(t1 || t2){
        sum=carry;
        if(t1) sum=sum+t1->data;
        if(t2) sum=sum+t2->data;
        Node* newNode=new Node(sum%10);
        curr->next=newNode;
        curr=curr->next;
        if(t1) t1=t1->next;
        if(t2) t2=t2->next;
        carry=sum/10;
    }

    if(carry){
        Node* newNode=new Node(carry);
        curr->next=newNode;
        curr=curr->next;
    }
    return dummy->next;
}

Node* oddAndEvenLL_brute(Node* head){
    if(!head || !head->next) return head; 
    vector<int> arr;
    Node* temp=head;
    while(temp && temp->next){
        arr.push_back(temp->data);
        temp=temp->next->next;
    }
    if(temp) arr.push_back(temp->data);
    temp=head->next;
    while(temp && temp->next){
        arr.push_back(temp->data);
        temp=temp->next->next;
    }
    if(temp) arr.push_back(temp->data);

    int i=0;
    temp=head;
    while(temp){
        temp->data=arr[i];
        i++;
        temp=temp->next;
    }
    return head;
}

Node* oddAndEvenLL_better(Node* head){
    Node* temp=head;
    int cnt=1;
    Node* temp1=new Node(-1);
    Node* temp2=new Node(-1);
    Node* head1=temp1;
    Node* head2=temp2;
    while(temp){
        if(cnt%2!=0){
            temp1->next=temp;
            temp1=temp1->next;
            temp=temp->next;
        }
        else{
            temp2->next=temp;
            temp2=temp2->next;
            temp=temp->next;
        }
        cnt++;
    }
    if(cnt%2==0) temp2->next=nullptr;
    temp1->next=head2->next;
    delete head2;
    head1=head1->next;
    return head1;
}

Node* oddAndEvenLL_optimal(Node* head){
    if(!head || !head->next) return head;
    Node* odd=head;
    Node* even=head->next;
    Node* newHead=odd;
    Node* evenHead=even;
    while(even!=NULL && even->next!=NULL){
        odd->next=odd->next->next;
        even->next=even->next->next;

        odd=odd->next;
        even=even->next;
    }
    odd->next=evenHead;
    return head;
}

Node* sort012_brute(Node* head){
    Node* temp=head;
    int cnt0=0;
    int cnt1=0;
    int cnt2=0;
    while(temp){
        if(temp->data==0) cnt0++;
        else if(temp->data==1) cnt1++;
        else if(temp->data==2) cnt2++;
        temp=temp->next;
    }
    temp=head;
    while(temp && cnt0>0){
        temp->data=0;
        cnt0--;
        temp=temp->next;
    }

    while(temp && cnt1>0){
        temp->data=1;
        cnt1--;
        temp=temp->next;
    }
    while(temp && cnt2>0){
        temp->data=2;
        cnt2--;
        temp=temp->next;
    }
    return head;
}

Node* sort012(Node* head){
    if(!head || !head->next) return head;
    Node* temp=head;
    Node* d0=new Node(-1);
    Node* d1=new Node(-1);
    Node* d2=new Node(-1);
    Node* t0=d0;
    Node* t1=d1;
    Node* t2=d2;
    while(temp){
        if(temp->data==0){
            Node* newNode=new Node(0);
            t0->next=newNode;
            t0=t0->next;
        }
        else if(temp->data==1){
            Node* newNode=new Node(1);
            t1->next=newNode;
            t1=t1->next;
        }
        else {
            Node* newNode=new Node(2);
            t2->next=newNode;
            t2=t2->next;
        }
        temp=temp->next;
    }
    if(d1->next) t0->next=d1->next;
    else t0->next=d2->next;
    t1->next=d2->next;
    t2->next=nullptr;
    head=d0->next;
    delete d0;
    delete d1;
    delete d2;
    return head;
}

Node* delNthNodeFromEnd_brute(Node* head,int n){
    int len=lenOfLL(head);
    if(len==n){
        Node* newHead=head->next;
        delete head;
        return newHead;
    }
    int res=len-n;
    Node* temp=head;
    //nth node from the end is same as (len-n+1)th node from beginning
    //And to delete nth node from beginning, we need to reach the n-1 th node
    while(temp){
        res--;
        if(res==0) break;
        temp=temp->next;
    }
    return head;

};

//Optimal Code
Node* delNthNodeFromEnd(Node* head,int n){
    if(!head) return head;
    Node* fast=head;
    for(int i=0;i<n;i++){
        fast=fast->next;
        if(!fast && i==n-1){
            Node* newHead=head->next;
            delete head;
            return newHead;
        }
        else if(!fast && i!=n-1) return head;
    }
    Node* slow=head;
    while(fast->next){
        fast=fast->next;
        slow=slow->next;
    }
    Node* temp=slow->next;
    slow->next=slow->next->next;
    delete temp;
    return head;
};

Node* reverseLL_brute(Node* head){
    if(!head || !head->next) return head;
    Node* temp=head;
    vector<int> arr;
    while(temp){
        arr.push_back(temp->data);
        temp=temp->next;
    }
    int n=arr.size();
    temp=head;
    int i=n-1;
    while(temp){
        temp->data=arr[i];
        i--;
        temp=temp->next;
    }
    return head;
};

//We can also use stack
Node* reverseLL_brute2(Node* head){
    if(!head || !head->next) return head;
    Node* temp=head;
    stack<int> st;
    while(temp){
        st.push(temp->data);
        temp=temp->next;
    }
    temp=head;
    while(temp){
        temp->data=st.top();
        temp=temp->next;
        st.pop();
    }
    return head;
}

//For optimal methods, think of reversing the links in LL rather than reversing the data
Node* reverseLL(Node* head){
    if(!head || !head->next) return head;
    Node* temp=head;
    Node* prev=nullptr;
    while(temp){
        Node* front=temp->next;
        temp->next=prev;
        prev=temp;
        temp=front;
    }
    return prev;
};

Node* reverseLL_recursive_optimal(Node* head){
    if(!head || !head->next) return head;
    Node* newHead=reverseLL_recursive_optimal(head->next);
    Node* front=head->next;
    front->next=head;
    head->next=NULL;
    return newHead;
}



Node* midOfLL_brute(Node* head){
    Node* temp=head;
    int cnt=0;
    while(temp){
        cnt++;
        temp=temp->next;
    }
    int mid=(cnt/2)+1;
    cnt=0;
    temp=head;
    while(temp){
        cnt++;
        if(cnt==mid) return temp;
        temp=temp->next;
    }
    return NULL;
}

//Optimal solution using tortoise hare method
//Concept : Suppose A runs with speed x and B runs with speed 2x, then distance covered by B at any time = 2xdistance covered by A
//Therefore when B reaches the last node, A will be at the middle
Node* midOfLL(Node* head){
    Node* fast=head;
    Node* slow=head;
    while(fast && fast->next){
        fast=fast->next->next;
        slow=slow->next;
    }

    return slow;
}
bool isLLPalindromic_brute(Node* head){
    Node* temp=head;
    vector<int> arr;
    while(temp){
        arr.push_back(temp->data);
        temp=temp->next;
    }
    int n=arr.size();
    int i=0;
    int j=n-1;
    while(i<j){
        if(arr[i]!=arr[j]) return false;
        i++;
        j--;
    }
    return true;

}

bool isLLPalindromic_brute2(Node* head){
    Node* temp=head;
    stack<int> st;
    while(temp){
        st.push(temp->data);
        temp=temp->next;
    }

    temp=head;
    while(temp){
        if(temp->data!=st.top()) return false;
        st.pop();
        temp=temp->next;
    }
    return true;
}

//Optimal Method

bool isLLPalindromic(Node* head){
    Node* head1=head;
    Node* mid=midOfLL(head);
    Node* head2=reverseLL_recursive_optimal(mid);
    Node* temp1=head1;
    Node* temp2=head2;
    while(temp1 && temp2){
        if(temp1->data!=temp2->data){
            reverseLL_recursive_optimal(head2);
            return false;
        }
        temp1=temp1->next;
        temp2=temp2->next;
    }
    reverseLL(head2);
    return true;
}
//Time Complexity will be O(2n)


//Adding 1 to a LL
//Brute Force : Extract the number, then add 1 then convert it into LL
Node* add1ToLL_brute(Node* head){
    if(!head) return head;
    string str="";
    Node* temp=head;
    while(temp){
        str+=to_string(temp->data);
        temp=temp->next;
    }
    int x=stoi(str);
    x=x+1;
    str=to_string(x);
    int n=str.size();
    char ch=str[0];
    int y=ch-'0';
    Node* newHead=new Node(y);
    temp=newHead;
    for(int i=1;i<n;i++){
        char ch=str[i];
        int y=ch-'0';
        Node* newNode=new Node(y);
        temp->next=newNode;
        temp=newNode;
    }
    return newHead;
}
//Time Complexity will be O(n+n) for the two traversals + some added time due to the to_string and stoi functions used

//Better Approach : To first reverse the LL, then keep adding while taking a carry and then reversing the LL again
Node* add1ToLL_better(Node* head){
    head=reverseLL_recursive_optimal(head);
    Node* temp=head;
    int carry=1;
    while(temp){
        temp->data=temp->data+carry;
        if(temp->data<10){
            carry=0;
            break;
        }
        else{
            temp->data=0;
            carry=1;
        }
        temp=temp->next;
    }

    if(carry==1){
        Node* newNode=new Node(1);
        head=reverseLL_recursive_optimal(head);
        newNode->next=head;
        return newNode;
    }
    head=reverseLL_recursive_optimal(head);
    return head;
}
//Time Complexity will be O(3n)

// Optimal Approach : Using recursion (without reversing the linked list) 
int helper(Node* temp){
    if(!temp) return 1;
    int carry=helper(temp->next);
    temp->data=(temp->data)+carry;
    if(temp->data<10) return 0;
    temp->data=0;
    return 1;
}
Node* add1ToLL(Node* head){
    int carry=helper(head);
    if(carry==1){
        Node* newNode=new Node(1);
        newNode->next=head;
        return newNode;
    }
    return head;
}
//Time Complexity will be O(n)
//Space Complexity will be O(n)


//Find Intersection point of a Y linked list
//Brute Force : Hashing
Node* intersectionOfYLL_brute(Node* head1,Node* head2){
    if(!head1 || !head2) return NULL;
    unordered_map<Node*,int> mpp;
    Node* temp=head1;
    while(temp){
        mpp[temp]++;
        temp=temp->next;
    }

    temp=head2;
    while(temp){
        if(mpp.find(temp)!=mpp.end()) return temp;
        temp=temp->next;
    }
    return NULL;
};

//Better Approach : Get the length of both linked lists, then start at same vertical level
Node* intersectionOfYLL_better(Node* head1,Node* head2){
    if(!head1 || !head2) return NULL;
    int n=lenOfLL(head1);
    int m=lenOfLL(head2);
    Node* temp1=head1;
    Node* temp2=head2;
    int x=abs(n-m);
    if(n>m){
        while(x>0){
            temp1=temp1->next;
            x--;
        }
    }
    else if(m>n){
        while(x>0){
            temp2=temp2->next;
            x--;
        }
    }

    while(temp1 && temp2){
        if(temp1==temp2) return temp1;
        temp1=temp1->next;
        temp2=temp2->next;
    }
    return NULL;
}
//Time Complexity will be O(n+m+(n-m)+m)(n>m)

//Optimal Approach : Very easy, just watch the video to get intuition
Node* intersectionOfYLL(Node* head1,Node* head2){
    if(!head1 || !head2) return NULL;
    Node* temp1=head1;
    Node* temp2=head2;
    if(temp1==temp2) return temp1;
    while(temp1!=temp2){
        temp1=temp1->next;
        temp2=temp2->next;
        if(temp1==temp2 && temp1==nullptr) return nullptr;
        //The condition where there is no intersection point is also covered since both the temp1 and temp2 will point to null
        //Therefore both will be equal and null will be returned

        if(!temp1) temp1=head2;
        if(!temp2) temp2=head1;
        if(temp1==temp2) return temp1;
    }
    return NULL;
}
//Time Complexity will be O(n+m)
//Space Complexity will be O(1)

//Detecting a loop in a linked list
Node* detectLoopInLL_brute(Node* head){
    if(!head) return NULL;
    unordered_map<Node*,int> mpp;
    Node* temp=head;
    while(temp){
        if(mpp.find(temp)!=mpp.end()) return temp;
        mpp[temp]++;
        temp=temp->next;
    }
    return NULL;
}
//Time Complexity will be O(n) (since unordered map takes O(1) time in almost all cases)
//Space Complexity will be O(n)

//Optimal Approach : Using Tortoise and Hare Method
Node* detectLoopInLL(Node* head){
    if(!head) return NULL;
    Node* slow=head;
    Node* fast=head;
    while(fast && fast->next){
        fast=fast->next->next;
        slow=slow->next;
        if(fast==slow) return fast;
    }
    return NULL;
}
//Time Complexity will be O(n) (can't pinpoint exactly)


//Length of Loop in a linked list
//Brute Force 
int lenOfLoopInLL_brute(Node* head){
    if(!head || !head->next) return 0;
    int cnt=1;
    Node* temp=head;
    unordered_map<Node*,int> mpp;
    while(temp){
        if(mpp.find(temp)!=mpp.end()){
            int ans=cnt-mpp[temp];
            return ans;
        };
        mpp[temp]=cnt;
        cnt++;
        temp=temp->next;
    }
    return 0;
}
//Time Complexity will be O(n)
//Space Complexity will be O(n)

//Optimal Approach : We first find any node inside the loop then making it the starting point, keep traversing while increasing the count
int lenOfLoopInLL(Node* head){
    if(!head || !head->next) return 0;
    Node* loopNode=detectLoopInLL(head);
    Node* temp=loopNode->next;
    int cnt=1;
    while(temp!=loopNode){
        cnt++;
        temp=temp->next;
    }
    return cnt;
};
//Time Complexity will be O(n+n)


//Delete the middle node in a linked list
//Brute Force : First get the length of LL, then calculate the middle, then delete the node
Node* delMidNode_brute(Node* head){
    if(!head || !head->next) return head;
    int n=lenOfLL(head);
    int mid=n/2;
    int cnt=0;
    Node* temp=head;
    while(temp){
        cnt++;
        if(cnt==mid) break;
        temp=temp->next;

    }
    Node* toDel=temp->next;
    temp->next=temp->next->next;
    delete toDel;
    return head;
}
//Time Complexity will be O(n+(n/2))

//Optimal Approach : Using the tortoise hare algorithm with slight modification
//The Slight modification is that instead of starting both slow and fast at same location, start fast at 3rd Node
Node* delMidNode(Node* head){
    if(!head || !head->next) return NULL;
    if(!head->next->next) return head;
    Node* slow=head;
    Node* fast=head->next->next;
    while(fast && fast->next){
        slow=slow->next;
        fast=fast->next->next;
    }
    Node* toDel=slow->next;
    slow->next=slow->next->next;
    delete toDel;
    return head;
}
//Time Complexity will be O(n/2)


//Find the starting point of a loop in a LL
Node* initialNodeOfLoop_brute(Node* head){
    if(!head || !head->next) return head;
    unordered_map<Node*,int> mpp;
    Node* temp=head;
    while(temp){
        if(mpp.find(temp)!=mpp.end()) return temp;
        mpp[temp]++;
        temp=temp->next;
    }
    return NULL;
}
//Time Complexity will be O(n) (as unordered_map takes almost constant time)
//Space Complexity will be O(n)

//Optimal Approach : Tortoise and the hare algorithm
//See video, Intuition is very interesting
Node* initialNodeOfLoop(Node* head){
    if(!head || !head->next) return head;
    Node* slow=head;
    Node* fast=head;
    while(fast && fast->next){
        fast=fast->next->next;
        slow=slow->next;
        if(fast==slow) break;
    }
    if(!fast || !fast->next) return NULL;
    slow=head;
    while(true){
        slow=slow->next;
        fast=fast->next;
        if(slow==fast) return slow;
    }
    return NULL;
}
//Time Complexity will be around O(2n)


//Reversing a Linked list in groups of size k
Node* findKthNode(Node* head,int k){
    int cnt=0;
    Node* temp=head;
    while(temp){
        cnt++;
        if(cnt==k) return temp;
        temp=temp->next;
    }
    return NULL;
}
Node* reverseLLInGroup(Node* head,int k){
    Node* temp=head;
    Node* prevNode=NULL;
    while(temp){
        Node* kthNode=findKthNode(temp,k);
        if(!kthNode){
            if(prevNode) prevNode->next=temp;
            break;
        }
        Node* nextNode=kthNode->next;
        kthNode->next=NULL;
        Node* revHead=reverseLL(temp);
        if(temp==head) head=kthNode;
        else prevNode->next=kthNode;
        prevNode=temp;
        temp=nextNode;
    }
    return head;
}
//Time Complexity will be O(2n)


//Rotating A Linked List
//Left Rotation By 1 Place
Node* rotateLeftBy1Place(Node* head){
    Node* temp=head;
    int lastData=temp->data;
    while(temp->next){
        temp->data=temp->next->data;
        temp=temp->next;
    }
    temp->data=lastData;
    return head;
}

//Right Rotation By 1 Place
Node* rotateRightBy1Place(Node* head){
    Node* temp=head;
    int curr=temp->data;
    while(temp->next){
        temp=temp->next;
        int tempData=temp->data;
        temp->data=curr;
        curr=tempData;
    }
    head->data=curr;
    return head;
}
//Time Complexity will be O(n)

//Right Rotation by K places 
//The idea is to change the links from the last node, make the kth node the first node.
Node* rotateRightByKPlaces(Node* head,int k){
    Node* temp=head;
    Node* initialNode=head;
    int n=lenOfLL(temp);
    k=k%n;
    if(k==0) return head;
    int cnt=0;
    while(temp->next){
        cnt++;
        if(cnt==(n-k)){
            head=temp->next;
            temp->next=NULL;
            temp=head;
            
        }
        else temp=temp->next;
    }
    temp->next=initialNode;
    return head;
}
//Time Complexity will be O(2n)



//Merge Two Sorted Linked List and return a new Linked List (which is sorted as well)
//Brute Force : Put all the elements in to a vector and then sort the vector, then put back the elements in to a linked list
Node* merge2SortedLL_brute(Node* head1, Node* head2){
    if(!head1 && !head2) return NULL;
    vector<int> merged;
    Node* temp1=head1;
    while(temp1){
        merged.push_back(temp1->data);
        temp1=temp1->next;
    }

    Node* temp2=head2;
    while(temp2){
        merged.push_back(temp2->data);
        temp2=temp2->next;
    }

    sort(merged.begin(),merged.end());
    Node* head=convertArr2LL(merged);
    return head;
}
//Time Complexity will be O(n+m+ (n+m)log(n+m)+(n+m))
//Space Complexity will be O(n+m)

//Better Approach : Use the Two Pointer Approach and make a new linked list
Node* merge2SortedLL_better(Node* head1, Node* head2){
    if(!head1 && !head2) return NULL;
    if(!head1) return head2;
    if(!head2) return head1;
    Node* temp1=head1;
    Node* temp2=head2;
    Node* head=new Node(-1);
    Node* temp=head;
    while(temp1 && temp2){
        int data1=temp1->data;
        int data2=temp2->data;
        if(data1>data2){
            temp->data=data2;
            temp2=temp2->next;
            if(!temp2) break;
        }
        else{
            temp->data=data1;
            temp1=temp1->next;
            if(!temp1) break;
        }
        Node* nextNode=new Node(-1);
        temp->next=nextNode;
        temp=temp->next;
    }

    while(temp1){
        int data1=temp1->data;
        temp->data=data1;
        temp1=temp1->next;
        if(!temp1) break;
        Node* nextNode=new Node(-1);
        temp->next=nextNode;
        temp=temp->next;
    }

    while(temp2){
        int data2=temp2->data;
        temp->data=data2;
        temp2=temp2->next;
        if(!temp2) break;
        Node* nextNode=new Node(-1);
        temp->next=nextNode;
        temp=temp->next;
    }
    return head;
}
//Time Complexity will be O(n+m)
//Space Complexity will be O(n+m)

//Optimal Approach : We need not create a new linked list, we can just keep changing the links
Node* merge2SortedLL(Node* head1, Node* head2){
    if(!head1 && !head2) return NULL;
    if(!head1) return head2;
    if(!head2) return head1;
    Node* temp1=head1;
    Node* temp2=head2;
    Node* head=new Node(-1);
    Node* temp=head;
    while(temp1 && temp2){
        int data1=temp1->data;
        int data2=temp2->data;
        if(data1<data2){
            temp->next=temp1;
            temp=temp1;
            temp1=temp1->next;
        }
        else{
            temp->next=temp2;
            temp=temp2;
            temp2=temp2->next;
        }
    }
    if(temp1) temp->next=temp1;
    if(temp2) temp->next=temp2;
    Node* toDel=head;
    head=head->next;
    delete toDel;
    return head;
}
//Time Complexity will be O(n+m)


//Merge K Sorted Linked Lists
Node* mergeKSortedLL_brute(vector<Node*> NodeList){
    int n=NodeList.size();
    vector<int> merged;
    for(int i=0;i<n;i++){
        Node* temp=NodeList[i];
        while(temp){
            merged.push_back(temp->data);
            temp=temp->next;
        }
    }
    sort(merged.begin(),merged.end());
    Node* head=convertArr2LL(merged);
    return head;
}
//Assuming Total lists are N with each having k elements, therefore total elements are m=k*n
//Time Complexity will be O(n*k + mlogm + m)
//Space Complexity will be O(m+m) (one m for arr, one for linked list creation) 

//Better Approach : Using the merge Two sorted LL method, take two LL at once
Node* mergeKSortedLL_better(vector<Node*> NodeList){
    int n=NodeList.size();
    Node* head=NodeList[0];
    int i=1;
    while(i<n){
        head=merge2SortedLL(head,NodeList[i]);
        i++;
    }
    return head;
}
//Time Complexity will be O((n1+n2)+(n1+n2+n3)+(n1+n2+n3+n4)+....)
//Assuming each to be of size n : TC ==> O(2n+3n+4n+...+kn)
//Just Assume the sum to be n+2n+3n (since adding one extra n won't matter much)
//Therefore the time complexity will be O(n(1+2+..+k)) ==> n*k*(k+1)/2, This is about in n cube power
//Space Complexity will be O(1)

//Optimal Approach 
//Using concept of min heap applied using priority queue
Node* mergeKSortedLL1(vector<Node*> NodeList){
    priority_queue<pair<int,Node*>,vector<pair<int,Node*>>,greater<pair<int,Node*>>> pq;
    //Priority queue takes three arguments : 1)type(required) 2)container(optional, default : vector) 3)comparator(default : less)
    int n=NodeList.size();
    for(int i=0;i<n;i++) pq.push({NodeList[i]->data,NodeList[i]});
    Node* dummy=new Node(-1);
    Node* dummyHead=dummy;
    while(!pq.empty()){
        pair<int,Node*> temp=pq.top();
        dummy->next=temp.second;
        pq.pop();
        Node* nextNode=temp.second->next;
        if(nextNode) pq.push({nextNode->data,nextNode});
        dummy=dummy->next;
    }
    Node* newHead=dummyHead->next;
    delete dummyHead;
    return newHead;
}
//Time Complexity will be O(k*logk + n*k*logk)
//Space Complexity will be O(k)

//We can do even better
//We don't need to store both node and value in the priority queue, instead we could only store the node
//Here is the best solution possible
class Compare{
    public:
    bool operator()(const ListNode* a, const ListNode* b){
        return a->val>b->val;
    }
};
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        int n=lists.size();
        if(n==0) return nullptr;
        priority_queue<ListNode*,vector<ListNode*>,Compare> pq;
        for(int i=0;i<n;i++){
            if(lists[i]) pq.push(lists[i]);
        }

        ListNode* dummy=new ListNode(-1);
        ListNode* curr=dummy;
        while(!pq.empty()){
            ListNode* temp=pq.top();
            pq.pop();
            if(temp->next) pq.push(temp->next);
            curr->next=temp;
            curr=temp;
        }
        return dummy->next;
    }
}
//Time Complexity will be O(k*logk + n*k*logk)
//Space Complexity will be O(k)

//Flattening a Linked List
//For this we would need a differently designed linked list
class LLNode{
    public:
        int val;
        LLNode* right;
        LLNode* down;
        LLNode(int val){
            this->val=val;
            this->right=nullptr;
            this->down=nullptr;
        }
        LLNode(int val,LLNode* right,LLNode* down){
            this->val=val;
            this->right=right;
            this->down=down;
        }
};


//We will be using this LL for flattening LL problems
//Brute Force : Traverse the whole LL, storing the values, then sorting them
void flattenFx(LLNode* node,vector<int> &temp){
    if(!node) return;
    temp.push_back(node->val);
    flattenFx(node->right,temp);
    flattenFx(node->down,temp);
    return;
}

LLNode* createFLL(vector<int> arr){
    int n=arr.size();
    LLNode* temp=new LLNode(arr[0]);
    LLNode* head=temp;
    for(int i=1;i<n;i++){
        LLNode* tempNode=new LLNode(arr[i]);
        temp->down=tempNode;
        temp=tempNode;
    }
    return head;
}
LLNode* flattenLL_brute(LLNode* head){
    if(!head) return head;
    vector<int> temp;
    flattenFx(head,temp);
    sort(temp.begin(),temp.end());
    head=createFLL(temp);
    return head;
}
//Assuming there are n rows with m elements each 
//Time Complexity wil be (n*m)*2 + (n*m)log(n*m)
//Space Complexity will be (n*m)*3(one for recursion, one for array, one for new ll)

//Optimal solution : Watch video for better explanation
//First we create a function to solve this problem if there were just two lines (using two pointer approach)
LLNode* mergeTwoFLL(LLNode* t1,LLNode* t2){
    LLNode* dummyHead=new LLNode(-1);
    LLNode* dummy=dummyHead;
    while(t1 && t2){
        int x1=t1->val;
        int x2=t2->val;
        if(x1>x2){
            dummy->down=t2;
            dummy=t2;
            t2=t2->down;
        }
        else{
            dummy->down=t1;
            dummy=t1;
            t1=t1->down;
        }
        dummy->right=nullptr;
    }

    if(t1) dummy->down=t1;
    else dummy->down=t2;
    return dummyHead->down;
}
//Time Complexity will be O(n1+n2)

LLNode* flattenLL(LLNode* head){
    if(!head || !head->right) return head;
    LLNode* mergeHead=flattenLL(head->right);
    return mergeTwoFLL(head,mergeHead);
}
//Time Complexity will be O(2mn)
//Space Complexity will be O(n) (recursion stack space)


//Sort a linke list
//Brute Force
//Store the values in a array, then sort the array then put the values back
Node* sortLL_brute(Node* head){
    if(!head || !head->next) return head;
    vector<int> arr;
    Node* temp=head;
    while(temp){
        arr.push_back(temp->data);
        temp=temp->next;
    }
    sort(arr.begin(),arr.end());
    int n=arr.size();
    temp=head;
    for(int i=0;i<n;i++){
        temp->data=arr[i];
        temp=temp->next;
    }
    //We could have just used convertArrToLL function, but it would have taken extra space, as it would create new nodes
    //Intead we have used the given nodes to optimise space

    return head;
}
//Time Complexity will be O(n+nlogn+n)
//Space Complexity will be O(n)

//Optimal Approach 
//Using merge and sort
Node* midOfLL_forMS(Node* head){
    if(!head || !head->next) return head;
    Node* slow=head;
    Node* fast=head;
    while(fast->next && fast->next->next){
        slow=slow->next;
        fast=fast->next->next;
    }
    return slow;
}
Node* sortLL(Node* head){
    if(!head || !head->next) return head;
    Node* middle=midOfLL_forMS(head);
    //We have modified the tortoise hare algorithm to find the first middle of a LL
    Node* leftHead=head;
    Node* rightHead=middle->next;
    middle->next=nullptr;
    leftHead=sortLL(leftHead);
    rightHead=sortLL(rightHead);
    return merge2SortedLL(leftHead,rightHead);
}
//Time Complexity will be O((n+n/2)*logn)
//Space Complexity will be O(1) excluding recursion stack space


//Cloning Linked List with random Pointers
//For this we would need a different kind of linked list with random pointers along with next 
//Therefore we first design such a linked list
class NodeR{
    public:
        int data;
        NodeR* next;
        NodeR* random;
        NodeR(int data){
            this->data=data;
            this->next=nullptr;
            this->random=nullptr;
        }
};

NodeR* cloneLL_brute(NodeR* head){
    NodeR* temp=head;
    unordered_map<NodeR*,NodeR*> mpp;
    while(temp){
        NodeR* newNode=new NodeR(temp->data);
        mpp[temp]=newNode;
        temp=temp->next;
    }
    temp=head;
    while(temp){
        NodeR* copyNode=mpp[temp];
        copyNode->next=mpp[temp->next];
        copyNode->random=mpp[temp->random];
        temp=temp->next;
    }
    return mpp[head];
}
//Time Complexity will be O(n+n) (assuming average case for unordered_map)
//Space Complexity will be O(n+n) (one n is required in the question)

//Optimal Approach 
NodeR* cloneLL(NodeR* head){
    NodeR* temp=head;

    //First we create new copied nodes and insert them in between
    while(temp){
        NodeR* newNode=new NodeR(temp->data);
        newNode->next=temp->next;
        temp->next=newNode;
        temp=temp->next->next;
    }

    //Now we link the random pointers
    temp=head;
    while(temp){
        if(temp->random) temp->next->random=temp->random->next;
        else temp->next->random=nullptr;
        temp=temp->next->next;
    }

    //Now removing the links 
    temp=head;
    NodeR* dummy=new NodeR(-1);
    NodeR* dummyHead=dummy;
    while(temp){
        dummy->next=temp->next;
        dummy=dummy->next;
        temp->next=temp->next->next;
        temp=temp->next;
    }

    NodeR* newHead=dummyHead->next;
    delete dummyHead;
    return newHead;

}
//Time Complexity will be O(n+n+n)
//Space Complexity will be O(n) (n is required to solve the question, therefore can't be reduced)


int main(){
    //Your function here
    return 0;
}
