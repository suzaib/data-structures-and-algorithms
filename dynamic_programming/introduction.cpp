//Dynamic Programming

//Tabulation : Bottom Up (From Base case to required ans)
//Memoization : Top Down

//Memoization and tabulation are opposite to each other in loop implementation


#include<bits/stdc++.h>
using namespace std;



//Fibonacci Sequence
//nth Fibonacci number
int nthFibonacci_brute(int n){
    if(n<=1) return n;
    return (nthFibonacci_brute(n-1)+nthFibonacci_brute(n-2));
}

//When we make the recursion tree, we find that some values like f(2) are calculated multiple times
//To avoid this, We can store such values and make code better
//This is called memoization
//Memoization
int fx(int n,vector<int> &temp){
    if(temp[n]!=-1) return temp[n];
    if(n<=1){
        temp[n]=n;
        return n;
    }
    int ans=fx(n-1,temp)+fx(n-2,temp);
    temp[n]=ans;
    return ans;
}
int nthFibonacci_memoization(int n){
    vector<int> temp(n+1,-1);
    return fx(n,temp);
}
//Time Complexity will be O(n) (since suppose for f(5) only 5,4,3,2,1 is evaluated once, rest call are constant since their value is fetched from array)
//Space Complexity will be O(n) for stack space + O(n) for array to store values

//Memoization without recursion is tabulation
//This allows us to eliminate the recursion stack space
//Tabulation
int nthFibonacci_tabulation(int n){
    vector<int> dp(n+1,-1);
    dp[0]=0;
    dp[1]=1;
    for(int i=2;i<=n;i++){
        dp[i]=dp[i-1]+dp[i-2];
    }
    return dp[n];
}
//Time Complexity will be O(n)
//Space Complexity will be O(n)

//We can optimise it even further
//Now we will try to eliminate the O(n) space that we were using
int nthFibonacci(int n){
    int last=0;
    if(n<=1) return n;
    int prev=1;
    int curr;
    for(int i=2;i<=n;i++){
        curr=prev+last;
        last=prev;
        prev=curr;
    }
    return curr;
}


//Total number of ways to climb stairs 
//You can take at max 2 steps at a time
int totalWaysToClimbStairs_brute(int n){
    if(n<=1) return 1;
    return (totalWaysToClimbStairs_brute(n-1)+totalWaysToClimbStairs_brute(n-2));
}
//At each step we have two options to jump
//Time Complexity in such cases is quite complex and we can say it is exponential
//Space will be used by recursion stack
//Time Complexity will be exponential
//Space Complexity will be O(n)

//Similar to the fibonacci problem
//Therefore we can memoize it, as well as do space optimization along with tabular form

int totalWaysToClimbStairs(int n){
    if(n<=2) return n;
    int last=1;
    int prev=2;
    int curr;
    for(int i=3;i<=n;i++){
        curr=prev+last;
        int temp=prev;
        prev=curr;
        last=temp;
    }
    return curr;
}
//Time Complexity will be O(n)


//Frog Jump I
//Can jump one or two steps at max
int fxFJ(vector<int> &arr,int idx){
    if(idx==0) return 0;
    int left=fxFJ(arr,idx-1)+abs(arr[idx-1]-arr[idx]);
    int right=INT_MAX;
    if(idx>1) right=fxFJ(arr,idx-2)+abs(arr[idx-2]-arr[idx]);
    return min(left,right);
}

//Frog Jump
int frogJump_brute(vector<int> arr){
    int n=arr.size();
    int ans=fxFJ(arr,n-1);
    return ans;
}

//Using Memoization
int f1FJ(vector<int> &arr,int idx,vector<int> &dp){
    if(dp[idx]!=-1) return dp[idx];
    if(idx==0) return 0;
    int left=f1FJ(arr,idx-1,dp)+abs(arr[idx-1]-arr[idx]);
    int right=INT_MAX;
    if(idx>1) right=f1FJ(arr,idx-2,dp)+abs(arr[idx-2]-arr[idx]);
    dp[idx]=min(left,right);
    return dp[idx];

}
int frogJump_memoized(vector<int> arr){
    int n=arr.size();
    vector<int> dp(n,-1);
    int ans=f1FJ(arr,n-1,dp);
    return ans;
}
//Time Complexity is reduced to O(n)
//Space Complexity is due to recursion stack space O(n) + dp array O(n) ==> O(2n)

//Using Tabulation form
int frogJump_tabulation(vector<int> &arr){
    int n=arr.size();
    vector<int> dp(n,-1);
    dp[0]=0;
    for(int i=1;i<n;i++){
        int firstStep=dp[i-1]+abs(arr[i]-arr[i-1]);
        int secondStep=INT_MAX;
        if(i>1) secondStep=dp[i-2]+abs(arr[i]-arr[i-2]);
        dp[i]=min(firstStep,secondStep);
    }
    return dp[n-1];
}

//Space Optimization
int frogJump(vector<int> &arr){
    int n=arr.size();
    int prev=0;
    int last=0;
    int curr=INT_MAX;
    for(int i=1;i<n;i++){
        int fs=prev+abs(arr[i]-arr[i-1]);
        int ss=INT_MAX;
        if(i>1) ss=last+abs(arr[i]-arr[i-2]);
        curr=min(fs,ss);
        last=prev;
        prev=curr;
    }
    return curr;
}
//Time Complexity will be O(n)


//Frog Jump II
//Frog can jump k distance at a time
int fxFJII_brute(vector<int> &arr,int idx,int k){
    if(idx==0) return 0;
    int minPoint=INT_MAX;
    for(int i=1;i<=k;i++){
        if(idx-i<0) break;
        if(idx-i>=0){
            int point=abs(arr[idx-i]-arr[idx])+fxFJII_brute(arr,idx-i,k);
            minPoint=min(minPoint,point);
        }
    }
    return minPoint;
}
int frogJumpII_brute(vector<int> &arr,int k){
    int n=arr.size();
    int ans=fxFJII_brute(arr,n-1,k);
    return ans;
}

//Memoization
int fxFJII_mem(int idx,vector<int> &arr,vector<int> &dp,int k){
    if(idx==0) return dp[idx]=0;
    if(dp[idx]!=-1) return dp[idx];
    int minPoint=INT_MAX;
    for(int i=1;i<=k;i++){
        if(idx-i<0) break;
        if(idx-i>=0){
            int point=abs(arr[idx-i]-arr[idx])+fxFJII_mem(idx-i,arr,dp,k);
            minPoint=min(minPoint,point);
        }
    }
    return dp[idx]=minPoint;
}
int frogJumpII_memoization(vector<int> &arr,int k){
    int n=arr.size();
    vector<int> dp(n,-1);
    return fxFJII_mem(n-1,arr,dp,k);
}

int frogJumpII(vector<int> &arr,int k){
    int n=arr.size();
    vector<int> dp(n,-1);
    dp[0]=0;
    for(int i=1;i<n;i++){
        int minPoint=INT_MAX;
        for(int j=1;j<=k;j++){
            if(i-j>=0){
                int point=abs(arr[i-j]-arr[i])+dp[i-j];
                minPoint=min(minPoint,point);
            }
        }
        dp[i]=minPoint;
    }
    return dp[n-1];
}

//House Robber
//Don't steal from adjacent houses, maximise profit
int robHouse(vector<int> &arr,int idx){
    if(idx==0) return arr[idx];
    if(idx<0) return 0;
    int pick=arr[idx]+robHouse(arr,idx-2);
    int notPick=0+robHouse(arr,idx-1);
    return max(pick,notPick);
}
int houseRobber_brute(vector<int> arr){
    int n=arr.size();
    int ans=robHouse(arr,n-1);
    return ans;
}
//The code runs exponentially, since for every element we have two choices
//Space is used by recursion stack
//Time Complexity will be pow(2,n)
//Space Complexity will be O(n)

//Memoization
int robHouse_memo(vector<int> &arr,vector<int> &dp,int idx){
    if(idx<0) return 0;
    if(dp[idx]!=-1) return dp[idx];
    if(idx==0) return arr[idx];
    int pick=arr[idx]+robHouse_memo(arr,dp,idx-2);
    int notPick=0+robHouse_memo(arr,dp,idx-1);
    dp[idx]=max(pick,notPick);
    return dp[idx];
}
int houseRobber_memoization(vector<int> arr){
    int n=arr.size();
    vector<int> dp(n,-1);
    int ans=robHouse_memo(arr,dp,n-1);
    return ans;
}
//The code runs to fill all the dp states 
//Space is used by the dp array and by recursion stack
//Time Complexity will be O(n) 
//Space Complexity will be O(2n)

//Tabulation Method
int houseRobber_tabulation(vector<int> arr){
    int n=arr.size();
    vector<int> dp(n,-1);
    dp[0]=arr[0];
    int neg=0;
    for(int i=1;i<n;i++){
        int pick=arr[i]+(i-2>=0? dp[i-2]:neg);
        int notPick=0+dp[i-1];
        dp[i]=max(pick,notPick);
    }
    return dp[n-1];
}
//There is one for loop that runs n time
//Space is used by the dp table
//Time Complexity will be O(n)
//Space Complexity will be O(n)

//Space Optimisation
int houseRobber(vector<int> arr){
    int n=arr.size();
    int prev=arr[0];
    int last=0;
    int curr;
    for(int i=1;i<n;i++){
        int pick=arr[i]+last;
        int notPick=0+prev;
        curr=max(pick,notPick);
        last=prev;
        prev=curr;
    }
    return curr;
}
//The code runs for a for loop taking n time
//No extra space is occupied
//Time Complexity will be O(n)
//Space Complexity will be O(1)


//House Robber II
//This time the array is circular so first and last elements are also adjacent
//We can solve this by calling the robberI function first by excluding 0th element and then by excluding (n-1)th element
//Then we can take maximum of both
int houseRobberII(vector<int> &arr){
    int n=arr.size();

    //If the array has a single element we can just return that
    if(n==1) return arr[0];

    //If the array has two elements, we can return the max of them
    if(n==2) return max(arr[0],arr[1]);

    //Let's create two arrays
    vector<int> arr1(n-1);
    for(int i=0;i<n-1;i++) arr1[i]=arr[i+1];

    vector<int> arr2=arr;
    arr2.pop_back();

    int a=houseRobber(arr1);
    int b=houseRobber(arr2);
    return max(a,b);
}
//The code uses houseRobberI function two times 
//The code also has a for loop
//Space is occupied by the two temp array
//Time Complexity will be O(3n)
//Space Complexity will be O(2n)


int main(){
    return 0;
}
